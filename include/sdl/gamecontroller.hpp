#pragma once

#include <cstdint>
#include <expected>
#include <string>

#include <SDL_gamecontroller.h>

#include <sdl/error.hpp>
#include <sdl/joystick.hpp>
#include <sdl/rwops.hpp>

namespace sdl
{
// Game controller types
enum class game_controller_type
{
  unknown           = SDL_CONTROLLER_TYPE_UNKNOWN,
  xbox360           = SDL_CONTROLLER_TYPE_XBOX360,
  xboxone           = SDL_CONTROLLER_TYPE_XBOXONE,
  ps3               = SDL_CONTROLLER_TYPE_PS3,
  ps4               = SDL_CONTROLLER_TYPE_PS4,
  nintendo_switch_pro = SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO,
  virtual_controller = SDL_CONTROLLER_TYPE_VIRTUAL,
  ps5               = SDL_CONTROLLER_TYPE_PS5,
  amazon_luna       = SDL_CONTROLLER_TYPE_AMAZON_LUNA,
  google_stadia     = SDL_CONTROLLER_TYPE_GOOGLE_STADIA,
  nvidia_shield     = SDL_CONTROLLER_TYPE_NVIDIA_SHIELD,
  nintendo_switch_joycon_left  = SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_JOYCON_LEFT,
  nintendo_switch_joycon_right = SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_JOYCON_RIGHT,
  nintendo_switch_joycon_pair  = SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_JOYCON_PAIR
};

// Game controller bind type
enum class game_controller_bind_type
{
  none   = SDL_CONTROLLER_BINDTYPE_NONE,
  button = SDL_CONTROLLER_BINDTYPE_BUTTON,
  axis   = SDL_CONTROLLER_BINDTYPE_AXIS,
  hat    = SDL_CONTROLLER_BINDTYPE_HAT
};

// Game controller axis
enum class game_controller_axis
{
  invalid       = SDL_CONTROLLER_AXIS_INVALID,
  left_x        = SDL_CONTROLLER_AXIS_LEFTX,
  left_y        = SDL_CONTROLLER_AXIS_LEFTY,
  right_x       = SDL_CONTROLLER_AXIS_RIGHTX,
  right_y       = SDL_CONTROLLER_AXIS_RIGHTY,
  trigger_left  = SDL_CONTROLLER_AXIS_TRIGGERLEFT,
  trigger_right = SDL_CONTROLLER_AXIS_TRIGGERRIGHT,
  max           = SDL_CONTROLLER_AXIS_MAX
};

// Game controller button
enum class game_controller_button
{
  invalid        = SDL_CONTROLLER_BUTTON_INVALID,
  a              = SDL_CONTROLLER_BUTTON_A,
  b              = SDL_CONTROLLER_BUTTON_B,
  x              = SDL_CONTROLLER_BUTTON_X,
  y              = SDL_CONTROLLER_BUTTON_Y,
  back           = SDL_CONTROLLER_BUTTON_BACK,
  guide          = SDL_CONTROLLER_BUTTON_GUIDE,
  start          = SDL_CONTROLLER_BUTTON_START,
  left_stick     = SDL_CONTROLLER_BUTTON_LEFTSTICK,
  right_stick    = SDL_CONTROLLER_BUTTON_RIGHTSTICK,
  left_shoulder  = SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
  right_shoulder = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
  dpad_up        = SDL_CONTROLLER_BUTTON_DPAD_UP,
  dpad_down      = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
  dpad_left      = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
  dpad_right     = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
  misc1          = SDL_CONTROLLER_BUTTON_MISC1,
  paddle1        = SDL_CONTROLLER_BUTTON_PADDLE1,
  paddle2        = SDL_CONTROLLER_BUTTON_PADDLE2,
  paddle3        = SDL_CONTROLLER_BUTTON_PADDLE3,
  paddle4        = SDL_CONTROLLER_BUTTON_PADDLE4,
  touchpad       = SDL_CONTROLLER_BUTTON_TOUCHPAD,
  max            = SDL_CONTROLLER_BUTTON_MAX
};

using native_game_controller = SDL_GameController;
using game_controller_button_bind = SDL_GameControllerButtonBind;

// Game controller mapping
inline std::expected<std::int32_t, std::string> game_controller_add_mappings_from_rw(SDL_RWops* rw, const bool free_rw)
{
  const auto result = SDL_GameControllerAddMappingsFromRW(rw, free_rw ? 1 : 0);
  if (result < 0)
    return std::unexpected(get_error());
  return result;
}

inline std::expected<std::int32_t, std::string> game_controller_add_mappings_from_file(const std::string& file)
{
  return game_controller_add_mappings_from_rw(SDL_RWFromFile(file.c_str(), "rb"), true);
}

inline std::expected<void, std::string> game_controller_add_mapping(const std::string& mapping)
{
  if (SDL_GameControllerAddMapping(mapping.c_str()) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline std::int32_t game_controller_num_mappings()
{
  return SDL_GameControllerNumMappings();
}

[[nodiscard]]
inline std::string game_controller_mapping_for_index(const std::int32_t mapping_index)
{
  const auto result = SDL_GameControllerMappingForIndex(mapping_index);
  if (!result)
    return "";
  const std::string str(result);
  SDL_free(result);
  return str;
}

[[nodiscard]]
inline std::string game_controller_mapping_for_guid(const guid& guid_value)
{
  const auto result = SDL_GameControllerMappingForGUID(guid_value);
  if (!result)
    return "";
  const std::string str(result);
  SDL_free(result);
  return str;
}

[[nodiscard]]
inline std::string game_controller_mapping(native_game_controller* game_controller)
{
  const auto result = SDL_GameControllerMapping(game_controller);
  if (!result)
    return "";
  const std::string str(result);
  SDL_free(result);
  return str;
}

// Game controller detection
[[nodiscard]]
inline bool is_game_controller(const std::int32_t joystick_index)
{
  return SDL_IsGameController(joystick_index) == SDL_TRUE;
}

[[nodiscard]]
inline std::string game_controller_name_for_index(const std::int32_t joystick_index)
{
  const auto result = SDL_GameControllerNameForIndex(joystick_index);
  return result ? result : "";
}

[[nodiscard]]
inline std::string game_controller_path_for_index(const std::int32_t joystick_index)
{
  const auto result = SDL_GameControllerPathForIndex(joystick_index);
  return result ? result : "";
}

[[nodiscard]]
inline game_controller_type game_controller_type_for_index(const std::int32_t joystick_index)
{
  return static_cast<game_controller_type>(SDL_GameControllerTypeForIndex(joystick_index));
}

[[nodiscard]]
inline std::string game_controller_mapping_for_device_index(const std::int32_t joystick_index)
{
  const auto result = SDL_GameControllerMappingForDeviceIndex(joystick_index);
  if (!result)
    return "";
  const std::string str(result);
  SDL_free(result);
  return str;
}

// Game controller opening/closing
[[nodiscard]]
inline std::expected<native_game_controller*, std::string> game_controller_open(const std::int32_t joystick_index)
{
  const auto result = SDL_GameControllerOpen(joystick_index);
  if (!result)
    return std::unexpected(get_error());
  return result;
}

[[nodiscard]]
inline native_game_controller* game_controller_from_instance_id(const native_joystick_id instance_id)
{
  return SDL_GameControllerFromInstanceID(instance_id);
}

[[nodiscard]]
inline native_game_controller* game_controller_from_player_index(const std::int32_t player_index)
{
  return SDL_GameControllerFromPlayerIndex(player_index);
}

inline void game_controller_close(native_game_controller* game_controller)
{
  SDL_GameControllerClose(game_controller);
}

// Game controller information
[[nodiscard]]
inline std::string game_controller_name(native_game_controller* game_controller)
{
  const auto result = SDL_GameControllerName(game_controller);
  return result ? result : "";
}

[[nodiscard]]
inline std::string game_controller_path(native_game_controller* game_controller)
{
  const auto result = SDL_GameControllerPath(game_controller);
  return result ? result : "";
}

[[nodiscard]]
inline game_controller_type game_controller_get_type(native_game_controller* game_controller)
{
  return static_cast<game_controller_type>(SDL_GameControllerGetType(game_controller));
}

[[nodiscard]]
inline std::int32_t game_controller_get_player_index(native_game_controller* game_controller)
{
  return SDL_GameControllerGetPlayerIndex(game_controller);
}

inline void game_controller_set_player_index(native_game_controller* game_controller, const std::int32_t player_index)
{
  SDL_GameControllerSetPlayerIndex(game_controller, player_index);
}

[[nodiscard]]
inline std::uint16_t game_controller_get_vendor(native_game_controller* game_controller)
{
  return SDL_GameControllerGetVendor(game_controller);
}

[[nodiscard]]
inline std::uint16_t game_controller_get_product(native_game_controller* game_controller)
{
  return SDL_GameControllerGetProduct(game_controller);
}

[[nodiscard]]
inline std::uint16_t game_controller_get_product_version(native_game_controller* game_controller)
{
  return SDL_GameControllerGetProductVersion(game_controller);
}

[[nodiscard]]
inline std::uint16_t game_controller_get_firmware_version(native_game_controller* game_controller)
{
  return SDL_GameControllerGetFirmwareVersion(game_controller);
}

[[nodiscard]]
inline std::string game_controller_get_serial(native_game_controller* game_controller)
{
  const auto result = SDL_GameControllerGetSerial(game_controller);
  return result ? result : "";
}

[[nodiscard]]
inline bool game_controller_get_attached(native_game_controller* game_controller)
{
  return SDL_GameControllerGetAttached(game_controller) == SDL_TRUE;
}

[[nodiscard]]
inline native_joystick* game_controller_get_joystick(native_game_controller* game_controller)
{
  return SDL_GameControllerGetJoystick(game_controller);
}

// Game controller event state
inline std::int32_t game_controller_event_state(const std::int32_t state)
{
  return SDL_GameControllerEventState(state);
}

// Game controller update
inline void game_controller_update()
{
  SDL_GameControllerUpdate();
}

// Game controller axis/button string conversions
[[nodiscard]]
inline game_controller_axis game_controller_get_axis_from_string(const std::string& str)
{
  return static_cast<game_controller_axis>(SDL_GameControllerGetAxisFromString(str.c_str()));
}

[[nodiscard]]
inline std::string game_controller_get_string_for_axis(const game_controller_axis axis)
{
  const auto result = SDL_GameControllerGetStringForAxis(static_cast<SDL_GameControllerAxis>(axis));
  return result ? result : "";
}

[[nodiscard]]
inline game_controller_button game_controller_get_button_from_string(const std::string& str)
{
  return static_cast<game_controller_button>(SDL_GameControllerGetButtonFromString(str.c_str()));
}

[[nodiscard]]
inline std::string game_controller_get_string_for_button(const game_controller_button button)
{
  const auto result = SDL_GameControllerGetStringForButton(static_cast<SDL_GameControllerButton>(button));
  return result ? result : "";
}

// Game controller binding
[[nodiscard]]
inline game_controller_button_bind game_controller_get_bind_for_axis(native_game_controller* game_controller, const game_controller_axis axis)
{
  return SDL_GameControllerGetBindForAxis(game_controller, static_cast<SDL_GameControllerAxis>(axis));
}

[[nodiscard]]
inline bool game_controller_has_axis(native_game_controller* game_controller, const game_controller_axis axis)
{
  return SDL_GameControllerHasAxis(game_controller, static_cast<SDL_GameControllerAxis>(axis)) == SDL_TRUE;
}

[[nodiscard]]
inline game_controller_button_bind game_controller_get_bind_for_button(native_game_controller* game_controller, const game_controller_button button)
{
  return SDL_GameControllerGetBindForButton(game_controller, static_cast<SDL_GameControllerButton>(button));
}

[[nodiscard]]
inline bool game_controller_has_button(native_game_controller* game_controller, const game_controller_button button)
{
  return SDL_GameControllerHasButton(game_controller, static_cast<SDL_GameControllerButton>(button)) == SDL_TRUE;
}

// Game controller state
[[nodiscard]]
inline std::int16_t game_controller_get_axis(native_game_controller* game_controller, const game_controller_axis axis)
{
  return SDL_GameControllerGetAxis(game_controller, static_cast<SDL_GameControllerAxis>(axis));
}

[[nodiscard]]
inline std::uint8_t game_controller_get_button(native_game_controller* game_controller, const game_controller_button button)
{
  return SDL_GameControllerGetButton(game_controller, static_cast<SDL_GameControllerButton>(button));
}

[[nodiscard]]
inline std::int32_t game_controller_get_num_touchpads(native_game_controller* game_controller)
{
  return SDL_GameControllerGetNumTouchpads(game_controller);
}

[[nodiscard]]
inline std::int32_t game_controller_get_num_touchpad_fingers(native_game_controller* game_controller, const std::int32_t touchpad)
{
  return SDL_GameControllerGetNumTouchpadFingers(game_controller, touchpad);
}

[[nodiscard]]
inline std::expected<void, std::string> game_controller_get_touchpad_finger(
  native_game_controller* game_controller,
  const std::int32_t      touchpad,
  const std::int32_t      finger,
  std::uint8_t&           state,
  float&                  x,
  float&                  y,
  float&                  pressure)
{
  if (SDL_GameControllerGetTouchpadFinger(game_controller, touchpad, finger, &state, &x, &y, &pressure) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline bool game_controller_has_sensor(native_game_controller* game_controller, const SDL_SensorType type)
{
  return SDL_GameControllerHasSensor(game_controller, type) == SDL_TRUE;
}

inline std::expected<void, std::string> game_controller_set_sensor_enabled(native_game_controller* game_controller, const SDL_SensorType type, const bool enabled)
{
  if (SDL_GameControllerSetSensorEnabled(game_controller, type, enabled ? SDL_TRUE : SDL_FALSE) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline bool game_controller_is_sensor_enabled(native_game_controller* game_controller, const SDL_SensorType type)
{
  return SDL_GameControllerIsSensorEnabled(game_controller, type) == SDL_TRUE;
}

[[nodiscard]]
inline float game_controller_get_sensor_data_rate(native_game_controller* game_controller, const SDL_SensorType type)
{
  return SDL_GameControllerGetSensorDataRate(game_controller, type);
}

[[nodiscard]]
inline std::expected<void, std::string> game_controller_get_sensor_data(
  native_game_controller* game_controller,
  const SDL_SensorType    type,
  float*                  data,
  const std::int32_t      num_values)
{
  if (SDL_GameControllerGetSensorData(game_controller, type, data, num_values) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline std::expected<void, std::string> game_controller_get_sensor_data_with_timestamp(
  native_game_controller* game_controller,
  const SDL_SensorType    type,
  std::uint64_t&          timestamp,
  float*                  data,
  const std::int32_t      num_values)
{
  if (SDL_GameControllerGetSensorDataWithTimestamp(game_controller, type, &timestamp, data, num_values) < 0)
    return std::unexpected(get_error());
  return {};
}

// Game controller rumble
inline std::expected<void, std::string> game_controller_rumble(
  native_game_controller* game_controller,
  const std::uint16_t     low_frequency_rumble,
  const std::uint16_t     high_frequency_rumble,
  const std::uint32_t     duration_ms)
{
  if (SDL_GameControllerRumble(game_controller, low_frequency_rumble, high_frequency_rumble, duration_ms) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> game_controller_rumble_triggers(
  native_game_controller* game_controller,
  const std::uint16_t     left_rumble,
  const std::uint16_t     right_rumble,
  const std::uint32_t     duration_ms)
{
  if (SDL_GameControllerRumbleTriggers(game_controller, left_rumble, right_rumble, duration_ms) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline bool game_controller_has_led(native_game_controller* game_controller)
{
  return SDL_GameControllerHasLED(game_controller) == SDL_TRUE;
}

[[nodiscard]]
inline bool game_controller_has_rumble(native_game_controller* game_controller)
{
  return SDL_GameControllerHasRumble(game_controller) == SDL_TRUE;
}

[[nodiscard]]
inline bool game_controller_has_rumble_triggers(native_game_controller* game_controller)
{
  return SDL_GameControllerHasRumbleTriggers(game_controller) == SDL_TRUE;
}

inline std::expected<void, std::string> game_controller_set_led(
  native_game_controller* game_controller,
  const std::uint8_t      red,
  const std::uint8_t      green,
  const std::uint8_t      blue)
{
  if (SDL_GameControllerSetLED(game_controller, red, green, blue) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> game_controller_send_effect(
  native_game_controller* game_controller,
  const void*             data,
  const std::int32_t      size)
{
  if (SDL_GameControllerSendEffect(game_controller, data, size) < 0)
    return std::unexpected(get_error());
  return {};
}

// Conveniences

class game_controller
{
public:
  game_controller() = default;
  
  explicit game_controller(native_game_controller* native, const bool managed = true)
  : native_(native), managed_(managed)
  {
  }

  game_controller(const game_controller&  that) = delete;
  game_controller(      game_controller&& temp) noexcept
  : native_(temp.native_), managed_(temp.managed_)
  {
    temp.native_  = nullptr;
    temp.managed_ = false;
  }
  
  ~game_controller()
  {
    if (native_ && managed_)
      SDL_GameControllerClose(native_);
  }
  
  game_controller& operator=(const game_controller&  that) = delete;
  game_controller& operator=(      game_controller&& temp) noexcept
  {
    if (this != &temp)
    {
      if (native_ && managed_)
        SDL_GameControllerClose(native_);
      native_       = temp.native_;
      managed_      = temp.managed_;
      temp.native_  = nullptr;
      temp.managed_ = false;
    }
    return *this;
  }

  [[nodiscard]]
  native_game_controller* native() const noexcept
  {
    return native_;
  }

  [[nodiscard]]
  bool is_managed() const noexcept
  {
    return managed_;
  }

private:
  native_game_controller* native_  {};
  bool                    managed_ {true};
};
}
