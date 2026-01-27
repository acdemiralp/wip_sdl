#pragma once

#include <array>
#include <cstdint>
#include <expected>
#include <string>

#include <SDL_joystick.h>

#include <sdl/error.hpp>
#include <sdl/guid.hpp>

namespace sdl
{
// Joystick types
enum class joystick_type
{
  unknown           = SDL_JOYSTICK_TYPE_UNKNOWN,
  gamecontroller    = SDL_JOYSTICK_TYPE_GAMECONTROLLER,
  wheel             = SDL_JOYSTICK_TYPE_WHEEL,
  arcade_stick      = SDL_JOYSTICK_TYPE_ARCADE_STICK,
  flight_stick      = SDL_JOYSTICK_TYPE_FLIGHT_STICK,
  dance_pad         = SDL_JOYSTICK_TYPE_DANCE_PAD,
  guitar            = SDL_JOYSTICK_TYPE_GUITAR,
  drum_kit          = SDL_JOYSTICK_TYPE_DRUM_KIT,
  arcade_pad        = SDL_JOYSTICK_TYPE_ARCADE_PAD,
  throttle          = SDL_JOYSTICK_TYPE_THROTTLE
};

// Joystick power level
enum class joystick_power_level
{
  unknown  = SDL_JOYSTICK_POWER_UNKNOWN,
  empty    = SDL_JOYSTICK_POWER_EMPTY,
  low      = SDL_JOYSTICK_POWER_LOW,
  medium   = SDL_JOYSTICK_POWER_MEDIUM,
  full     = SDL_JOYSTICK_POWER_FULL,
  wired    = SDL_JOYSTICK_POWER_WIRED,
  max      = SDL_JOYSTICK_POWER_MAX
};

using native_joystick    = SDL_Joystick;
using native_joystick_id = SDL_JoystickID;

// Joystick locking
inline void lock_joysticks()
{
  SDL_LockJoysticks();
}

inline void unlock_joysticks()
{
  SDL_UnlockJoysticks();
}

// Joystick enumeration
[[nodiscard]]
inline std::int32_t num_joysticks()
{
  return SDL_NumJoysticks();
}

[[nodiscard]]
inline std::string joystick_name_for_index(const std::int32_t device_index)
{
  const auto result = SDL_JoystickNameForIndex(device_index);
  return result ? result : "";
}

[[nodiscard]]
inline std::string joystick_path_for_index(const std::int32_t device_index)
{
  const auto result = SDL_JoystickPathForIndex(device_index);
  return result ? result : "";
}

[[nodiscard]]
inline std::int32_t joystick_get_device_player_index(const std::int32_t device_index)
{
  return SDL_JoystickGetDevicePlayerIndex(device_index);
}

[[nodiscard]]
inline guid joystick_get_device_guid(const std::int32_t device_index)
{
  return SDL_JoystickGetDeviceGUID(device_index);
}

[[nodiscard]]
inline std::uint16_t joystick_get_device_vendor(const std::int32_t device_index)
{
  return SDL_JoystickGetDeviceVendor(device_index);
}

[[nodiscard]]
inline std::uint16_t joystick_get_device_product(const std::int32_t device_index)
{
  return SDL_JoystickGetDeviceProduct(device_index);
}

[[nodiscard]]
inline std::uint16_t joystick_get_device_product_version(const std::int32_t device_index)
{
  return SDL_JoystickGetDeviceProductVersion(device_index);
}

[[nodiscard]]
inline joystick_type joystick_get_device_type(const std::int32_t device_index)
{
  return static_cast<joystick_type>(SDL_JoystickGetDeviceType(device_index));
}

[[nodiscard]]
inline native_joystick_id joystick_get_device_instance_id(const std::int32_t device_index)
{
  return SDL_JoystickGetDeviceInstanceID(device_index);
}

// Joystick opening/closing
[[nodiscard]]
inline std::expected<native_joystick*, std::string> joystick_open(const std::int32_t device_index)
{
  const auto result = SDL_JoystickOpen(device_index);
  if (!result)
    return std::unexpected(get_error());
  return result;
}

[[nodiscard]]
inline native_joystick* joystick_from_instance_id(const native_joystick_id instance_id)
{
  return SDL_JoystickFromInstanceID(instance_id);
}

[[nodiscard]]
inline native_joystick* joystick_from_player_index(const std::int32_t player_index)
{
  return SDL_JoystickFromPlayerIndex(player_index);
}

inline void joystick_close(native_joystick* joystick)
{
  SDL_JoystickClose(joystick);
}

// Joystick information
[[nodiscard]]
inline std::string joystick_name(native_joystick* joystick)
{
  const auto result = SDL_JoystickName(joystick);
  return result ? result : "";
}

[[nodiscard]]
inline std::string joystick_path(native_joystick* joystick)
{
  const auto result = SDL_JoystickPath(joystick);
  return result ? result : "";
}

[[nodiscard]]
inline std::int32_t joystick_get_player_index(native_joystick* joystick)
{
  return SDL_JoystickGetPlayerIndex(joystick);
}

inline void joystick_set_player_index(native_joystick* joystick, const std::int32_t player_index)
{
  SDL_JoystickSetPlayerIndex(joystick, player_index);
}

[[nodiscard]]
inline guid joystick_get_guid(native_joystick* joystick)
{
  return SDL_JoystickGetGUID(joystick);
}

[[nodiscard]]
inline std::uint16_t joystick_get_vendor(native_joystick* joystick)
{
  return SDL_JoystickGetVendor(joystick);
}

[[nodiscard]]
inline std::uint16_t joystick_get_product(native_joystick* joystick)
{
  return SDL_JoystickGetProduct(joystick);
}

[[nodiscard]]
inline std::uint16_t joystick_get_product_version(native_joystick* joystick)
{
  return SDL_JoystickGetProductVersion(joystick);
}

[[nodiscard]]
inline std::uint16_t joystick_get_firmware_version(native_joystick* joystick)
{
  return SDL_JoystickGetFirmwareVersion(joystick);
}

[[nodiscard]]
inline std::string joystick_get_serial(native_joystick* joystick)
{
  const auto result = SDL_JoystickGetSerial(joystick);
  return result ? result : "";
}

[[nodiscard]]
inline joystick_type joystick_get_type(native_joystick* joystick)
{
  return static_cast<joystick_type>(SDL_JoystickGetType(joystick));
}

[[nodiscard]]
inline bool joystick_get_attached(native_joystick* joystick)
{
  return SDL_JoystickGetAttached(joystick) == SDL_TRUE;
}

[[nodiscard]]
inline native_joystick_id joystick_instance_id(native_joystick* joystick)
{
  return SDL_JoystickInstanceID(joystick);
}

// Joystick capabilities
[[nodiscard]]
inline std::int32_t joystick_num_axes(native_joystick* joystick)
{
  return SDL_JoystickNumAxes(joystick);
}

[[nodiscard]]
inline std::int32_t joystick_num_balls(native_joystick* joystick)
{
  return SDL_JoystickNumBalls(joystick);
}

[[nodiscard]]
inline std::int32_t joystick_num_hats(native_joystick* joystick)
{
  return SDL_JoystickNumHats(joystick);
}

[[nodiscard]]
inline std::int32_t joystick_num_buttons(native_joystick* joystick)
{
  return SDL_JoystickNumButtons(joystick);
}

// Joystick state
inline void joystick_update()
{
  SDL_JoystickUpdate();
}

[[nodiscard]]
inline std::int16_t joystick_get_axis(native_joystick* joystick, const std::int32_t axis)
{
  return SDL_JoystickGetAxis(joystick, axis);
}

[[nodiscard]]
inline std::expected<std::int16_t, std::string> joystick_get_axis_initial_state(native_joystick* joystick, const std::int32_t axis)
{
  std::int16_t state;
  if (!SDL_JoystickGetAxisInitialState(joystick, axis, &state))
    return std::unexpected(get_error());
  return state;
}

[[nodiscard]]
inline std::uint8_t joystick_get_hat(native_joystick* joystick, const std::int32_t hat)
{
  return SDL_JoystickGetHat(joystick, hat);
}

[[nodiscard]]
inline std::expected<std::array<std::int32_t, 2>, std::string> joystick_get_ball(native_joystick* joystick, const std::int32_t ball)
{
  std::array<std::int32_t, 2> delta;
  if (SDL_JoystickGetBall(joystick, ball, &delta[0], &delta[1]) < 0)
    return std::unexpected(get_error());
  return delta;
}

[[nodiscard]]
inline std::uint8_t joystick_get_button(native_joystick* joystick, const std::int32_t button)
{
  return SDL_JoystickGetButton(joystick, button);
}

// Joystick rumble
inline std::expected<void, std::string> joystick_rumble(
  native_joystick*      joystick,
  const std::uint16_t   low_frequency_rumble,
  const std::uint16_t   high_frequency_rumble,
  const std::uint32_t   duration_ms)
{
  if (SDL_JoystickRumble(joystick, low_frequency_rumble, high_frequency_rumble, duration_ms) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> joystick_rumble_triggers(
  native_joystick*      joystick,
  const std::uint16_t   left_rumble,
  const std::uint16_t   right_rumble,
  const std::uint32_t   duration_ms)
{
  if (SDL_JoystickRumbleTriggers(joystick, left_rumble, right_rumble, duration_ms) < 0)
    return std::unexpected(get_error());
  return {};
}

// Joystick LED
inline std::expected<void, std::string> joystick_set_led(
  native_joystick*    joystick,
  const std::uint8_t  red,
  const std::uint8_t  green,
  const std::uint8_t  blue)
{
  if (SDL_JoystickSetLED(joystick, red, green, blue) < 0)
    return std::unexpected(get_error());
  return {};
}

// Joystick sensors
inline std::expected<void, std::string> joystick_send_effect(
  native_joystick*  joystick,
  const void*       data,
  const std::int32_t size)
{
  if (SDL_JoystickSendEffect(joystick, data, size) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline bool joystick_has_led(native_joystick* joystick)
{
  return SDL_JoystickHasLED(joystick) == SDL_TRUE;
}

[[nodiscard]]
inline bool joystick_has_rumble(native_joystick* joystick)
{
  return SDL_JoystickHasRumble(joystick) == SDL_TRUE;
}

[[nodiscard]]
inline bool joystick_has_rumble_triggers(native_joystick* joystick)
{
  return SDL_JoystickHasRumbleTriggers(joystick) == SDL_TRUE;
}

// Joystick power
[[nodiscard]]
inline joystick_power_level joystick_current_power_level(native_joystick* joystick)
{
  return static_cast<joystick_power_level>(SDL_JoystickCurrentPowerLevel(joystick));
}

// Event state
inline void joystick_event_state(const std::int32_t state)
{
  SDL_JoystickEventState(state);
}

// Conveniences

class joystick
{
public:
  joystick() = default;
  
  explicit joystick(native_joystick* native, const bool managed = true)
  : native_(native), managed_(managed)
  {
  }

  joystick(const joystick&  that) = delete;
  joystick(      joystick&& temp) noexcept
  : native_(temp.native_), managed_(temp.managed_)
  {
    temp.native_  = nullptr;
    temp.managed_ = false;
  }
  
  ~joystick()
  {
    if (native_ && managed_)
      SDL_JoystickClose(native_);
  }
  
  joystick& operator=(const joystick&  that) = delete;
  joystick& operator=(      joystick&& temp) noexcept
  {
    if (this != &temp)
    {
      if (native_ && managed_)
        SDL_JoystickClose(native_);
      native_       = temp.native_;
      managed_      = temp.managed_;
      temp.native_  = nullptr;
      temp.managed_ = false;
    }
    return *this;
  }

  [[nodiscard]]
  native_joystick* native() const noexcept
  {
    return native_;
  }

  [[nodiscard]]
  bool is_managed() const noexcept
  {
    return managed_;
  }

private:
  native_joystick* native_  {};
  bool             managed_ {true};
};
}
