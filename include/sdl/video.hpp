#pragma once

#include <array>
#include <cstdint>
#include <expected>
#include <string>
#include <type_traits>
#include <vector>

#include <SDL_syswm.h>
#include <SDL_video.h>
#include <SDL_shape.h>

#include <sdl/bitset_enum.hpp>
#include <sdl/error.hpp>
#include <sdl/pixels.hpp>
#include <sdl/rect.hpp>
#include <sdl/surface.hpp>

namespace sdl
{
using sys_wm_info       = SDL_SysWMinfo;
using window_shape_mode = SDL_WindowShapeMode;

using native_window     = SDL_Window;
using native_display_mode = SDL_DisplayMode;

// Window flags
enum class window_flags : std::uint32_t
{
  fullscreen         = SDL_WINDOW_FULLSCREEN,
  opengl             = SDL_WINDOW_OPENGL,
  shown              = SDL_WINDOW_SHOWN,
  hidden             = SDL_WINDOW_HIDDEN,
  borderless         = SDL_WINDOW_BORDERLESS,
  resizable          = SDL_WINDOW_RESIZABLE,
  minimized          = SDL_WINDOW_MINIMIZED,
  maximized          = SDL_WINDOW_MAXIMIZED,
  mouse_grabbed      = SDL_WINDOW_MOUSE_GRABBED,
  input_focus        = SDL_WINDOW_INPUT_FOCUS,
  mouse_focus        = SDL_WINDOW_MOUSE_FOCUS,
  fullscreen_desktop = SDL_WINDOW_FULLSCREEN_DESKTOP,
  foreign            = SDL_WINDOW_FOREIGN,
  allow_highdpi      = SDL_WINDOW_ALLOW_HIGHDPI,
  mouse_capture      = SDL_WINDOW_MOUSE_CAPTURE,
  always_on_top      = SDL_WINDOW_ALWAYS_ON_TOP,
  skip_taskbar       = SDL_WINDOW_SKIP_TASKBAR,
  utility            = SDL_WINDOW_UTILITY,
  tooltip            = SDL_WINDOW_TOOLTIP,
  popup_menu         = SDL_WINDOW_POPUP_MENU,
  keyboard_grabbed   = SDL_WINDOW_KEYBOARD_GRABBED,
  vulkan             = SDL_WINDOW_VULKAN,
  metal              = SDL_WINDOW_METAL,
  input_grabbed      = SDL_WINDOW_INPUT_GRABBED
};

template <>
struct is_bitset_enum<window_flags> : std::true_type {};

// Window event IDs
enum class window_event_id : std::uint8_t
{
  none           = SDL_WINDOWEVENT_NONE,
  shown          = SDL_WINDOWEVENT_SHOWN,
  hidden         = SDL_WINDOWEVENT_HIDDEN,
  exposed        = SDL_WINDOWEVENT_EXPOSED,
  moved          = SDL_WINDOWEVENT_MOVED,
  resized        = SDL_WINDOWEVENT_RESIZED,
  size_changed   = SDL_WINDOWEVENT_SIZE_CHANGED,
  minimized      = SDL_WINDOWEVENT_MINIMIZED,
  maximized      = SDL_WINDOWEVENT_MAXIMIZED,
  restored       = SDL_WINDOWEVENT_RESTORED,
  enter          = SDL_WINDOWEVENT_ENTER,
  leave          = SDL_WINDOWEVENT_LEAVE,
  focus_gained   = SDL_WINDOWEVENT_FOCUS_GAINED,
  focus_lost     = SDL_WINDOWEVENT_FOCUS_LOST,
  close          = SDL_WINDOWEVENT_CLOSE,
  take_focus     = SDL_WINDOWEVENT_TAKE_FOCUS,
  hit_test       = SDL_WINDOWEVENT_HIT_TEST,
  iccprof_changed = SDL_WINDOWEVENT_ICCPROF_CHANGED,
  display_changed = SDL_WINDOWEVENT_DISPLAY_CHANGED
};

// Display mode
struct display_mode
{
  [[nodiscard]]
  SDL_DisplayMode native() const
  {
    return SDL_DisplayMode{format, w, h, refresh_rate, driverdata};
  }

