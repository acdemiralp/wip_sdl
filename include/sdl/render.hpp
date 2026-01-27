#pragma once

#include <array>
#include <cstdint>
#include <expected>
#include <span>
#include <string>
#include <type_traits>
#include <vector>

#include <SDL_render.h>

#include <sdl/bitset_enum.hpp>
#include <sdl/blend_mode.hpp>
#include <sdl/error.hpp>
#include <sdl/pixels.hpp>
#include <sdl/rect.hpp>
#include <sdl/surface.hpp>
#include <sdl/video.hpp>

namespace sdl
{
// Renderer flags
enum class renderer_flags : std::uint32_t
{
  software       = SDL_RENDERER_SOFTWARE,
  accelerated    = SDL_RENDERER_ACCELERATED,
  present_vsync  = SDL_RENDERER_PRESENTVSYNC,
  target_texture = SDL_RENDERER_TARGETTEXTURE
};

template <>
struct is_bitset_enum<renderer_flags> : std::true_type {};

// Texture access
enum class texture_access
{
  static_access  = SDL_TEXTUREACCESS_STATIC,
  streaming      = SDL_TEXTUREACCESS_STREAMING,
  target         = SDL_TEXTUREACCESS_TARGET
};

// Texture modulate
enum class texture_modulate
{
  none  = SDL_TEXTUREMODULATE_NONE,
  color = SDL_TEXTUREMODULATE_COLOR,
  alpha = SDL_TEXTUREMODULATE_ALPHA
};

// Renderer flip
enum class renderer_flip : std::uint32_t
{
  none       = SDL_FLIP_NONE,
  horizontal = SDL_FLIP_HORIZONTAL,
  vertical   = SDL_FLIP_VERTICAL
};

template <>
struct is_bitset_enum<renderer_flip> : std::true_type {};

// Renderer info
struct renderer_info
{
  [[nodiscard]]
  static renderer_info from_native(const SDL_RendererInfo& native)
  {
    renderer_info result;
    result.name                     = native.name;
    result.flags                    = static_cast<renderer_flags>(native.flags);
    result.num_texture_formats      = native.num_texture_formats;
    for (std::uint32_t i = 0; i < native.num_texture_formats && i < 16; ++i)
      result.texture_formats[i] = native.texture_formats[i];
    result.max_texture_width  = native.max_texture_width;
    result.max_texture_height = native.max_texture_height;
    return result;
  }

