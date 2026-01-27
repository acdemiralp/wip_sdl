#pragma once

#include <cstdint>
#include <expected>
#include <functional>
#include <string>

#include <SDL_events.h>

#include <sdl/error.hpp>
#include <sdl/joystick.hpp>
#include <sdl/keyboard.hpp>
#include <sdl/mouse.hpp>
#include <sdl/touch.hpp>

namespace sdl
{
// Event types
enum class event_type : std::uint32_t
{
  first_event              = SDL_FIRSTEVENT,
  quit                     = SDL_QUIT,
  app_terminating          = SDL_APP_TERMINATING,
  app_low_memory           = SDL_APP_LOWMEMORY,
  app_will_enter_background = SDL_APP_WILLENTERBACKGROUND,
  app_did_enter_background = SDL_APP_DIDENTERBACKGROUND,
  app_will_enter_foreground = SDL_APP_WILLENTERFOREGROUND,
  app_did_enter_foreground = SDL_APP_DIDENTERFOREGROUND,
  locale_changed           = SDL_LOCALECHANGED,
  display_event            = SDL_DISPLAYEVENT,
  window_event             = SDL_WINDOWEVENT,
  syswm_event              = SDL_SYSWMEVENT,
  key_down                 = SDL_KEYDOWN,
  key_up                   = SDL_KEYUP,
  text_editing             = SDL_TEXTEDITING,
  text_input               = SDL_TEXTINPUT,
  keymap_changed           = SDL_KEYMAPCHANGED,
  text_editing_ext         = SDL_TEXTEDITING_EXT,
  mouse_motion             = SDL_MOUSEMOTION,
  mouse_button_down        = SDL_MOUSEBUTTONDOWN,
  mouse_button_up          = SDL_MOUSEBUTTONUP,
  mouse_wheel              = SDL_MOUSEWHEEL,
  joy_axis_motion          = SDL_JOYAXISMOTION,
  joy_ball_motion          = SDL_JOYBALLMOTION,
  joy_hat_motion           = SDL_JOYHATMOTION,
  joy_button_down          = SDL_JOYBUTTONDOWN,
  joy_button_up            = SDL_JOYBUTTONUP,
  joy_device_added         = SDL_JOYDEVICEADDED,
  joy_device_removed       = SDL_JOYDEVICEREMOVED,
  joy_battery_updated      = SDL_JOYBATTERYUPDATED,
  controller_axis_motion   = SDL_CONTROLLERAXISMOTION,
  controller_button_down   = SDL_CONTROLLERBUTTONDOWN,
  controller_button_up     = SDL_CONTROLLERBUTTONUP,
  controller_device_added  = SDL_CONTROLLERDEVICEADDED,
  controller_device_removed = SDL_CONTROLLERDEVICEREMOVED,
  controller_device_remapped = SDL_CONTROLLERDEVICEREMAPPED,
  controller_touchpad_down = SDL_CONTROLLERTOUCHPADDOWN,
  controller_touchpad_motion = SDL_CONTROLLERTOUCHPADMOTION,
  controller_touchpad_up   = SDL_CONTROLLERTOUCHPADUP,
  controller_sensor_update = SDL_CONTROLLERSENSORUPDATE,
  finger_down              = SDL_FINGERDOWN,
  finger_up                = SDL_FINGERUP,
  finger_motion            = SDL_FINGERMOTION,
  dollar_gesture           = SDL_DOLLARGESTURE,
  dollar_record            = SDL_DOLLARRECORD,
  multi_gesture            = SDL_MULTIGESTURE,
  clipboard_update         = SDL_CLIPBOARDUPDATE,
  drop_file                = SDL_DROPFILE,
  drop_text                = SDL_DROPTEXT,
  drop_begin               = SDL_DROPBEGIN,
  drop_complete            = SDL_DROPCOMPLETE,
  audio_device_added       = SDL_AUDIODEVICEADDED,
  audio_device_removed     = SDL_AUDIODEVICEREMOVED,
  sensor_update            = SDL_SENSORUPDATE,
  render_targets_reset     = SDL_RENDER_TARGETS_RESET,
  render_device_reset      = SDL_RENDER_DEVICE_RESET,
  poll_sentinel            = SDL_POLLSENTINEL,
  user_event               = SDL_USEREVENT,
  last_event               = SDL_LASTEVENT
};

// Event action
enum class event_action
{
  add_event  = SDL_ADDEVENT,
  peek_event = SDL_PEEKEVENT,
  get_event  = SDL_GETEVENT
};

// Event state
constexpr std::int32_t query   = SDL_QUERY;
constexpr std::int32_t ignore  = SDL_IGNORE;
constexpr std::int32_t disable = SDL_DISABLE;
constexpr std::int32_t enable  = SDL_ENABLE;

using event = SDL_Event;
using event_filter = SDL_EventFilter;

// Event queue management
inline void pump_events()
{
  SDL_PumpEvents();
}

[[nodiscard]]
inline std::int32_t peep_events(
  event*            events,
  const std::int32_t num_events,
  const event_action action,
  const std::uint32_t min_type,
  const std::uint32_t max_type)
{
  return SDL_PeepEvents(events, num_events, static_cast<SDL_eventaction>(action), min_type, max_type);
}

[[nodiscard]]
inline bool has_event(const std::uint32_t type)
{
  return SDL_HasEvent(type) == SDL_TRUE;
}

[[nodiscard]]
inline bool has_events(const std::uint32_t min_type, const std::uint32_t max_type)
{
  return SDL_HasEvents(min_type, max_type) == SDL_TRUE;
}

inline void flush_event(const std::uint32_t type)
{
  SDL_FlushEvent(type);
}

inline void flush_events(const std::uint32_t min_type, const std::uint32_t max_type)
{
  SDL_FlushEvents(min_type, max_type);
}

[[nodiscard]]
inline bool poll_event(event* event_ptr)
{
  return SDL_PollEvent(event_ptr) != 0;
}

[[nodiscard]]
inline std::int32_t wait_event(event* event_ptr)
{
  return SDL_WaitEvent(event_ptr);
}

[[nodiscard]]
inline std::int32_t wait_event_timeout(event* event_ptr, const std::int32_t timeout)
{
  return SDL_WaitEventTimeout(event_ptr, timeout);
}

inline std::expected<void, std::string> push_event(event* event_ptr)
{
  const auto result = SDL_PushEvent(event_ptr);
  if (result < 0)
    return std::unexpected(get_error());
  return {};
}

inline void set_event_filter(event_filter filter, void* user_data)
{
  SDL_SetEventFilter(filter, user_data);
}

[[nodiscard]]
inline bool get_event_filter(event_filter* filter, void** user_data)
{
  return SDL_GetEventFilter(filter, user_data) == SDL_TRUE;
}

inline void add_event_watch(event_filter filter, void* user_data)
{
  SDL_AddEventWatch(filter, user_data);
}

inline void del_event_watch(event_filter filter, void* user_data)
{
  SDL_DelEventWatch(filter, user_data);
}

inline void filter_events(event_filter filter, void* user_data)
{
  SDL_FilterEvents(filter, user_data);
}

inline std::uint8_t event_state(const std::uint32_t type, const std::int32_t state)
{
  return SDL_EventState(type, state);
}

[[nodiscard]]
inline std::uint8_t get_event_state(const std::uint32_t type)
{
  return SDL_GetEventState(type);
}

[[nodiscard]]
inline std::uint32_t register_events(const std::int32_t num_events)
{
  return SDL_RegisterEvents(num_events);
}

// Conveniences

class event_handler
{
public:
  event_handler() = default;
  
