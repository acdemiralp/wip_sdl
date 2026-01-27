#pragma once

#include <cstdint>
#include <expected>
#include <string>

#include <SDL_system.h>

#include <sdl/error.hpp>

namespace sdl
{
// Windows-specific functions
#ifdef SDL_PLATFORM_WINDOWS
inline std::expected<void, std::string> direct3d9_get_adapter_index(const std::uint32_t display_index, std::uint32_t& adapter_index)
{
  const auto result = SDL_Direct3D9GetAdapterIndex(display_index);
  if (result < 0)
    return std::unexpected(get_error());
  adapter_index = static_cast<std::uint32_t>(result);
  return {};
}

using id_direct3d_device9  = IDirect3DDevice9;
using id_direct3d_device11 = ID3D11Device;
using id_direct3d_device12 = ID3D12Device;

inline id_direct3d_device9* render_get_d3d9_device(SDL_Renderer* renderer)
{
  return SDL_RenderGetD3D9Device(renderer);
}
inline id_direct3d_device11* render_get_d3d11_device(SDL_Renderer* renderer)
{
  return SDL_RenderGetD3D11Device(renderer);
}
inline id_direct3d_device12* render_get_d3d12_device(SDL_Renderer* renderer)
{
  return SDL_RenderGetD3D12Device(renderer);
}

inline std::expected<void, std::string> dx_gi_get_output_info(const std::uint32_t display_index, std::int32_t& adapter_index, std::int32_t& output_index)
{
  if (SDL_DXGIGetOutputInfo(display_index, &adapter_index, &output_index) < 0)
    return std::unexpected(get_error());
  return {};
}
#endif

// Linux-specific functions
#ifdef SDL_PLATFORM_LINUX
inline std::expected<void, std::string> set_linux_thread_priority(const std::int64_t thread_id, const int priority)
{
  if (SDL_SetLinuxThreadPriority(thread_id, priority) < 0)
    return std::unexpected(get_error());
  return {};
}
inline std::expected<void, std::string> set_linux_thread_priority_and_policy(const std::int64_t thread_id, const int sdl_priority, const int sched_policy)
{
  if (SDL_SetLinuxThreadPriorityAndPolicy(thread_id, sdl_priority, sched_policy) < 0)
    return std::unexpected(get_error());
  return {};
}
#endif

// iOS-specific functions
#ifdef SDL_PLATFORM_IOS
inline void on_application_did_change_status_bar_orientation()
{
  SDL_OnApplicationDidChangeStatusBarOrientation();
}
#endif

// Android-specific functions
#ifdef SDL_PLATFORM_ANDROID
inline void* android_get_jni_env()
{
  return SDL_AndroidGetJNIEnv();
}
inline void* android_get_activity()
{
  return SDL_AndroidGetActivity();
}
inline int android_get_sdk_version()
{
  return SDL_GetAndroidSDKVersion();
}
inline bool is_android_tv()
{
  return SDL_IsAndroidTV() == SDL_TRUE;
}
inline bool is_chromebook()
{
  return SDL_IsChromebook() == SDL_TRUE;
}
inline bool is_dex_mode()
{
  return SDL_IsDeXMode() == SDL_TRUE;
}
inline void android_back_button()
{
  SDL_AndroidBackButton();
}

enum class android_external_storage_state
{
  read  = SDL_ANDROID_EXTERNAL_STORAGE_READ ,
  write = SDL_ANDROID_EXTERNAL_STORAGE_WRITE
};

[[nodiscard]]
inline std::string android_get_internal_storage_path()
{
  const auto result = SDL_AndroidGetInternalStoragePath();
  return result ? result : "";
}
[[nodiscard]]
inline std::int32_t android_get_external_storage_state()
{
  return SDL_AndroidGetExternalStorageState();
}
[[nodiscard]]
inline std::string android_get_external_storage_path()
{
  const auto result = SDL_AndroidGetExternalStoragePath();
  return result ? result : "";
}

inline std::expected<void, std::string> android_request_permission(const std::string& permission)
{
  if (SDL_AndroidRequestPermission(permission.c_str()) == SDL_FALSE)
    return std::unexpected(get_error());
  return {};
}

inline int android_show_toast(const std::string& message, const int duration, const int gravity, const int xoffset, const int yoffset)
{
  return SDL_AndroidShowToast(message.c_str(), duration, gravity, xoffset, yoffset);
}

inline std::expected<void, std::string> android_send_message(const std::uint32_t command, const int param)
{
  if (SDL_AndroidSendMessage(command, param) < 0)
    return std::unexpected(get_error());
  return {};
}
#endif

// WinRT-specific functions
#ifdef SDL_PLATFORM_WINRT
enum class win_rt_device_family
{
  unknown = SDL_WINRT_DEVICEFAMILY_UNKNOWN,
  desktop = SDL_WINRT_DEVICEFAMILY_DESKTOP,
  mobile  = SDL_WINRT_DEVICEFAMILY_MOBILE,
  xbox    = SDL_WINRT_DEVICEFAMILY_XBOX
};

[[nodiscard]]
inline win_rt_device_family win_rt_get_device_family()
{
  return static_cast<win_rt_device_family>(SDL_WinRTGetDeviceFamily());
}
#endif

// General platform detection
[[nodiscard]]
inline bool is_tablet()
{
  return SDL_IsTablet() == SDL_TRUE;
}
}