  [[nodiscard]]
  static display_mode from_native(const SDL_DisplayMode& native)
  {
    return display_mode{native.format, native.w, native.h, native.refresh_rate, native.driverdata};
  }

  std::uint32_t format       {};
  std::int32_t  w            {};
  std::int32_t  h            {};
  std::int32_t  refresh_rate {};
  void*         driverdata   {};
};

// Display orientation
enum class display_orientation
{
  unknown           = SDL_ORIENTATION_UNKNOWN,
  landscape         = SDL_ORIENTATION_LANDSCAPE,
  landscape_flipped = SDL_ORIENTATION_LANDSCAPE_FLIPPED,
  portrait          = SDL_ORIENTATION_PORTRAIT,
  portrait_flipped  = SDL_ORIENTATION_PORTRAIT_FLIPPED
};

// Flash operation
enum class flash_operation
{
  cancel           = SDL_FLASH_CANCEL,
  briefly          = SDL_FLASH_BRIEFLY,
  until_focused    = SDL_FLASH_UNTIL_FOCUSED
};

// GL attributes
enum class gl_attr
{
  red_size                   = SDL_GL_RED_SIZE,
  green_size                 = SDL_GL_GREEN_SIZE,
  blue_size                  = SDL_GL_BLUE_SIZE,
  alpha_size                 = SDL_GL_ALPHA_SIZE,
  buffer_size                = SDL_GL_BUFFER_SIZE,
  doublebuffer               = SDL_GL_DOUBLEBUFFER,
  depth_size                 = SDL_GL_DEPTH_SIZE,
  stencil_size               = SDL_GL_STENCIL_SIZE,
  accum_red_size             = SDL_GL_ACCUM_RED_SIZE,
  accum_green_size           = SDL_GL_ACCUM_GREEN_SIZE,
  accum_blue_size            = SDL_GL_ACCUM_BLUE_SIZE,
  accum_alpha_size           = SDL_GL_ACCUM_ALPHA_SIZE,
  stereo                     = SDL_GL_STEREO,
  multisamplebuffers         = SDL_GL_MULTISAMPLEBUFFERS,
  multisamplesamples         = SDL_GL_MULTISAMPLESAMPLES,
  accelerated_visual         = SDL_GL_ACCELERATED_VISUAL,
  retained_backing           = SDL_GL_RETAINED_BACKING,
  context_major_version      = SDL_GL_CONTEXT_MAJOR_VERSION,
  context_minor_version      = SDL_GL_CONTEXT_MINOR_VERSION,
  context_egl                = SDL_GL_CONTEXT_EGL,
  context_flags              = SDL_GL_CONTEXT_FLAGS,
  context_profile_mask       = SDL_GL_CONTEXT_PROFILE_MASK,
  share_with_current_context = SDL_GL_SHARE_WITH_CURRENT_CONTEXT,
  framebuffer_srgb_capable   = SDL_GL_FRAMEBUFFER_SRGB_CAPABLE,
  context_release_behavior   = SDL_GL_CONTEXT_RELEASE_BEHAVIOR,
  context_reset_notification = SDL_GL_CONTEXT_RESET_NOTIFICATION,
  context_no_error           = SDL_GL_CONTEXT_NO_ERROR,
  floatbuffers               = SDL_GL_FLOATBUFFERS
};

// GL profiles
enum class gl_profile
{
  core          = SDL_GL_CONTEXT_PROFILE_CORE,
  compatibility = SDL_GL_CONTEXT_PROFILE_COMPATIBILITY,
  es            = SDL_GL_CONTEXT_PROFILE_ES
};

// GL context flags
enum class gl_context_flag : std::uint32_t
{
  debug              = SDL_GL_CONTEXT_DEBUG_FLAG,
  forward_compatible = SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG,
  robust_access      = SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG,
  reset_isolation    = SDL_GL_CONTEXT_RESET_ISOLATION_FLAG
};

template <>
struct is_bitset_enum<gl_context_flag> : std::true_type {};

using gl_context = SDL_GLContext;

// Hit test result
enum class hit_test_result
{
  normal             = SDL_HITTEST_NORMAL,
  draggable          = SDL_HITTEST_DRAGGABLE,
  resize_topleft     = SDL_HITTEST_RESIZE_TOPLEFT,
  resize_top         = SDL_HITTEST_RESIZE_TOP,
  resize_topright    = SDL_HITTEST_RESIZE_TOPRIGHT,
  resize_right       = SDL_HITTEST_RESIZE_RIGHT,
  resize_bottomright = SDL_HITTEST_RESIZE_BOTTOMRIGHT,
  resize_bottom      = SDL_HITTEST_RESIZE_BOTTOM,
  resize_bottomleft  = SDL_HITTEST_RESIZE_BOTTOMLEFT,
  resize_left        = SDL_HITTEST_RESIZE_LEFT
};

using hit_test = SDL_HitTest;

// Video driver functions
[[nodiscard]]
inline std::int32_t get_num_video_drivers()
{
  return SDL_GetNumVideoDrivers();
}

[[nodiscard]]
inline std::string get_video_driver(const std::int32_t index)
{
  const auto result = SDL_GetVideoDriver(index);
  return result ? result : "";
}

inline std::expected<void, std::string> video_init(const std::string* driver_name)
{
  if (SDL_VideoInit(driver_name ? driver_name->c_str() : nullptr) < 0)
    return std::unexpected(get_error());
  return {};
}

inline void video_quit()
{
  SDL_VideoQuit();
}

[[nodiscard]]
inline std::string get_current_video_driver()
{
  const auto result = SDL_GetCurrentVideoDriver();
  return result ? result : "";
}

// Display functions
[[nodiscard]]
inline std::int32_t get_num_video_displays()
{
  return SDL_GetNumVideoDisplays();
}

[[nodiscard]]
inline std::string get_display_name(const std::int32_t display_index)
{
  const auto result = SDL_GetDisplayName(display_index);
  return result ? result : "";
}

[[nodiscard]]
inline std::expected<rectangle<std::int32_t>, std::string> get_display_bounds(const std::int32_t display_index)
{
  rectangle<std::int32_t> rect;
  if (SDL_GetDisplayBounds(display_index, reinterpret_cast<SDL_Rect*>(&rect)) < 0)
    return std::unexpected(get_error());
  return rect;
}

[[nodiscard]]
inline std::expected<rectangle<std::int32_t>, std::string> get_display_usable_bounds(const std::int32_t display_index)
{
  rectangle<std::int32_t> rect;
  if (SDL_GetDisplayUsableBounds(display_index, reinterpret_cast<SDL_Rect*>(&rect)) < 0)
    return std::unexpected(get_error());
  return rect;
}

[[nodiscard]]
inline std::expected<std::array<float, 2>, std::string> get_display_dpi(const std::int32_t display_index)
{
  std::array<float, 2> dpi;
  float ddpi;
  if (SDL_GetDisplayDPI(display_index, &ddpi, &dpi[0], &dpi[1]) < 0)
    return std::unexpected(get_error());
  return dpi;
}

[[nodiscard]]
inline display_orientation get_display_orientation(const std::int32_t display_index)
{
  return static_cast<display_orientation>(SDL_GetDisplayOrientation(display_index));
}

// Display mode functions
[[nodiscard]]
inline std::int32_t get_num_display_modes(const std::int32_t display_index)
{
  return SDL_GetNumDisplayModes(display_index);
}

[[nodiscard]]
inline std::expected<display_mode, std::string> get_display_mode(const std::int32_t display_index, const std::int32_t mode_index)
{
  SDL_DisplayMode mode;
  if (SDL_GetDisplayMode(display_index, mode_index, &mode) < 0)
    return std::unexpected(get_error());
  return display_mode::from_native(mode);
}

[[nodiscard]]
inline std::expected<display_mode, std::string> get_desktop_display_mode(const std::int32_t display_index)
{
  SDL_DisplayMode mode;
  if (SDL_GetDesktopDisplayMode(display_index, &mode) < 0)
    return std::unexpected(get_error());
  return display_mode::from_native(mode);
}

[[nodiscard]]
inline std::expected<display_mode, std::string> get_current_display_mode(const std::int32_t display_index)
{
  SDL_DisplayMode mode;
  if (SDL_GetCurrentDisplayMode(display_index, &mode) < 0)
    return std::unexpected(get_error());
  return display_mode::from_native(mode);
}

[[nodiscard]]
inline std::expected<display_mode, std::string> get_closest_display_mode(const std::int32_t display_index, const display_mode& mode)
{
  SDL_DisplayMode native_mode = mode.native();
  SDL_DisplayMode closest;
  if (!SDL_GetClosestDisplayMode(display_index, &native_mode, &closest))
    return std::unexpected(get_error());
  return display_mode::from_native(closest);
}

[[nodiscard]]
inline std::int32_t get_point_display_index(const std::array<std::int32_t, 2>& point)
{
  SDL_Point p{point[0], point[1]};
  return SDL_GetPointDisplayIndex(&p);
}

[[nodiscard]]
inline std::int32_t get_rect_display_index(const rectangle<std::int32_t>& rect)
{
  return SDL_GetRectDisplayIndex(reinterpret_cast<const SDL_Rect*>(&rect));
}

// Window functions
[[nodiscard]]
inline std::expected<native_window*, std::string> create_window(
  const std::string&                 title,
  const std::array<std::int32_t, 2>& position,
  const std::array<std::int32_t, 2>& size,
  const window_flags                 flags)
{
  const auto result = SDL_CreateWindow(title.c_str(), position[0], position[1], size[0], size[1], static_cast<std::uint32_t>(flags));
  if (!result)
    return std::unexpected(get_error());
  return result;
}

[[nodiscard]]
inline std::expected<native_window*, std::string> create_window_from(const void* data)
{
  const auto result = SDL_CreateWindowFrom(data);
  if (!result)
    return std::unexpected(get_error());
  return result;
}

inline void destroy_window(native_window* window)
{
  SDL_DestroyWindow(window);
}

[[nodiscard]]
inline std::uint32_t get_window_id(native_window* window)
{
  return SDL_GetWindowID(window);
}

[[nodiscard]]
inline native_window* get_window_from_id(const std::uint32_t id)
{
  return SDL_GetWindowFromID(id);
}

[[nodiscard]]
inline window_flags get_window_flags(native_window* window)
{
  return static_cast<window_flags>(SDL_GetWindowFlags(window));
}

inline void set_window_title(native_window* window, const std::string& title)
{
  SDL_SetWindowTitle(window, title.c_str());
}

[[nodiscard]]
inline std::string get_window_title(native_window* window)
{
  const auto result = SDL_GetWindowTitle(window);
  return result ? result : "";
}

inline void set_window_icon(native_window* window, SDL_Surface* icon)
{
  SDL_SetWindowIcon(window, icon);
}

inline void* set_window_data(native_window* window, const std::string& name, void* userdata)
{
  return SDL_SetWindowData(window, name.c_str(), userdata);
}

[[nodiscard]]
inline void* get_window_data(native_window* window, const std::string& name)
{
  return SDL_GetWindowData(window, name.c_str());
}

inline void set_window_position(native_window* window, const std::array<std::int32_t, 2>& position)
{
  SDL_SetWindowPosition(window, position[0], position[1]);
}

[[nodiscard]]
inline std::array<std::int32_t, 2> get_window_position(native_window* window)
{
  std::array<std::int32_t, 2> position;
  SDL_GetWindowPosition(window, &position[0], &position[1]);
  return position;
}

inline void set_window_size(native_window* window, const std::array<std::int32_t, 2>& size)
{
  SDL_SetWindowSize(window, size[0], size[1]);
}

[[nodiscard]]
inline std::array<std::int32_t, 2> get_window_size(native_window* window)
{
  std::array<std::int32_t, 2> size;
  SDL_GetWindowSize(window, &size[0], &size[1]);
  return size;
}

[[nodiscard]]
inline std::expected<rectangle<std::int32_t>, std::string> get_window_borders_size(native_window* window)
{
  rectangle<std::int32_t> borders;
  if (SDL_GetWindowBordersSize(window, &borders.y, &borders.x, &borders.h, &borders.w) < 0)
    return std::unexpected(get_error());
  return borders;
}

[[nodiscard]]
inline std::array<std::int32_t, 2> get_window_size_in_pixels(native_window* window)
{
  std::array<std::int32_t, 2> size;
  SDL_GetWindowSizeInPixels(window, &size[0], &size[1]);
  return size;
}

inline void set_window_minimum_size(native_window* window, const std::array<std::int32_t, 2>& size)
{
  SDL_SetWindowMinimumSize(window, size[0], size[1]);
}

[[nodiscard]]
inline std::array<std::int32_t, 2> get_window_minimum_size(native_window* window)
{
  std::array<std::int32_t, 2> size;
  SDL_GetWindowMinimumSize(window, &size[0], &size[1]);
  return size;
}

inline void set_window_maximum_size(native_window* window, const std::array<std::int32_t, 2>& size)
{
  SDL_SetWindowMaximumSize(window, size[0], size[1]);
}

[[nodiscard]]
inline std::array<std::int32_t, 2> get_window_maximum_size(native_window* window)
{
  std::array<std::int32_t, 2> size;
  SDL_GetWindowMaximumSize(window, &size[0], &size[1]);
  return size;
}

inline void set_window_bordered(native_window* window, const bool bordered)
{
  SDL_SetWindowBordered(window, bordered ? SDL_TRUE : SDL_FALSE);
}

inline void set_window_resizable(native_window* window, const bool resizable)
{
  SDL_SetWindowResizable(window, resizable ? SDL_TRUE : SDL_FALSE);
}

inline void set_window_always_on_top(native_window* window, const bool on_top)
{
  SDL_SetWindowAlwaysOnTop(window, on_top ? SDL_TRUE : SDL_FALSE);
}

inline void show_window(native_window* window)
{
  SDL_ShowWindow(window);
}

inline void hide_window(native_window* window)
{
  SDL_HideWindow(window);
}

inline void raise_window(native_window* window)
{
  SDL_RaiseWindow(window);
}

inline void maximize_window(native_window* window)
{
  SDL_MaximizeWindow(window);
}

inline void minimize_window(native_window* window)
{
  SDL_MinimizeWindow(window);
}

inline void restore_window(native_window* window)
{
  SDL_RestoreWindow(window);
}

inline std::expected<void, std::string> set_window_fullscreen(native_window* window, const std::uint32_t flags)
{
  if (SDL_SetWindowFullscreen(window, flags) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline bool has_window_surface(native_window* window)
{
  return SDL_HasWindowSurface(window) == SDL_TRUE;
}

[[nodiscard]]
inline std::expected<SDL_Surface*, std::string> get_window_surface(native_window* window)
{
  const auto result = SDL_GetWindowSurface(window);
  if (!result)
    return std::unexpected(get_error());
  return result;
}

inline std::expected<void, std::string> update_window_surface(native_window* window)
{
  if (SDL_UpdateWindowSurface(window) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> update_window_surface_rects(native_window* window, const rectangle<std::int32_t>* rects, const std::int32_t num_rects)
{
  if (SDL_UpdateWindowSurfaceRects(window, reinterpret_cast<const SDL_Rect*>(rects), num_rects) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> destroy_window_surface(native_window* window)
{
  if (SDL_DestroyWindowSurface(window) < 0)
    return std::unexpected(get_error());
  return {};
}

inline void set_window_grab(native_window* window, const bool grabbed)
{
  SDL_SetWindowGrab(window, grabbed ? SDL_TRUE : SDL_FALSE);
}

inline void set_window_keyboard_grab(native_window* window, const bool grabbed)
{
  SDL_SetWindowKeyboardGrab(window, grabbed ? SDL_TRUE : SDL_FALSE);
}

inline void set_window_mouse_grab(native_window* window, const bool grabbed)
{
  SDL_SetWindowMouseGrab(window, grabbed ? SDL_TRUE : SDL_FALSE);
}

[[nodiscard]]
inline bool get_window_grab(native_window* window)
{
  return SDL_GetWindowGrab(window) == SDL_TRUE;
}

[[nodiscard]]
inline bool get_window_keyboard_grab(native_window* window)
{
  return SDL_GetWindowKeyboardGrab(window) == SDL_TRUE;
}

[[nodiscard]]
inline bool get_window_mouse_grab(native_window* window)
{
  return SDL_GetWindowMouseGrab(window) == SDL_TRUE;
}

[[nodiscard]]
inline native_window* get_grabbed_window()
{
  return SDL_GetGrabbedWindow();
}

inline std::expected<void, std::string> set_window_mouse_rect(native_window* window, const rectangle<std::int32_t>* rect)
{
  if (SDL_SetWindowMouseRect(window, reinterpret_cast<const SDL_Rect*>(rect)) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline const SDL_Rect* get_window_mouse_rect(native_window* window)
{
  return SDL_GetWindowMouseRect(window);
}

inline std::expected<void, std::string> set_window_brightness(native_window* window, const float brightness)
{
  if (SDL_SetWindowBrightness(window, brightness) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline float get_window_brightness(native_window* window)
{
  return SDL_GetWindowBrightness(window);
}

inline std::expected<void, std::string> set_window_opacity(native_window* window, const float opacity)
{
  if (SDL_SetWindowOpacity(window, opacity) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline std::expected<float, std::string> get_window_opacity(native_window* window)
{
  float opacity;
  if (SDL_GetWindowOpacity(window, &opacity) < 0)
    return std::unexpected(get_error());
  return opacity;
}

inline void set_window_modal_for(native_window* modal_window, native_window* parent_window)
{
  SDL_SetWindowModalFor(modal_window, parent_window);
}

inline void set_window_input_focus(native_window* window)
{
  SDL_SetWindowInputFocus(window);
}

inline std::expected<void, std::string> set_window_gamma_ramp(
  native_window*      window,
  const std::uint16_t* red,
  const std::uint16_t* green,
  const std::uint16_t* blue)
{
  if (SDL_SetWindowGammaRamp(window, red, green, blue) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline std::expected<void, std::string> get_window_gamma_ramp(
  native_window* window,
  std::uint16_t*  red,
  std::uint16_t*  green,
  std::uint16_t*  blue)
{
  if (SDL_GetWindowGammaRamp(window, red, green, blue) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> set_window_hit_test(native_window* window, hit_test callback, void* callback_data)
{
  if (SDL_SetWindowHitTest(window, callback, callback_data) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> flash_window(native_window* window, const flash_operation operation)
{
  if (SDL_FlashWindow(window, static_cast<SDL_FlashOperation>(operation)) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline std::int32_t get_window_display_index(native_window* window)
{
  return SDL_GetWindowDisplayIndex(window);
}

inline std::expected<void, std::string> set_window_display_mode(native_window* window, const display_mode* mode)
{
  if (SDL_SetWindowDisplayMode(window, mode ? &mode->native() : nullptr) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline std::expected<display_mode, std::string> get_window_display_mode(native_window* window)
{
  SDL_DisplayMode mode;
  if (SDL_GetWindowDisplayMode(window, &mode) < 0)
    return std::unexpected(get_error());
  return display_mode::from_native(mode);
}

[[nodiscard]]
inline void* get_window_icc_profile(native_window* window, std::size_t* size)
{
  return SDL_GetWindowICCProfile(window, size);
}

[[nodiscard]]
inline std::uint32_t get_window_pixel_format(native_window* window)
{
  return SDL_GetWindowPixelFormat(window);
}

// OpenGL functions
inline std::expected<void, std::string> gl_load_library(const std::string* path)
{
  if (SDL_GL_LoadLibrary(path ? path->c_str() : nullptr) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline void* gl_get_proc_address(const std::string& proc)
{
  return SDL_GL_GetProcAddress(proc.c_str());
}

inline void gl_unload_library()
{
  SDL_GL_UnloadLibrary();
}

[[nodiscard]]
inline bool gl_extension_supported(const std::string& extension)
{
  return SDL_GL_ExtensionSupported(extension.c_str()) == SDL_TRUE;
}

inline void gl_reset_attributes()
{
  SDL_GL_ResetAttributes();
}

inline std::expected<void, std::string> gl_set_attribute(const gl_attr attr, const std::int32_t value)
{
  if (SDL_GL_SetAttribute(static_cast<SDL_GLattr>(attr), value) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline std::expected<std::int32_t, std::string> gl_get_attribute(const gl_attr attr)
{
  std::int32_t value;
  if (SDL_GL_GetAttribute(static_cast<SDL_GLattr>(attr), &value) < 0)
    return std::unexpected(get_error());
  return value;
}

[[nodiscard]]
inline std::expected<gl_context, std::string> gl_create_context(native_window* window)
{
  const auto result = SDL_GL_CreateContext(window);
  if (!result)
    return std::unexpected(get_error());
  return result;
}

inline std::expected<void, std::string> gl_make_current(native_window* window, gl_context context)
{
  if (SDL_GL_MakeCurrent(window, context) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline native_window* gl_get_current_window()
{
  return SDL_GL_GetCurrentWindow();
}

[[nodiscard]]
inline gl_context gl_get_current_context()
{
  return SDL_GL_GetCurrentContext();
}

[[nodiscard]]
inline std::array<std::int32_t, 2> gl_get_drawable_size(native_window* window)
{
  std::array<std::int32_t, 2> size;
  SDL_GL_GetDrawableSize(window, &size[0], &size[1]);
  return size;
}

inline std::expected<void, std::string> gl_set_swap_interval(const std::int32_t interval)
{
  if (SDL_GL_SetSwapInterval(interval) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline std::int32_t gl_get_swap_interval()
{
  return SDL_GL_GetSwapInterval();
}

inline void gl_swap_window(native_window* window)
{
  SDL_GL_SwapWindow(window);
}

inline void gl_delete_context(gl_context context)
{
  SDL_GL_DeleteContext(context);
}

// Conveniences

class window
{
public:
  // Conveniences.

  // Conveniences from mouse.hpp.

  [[nodiscard]]
  static window                                 with_mouse_focus        ();

  void                                          warp_mouse              (const std::array<std::int32_t, 2>& position) const;

  // Conveniences from shape.hpp.

  // The constructor cannot transmit error state. You should use `sdl::make_shaped_window(...)` to handle errors.
  window(const std::string& title, const std::array<std::int32_t, 2>& position, const std::array<std::int32_t, 2>& size, const std::uint32_t flags);

  [[nodiscard]]
  bool                                          is_shaped_window        () const;

  std::expected<void             , std::string> set_window_shape        (const sdl::surface& surface, window_shape_mode& mode) const;
  [[nodiscard]]
  std::expected<window_shape_mode, std::string> get_shaped_window_mode  () const;

  // Conveniences from keyboard.hpp.
  [[nodiscard]]
  static window                                 with_keyboard_focus     ();

  [[nodiscard]]
  bool                                          is_screen_keyboard_shown() const;

  // Conveniences from syswm.hpp.

  [[nodiscard]]
  std::expected<sys_wm_info      , std::string> get_wm_info             () const;

  [[nodiscard]]
  SDL_Window*                                   native                  () const
  {
    return native_;
  }

private:
  window(SDL_Window* native, const bool managed)
  : native_(native), managed_(managed)
  {
    
  }

  SDL_Window* native_  {};
  bool        managed_ {true};
};

[[nodiscard]]
inline std::expected<window, std::string> make_shaped_window(const std::string& title, const std::array<std::int32_t, 2>& position, const std::array<std::int32_t, 2>& size, const std::uint32_t flags)
{
  window result(title, position, size, flags);
  if (!result.native())
    return std::unexpected(get_error());
  return result;
}
}