  explicit event_handler(std::function<int(void*, event*)> callback)
  : callback_(std::move(callback))
  {
    SDL_SetEventFilter(
      [](void* user_data, SDL_Event* event_ptr) -> int
      {
        const auto handler = static_cast<event_handler*>(user_data);
        return handler->callback_(user_data, event_ptr);
      },
      this);
  }
  
  event_handler(const event_handler&  that) = delete;
  event_handler(      event_handler&& temp) = delete;
  
  ~event_handler()
  {
    SDL_SetEventFilter(nullptr, nullptr);
  }
  
  event_handler& operator=(const event_handler&  that) = delete;
  event_handler& operator=(      event_handler&& temp) = delete;

private:
  std::function<int(void*, event*)> callback_;
};

// Common event structures for convenience
struct common_event
{
  std::uint32_t type;
  std::uint32_t timestamp;
};

struct display_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  std::uint32_t display;
  std::uint8_t  event;
  std::uint8_t  padding1;
  std::uint8_t  padding2;
  std::uint8_t  padding3;
  std::int32_t  data1;
};

struct window_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  std::uint32_t window_id;
  std::uint8_t  event;
  std::uint8_t  padding1;
  std::uint8_t  padding2;
  std::uint8_t  padding3;
  std::int32_t  data1;
  std::int32_t  data2;
};

