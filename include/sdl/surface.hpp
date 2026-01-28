#pragma once

#include <array>
#include <cstdint>
#include <expected>
#include <memory>
#include <string>

#include <SDL_surface.h>

#include <sdl/blend_mode.hpp>
#include <sdl/error.hpp>
#include <sdl/pixels.hpp>
#include <sdl/rect.hpp>
#include <sdl/rwops.hpp>

namespace sdl
{
using native_surface = SDL_Surface;

// Surface creation functions
[[nodiscard]]
inline std::expected<SDL_Surface*, std::string> create_rgb_surface(
  const std::array<std::int32_t, 2>& size,
  const std::int32_t                  depth,
  const std::uint32_t                 r_mask,
  const std::uint32_t                 g_mask,
  const std::uint32_t                 b_mask,
  const std::uint32_t                 a_mask,
  const std::uint32_t                 flags = 0)
{
  const auto result = SDL_CreateRGBSurface(flags, size[0], size[1], depth, r_mask, g_mask, b_mask, a_mask);
  if (!result)
    return std::unexpected(get_error());
  return result;
}

[[nodiscard]]
inline std::expected<SDL_Surface*, std::string> create_rgb_surface_with_format(
  const std::array<std::int32_t, 2>& size,
  const std::int32_t                  depth,
  const std::uint32_t                 format,
  const std::uint32_t                 flags = 0)
{
  const auto result = SDL_CreateRGBSurfaceWithFormat(flags, size[0], size[1], depth, format);
  if (!result)
    return std::unexpected(get_error());
  return result;
}

[[nodiscard]]
inline std::expected<SDL_Surface*, std::string> create_rgb_surface_from(
  void*                               pixels,
  const std::array<std::int32_t, 2>&  size,
  const std::int32_t                  depth,
  const std::int32_t                  pitch,
  const std::uint32_t                 r_mask,
  const std::uint32_t                 g_mask,
  const std::uint32_t                 b_mask,
  const std::uint32_t                 a_mask)
{
  const auto result = SDL_CreateRGBSurfaceFrom(pixels, size[0], size[1], depth, pitch, r_mask, g_mask, b_mask, a_mask);
  if (!result)
    return std::unexpected(get_error());
  return result;
}

[[nodiscard]]
inline std::expected<SDL_Surface*, std::string> create_rgb_surface_with_format_from(
  void*                               pixels,
  const std::array<std::int32_t, 2>&  size,
  const std::int32_t                  depth,
  const std::int32_t                  pitch,
  const std::uint32_t                 format)
{
  const auto result = SDL_CreateRGBSurfaceWithFormatFrom(pixels, size[0], size[1], depth, pitch, format);
  if (!result)
    return std::unexpected(get_error());
  return result;
}

inline void free_surface(SDL_Surface* surface)
{
  SDL_FreeSurface(surface);
}

// Surface palette functions
inline std::expected<void, std::string> set_surface_palette(SDL_Surface* surface, SDL_Palette* palette)
{
  if (SDL_SetSurfacePalette(surface, palette) < 0)
    return std::unexpected(get_error());
  return {};
}

// Surface locking functions
inline std::expected<void, std::string> lock_surface(SDL_Surface* surface)
{
  if (SDL_LockSurface(surface) < 0)
    return std::unexpected(get_error());
  return {};
}

inline void unlock_surface(SDL_Surface* surface)
{
  SDL_UnlockSurface(surface);
}

// Surface loading/saving functions
[[nodiscard]]
inline std::expected<SDL_Surface*, std::string> load_bmp_rw(SDL_RWops* src, const bool free_src)
{
  const auto result = SDL_LoadBMP_RW(src, free_src ? 1 : 0);
  if (!result)
    return std::unexpected(get_error());
  return result;
}

[[nodiscard]]
inline std::expected<SDL_Surface*, std::string> load_bmp(const std::string& file)
{
  return load_bmp_rw(SDL_RWFromFile(file.c_str(), "rb"), true);
}

inline std::expected<void, std::string> save_bmp_rw(SDL_Surface* surface, SDL_RWops* dst, const bool free_dst)
{
  if (SDL_SaveBMP_RW(surface, dst, free_dst ? 1 : 0) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> save_bmp(SDL_Surface* surface, const std::string& file)
{
  return save_bmp_rw(surface, SDL_RWFromFile(file.c_str(), "wb"), true);
}

// Surface RLE functions
inline std::expected<void, std::string> set_surface_rle(SDL_Surface* surface, const bool enabled)
{
  if (SDL_SetSurfaceRLE(surface, enabled ? 1 : 0) < 0)
    return std::unexpected(get_error());
  return {};
}

inline bool has_surface_rle(SDL_Surface* surface)
{
  return SDL_HasSurfaceRLE(surface) == SDL_TRUE;
}

// Surface color key functions
inline std::expected<void, std::string> set_color_key(SDL_Surface* surface, const bool enabled, const std::uint32_t key)
{
  if (SDL_SetColorKey(surface, enabled ? SDL_TRUE : SDL_FALSE, key) < 0)
    return std::unexpected(get_error());
  return {};
}

inline bool has_color_key(SDL_Surface* surface)
{
  return SDL_HasColorKey(surface) == SDL_TRUE;
}

[[nodiscard]]
inline std::expected<std::uint32_t, std::string> get_color_key(SDL_Surface* surface)
{
  std::uint32_t key;
  if (SDL_GetColorKey(surface, &key) < 0)
    return std::unexpected(get_error());
  return key;
}

// Surface color mod functions
inline std::expected<void, std::string> set_surface_color_mod(SDL_Surface* surface, const std::uint8_t r, const std::uint8_t g, const std::uint8_t b)
{
  if (SDL_SetSurfaceColorMod(surface, r, g, b) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline std::expected<std::array<std::uint8_t, 3>, std::string> get_surface_color_mod(SDL_Surface* surface)
{
  std::array<std::uint8_t, 3> rgb;
  if (SDL_GetSurfaceColorMod(surface, &rgb[0], &rgb[1], &rgb[2]) < 0)
    return std::unexpected(get_error());
  return rgb;
}

inline std::expected<void, std::string> set_surface_alpha_mod(SDL_Surface* surface, const std::uint8_t alpha)
{
  if (SDL_SetSurfaceAlphaMod(surface, alpha) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline std::expected<std::uint8_t, std::string> get_surface_alpha_mod(SDL_Surface* surface)
{
  std::uint8_t alpha;
  if (SDL_GetSurfaceAlphaMod(surface, &alpha) < 0)
    return std::unexpected(get_error());
  return alpha;
}

inline std::expected<void, std::string> set_surface_blend_mode(SDL_Surface* surface, const blend_mode mode)
{
  if (SDL_SetSurfaceBlendMode(surface, static_cast<SDL_BlendMode>(mode)) < 0)
    return std::unexpected(get_error());
  return {};
}

[[nodiscard]]
inline std::expected<blend_mode, std::string> get_surface_blend_mode(SDL_Surface* surface)
{
  SDL_BlendMode mode;
  if (SDL_GetSurfaceBlendMode(surface, &mode) < 0)
    return std::unexpected(get_error());
  return static_cast<blend_mode>(mode);
}

// Surface clipping functions
inline bool set_clip_rect(SDL_Surface* surface, const rectangle<std::int32_t>* rect)
{
  return SDL_SetClipRect(surface, reinterpret_cast<const SDL_Rect*>(rect)) == SDL_TRUE;
}

inline rectangle<std::int32_t> get_clip_rect(SDL_Surface* surface)
{
  rectangle<std::int32_t> rect;
  SDL_GetClipRect(surface, reinterpret_cast<SDL_Rect*>(&rect));
  return rect;
}

// Surface duplication and conversion
[[nodiscard]]
inline std::expected<SDL_Surface*, std::string> duplicate_surface(SDL_Surface* surface)
{
  const auto result = SDL_DuplicateSurface(surface);
  if (!result)
    return std::unexpected(get_error());
  return result;
}

[[nodiscard]]
inline std::expected<SDL_Surface*, std::string> convert_surface(SDL_Surface* surface, const SDL_PixelFormat* format)
{
  const auto result = SDL_ConvertSurface(surface, format, 0);
  if (!result)
    return std::unexpected(get_error());
  return result;
}

[[nodiscard]]
inline std::expected<SDL_Surface*, std::string> convert_surface_format(SDL_Surface* surface, const std::uint32_t pixel_format)
{
  const auto result = SDL_ConvertSurfaceFormat(surface, pixel_format, 0);
  if (!result)
    return std::unexpected(get_error());
  return result;
}

// Surface pixel conversion
inline std::expected<void, std::string> convert_pixels(
  const std::array<std::int32_t, 2>& size,
  const std::uint32_t                src_format,
  const void*                        src,
  const std::int32_t                 src_pitch,
  const std::uint32_t                dst_format,
  void*                              dst,
  const std::int32_t                 dst_pitch)
{
  if (SDL_ConvertPixels(size[0], size[1], src_format, src, src_pitch, dst_format, dst, dst_pitch) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> premultiply_alpha(
  const std::array<std::int32_t, 2>& size,
  const std::uint32_t                src_format,
  const void*                        src,
  const std::int32_t                 src_pitch,
  const std::uint32_t                dst_format,
  void*                              dst,
  const std::int32_t                 dst_pitch)
{
  if (SDL_PremultiplyAlpha(size[0], size[1], src_format, src, src_pitch, dst_format, dst, dst_pitch) < 0)
    return std::unexpected(get_error());
  return {};
}

// Surface fill functions
inline std::expected<void, std::string> fill_rect(SDL_Surface* surface, const rectangle<std::int32_t>* rect, const std::uint32_t color)
{
  if (SDL_FillRect(surface, reinterpret_cast<const SDL_Rect*>(rect), color) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> fill_rects(SDL_Surface* surface, const rectangle<std::int32_t>* rects, const std::int32_t count, const std::uint32_t color)
{
  if (SDL_FillRects(surface, reinterpret_cast<const SDL_Rect*>(rects), count, color) < 0)
    return std::unexpected(get_error());
  return {};
}

// Surface blitting functions
inline std::expected<void, std::string> blit_surface(
  SDL_Surface*               src,
  const rectangle<std::int32_t>* src_rect,
  SDL_Surface*               dst,
  rectangle<std::int32_t>*       dst_rect)
{
  if (SDL_BlitSurface(src, reinterpret_cast<const SDL_Rect*>(src_rect), dst, reinterpret_cast<SDL_Rect*>(dst_rect)) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> upper_blit(
  SDL_Surface*               src,
  const rectangle<std::int32_t>* src_rect,
  SDL_Surface*               dst,
  rectangle<std::int32_t>*       dst_rect)
{
  if (SDL_UpperBlit(src, reinterpret_cast<const SDL_Rect*>(src_rect), dst, reinterpret_cast<SDL_Rect*>(dst_rect)) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> lower_blit(
  SDL_Surface*         src,
  rectangle<std::int32_t>* src_rect,
  SDL_Surface*         dst,
  rectangle<std::int32_t>* dst_rect)
{
  if (SDL_LowerBlit(src, reinterpret_cast<SDL_Rect*>(src_rect), dst, reinterpret_cast<SDL_Rect*>(dst_rect)) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> soft_stretch(
  SDL_Surface*               src,
  const rectangle<std::int32_t>* src_rect,
  SDL_Surface*               dst,
  const rectangle<std::int32_t>* dst_rect)
{
  if (SDL_SoftStretch(src, reinterpret_cast<const SDL_Rect*>(src_rect), dst, reinterpret_cast<const SDL_Rect*>(dst_rect)) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> soft_stretch_linear(
  SDL_Surface*               src,
  const rectangle<std::int32_t>* src_rect,
  SDL_Surface*               dst,
  const rectangle<std::int32_t>* dst_rect)
{
  if (SDL_SoftStretchLinear(src, reinterpret_cast<const SDL_Rect*>(src_rect), dst, reinterpret_cast<const SDL_Rect*>(dst_rect)) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> blit_scaled(
  SDL_Surface*               src,
  const rectangle<std::int32_t>* src_rect,
  SDL_Surface*               dst,
  rectangle<std::int32_t>*       dst_rect)
{
  if (SDL_BlitScaled(src, reinterpret_cast<const SDL_Rect*>(src_rect), dst, reinterpret_cast<SDL_Rect*>(dst_rect)) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> upper_blit_scaled(
  SDL_Surface*               src,
  const rectangle<std::int32_t>* src_rect,
  SDL_Surface*               dst,
  rectangle<std::int32_t>*       dst_rect)
{
  if (SDL_UpperBlitScaled(src, reinterpret_cast<const SDL_Rect*>(src_rect), dst, reinterpret_cast<SDL_Rect*>(dst_rect)) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void, std::string> lower_blit_scaled(
  SDL_Surface*         src,
  rectangle<std::int32_t>* src_rect,
  SDL_Surface*         dst,
  rectangle<std::int32_t>* dst_rect)
{
  if (SDL_LowerBlitScaled(src, reinterpret_cast<SDL_Rect*>(src_rect), dst, reinterpret_cast<SDL_Rect*>(dst_rect)) < 0)
    return std::unexpected(get_error());
  return {};
}

inline void set_yuv_conversion_mode(const SDL_YUV_CONVERSION_MODE mode)
{
  SDL_SetYUVConversionMode(mode);
}

[[nodiscard]]
inline SDL_YUV_CONVERSION_MODE get_yuv_conversion_mode()
{
  return SDL_GetYUVConversionMode();
}

[[nodiscard]]
inline SDL_YUV_CONVERSION_MODE get_yuv_conversion_mode_for_resolution(const std::int32_t width, const std::int32_t height)
{
  return SDL_GetYUVConversionModeForResolution(width, height);
}

// Conveniences.

class surface
{
public:
  surface() = default;
  
  explicit surface(SDL_Surface* native, const bool managed = true)
  : native_(native), managed_(managed)
  {
  }

  surface(const surface&  that) = delete;
  surface(      surface&& temp) noexcept
  : native_(temp.native_), managed_(temp.managed_)
  {
    temp.native_  = nullptr;
    temp.managed_ = false;
  }
  
  ~surface()
  {
    if (native_ && managed_)
      SDL_FreeSurface(native_);
  }
  
  surface& operator=(const surface&  that) = delete;
  surface& operator=(      surface&& temp) noexcept
  {
    if (this != &temp)
    {
      if (native_ && managed_)
        SDL_FreeSurface(native_);
      native_       = temp.native_;
      managed_      = temp.managed_;
      temp.native_  = nullptr;
      temp.managed_ = false;
    }
    return *this;
  }

  [[nodiscard]]
  SDL_Surface* native() const noexcept
  {
    return native_;
  }

  [[nodiscard]]
  bool is_managed() const noexcept
  {
    return managed_;
  }

  // Convenience methods
  std::expected<void, std::string> set_palette(SDL_Palette* palette) const
  {
    return set_surface_palette(native_, palette);
  }

  std::expected<void, std::string> lock() const
  {
    return lock_surface(native_);
  }

  void unlock() const
  {
    unlock_surface(native_);
  }

  std::expected<void, std::string> set_rle(const bool enabled) const
  {
    return set_surface_rle(native_, enabled);
  }

  [[nodiscard]]
  bool has_rle() const
  {
    return has_surface_rle(native_);
  }

  std::expected<void, std::string> set_color_key(const bool enabled, const std::uint32_t key) const
  {
    return sdl::set_color_key(native_, enabled, key);
  }

  [[nodiscard]]
  bool has_color_key() const
  {
    return sdl::has_color_key(native_);
  }

  [[nodiscard]]
  std::expected<std::uint32_t, std::string> get_color_key() const
  {
    return sdl::get_color_key(native_);
  }

  std::expected<void, std::string> set_color_mod(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b) const
  {
    return set_surface_color_mod(native_, r, g, b);
  }

  [[nodiscard]]
  std::expected<std::array<std::uint8_t, 3>, std::string> get_color_mod() const
  {
    return get_surface_color_mod(native_);
  }

  std::expected<void, std::string> set_alpha_mod(const std::uint8_t alpha) const
  {
    return set_surface_alpha_mod(native_, alpha);
  }

  [[nodiscard]]
  std::expected<std::uint8_t, std::string> get_alpha_mod() const
  {
    return get_surface_alpha_mod(native_);
  }

  std::expected<void, std::string> set_blend_mode(const blend_mode mode) const
  {
    return set_surface_blend_mode(native_, mode);
  }

  [[nodiscard]]
  std::expected<blend_mode, std::string> get_blend_mode() const
  {
    return get_surface_blend_mode(native_);
  }

  bool set_clip_rect(const rectangle<std::int32_t>* rect) const
  {
    return sdl::set_clip_rect(native_, rect);
  }

  [[nodiscard]]
  rectangle<std::int32_t> get_clip_rect() const
  {
    return sdl::get_clip_rect(native_);
  }

  [[nodiscard]]
  std::expected<SDL_Surface*, std::string> duplicate() const
  {
    return duplicate_surface(native_);
  }

  [[nodiscard]]
  std::expected<SDL_Surface*, std::string> convert(const SDL_PixelFormat* format) const
  {
    return convert_surface(native_, format);
  }

  [[nodiscard]]
  std::expected<SDL_Surface*, std::string> convert_format(const std::uint32_t pixel_format) const
  {
    return convert_surface_format(native_, pixel_format);
  }

  std::expected<void, std::string> fill_rect(const rectangle<std::int32_t>* rect, const std::uint32_t color) const
  {
    return sdl::fill_rect(native_, rect, color);
  }

  std::expected<void, std::string> blit(
    const rectangle<std::int32_t>* src_rect,
    SDL_Surface*                   dst,
    rectangle<std::int32_t>*       dst_rect) const
  {
    return blit_surface(native_, src_rect, dst, dst_rect);
  }

  std::expected<void, std::string> blit_scaled(
    const rectangle<std::int32_t>* src_rect,
    SDL_Surface*                   dst,
    rectangle<std::int32_t>*       dst_rect) const
  {
    return sdl::blit_scaled(native_, src_rect, dst, dst_rect);
  }

  std::expected<void, std::string> save_bmp(const std::string& file) const
  {
    return sdl::save_bmp(native_, file);
  }

private:
  SDL_Surface* native_  {};
  bool         managed_ {true};
};
}