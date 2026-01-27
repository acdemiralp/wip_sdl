#pragma once

#include <cstdint>
#include <expected>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include <SDL_audio.h>

#include <sdl/error.hpp>
#include <sdl/rwops.hpp>

namespace sdl
{
// Audio format definitions
using audio_format = SDL_AudioFormat;

constexpr audio_format audio_u8     = AUDIO_U8;
constexpr audio_format audio_s8     = AUDIO_S8;
constexpr audio_format audio_u16lsb = AUDIO_U16LSB;
constexpr audio_format audio_s16lsb = AUDIO_S16LSB;
constexpr audio_format audio_u16msb = AUDIO_U16MSB;
constexpr audio_format audio_s16msb = AUDIO_S16MSB;
constexpr audio_format audio_u16    = AUDIO_U16;
constexpr audio_format audio_s16    = AUDIO_S16;
constexpr audio_format audio_s32lsb = AUDIO_S32LSB;
constexpr audio_format audio_s32msb = AUDIO_S32MSB;
constexpr audio_format audio_s32    = AUDIO_S32;
constexpr audio_format audio_f32lsb = AUDIO_F32LSB;
constexpr audio_format audio_f32msb = AUDIO_F32MSB;
constexpr audio_format audio_f32    = AUDIO_F32;

// Audio status
enum class audio_status
{
  stopped = SDL_AUDIO_STOPPED,
  playing = SDL_AUDIO_PLAYING,
  paused  = SDL_AUDIO_PAUSED
};

// Audio allow flags
enum class audio_allow_flags : std::uint32_t
{
  frequency_change = SDL_AUDIO_ALLOW_FREQUENCY_CHANGE,
  format_change    = SDL_AUDIO_ALLOW_FORMAT_CHANGE,
  channels_change  = SDL_AUDIO_ALLOW_CHANNELS_CHANGE,
  samples_change   = SDL_AUDIO_ALLOW_SAMPLES_CHANGE,
  any_change       = SDL_AUDIO_ALLOW_ANY_CHANGE
};

// Audio spec
struct audio_spec
{
  [[nodiscard]]
  SDL_AudioSpec native() const
  {
    return SDL_AudioSpec{
      freq,
      format,
      channels,
      silence,
      samples,
      padding,
      size,
      callback,
      userdata
    };
  }

  [[nodiscard]]
  static audio_spec from_native(const SDL_AudioSpec& native)
  {
    audio_spec result;
    result.freq      = native.freq;
    result.format    = native.format;
    result.channels  = native.channels;
    result.silence   = native.silence;
    result.samples   = native.samples;
    result.padding   = native.padding;
    result.size      = native.size;
    result.callback  = native.callback;
    result.userdata  = native.userdata;
    return result;
  }