struct keyboard_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  std::uint32_t window_id;
  std::uint8_t  state;
  std::uint8_t  repeat;
  std::uint8_t  padding2;
  std::uint8_t  padding3;
  key_sym       keysym;
};

struct text_editing_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  std::uint32_t window_id;
  char          text[32];
  std::int32_t  start;
  std::int32_t  length;
};

struct text_editing_ext_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  std::uint32_t window_id;
  char*         text;
  std::int32_t  start;
  std::int32_t  length;
};

struct text_input_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  std::uint32_t window_id;
  char          text[32];
};

struct mouse_motion_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  std::uint32_t window_id;
  std::uint32_t which;
  std::uint32_t state;
  std::int32_t  x;
  std::int32_t  y;
  std::int32_t  xrel;
  std::int32_t  yrel;
};

struct mouse_button_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  std::uint32_t window_id;
  std::uint32_t which;
  std::uint8_t  button;
  std::uint8_t  state;
  std::uint8_t  clicks;
  std::uint8_t  padding1;
  std::int32_t  x;
  std::int32_t  y;
};

struct mouse_wheel_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  std::uint32_t window_id;
  std::uint32_t which;
  std::int32_t  x;
  std::int32_t  y;
  std::uint32_t direction;
  float         precise_x;
  float         precise_y;
};

struct joy_axis_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  native_joystick_id which;
  std::uint8_t  axis;
  std::uint8_t  padding1;
  std::uint8_t  padding2;
  std::uint8_t  padding3;
  std::int16_t  value;
  std::uint16_t padding4;
};

struct joy_ball_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  native_joystick_id which;
  std::uint8_t  ball;
  std::uint8_t  padding1;
  std::uint8_t  padding2;
  std::uint8_t  padding3;
  std::int16_t  xrel;
  std::int16_t  yrel;
};

struct joy_hat_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  native_joystick_id which;
  std::uint8_t  hat;
  std::uint8_t  value;
  std::uint8_t  padding1;
  std::uint8_t  padding2;
};

struct joy_button_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  native_joystick_id which;
  std::uint8_t  button;
  std::uint8_t  state;
  std::uint8_t  padding1;
  std::uint8_t  padding2;
};

struct joy_device_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  std::int32_t  which;
};

struct joy_battery_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  native_joystick_id which;
  SDL_JoystickPowerLevel level;
};

struct controller_axis_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  native_joystick_id which;
  std::uint8_t  axis;
  std::uint8_t  padding1;
  std::uint8_t  padding2;
  std::uint8_t  padding3;
  std::int16_t  value;
  std::uint16_t padding4;
};

struct controller_button_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  native_joystick_id which;
  std::uint8_t  button;
  std::uint8_t  state;
  std::uint8_t  padding1;
  std::uint8_t  padding2;
};

struct controller_device_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  std::int32_t  which;
};

struct controller_touchpad_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  native_joystick_id which;
  std::int32_t  touchpad;
  std::int32_t  finger;
  float         x;
  float         y;
  float         pressure;
};

struct controller_sensor_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  native_joystick_id which;
  std::int32_t  sensor;
  float         data[3];
  std::uint64_t timestamp_us;
};

struct audio_device_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  std::uint32_t which;
  std::uint8_t  iscapture;
  std::uint8_t  padding1;
  std::uint8_t  padding2;
  std::uint8_t  padding3;
};

struct touch_finger_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  touch_id      touch_id;
  finger_id     finger_id;
  float         x;
  float         y;
  float         dx;
  float         dy;
  float         pressure;
  std::uint32_t window_id;
};

struct multi_gesture_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  touch_id      touch_id;
  float         d_theta;
  float         d_dist;
  float         x;
  float         y;
  std::uint16_t num_fingers;
  std::uint16_t padding;
};

struct dollar_gesture_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  touch_id      touch_id;
  gesture_id    gesture_id;
  std::uint32_t num_fingers;
  float         error;
  float         x;
  float         y;
};

struct drop_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  char*         file;
  std::uint32_t window_id;
};

struct sensor_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  std::int32_t  which;
  float         data[6];
  std::uint64_t timestamp_us;
};

struct quit_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
};

struct user_event_data
{
  std::uint32_t type;
  std::uint32_t timestamp;
  std::uint32_t window_id;
  std::int32_t  code;
  void*         data1;
  void*         data2;
};

struct syswm_event_data
{
  std::uint32_t    type;
  std::uint32_t    timestamp;
  SDL_SysWMmsg*    msg;
};
}