  std::string                      name                 {};
  renderer_flags                   flags                {};
  std::uint32_t                    num_texture_formats  {};
  std::array<std::uint32_t, 16>    texture_formats      {};
  std::int32_t                     max_texture_width    {};
  std::int32_t                     max_texture_height   {};
};

using native_renderer = SDL_Renderer;
using native_texture  = SDL_Texture;

// Renderer functions
[[nodiscard]]
inline std::int32_t get_num_render_drivers()
{
  return SDL_GetNumRenderDrivers();
}

[[nodiscard]]
inline std::expected<renderer_info, std::string> get_render_driver_info(const std::int32_t index)
{
  SDL_RendererInfo info;
  if (SDL_GetRenderDriverInfo(index, &info) < 0)
    return std::unexpected(get_error());
  return renderer_info::from_native(info);
}

inline std::expected<void, std::string> create_window_and_renderer(
  const std::array<std::int32_t, 2>& size,
  const std::uint32_t                window_flags,
  SDL_Window**                       window,
  SDL_Renderer**                     renderer)
{
  if (SDL_CreateWindowAndRenderer(size[0], size[1], window_flags, window, renderer) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline std::expected<SDL_Renderer*, std::string> create_renderer(
  SDL_Window*        window,
  const std::int32_t index = -1,
  renderer_flags     flags = renderer_flags::accelerated)
{
  const auto result = SDL_CreateRenderer(window, index, static_cast<std::uint32_t>(flags));
  if (!result)
    return std::unexpected(get_error());
  return result;
}

[[nodiscard]]
inline std::expected<SDL_Renderer*, std::string> create_software_renderer(SDL_Surface* surface)
{
  const auto result = SDL_CreateSoftwareRenderer(surface);
  if (!result)
    return std::unexpected(get_error());
  return result;
}

[[nodiscard]]
inline SDL_Renderer* get_renderer(SDL_Window* window)
{
  return SDL_GetRenderer(window);
}

[[nodiscard]]
inline SDL_Window* render_get_window(SDL_Renderer* renderer)
{
  return SDL_RenderGetWindow(renderer);
}

[[nodiscard]]
inline std::expected<renderer_info, std::string> get_renderer_info(SDL_Renderer* renderer)
{
  SDL_RendererInfo info;
  if (SDL_GetRendererInfo(renderer, &info) < 0)
    return std::unexpected(get_error());
  return renderer_info::from_native(info);
}

[[nodiscard]]
inline std::expected<std::array<std::int32_t, 2>, std::string> get_renderer_output_size(SDL_Renderer* renderer)
{
  std::array<std::int32_t, 2> size;
  if (SDL_GetRendererOutputSize(renderer, &size[0], &size[1]) < 0)
    return std::unexpected(get_error());
  return size;
}

// Texture functions
[[nodiscard]]
inline std::expected<SDL_Texture*, std::string> create_texture(
  SDL_Renderer*      renderer,
  const std::uint32_t format,
  const texture_access access,
  const std::array<std::int32_t, 2>& size)
{
  const auto result = SDL_CreateTexture(renderer, format, static_cast<int>(access), size[0], size[1]);
  if (!result)
    return std::unexpected(get_error());
  return result;
}

[[nodiscard]]
inline std::expected<SDL_Texture*, std::string> create_texture_from_surface(SDL_Renderer* renderer, SDL_Surface* surface)
{
  const auto result = SDL_CreateTextureFromSurface(renderer, surface);
  if (!result)
    return std::unexpected(get_error());
  return result;
}

[[nodiscard]]
inline std::expected<std::tuple<std::uint32_t, texture_access, std::array<std::int32_t, 2>>, std::string> query_texture(SDL_Texture* texture)
{
  std::uint32_t               format;
  int                         access;
  std::array<std::int32_t, 2> size;
  if (SDL_QueryTexture(texture, &format, &access, &size[0], &size[1]) < 0)
    return std::unexpected(get_error());
  return std::make_tuple(format, static_cast<texture_access>(access), size);
}

inline std::expected<void, std::string> set_texture_color_mod(SDL_Texture* texture, const std::uint8_t r, const std::uint8_t g, const std::uint8_t b)
{
  if (SDL_SetTextureColorMod(texture, r, g, b) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline std::expected<std::array<std::uint8_t, 3>, std::string> get_texture_color_mod(SDL_Texture* texture)
{
  std::array<std::uint8_t, 3> rgb;
  if (SDL_GetTextureColorMod(texture, &rgb[0], &rgb[1], &rgb[2]) < 0)
    return std::unexpected(get_error());
  return rgb;
}

inline std::expected<void, std::string> set_texture_alpha_mod(SDL_Texture* texture, const std::uint8_t alpha)
{
  if (SDL_SetTextureAlphaMod(texture, alpha) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline std::expected<std::uint8_t, std::string> get_texture_alpha_mod(SDL_Texture* texture)
{
  std::uint8_t alpha;
  if (SDL_GetTextureAlphaMod(texture, &alpha) < 0)
    return std::unexpected(get_error());
  return alpha;
}

inline std::expected<void, std::string> set_texture_blend_mode(SDL_Texture* texture, const blend_mode mode)
{
  if (SDL_SetTextureBlendMode(texture, static_cast<SDL_BlendMode>(mode)) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline std::expected<blend_mode, std::string> get_texture_blend_mode(SDL_Texture* texture)
{
  SDL_BlendMode mode;
  if (SDL_GetTextureBlendMode(texture, &mode) < 0)
    return std::unexpected(get_error());
  return static_cast<blend_mode>(mode);
}

inline std::expected<void, std::string> set_texture_scale_mode(SDL_Texture* texture, const SDL_ScaleMode mode)
{
  if (SDL_SetTextureScaleMode(texture, mode) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline std::expected<SDL_ScaleMode, std::string> get_texture_scale_mode(SDL_Texture* texture)
{
  SDL_ScaleMode mode;
  if (SDL_GetTextureScaleMode(texture, &mode) < 0)
    return std::unexpected(get_error());
  return mode;
}

inline std::expected<void, std::string> set_texture_user_data(SDL_Texture* texture, void* user_data)
{
  if (SDL_SetTextureUserData(texture, user_data) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline void* get_texture_user_data(SDL_Texture* texture)
{
  return SDL_GetTextureUserData(texture);
}

inline std::expected<void, std::string> update_texture(
  SDL_Texture*                    texture,
  const rectangle<std::int32_t>*  rect,
  const void*                     pixels,
  const std::int32_t              pitch)
{
  if (SDL_UpdateTexture(texture, reinterpret_cast<const SDL_Rect*>(rect), pixels, pitch) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> update_yuv_texture(
  SDL_Texture*                    texture,
  const rectangle<std::int32_t>*  rect,
  const std::uint8_t*             y_plane,
  const std::int32_t              y_pitch,
  const std::uint8_t*             u_plane,
  const std::int32_t              u_pitch,
  const std::uint8_t*             v_plane,
  const std::int32_t              v_pitch)
{
  if (SDL_UpdateYUVTexture(texture, reinterpret_cast<const SDL_Rect*>(rect), y_plane, y_pitch, u_plane, u_pitch, v_plane, v_pitch) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> update_nv_texture(
  SDL_Texture*                    texture,
  const rectangle<std::int32_t>*  rect,
  const std::uint8_t*             y_plane,
  const std::int32_t              y_pitch,
  const std::uint8_t*             uv_plane,
  const std::int32_t              uv_pitch)
{
  if (SDL_UpdateNVTexture(texture, reinterpret_cast<const SDL_Rect*>(rect), y_plane, y_pitch, uv_plane, uv_pitch) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> lock_texture(
  SDL_Texture*                    texture,
  const rectangle<std::int32_t>*  rect,
  void**                          pixels,
  int*                            pitch)
{
  if (SDL_LockTexture(texture, reinterpret_cast<const SDL_Rect*>(rect), pixels, pitch) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> lock_texture_to_surface(
  SDL_Texture*                    texture,
  const rectangle<std::int32_t>*  rect,
  SDL_Surface**                   surface)
{
  if (SDL_LockTextureToSurface(texture, reinterpret_cast<const SDL_Rect*>(rect), surface) < 0)
    return std::unexpected(get_error());
  return {};
}

inline void unlock_texture(SDL_Texture* texture)
{
  SDL_UnlockTexture(texture);
}

inline void destroy_texture(SDL_Texture* texture)
{
  SDL_DestroyTexture(texture);
}

inline void destroy_renderer(SDL_Renderer* renderer)
{
  SDL_DestroyRenderer(renderer);
}

// Render target functions
[[nodiscard]]
inline bool render_target_supported(SDL_Renderer* renderer)
{
  return SDL_RenderTargetSupported(renderer) == SDL_TRUE;
}

inline std::expected<void, std::string> set_render_target(SDL_Renderer* renderer, SDL_Texture* texture)
{
  if (SDL_SetRenderTarget(renderer, texture) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline SDL_Texture* get_render_target(SDL_Renderer* renderer)
{
  return SDL_GetRenderTarget(renderer);
}

// Render logical size functions
inline std::expected<void, std::string> render_set_logical_size(SDL_Renderer* renderer, const std::array<std::int32_t, 2>& size)
{
  if (SDL_RenderSetLogicalSize(renderer, size[0], size[1]) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::array<std::int32_t, 2> render_get_logical_size(SDL_Renderer* renderer)
{
  std::array<std::int32_t, 2> size;
  SDL_RenderGetLogicalSize(renderer, &size[0], &size[1]);
  return size;
}

inline std::expected<void, std::string> render_set_integer_scale(SDL_Renderer* renderer, const bool enable)
{
  if (SDL_RenderSetIntegerScale(renderer, enable ? SDL_TRUE : SDL_FALSE) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline bool render_get_integer_scale(SDL_Renderer* renderer)
{
  return SDL_RenderGetIntegerScale(renderer) == SDL_TRUE;
}

// Viewport and clipping
inline std::expected<void, std::string> render_set_viewport(SDL_Renderer* renderer, const rectangle<std::int32_t>* rect)
{
  if (SDL_RenderSetViewport(renderer, reinterpret_cast<const SDL_Rect*>(rect)) < 0)
    return std::unexpected(get_error());
  return {};
}

inline rectangle<std::int32_t> render_get_viewport(SDL_Renderer* renderer)
{
  rectangle<std::int32_t> rect;
  SDL_RenderGetViewport(renderer, reinterpret_cast<SDL_Rect*>(&rect));
  return rect;
}

inline std::expected<void, std::string> render_set_clip_rect(SDL_Renderer* renderer, const rectangle<std::int32_t>* rect)
{
  if (SDL_RenderSetClipRect(renderer, reinterpret_cast<const SDL_Rect*>(rect)) < 0)
    return std::unexpected(get_error());
  return {};
}

inline rectangle<std::int32_t> render_get_clip_rect(SDL_Renderer* renderer)
{
  rectangle<std::int32_t> rect;
  SDL_RenderGetClipRect(renderer, reinterpret_cast<SDL_Rect*>(&rect));
  return rect;
}

[[nodiscard]]
inline bool render_is_clip_enabled(SDL_Renderer* renderer)
{
  return SDL_RenderIsClipEnabled(renderer) == SDL_TRUE;
}

// Scale
inline std::expected<void, std::string> render_set_scale(SDL_Renderer* renderer, const float scale_x, const float scale_y)
{
  if (SDL_RenderSetScale(renderer, scale_x, scale_y) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::array<float, 2> render_get_scale(SDL_Renderer* renderer)
{
  std::array<float, 2> scale;
  SDL_RenderGetScale(renderer, &scale[0], &scale[1]);
  return scale;
}

inline void render_window_to_logical(SDL_Renderer* renderer, const std::int32_t window_x, const std::int32_t window_y, float& logical_x, float& logical_y)
{
  SDL_RenderWindowToLogical(renderer, window_x, window_y, &logical_x, &logical_y);
}

inline void render_logical_to_window(SDL_Renderer* renderer, const float logical_x, const float logical_y, std::int32_t& window_x, std::int32_t& window_y)
{
  SDL_RenderLogicalToWindow(renderer, logical_x, logical_y, &window_x, &window_y);
}

// Drawing color
inline std::expected<void, std::string> set_render_draw_color(SDL_Renderer* renderer, const std::uint8_t r, const std::uint8_t g, const std::uint8_t b, const std::uint8_t a)
{
  if (SDL_SetRenderDrawColor(renderer, r, g, b, a) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline std::expected<std::array<std::uint8_t, 4>, std::string> get_render_draw_color(SDL_Renderer* renderer)
{
  std::array<std::uint8_t, 4> rgba;
  if (SDL_GetRenderDrawColor(renderer, &rgba[0], &rgba[1], &rgba[2], &rgba[3]) < 0)
    return std::unexpected(get_error());
  return rgba;
}

inline std::expected<void, std::string> set_render_draw_blend_mode(SDL_Renderer* renderer, const blend_mode mode)
{
  if (SDL_SetRenderDrawBlendMode(renderer, static_cast<SDL_BlendMode>(mode)) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline std::expected<blend_mode, std::string> get_render_draw_blend_mode(SDL_Renderer* renderer)
{
  SDL_BlendMode mode;
  if (SDL_GetRenderDrawBlendMode(renderer, &mode) < 0)
    return std::unexpected(get_error());
  return static_cast<blend_mode>(mode);
}

// Drawing primitives
inline std::expected<void, std::string> render_clear(SDL_Renderer* renderer)
{
  if (SDL_RenderClear(renderer) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> render_draw_point(SDL_Renderer* renderer, const std::array<std::int32_t, 2>& point)
{
  if (SDL_RenderDrawPoint(renderer, point[0], point[1]) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> render_draw_points(SDL_Renderer* renderer, const SDL_Point* points, const std::int32_t count)
{
  if (SDL_RenderDrawPoints(renderer, points, count) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> render_draw_line(SDL_Renderer* renderer, const std::array<std::int32_t, 2>& p1, const std::array<std::int32_t, 2>& p2)
{
  if (SDL_RenderDrawLine(renderer, p1[0], p1[1], p2[0], p2[1]) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> render_draw_lines(SDL_Renderer* renderer, const SDL_Point* points, const std::int32_t count)
{
  if (SDL_RenderDrawLines(renderer, points, count) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> render_draw_rect(SDL_Renderer* renderer, const rectangle<std::int32_t>* rect)
{
  if (SDL_RenderDrawRect(renderer, reinterpret_cast<const SDL_Rect*>(rect)) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> render_draw_rects(SDL_Renderer* renderer, const rectangle<std::int32_t>* rects, const std::int32_t count)
{
  if (SDL_RenderDrawRects(renderer, reinterpret_cast<const SDL_Rect*>(rects), count) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> render_fill_rect(SDL_Renderer* renderer, const rectangle<std::int32_t>* rect)
{
  if (SDL_RenderFillRect(renderer, reinterpret_cast<const SDL_Rect*>(rect)) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> render_fill_rects(SDL_Renderer* renderer, const rectangle<std::int32_t>* rects, const std::int32_t count)
{
  if (SDL_RenderFillRects(renderer, reinterpret_cast<const SDL_Rect*>(rects), count) < 0)
    return std::unexpected(get_error());
  return {};
}

// Texture rendering
inline std::expected<void, std::string> render_copy(
  SDL_Renderer*                   renderer,
  SDL_Texture*                    texture,
  const rectangle<std::int32_t>*  src_rect,
  const rectangle<std::int32_t>*  dst_rect)
{
  if (SDL_RenderCopy(renderer, texture, reinterpret_cast<const SDL_Rect*>(src_rect), reinterpret_cast<const SDL_Rect*>(dst_rect)) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> render_copy_ex(
  SDL_Renderer*                   renderer,
  SDL_Texture*                    texture,
  const rectangle<std::int32_t>*  src_rect,
  const rectangle<std::int32_t>*  dst_rect,
  const double                    angle,
  const SDL_Point*                center,
  const renderer_flip             flip)
{
  if (SDL_RenderCopyEx(renderer, texture, reinterpret_cast<const SDL_Rect*>(src_rect), reinterpret_cast<const SDL_Rect*>(dst_rect), angle, center, static_cast<SDL_RendererFlip>(flip)) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> render_draw_point_f(SDL_Renderer* renderer, const float x, const float y)
{
  if (SDL_RenderDrawPointF(renderer, x, y) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> render_draw_points_f(SDL_Renderer* renderer, const SDL_FPoint* points, const std::int32_t count)
{
  if (SDL_RenderDrawPointsF(renderer, points, count) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> render_draw_line_f(SDL_Renderer* renderer, const float x1, const float y1, const float x2, const float y2)
{
  if (SDL_RenderDrawLineF(renderer, x1, y1, x2, y2) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> render_draw_lines_f(SDL_Renderer* renderer, const SDL_FPoint* points, const std::int32_t count)
{
  if (SDL_RenderDrawLinesF(renderer, points, count) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> render_draw_rect_f(SDL_Renderer* renderer, const SDL_FRect* rect)
{
  if (SDL_RenderDrawRectF(renderer, rect) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> render_draw_rects_f(SDL_Renderer* renderer, const SDL_FRect* rects, const std::int32_t count)
{
  if (SDL_RenderDrawRectsF(renderer, rects, count) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> render_fill_rect_f(SDL_Renderer* renderer, const SDL_FRect* rect)
{
  if (SDL_RenderFillRectF(renderer, rect) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> render_fill_rects_f(SDL_Renderer* renderer, const SDL_FRect* rects, const std::int32_t count)
{
  if (SDL_RenderFillRectsF(renderer, rects, count) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> render_copy_f(
  SDL_Renderer*    renderer,
  SDL_Texture*     texture,
  const SDL_Rect*  src_rect,
  const SDL_FRect* dst_rect)
{
  if (SDL_RenderCopyF(renderer, texture, src_rect, dst_rect) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> render_copy_ex_f(
  SDL_Renderer*         renderer,
  SDL_Texture*          texture,
  const SDL_Rect*       src_rect,
  const SDL_FRect*      dst_rect,
  const double          angle,
  const SDL_FPoint*     center,
  const renderer_flip   flip)
{
  if (SDL_RenderCopyExF(renderer, texture, src_rect, dst_rect, angle, center, static_cast<SDL_RendererFlip>(flip)) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> render_geometry(
  SDL_Renderer*       renderer,
  SDL_Texture*        texture,
  const SDL_Vertex*   vertices,
  const int           num_vertices,
  const int*          indices,
  const int           num_indices)
{
  if (SDL_RenderGeometry(renderer, texture, vertices, num_vertices, indices, num_indices) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> render_geometry_raw(
  SDL_Renderer*        renderer,
  SDL_Texture*         texture,
  const float*         xy,
  const int            xy_stride,
  const SDL_Color*     color,
  const int            color_stride,
  const float*         uv,
  const int            uv_stride,
  const int            num_vertices,
  const void*          indices,
  const int            num_indices,
  const int            size_indices)
{
  if (SDL_RenderGeometryRaw(renderer, texture, xy, xy_stride, color, color_stride, uv, uv_stride, num_vertices, indices, num_indices, size_indices) < 0)
    return std::unexpected(get_error());
  return {};
}

// Read pixels
inline std::expected<void, std::string> render_read_pixels(
  SDL_Renderer*                   renderer,
  const rectangle<std::int32_t>*  rect,
  const std::uint32_t             format,
  void*                           pixels,
  const std::int32_t              pitch)
{
  if (SDL_RenderReadPixels(renderer, reinterpret_cast<const SDL_Rect*>(rect), format, pixels, pitch) < 0)
    return std::unexpected(get_error());
  return {};
}

// Present
inline void render_present(SDL_Renderer* renderer)
{
  SDL_RenderPresent(renderer);
}

// VSync
inline std::expected<void, std::string> render_set_v_sync(SDL_Renderer* renderer, const int vsync)
{
  if (SDL_RenderSetVSync(renderer, vsync) < 0)
    return std::unexpected(get_error());
  return {};
}

// Renderer and texture RAII wrappers
class texture
{
public:
  texture() = default;
  
  explicit texture(SDL_Texture* native, const bool managed = true)
  : native_(native), managed_(managed)
  {
  }

  texture(const texture&  that) = delete;
  texture(      texture&& temp) noexcept
  : native_(temp.native_), managed_(temp.managed_)
  {
    temp.native_  = nullptr;
    temp.managed_ = false;
  }
  
  ~texture()
  {
    if (native_ && managed_)
      SDL_DestroyTexture(native_);
  }
  
  texture& operator=(const texture&  that) = delete;
  texture& operator=(      texture&& temp) noexcept
  {
    if (this != &temp)
    {
      if (native_ && managed_)
        SDL_DestroyTexture(native_);
      native_       = temp.native_;
      managed_      = temp.managed_;
      temp.native_  = nullptr;
      temp.managed_ = false;
    }
    return *this;
  }

  [[nodiscard]]
  SDL_Texture* native() const noexcept
  {
    return native_;
  }

  [[nodiscard]]
  bool is_managed() const noexcept
  {
    return managed_;
  }

private:
  SDL_Texture* native_  {};
  bool         managed_ {true};
};

class renderer
{
public:
  renderer() = default;
  
  explicit renderer(SDL_Renderer* native, const bool managed = true)
  : native_(native), managed_(managed)
  {
  }

  renderer(const renderer&  that) = delete;
  renderer(      renderer&& temp) noexcept
  : native_(temp.native_), managed_(temp.managed_)
  {
    temp.native_  = nullptr;
    temp.managed_ = false;
  }
  
  ~renderer()
  {
    if (native_ && managed_)
      SDL_DestroyRenderer(native_);
  }
  
  renderer& operator=(const renderer&  that) = delete;
  renderer& operator=(      renderer&& temp) noexcept
  {
    if (this != &temp)
    {
      if (native_ && managed_)
        SDL_DestroyRenderer(native_);
      native_       = temp.native_;
      managed_      = temp.managed_;
      temp.native_  = nullptr;
      temp.managed_ = false;
    }
    return *this;
  }

  [[nodiscard]]
  SDL_Renderer* native() const noexcept
  {
    return native_;
  }

  [[nodiscard]]
  bool is_managed() const noexcept
  {
    return managed_;
  }

private:
  SDL_Renderer* native_  {};
  bool          managed_ {true};
};
}
