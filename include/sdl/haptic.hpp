#pragma once

#include <cstdint>
#include <expected>
#include <string>

#include <SDL_haptic.h>

#include <sdl/error.hpp>
#include <sdl/joystick.hpp>

namespace sdl
{
// Haptic effects
using haptic_effect = SDL_HapticEffect;
using haptic_constant = SDL_HapticConstant;
using haptic_periodic = SDL_HapticPeriodic;
using haptic_condition = SDL_HapticCondition;
using haptic_ramp = SDL_HapticRamp;
using haptic_left_right = SDL_HapticLeftRight;
using haptic_custom = SDL_HapticCustom;
using haptic_direction = SDL_HapticDirection;

// Haptic effect types
constexpr std::uint16_t haptic_constant_effect     = SDL_HAPTIC_CONSTANT;
constexpr std::uint16_t haptic_sine                = SDL_HAPTIC_SINE;
constexpr std::uint16_t haptic_left_right_effect   = SDL_HAPTIC_LEFTRIGHT;
constexpr std::uint16_t haptic_triangle            = SDL_HAPTIC_TRIANGLE;
constexpr std::uint16_t haptic_sawtooth_up         = SDL_HAPTIC_SAWTOOTHUP;
constexpr std::uint16_t haptic_sawtooth_down       = SDL_HAPTIC_SAWTOOTHDOWN;
constexpr std::uint16_t haptic_ramp_effect         = SDL_HAPTIC_RAMP;
constexpr std::uint16_t haptic_spring              = SDL_HAPTIC_SPRING;
constexpr std::uint16_t haptic_damper              = SDL_HAPTIC_DAMPER;
constexpr std::uint16_t haptic_inertia             = SDL_HAPTIC_INERTIA;
constexpr std::uint16_t haptic_friction            = SDL_HAPTIC_FRICTION;
constexpr std::uint16_t haptic_custom_effect       = SDL_HAPTIC_CUSTOM;
constexpr std::uint16_t haptic_gain                = SDL_HAPTIC_GAIN;
constexpr std::uint16_t haptic_autocenter          = SDL_HAPTIC_AUTOCENTER;
constexpr std::uint16_t haptic_status              = SDL_HAPTIC_STATUS;
constexpr std::uint16_t haptic_pause               = SDL_HAPTIC_PAUSE;

// Direction encodings
constexpr std::uint8_t haptic_polar                = SDL_HAPTIC_POLAR;
constexpr std::uint8_t haptic_cartesian            = SDL_HAPTIC_CARTESIAN;
constexpr std::uint8_t haptic_spherical            = SDL_HAPTIC_SPHERICAL;
constexpr std::uint8_t haptic_steering_axis        = SDL_HAPTIC_STEERING_AXIS;

// Special values
constexpr std::uint32_t haptic_infinity            = SDL_HAPTIC_INFINITY;

using native_haptic = SDL_Haptic;

// Haptic device functions
[[nodiscard]]
inline std::int32_t num_haptics()
{
  return SDL_NumHaptics();
}

[[nodiscard]]
inline std::string haptic_name(const std::int32_t device_index)
{
  const auto result = SDL_HapticName(device_index);
  return result ? result : "";
}

[[nodiscard]]
inline std::expected<native_haptic*, std::string> haptic_open(const std::int32_t device_index)
{
  const auto result = SDL_HapticOpen(device_index);
  if (!result)
    return std::unexpected(get_error());
  return result;
}

[[nodiscard]]
inline bool haptic_opened(const std::int32_t device_index)
{
  return SDL_HapticOpened(device_index) != 0;
}

[[nodiscard]]
inline std::int32_t haptic_index(native_haptic* haptic)
{
  return SDL_HapticIndex(haptic);
}

[[nodiscard]]
inline bool mouse_is_haptic()
{
  return SDL_MouseIsHaptic() == SDL_TRUE;
}

[[nodiscard]]
inline std::expected<native_haptic*, std::string> haptic_open_from_mouse()
{
  const auto result = SDL_HapticOpenFromMouse();
  if (!result)
    return std::unexpected(get_error());
  return result;
}

[[nodiscard]]
inline bool joystick_is_haptic(native_joystick* joystick)
{
  const auto result = SDL_JoystickIsHaptic(joystick);
  if (result < 0)
    return false;
  return result == SDL_TRUE;
}

[[nodiscard]]
inline std::expected<native_haptic*, std::string> haptic_open_from_joystick(native_joystick* joystick)
{
  const auto result = SDL_HapticOpenFromJoystick(joystick);
  if (!result)
    return std::unexpected(get_error());
  return result;
}

inline void haptic_close(native_haptic* haptic)
{
  SDL_HapticClose(haptic);
}

// Haptic capabilities
[[nodiscard]]
inline std::int32_t haptic_num_effects(native_haptic* haptic)
{
  return SDL_HapticNumEffects(haptic);
}

[[nodiscard]]
inline std::int32_t haptic_num_effects_playing(native_haptic* haptic)
{
  return SDL_HapticNumEffectsPlaying(haptic);
}

[[nodiscard]]
inline std::uint32_t haptic_query(native_haptic* haptic)
{
  return SDL_HapticQuery(haptic);
}

[[nodiscard]]
inline std::int32_t haptic_num_axes(native_haptic* haptic)
{
  return SDL_HapticNumAxes(haptic);
}

[[nodiscard]]
inline std::expected<bool, std::string> haptic_effect_supported(native_haptic* haptic, const haptic_effect* effect)
{
  const auto result = SDL_HapticEffectSupported(haptic, effect);
  if (result < 0)
    return std::unexpected(get_error());
  return result == SDL_TRUE;
}

// Haptic effects management
[[nodiscard]]
inline std::expected<std::int32_t, std::string> haptic_new_effect(native_haptic* haptic, const haptic_effect* effect)
{
  const auto result = SDL_HapticNewEffect(haptic, effect);
  if (result < 0)
    return std::unexpected(get_error());
  return result;
}

inline std::expected<void, std::string> haptic_update_effect(native_haptic* haptic, const std::int32_t effect, const haptic_effect* data)
{
  if (SDL_HapticUpdateEffect(haptic, effect, data) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> haptic_run_effect(native_haptic* haptic, const std::int32_t effect, const std::uint32_t iterations)
{
  if (SDL_HapticRunEffect(haptic, effect, iterations) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> haptic_stop_effect(native_haptic* haptic, const std::int32_t effect)
{
  if (SDL_HapticStopEffect(haptic, effect) < 0)
    return std::unexpected(get_error());
  return {};
}

inline void haptic_destroy_effect(native_haptic* haptic, const std::int32_t effect)
{
  SDL_HapticDestroyEffect(haptic, effect);
}

[[nodiscard]]
inline std::expected<bool, std::string> haptic_get_effect_status(native_haptic* haptic, const std::int32_t effect)
{
  const auto result = SDL_HapticGetEffectStatus(haptic, effect);
  if (result < 0)
    return std::unexpected(get_error());
  return result != 0;
}

// Haptic global settings
inline std::expected<void, std::string> haptic_set_gain(native_haptic* haptic, const std::int32_t gain)
{
  if (SDL_HapticSetGain(haptic, gain) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> haptic_set_autocenter(native_haptic* haptic, const std::int32_t autocenter)
{
  if (SDL_HapticSetAutocenter(haptic, autocenter) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> haptic_pause(native_haptic* haptic)
{
  if (SDL_HapticPause(haptic) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> haptic_unpause(native_haptic* haptic)
{
  if (SDL_HapticUnpause(haptic) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> haptic_stop_all(native_haptic* haptic)
{
  if (SDL_HapticStopAll(haptic) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline std::expected<bool, std::string> haptic_rumble_supported(native_haptic* haptic)
{
  const auto result = SDL_HapticRumbleSupported(haptic);
  if (result < 0)
    return std::unexpected(get_error());
  return result == SDL_TRUE;
}

inline std::expected<void, std::string> haptic_rumble_init(native_haptic* haptic)
{
  if (SDL_HapticRumbleInit(haptic) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> haptic_rumble_play(native_haptic* haptic, const float strength, const std::uint32_t length)
{
  if (SDL_HapticRumblePlay(haptic, strength, length) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> haptic_rumble_stop(native_haptic* haptic)
{
  if (SDL_HapticRumbleStop(haptic) < 0)
    return std::unexpected(get_error());
  return {};
}

// Conveniences

class haptic
{
public:
  haptic() = default;
  
  explicit haptic(native_haptic* native, const bool managed = true)
  : native_(native), managed_(managed)
  {
  }

  haptic(const haptic&  that) = delete;
  haptic(      haptic&& temp) noexcept
  : native_(temp.native_), managed_(temp.managed_)
  {
    temp.native_  = nullptr;
    temp.managed_ = false;
  }
  
  ~haptic()
  {
    if (native_ && managed_)
      SDL_HapticClose(native_);
  }
  
  haptic& operator=(const haptic&  that) = delete;
  haptic& operator=(      haptic&& temp) noexcept
  {
    if (this != &temp)
    {
      if (native_ && managed_)
        SDL_HapticClose(native_);
      native_       = temp.native_;
      managed_      = temp.managed_;
      temp.native_  = nullptr;
      temp.managed_ = false;
    }
    return *this;
  }

  [[nodiscard]]
  native_haptic* native() const noexcept
  {
    return native_;
  }

  [[nodiscard]]
  bool is_managed() const noexcept
  {
    return managed_;
  }

  // Convenience methods
  [[nodiscard]]
  std::int32_t index() const
  {
    return haptic_index(native_);
  }

  [[nodiscard]]
  std::int32_t num_effects() const
  {
    return haptic_num_effects(native_);
  }

  [[nodiscard]]
  std::int32_t num_effects_playing() const
  {
    return haptic_num_effects_playing(native_);
  }

  [[nodiscard]]
  std::uint32_t query() const
  {
    return haptic_query(native_);
  }

  [[nodiscard]]
  std::int32_t num_axes() const
  {
    return haptic_num_axes(native_);
  }

  [[nodiscard]]
  std::expected<bool, std::string> effect_supported(const haptic_effect* effect) const
  {
    return haptic_effect_supported(native_, effect);
  }

  [[nodiscard]]
  std::expected<std::int32_t, std::string> new_effect(const haptic_effect* effect) const
  {
    return haptic_new_effect(native_, effect);
  }

  std::expected<void, std::string> update_effect(const std::int32_t effect, const haptic_effect* data) const
  {
    return haptic_update_effect(native_, effect, data);
  }

  std::expected<void, std::string> run_effect(const std::int32_t effect, const std::uint32_t iterations) const
  {
    return haptic_run_effect(native_, effect, iterations);
  }

  std::expected<void, std::string> stop_effect(const std::int32_t effect) const
  {
    return haptic_stop_effect(native_, effect);
  }

  void destroy_effect(const std::int32_t effect) const
  {
    haptic_destroy_effect(native_, effect);
  }

  [[nodiscard]]
  std::expected<bool, std::string> get_effect_status(const std::int32_t effect) const
  {
    return haptic_get_effect_status(native_, effect);
  }

  std::expected<void, std::string> set_gain(const std::int32_t gain) const
  {
    return haptic_set_gain(native_, gain);
  }

  std::expected<void, std::string> set_autocenter(const std::int32_t autocenter) const
  {
    return haptic_set_autocenter(native_, autocenter);
  }

  std::expected<void, std::string> pause() const
  {
    return haptic_pause(native_);
  }

  std::expected<void, std::string> unpause() const
  {
    return haptic_unpause(native_);
  }

  std::expected<void, std::string> stop_all() const
  {
    return haptic_stop_all(native_);
  }

  std::expected<void, std::string> rumble_init() const
  {
    return haptic_rumble_init(native_);
  }

  std::expected<void, std::string> rumble_play(const float strength, const std::uint32_t length) const
  {
    return haptic_rumble_play(native_, strength, length);
  }

  std::expected<void, std::string> rumble_stop() const
  {
    return haptic_rumble_stop(native_);
  }

private:
  native_haptic* native_  {};
  bool           managed_ {true};
};
}