  std::int32_t       freq      {}; // DSP frequency
  audio_format       format    {}; // Audio data format
  std::uint8_t       channels  {}; // Number of channels: 1 mono, 2 stereo
  std::uint8_t       silence   {}; // Audio buffer silence value (calculated)
  std::uint16_t      samples   {}; // Audio buffer size in sample FRAMES (total samples divided by channel count)
  std::uint16_t      padding   {}; // Necessary for some compile environments
  std::uint32_t      size      {}; // Audio buffer size in bytes (calculated)
  SDL_AudioCallback  callback  {}; // Callback that feeds the audio device
  void*              userdata  {}; // Userdata passed to callback
};

using audio_callback = void (*)(void*, std::uint8_t*, int);
using audio_filter   = void (*)(SDL_AudioCVT*, audio_format);

using native_audio_device_id = SDL_AudioDeviceID;
using native_audio_stream    = SDL_AudioStream;

// Audio driver functions
[[nodiscard]]
inline std::int32_t get_num_audio_drivers()
{
  return SDL_GetNumAudioDrivers();
}

[[nodiscard]]
inline std::string get_audio_driver(const std::int32_t index)
{
  const auto result = SDL_GetAudioDriver(index);
  return result ? result : "";
}

[[nodiscard]]
inline std::string get_current_audio_driver()
{
  const auto result = SDL_GetCurrentAudioDriver();
  return result ? result : "";
}

// Audio device functions
[[nodiscard]]
inline std::int32_t get_num_audio_devices(const bool is_capture)
{
  return SDL_GetNumAudioDevices(is_capture ? 1 : 0);
}

[[nodiscard]]
inline std::string get_audio_device_name(const std::int32_t index, const bool is_capture)
{
  const auto result = SDL_GetAudioDeviceName(index, is_capture ? 1 : 0);
  return result ? result : "";
}

[[nodiscard]]
inline std::expected<audio_spec, std::string> get_audio_device_spec(const std::int32_t index, const bool is_capture)
{
  SDL_AudioSpec spec;
  if (SDL_GetAudioDeviceSpec(index, is_capture ? 1 : 0, &spec) < 0)
    return std::unexpected(get_error());
  return audio_spec::from_native(spec);
}

[[nodiscard]]
inline std::string get_default_audio_info(std::string* name, audio_spec* spec, const bool is_capture)
{
  char* device_name = nullptr;
  SDL_AudioSpec native_spec;
  const auto result = SDL_GetDefaultAudioInfo(&device_name, &native_spec, is_capture ? 1 : 0);
  
  if (name && device_name)
    *name = device_name;
  if (spec)
    *spec = audio_spec::from_native(native_spec);
  
  SDL_free(device_name);
  
  return result < 0 ? get_error() : "";
}

// Open/close audio device
[[nodiscard]]
inline std::expected<native_audio_device_id, std::string> open_audio_device(
  const std::string* device,
  const bool         is_capture,
  const audio_spec&  desired,
  audio_spec*        obtained,
  const std::int32_t allowed_changes)
{
  SDL_AudioSpec native_desired = desired.native();
  SDL_AudioSpec native_obtained;
  const auto result = SDL_OpenAudioDevice(
    device ? device->c_str() : nullptr,
    is_capture ? 1 : 0,
    &native_desired,
    obtained ? &native_obtained : nullptr,
    allowed_changes);
  
  if (result == 0)
    return std::unexpected(get_error());
  
  if (obtained)
    *obtained = audio_spec::from_native(native_obtained);
  
  return result;
}

[[nodiscard]]
inline audio_status get_audio_device_status(const native_audio_device_id device)
{
  return static_cast<audio_status>(SDL_GetAudioDeviceStatus(device));
}

inline void pause_audio_device(const native_audio_device_id device, const bool pause_on)
{
  SDL_PauseAudioDevice(device, pause_on ? 1 : 0);
}

inline void close_audio_device(const native_audio_device_id device)
{
  SDL_CloseAudioDevice(device);
}

// Audio loading/freeing
struct audio_wav_data
{
  audio_spec     spec   {};
  std::uint8_t*  buffer {};
  std::uint32_t  length {};
};

[[nodiscard]]
inline std::expected<audio_wav_data, std::string> load_wav_rw(SDL_RWops* src, const bool free_src)
{
  audio_wav_data result;
  SDL_AudioSpec  native_spec;
  
  if (!SDL_LoadWAV_RW(src, free_src ? 1 : 0, &native_spec, &result.buffer, &result.length))
    return std::unexpected(get_error());
  
  result.spec = audio_spec::from_native(native_spec);
  return result;
}

[[nodiscard]]
inline std::expected<audio_wav_data, std::string> load_wav(const std::string& file)
{
  return load_wav_rw(SDL_RWFromFile(file.c_str(), "rb"), true);
}

inline void free_wav(std::uint8_t* audio_buf)
{
  SDL_FreeWAV(audio_buf);
}

// Audio conversion
struct audio_cvt
{
  [[nodiscard]]
  SDL_AudioCVT& native()
  {
    return native_;
  }
  
  [[nodiscard]]
  const SDL_AudioCVT& native() const
  {
    return native_;
  }

private:
  SDL_AudioCVT native_ {};
};

inline std::expected<void, std::string> build_audio_cvt(
  audio_cvt&           cvt,
  const audio_format   src_format,
  const std::uint8_t   src_channels,
  const std::int32_t   src_rate,
  const audio_format   dst_format,
  const std::uint8_t   dst_channels,
  const std::int32_t   dst_rate)
{
  if (SDL_BuildAudioCVT(&cvt.native(), src_format, src_channels, src_rate, dst_format, dst_channels, dst_rate) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> convert_audio(audio_cvt& cvt)
{
  if (SDL_ConvertAudio(&cvt.native()) < 0)
    return std::unexpected(get_error());
  return {};
}

// Audio stream
[[nodiscard]]
inline std::expected<native_audio_stream*, std::string> new_audio_stream(
  const audio_format  src_format,
  const std::uint8_t  src_channels,
  const std::int32_t  src_rate,
  const audio_format  dst_format,
  const std::uint8_t  dst_channels,
  const std::int32_t  dst_rate)
{
  const auto result = SDL_NewAudioStream(src_format, src_channels, src_rate, dst_format, dst_channels, dst_rate);
  if (!result)
    return std::unexpected(get_error());
  return result;
}

inline std::expected<void, std::string> audio_stream_put(native_audio_stream* stream, const void* buf, const std::int32_t len)
{
  if (SDL_AudioStreamPut(stream, buf, len) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline std::int32_t audio_stream_get(native_audio_stream* stream, void* buf, const std::int32_t len)
{
  return SDL_AudioStreamGet(stream, buf, len);
}

[[nodiscard]]
inline std::int32_t audio_stream_available(native_audio_stream* stream)
{
  return SDL_AudioStreamAvailable(stream);
}

inline std::expected<void, std::string> audio_stream_flush(native_audio_stream* stream)
{
  if (SDL_AudioStreamFlush(stream) < 0)
    return std::unexpected(get_error());
  return {};
}

inline void audio_stream_clear(native_audio_stream* stream)
{
  SDL_AudioStreamClear(stream);
}

inline void free_audio_stream(native_audio_stream* stream)
{
  SDL_FreeAudioStream(stream);
}

// Audio mixing
inline void mix_audio(std::uint8_t* dst, const std::uint8_t* src, const std::uint32_t len, const std::int32_t volume)
{
  SDL_MixAudio(dst, src, len, volume);
}

inline void mix_audio_format(std::uint8_t* dst, const std::uint8_t* src, const audio_format format, const std::uint32_t len, const std::int32_t volume)
{
  SDL_MixAudioFormat(dst, src, format, len, volume);
}

// Audio queue
inline std::expected<void, std::string> queue_audio(const native_audio_device_id device, const void* data, const std::uint32_t len)
{
  if (SDL_QueueAudio(device, data, len) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline std::uint32_t dequeue_audio(const native_audio_device_id device, void* data, const std::uint32_t len)
{
  return SDL_DequeueAudio(device, data, len);
}

[[nodiscard]]
inline std::uint32_t get_queued_audio_size(const native_audio_device_id device)
{
  return SDL_GetQueuedAudioSize(device);
}

inline void clear_queued_audio(const native_audio_device_id device)
{
  SDL_ClearQueuedAudio(device);
}

// Audio locking
inline void lock_audio_device(const native_audio_device_id device)
{
  SDL_LockAudioDevice(device);
}

inline void unlock_audio_device(const native_audio_device_id device)
{
  SDL_UnlockAudioDevice(device);
}

// Conveniences

class audio_device
{
public:
  audio_device() = default;
  
  explicit audio_device(const native_audio_device_id native)
  : native_(native)
  {
  }

  audio_device(const audio_device&  that) = delete;
  audio_device(      audio_device&& temp) noexcept
  : native_(temp.native_)
  {
    temp.native_ = 0;
  }
  
  ~audio_device()
  {
    if (native_)
      SDL_CloseAudioDevice(native_);
  }
  
  audio_device& operator=(const audio_device&  that) = delete;
  audio_device& operator=(      audio_device&& temp) noexcept
  {
    if (this != &temp)
    {
      if (native_)
        SDL_CloseAudioDevice(native_);
      native_      = temp.native_;
      temp.native_ = 0;
    }
    return *this;
  }

  [[nodiscard]]
  native_audio_device_id native() const noexcept
  {
    return native_;
  }

  void pause(const bool pause_on) const
  {
    SDL_PauseAudioDevice(native_, pause_on ? 1 : 0);
  }

  [[nodiscard]]
  audio_status status() const
  {
    return static_cast<audio_status>(SDL_GetAudioDeviceStatus(native_));
  }

  void lock() const
  {
    SDL_LockAudioDevice(native_);
  }

  void unlock() const
  {
    SDL_UnlockAudioDevice(native_);
  }

private:
  native_audio_device_id native_ {};
};

class audio_stream
{
public:
  audio_stream() = default;
  
  explicit audio_stream(native_audio_stream* native)
  : native_(native)
  {
  }

  audio_stream(const audio_stream&  that) = delete;
  audio_stream(      audio_stream&& temp) noexcept
  : native_(temp.native_)
  {
    temp.native_ = nullptr;
  }
  
  ~audio_stream()
  {
    if (native_)
      SDL_FreeAudioStream(native_);
  }
  
  audio_stream& operator=(const audio_stream&  that) = delete;
  audio_stream& operator=(      audio_stream&& temp) noexcept
  {
    if (this != &temp)
    {
      if (native_)
        SDL_FreeAudioStream(native_);
      native_      = temp.native_;
      temp.native_ = nullptr;
    }
    return *this;
  }

  [[nodiscard]]
  native_audio_stream* native() const noexcept
  {
    return native_;
  }

  std::expected<void, std::string> put(const void* buf, const std::int32_t len) const
  {
    return audio_stream_put(native_, buf, len);
  }

  [[nodiscard]]
  std::int32_t get(void* buf, const std::int32_t len) const
  {
    return audio_stream_get(native_, buf, len);
  }

  [[nodiscard]]
  std::int32_t available() const
  {
    return audio_stream_available(native_);
  }

  std::expected<void, std::string> flush() const
  {
    return audio_stream_flush(native_);
  }

  void clear() const
  {
    audio_stream_clear(native_);
  }

private:
  native_audio_stream* native_ {};
};
}
