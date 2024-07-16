#pragma once

#include <array>
#include <cstdint>
#include <expected>
#include <span>
#include <string>
#include <variant>

#include <SDL_pixels.h>

#include <sdl/error.hpp>

namespace sdl
{
inline constexpr auto alpha_opaque      = SDL_ALPHA_OPAQUE;
inline constexpr auto alpha_transparent = SDL_ALPHA_TRANSPARENT;

enum class pixel_type : std::uint8_t
{
  unknown    = SDL_PIXELTYPE_UNKNOWN   ,
  index1     = SDL_PIXELTYPE_INDEX1    ,
  index4     = SDL_PIXELTYPE_INDEX4    ,
  index8     = SDL_PIXELTYPE_INDEX8    ,
  packed8    = SDL_PIXELTYPE_PACKED8   ,
  packed16   = SDL_PIXELTYPE_PACKED16  ,
  packed32   = SDL_PIXELTYPE_PACKED32  ,
  array_u8   = SDL_PIXELTYPE_ARRAYU8   ,
  array_u16  = SDL_PIXELTYPE_ARRAYU16  ,
  array_u32  = SDL_PIXELTYPE_ARRAYU32  ,
  array_f16  = SDL_PIXELTYPE_ARRAYF16  ,
  array_f32  = SDL_PIXELTYPE_ARRAYF32
};
enum class bitmap_order : std::uint8_t
{
  none       = SDL_BITMAPORDER_NONE    ,
  _4321      = SDL_BITMAPORDER_4321    ,
  _1234      = SDL_BITMAPORDER_1234
};
enum class packed_order : std::uint8_t
{
  none       = SDL_PACKEDORDER_NONE    ,
  xrgb       = SDL_PACKEDORDER_XRGB    ,
  rgbx       = SDL_PACKEDORDER_RGBX    ,
  argb       = SDL_PACKEDORDER_ARGB    ,
  rgba       = SDL_PACKEDORDER_RGBA    ,
  xbgr       = SDL_PACKEDORDER_XBGR    ,
  bgrx       = SDL_PACKEDORDER_BGRX    ,
  abgr       = SDL_PACKEDORDER_ABGR    ,
  bgra       = SDL_PACKEDORDER_BGRA
};
enum class array_order : std::uint8_t
{
  none       = SDL_ARRAYORDER_NONE     ,
  rgb        = SDL_ARRAYORDER_RGB      ,
  rgba       = SDL_ARRAYORDER_RGBA     ,
  argb       = SDL_ARRAYORDER_ARGB     ,
  bgr        = SDL_ARRAYORDER_BGR      ,
  bgra       = SDL_ARRAYORDER_BGRA     ,
  abgr       = SDL_ARRAYORDER_ABGR
};
enum class packed_layout : std::uint8_t
{
  none       = SDL_PACKEDLAYOUT_NONE   ,
  _332       = SDL_PACKEDLAYOUT_332    ,
  _4444      = SDL_PACKEDLAYOUT_4444   ,
  _1555      = SDL_PACKEDLAYOUT_1555   ,
  _5551      = SDL_PACKEDLAYOUT_5551   ,
  _565       = SDL_PACKEDLAYOUT_565    ,
  _8888      = SDL_PACKEDLAYOUT_8888   ,
  _2101010   = SDL_PACKEDLAYOUT_2101010,
  _1010102   = SDL_PACKEDLAYOUT_1010102
};

enum class pixel_format_type : std::uint32_t
{
  unknown      = SDL_PIXELFORMAT_UNKNOWN     ,
  index1lsb    = SDL_PIXELFORMAT_INDEX1LSB   ,
  index1msb    = SDL_PIXELFORMAT_INDEX1MSB   ,
  index4lsb    = SDL_PIXELFORMAT_INDEX4LSB   ,
  index4msb    = SDL_PIXELFORMAT_INDEX4MSB   ,
  index8       = SDL_PIXELFORMAT_INDEX8      ,
  rgb332       = SDL_PIXELFORMAT_RGB332      ,
  xrgb4444     = SDL_PIXELFORMAT_XRGB4444    ,
  rgb444       = SDL_PIXELFORMAT_RGB444      ,
  xbgr4444     = SDL_PIXELFORMAT_XBGR4444    ,
  bgr444       = SDL_PIXELFORMAT_BGR444      ,
  xrgb1555     = SDL_PIXELFORMAT_XRGB1555    ,
  rgb555       = SDL_PIXELFORMAT_RGB555      ,
  xbgr1555     = SDL_PIXELFORMAT_XBGR1555    ,
  bgr555       = SDL_PIXELFORMAT_BGR555      ,
  argb4444     = SDL_PIXELFORMAT_ARGB4444    ,
  rgba4444     = SDL_PIXELFORMAT_RGBA4444    ,
  abgr4444     = SDL_PIXELFORMAT_ABGR4444    ,
  bgra4444     = SDL_PIXELFORMAT_BGRA4444    ,
  argb1555     = SDL_PIXELFORMAT_ARGB1555    ,
  rgba5551     = SDL_PIXELFORMAT_RGBA5551    ,
  abgr1555     = SDL_PIXELFORMAT_ABGR1555    ,
  bgra5551     = SDL_PIXELFORMAT_BGRA5551    ,
  rgb565       = SDL_PIXELFORMAT_RGB565      ,
  bgr565       = SDL_PIXELFORMAT_BGR565      ,
  rgb24        = SDL_PIXELFORMAT_RGB24       ,
  bgr24        = SDL_PIXELFORMAT_BGR24       ,
  xrgb8888     = SDL_PIXELFORMAT_XRGB8888    ,
  rgb888       = SDL_PIXELFORMAT_RGB888      ,
  rgbx8888     = SDL_PIXELFORMAT_RGBX8888    ,
  xbgr8888     = SDL_PIXELFORMAT_XBGR8888    ,
  bgr888       = SDL_PIXELFORMAT_BGR888      ,
  bgrx8888     = SDL_PIXELFORMAT_BGRX8888    ,
  argb8888     = SDL_PIXELFORMAT_ARGB8888    ,
  rgba8888     = SDL_PIXELFORMAT_RGBA8888    ,
  abgr8888     = SDL_PIXELFORMAT_ABGR8888    ,
  bgra8888     = SDL_PIXELFORMAT_BGRA8888    ,
  argb2101010  = SDL_PIXELFORMAT_ARGB2101010 ,
  rgba32       = SDL_PIXELFORMAT_RGBA32      ,
  argb32       = SDL_PIXELFORMAT_ARGB32      ,
  bgra32       = SDL_PIXELFORMAT_BGRA32      ,
  abgr32       = SDL_PIXELFORMAT_ABGR32      ,
  yv12         = SDL_PIXELFORMAT_YV12        ,
  iyuv         = SDL_PIXELFORMAT_IYUV        ,
  yuy2         = SDL_PIXELFORMAT_YUY2        ,
  uyvy         = SDL_PIXELFORMAT_UYVY        ,
  yvyu         = SDL_PIXELFORMAT_YVYU        ,
  nv12         = SDL_PIXELFORMAT_NV12        ,
  nv21         = SDL_PIXELFORMAT_NV21        ,
  external_oes = SDL_PIXELFORMAT_EXTERNAL_OES
};

using color               = SDL_Color;
using colour              = SDL_Colour;
using native_palette      = SDL_Palette;
using native_pixel_format = SDL_PixelFormat;

struct pixel_format_mask;
std::expected<pixel_format_type, std::string>           masks_to_pixel_format_enum (const pixel_format_mask& mask);

struct pixel_format_mask
{
  [[nodiscard]]
  std::expected<pixel_format_type, std::string> to_pixel_format_enum() const
  {
    return masks_to_pixel_format_enum(*this);
  }

  std::int32_t                 bits_per_pixel;
  std::array<std::uint32_t, 4> rgba;
};

using pixel_order = std::variant<bitmap_order, packed_order, array_order>;

[[nodiscard]]
constexpr pixel_format_type                             define_pixel_four_char_code(const std::array<std::uint8_t, 4> values) noexcept
{
  return static_cast<pixel_format_type>(SDL_DEFINE_PIXELFOURCC(values[0], values[1], values[2], values[3]));
}
[[nodiscard]]
constexpr pixel_format_type                             define_pixel_format        (const pixel_type type, const pixel_order order, const packed_layout layout, const std::uint8_t bits, const std::uint8_t bytes) noexcept
{
  return static_cast<pixel_format_type>(SDL_DEFINE_PIXELFORMAT(static_cast<std::uint8_t>(type), std::visit([&] (auto&& current) { return static_cast<std::uint8_t>(current); }, order), static_cast<std::uint8_t>(layout), bits, bytes));
}


[[nodiscard]]
constexpr bool                                          is_pixel_format_indexed    (const pixel_format_type type) noexcept
{
  return SDL_ISPIXELFORMAT_INDEXED(static_cast<std::uint32_t>(type));
}
[[nodiscard]]
constexpr bool                                          is_pixel_format_packed     (const pixel_format_type type) noexcept
{
  return SDL_ISPIXELFORMAT_PACKED (static_cast<std::uint32_t>(type));
}
[[nodiscard]]
constexpr bool                                          is_pixel_format_array      (const pixel_format_type type) noexcept
{
  return SDL_ISPIXELFORMAT_ARRAY  (static_cast<std::uint32_t>(type));
}
[[nodiscard]]
constexpr bool                                          is_pixel_format_alpha      (const pixel_format_type type) noexcept
{
  return SDL_ISPIXELFORMAT_ALPHA  (static_cast<std::uint32_t>(type));
}
[[nodiscard]]
constexpr bool                                          is_pixel_format_four_cc    (const pixel_format_type type) noexcept
{
  return SDL_ISPIXELFORMAT_FOURCC (static_cast<std::uint32_t>(type));
}


[[nodiscard]]
constexpr std::uint8_t                                  get_pixel_flag             (const pixel_format_type type) noexcept
{
  return static_cast<std::uint8_t> (SDL_PIXELFLAG    (static_cast<std::uint32_t>(type)));
}
[[nodiscard]]
constexpr pixel_type                                    get_pixel_type             (const pixel_format_type type) noexcept
{
  return static_cast<pixel_type>   (SDL_PIXELTYPE    (static_cast<std::uint32_t>(type)));
}
[[nodiscard]]
constexpr pixel_order                                   get_pixel_order            (const pixel_format_type type) noexcept
{
  const auto result = static_cast<std::uint8_t>(SDL_PIXELORDER(static_cast<std::uint32_t>(type)));
  if      constexpr (is_pixel_format_packed(type))
    return static_cast<packed_order>(result);
  else if constexpr (is_pixel_format_array (type))
    return static_cast<array_order> (result);
  else
    return static_cast<bitmap_order>(result);
}
[[nodiscard]]
constexpr packed_layout                                 get_pixel_layout           (const pixel_format_type type) noexcept
{
  return static_cast<packed_layout>(SDL_PIXELLAYOUT  (static_cast<std::uint32_t>(type)));
}
[[nodiscard]]
constexpr std::uint8_t                                  bits_per_pixel             (const pixel_format_type type) noexcept
{
  return static_cast<std::uint8_t> (SDL_BITSPERPIXEL (static_cast<std::uint32_t>(type)));
}
[[nodiscard]]
constexpr std::uint8_t                                  bytes_per_pixel            (const pixel_format_type type) noexcept
{
  return static_cast<std::uint8_t> (SDL_BYTESPERPIXEL(static_cast<std::uint32_t>(type)));
}
[[nodiscard]]
inline std::string                                      get_pixel_format_name      (const pixel_format_type type)
{
  return SDL_GetPixelFormatName(static_cast<std::uint32_t>(type));
}


[[nodiscard]]
inline std::expected<pixel_format_mask   , std::string> pixel_format_enum_to_masks (const pixel_format_type type)
{
  pixel_format_mask result {};
  if (SDL_PixelFormatEnumToMasks(static_cast<std::uint32_t>(type), 
      &result.bits_per_pixel, 
      &result.rgba[0],
      &result.rgba[1],
      &result.rgba[2],
      &result.rgba[3]) == SDL_FALSE)
    return std::unexpected(get_error());
  return result;
}
[[nodiscard]]
inline std::expected<pixel_format_type   , std::string> masks_to_pixel_format_enum (const pixel_format_mask& mask)
{
  return static_cast<pixel_format_type>(SDL_MasksToPixelFormatEnum(
    mask.bits_per_pixel,
    mask.rgba[0],
    mask.rgba[1],
    mask.rgba[2],
    mask.rgba[3]));
}


[[nodiscard]]
inline std::expected<native_pixel_format*, std::string> alloc_format               (const pixel_format_type type)
{
  auto result = SDL_AllocFormat(static_cast<std::uint32_t>(type));
  if (!result)
    return std::unexpected(get_error());
  return result;
}

inline void                                             free_format                (native_pixel_format* format) noexcept
{
  SDL_FreeFormat(format);
}


[[nodiscard]]
inline std::expected<native_palette*     , std::string> alloc_palette              (const std::int32_t num_colors)
{
  auto result = SDL_AllocPalette(num_colors);
  if (!result)
    return std::unexpected(get_error());
  return result;
}

inline std::expected<void                , std::string> set_pixel_format_palette   (native_pixel_format* format, native_palette* palette)
{
  if (SDL_SetPixelFormatPalette(format, palette) < 0)
    return std::unexpected(get_error());
  return {};
}

inline std::expected<void                , std::string> set_palette_colors         (native_palette* palette, const std::span<color>& colors, const std::int32_t index = 0)
{
  if (SDL_SetPaletteColors(palette, colors.data(), index, static_cast<std::int32_t>(colors.size())) < 0)
    return std::unexpected(get_error());
  return {};
}

inline void                                             free_palette               (native_palette* palette) noexcept
{
  SDL_FreePalette(palette);
}


[[nodiscard]]
inline std::uint32_t                                    map_rgb                    (const native_pixel_format* format, const color& value) noexcept
{
  return SDL_MapRGB(format, value.r, value.g, value.b);
}
[[nodiscard]]
inline std::uint32_t                                    map_rgba                   (const native_pixel_format* format, const color& value) noexcept
{
  return SDL_MapRGBA(format, value.r, value.g, value.b, value.a);
}

inline color                                            get_rgb                    (const std::uint32_t pixel, const native_pixel_format* format) noexcept
{
  color result {};
  SDL_GetRGB(pixel, format, &result.r, &result.g, &result.b);
  return result;

}

inline color                                            get_rgba                   (const std::uint32_t pixel, const native_pixel_format* format) noexcept
{
  color result {};
  SDL_GetRGBA(pixel, format, &result.r, &result.g, &result.b, &result.a);
  return result;
}


[[nodiscard]]
inline std::array<std::uint16_t, 256>                   calculate_gamma_ramp       (const float gamma)
{
  std::array<std::uint16_t, 256> result {};
  SDL_CalculateGammaRamp(gamma, result.data());
  return result;
}

// Conveniences.

class palette;

class pixel_format
{
public:
  // The constructor cannot transmit error state. You should use `sdl::make_pixel_format(...)` to handle errors.
  explicit pixel_format  (const pixel_format_type type)
  : type_  (type)
  , native_(alloc_format(type_).value_or(nullptr))
  {
    
  }
  // The constructor cannot transmit error state. You should use `sdl::make_pixel_format(...)` to handle errors.
  explicit pixel_format  (const std::array<std::uint8_t, 4>& values)
  : pixel_format(define_pixel_four_char_code(values))
  {
    
  }
  // The constructor cannot transmit error state. You should use `sdl::make_pixel_format(...)` to handle errors.
  explicit pixel_format  (const pixel_type type, const pixel_order order, const packed_layout layout, const std::uint8_t bits, const std::uint8_t bytes)
  : pixel_format(define_pixel_format(type, order, layout, bits, bytes))
  {
    
  }
  pixel_format           (const pixel_format&  that) = delete;
  pixel_format           (      pixel_format&& temp) noexcept
  : type_  (temp.type_  )
  , native_(temp.native_)
  {
    temp.native_ = nullptr;
  }
 ~pixel_format           () noexcept
  {
    if (native_)
      free_format(native_);
  }
  pixel_format& operator=(const pixel_format&  that) = delete;
  pixel_format& operator=(      pixel_format&& temp) noexcept
  {
    if (this != &temp)
    {
      if (native_)
        free_format(native_);

      std::swap(type_  , temp.type_  );
      std::swap(native_, temp.native_);
    }
    return *this;
  }

  // Pixel format type functions.

  [[nodiscard]]
  bool                                          is_indexed     () const noexcept
  {
    return is_pixel_format_indexed   (type_);
  }
  [[nodiscard]]
  bool                                          is_packed      () const noexcept
  {
    return is_pixel_format_packed    (type_);
  }
  [[nodiscard]]
  bool                                          is_array       () const noexcept
  {
    return is_pixel_format_array     (type_);
  }
  [[nodiscard]]
  bool                                          is_alpha       () const noexcept
  {
    return is_pixel_format_alpha     (type_);
  }
  [[nodiscard]]
  bool                                          is_four_cc     () const noexcept
  {
    return is_pixel_format_four_cc   (type_);
  }

  [[nodiscard]]
  std::uint8_t                                  flag           () const noexcept
  {
    return get_pixel_flag            (type_);
  }
  [[nodiscard]]
  pixel_order                                   order          () const noexcept
  {
    return get_pixel_order           (type_);
  }
  [[nodiscard]]
  packed_layout                                 layout         () const noexcept
  {
    return get_pixel_layout          (type_);
  }
  [[nodiscard]]
  std::uint8_t                                  bits_per_pixel () const noexcept
  {
    return sdl::bits_per_pixel       (type_);
  }
  [[nodiscard]]
  std::uint8_t                                  bytes_per_pixel() const noexcept
  {
    return sdl::bytes_per_pixel      (type_);
  }
  [[nodiscard]]
  std::string                                   name           () const
  {
    return get_pixel_format_name     (type_);
  }

  [[nodiscard]]
  std::expected<pixel_format_mask, std::string> to_masks       () const
  {
    return pixel_format_enum_to_masks(type_);
  }

  // Pixel format functions.

  std::expected<void, std::string>              set_palette    (const palette* palette) const;

  [[nodiscard]]
  std::uint32_t                                 map_rgb        (const color& value) const noexcept
  {
    return sdl::map_rgb(native_, value);
  }
  [[nodiscard]]
  std::uint32_t                                 map_rgba       (const color& value) const noexcept
  {
    return sdl::map_rgba(native_, value);
  }
  [[nodiscard]]
  color                                         get_rgb        (const std::uint32_t pixel) const noexcept
  {
    return sdl::get_rgb(pixel, native_);
  }
  [[nodiscard]]
  color                                         get_rgba       (const std::uint32_t pixel) const noexcept
  {
    return sdl::get_rgba(pixel, native_);
  }

  // Accessors.

  [[nodiscard]]
  pixel_format_type                             type           () const noexcept
  {
    return type_;
  }
  [[nodiscard]]
  native_pixel_format*                          native         () const noexcept
  {
    return native_;
  }

protected:
  pixel_format_type    type_   {};
  native_pixel_format* native_ {};
};

class palette
{
public:
  // The constructor cannot transmit error state. You should use `sdl::make_palette(...)` to handle errors.
  palette           (const std::int32_t num_colors)
  : native_(alloc_palette(num_colors).value_or(nullptr))
  {
    
  }
  palette           (const palette&  that) = delete;
  palette           (      palette&& temp) noexcept
  : native_(temp.native_)
  {
    temp.native_ = nullptr;
  }
 ~palette           () noexcept
  {
    if (native_)
      free_palette(native_);
  }
  palette& operator=(const palette&  that) = delete;
  palette& operator=(      palette&& temp) noexcept
  {
    if (this != &temp)
    {
      if (native_)
        free_palette(native_);

      std::swap(native_, temp.native_);
    }
    return *this;
  }

  std::expected<void, std::string> set_colors(const std::span<color>& colors, const std::int32_t index = 0) const
  {
    return set_palette_colors(native_, colors, index);
  }

  [[nodiscard]]
  native_palette*                  native    () const noexcept
  {
    return native_;
  }

protected:
  native_palette* native_ {};
};

inline std::expected<void, std::string> pixel_format::set_palette(const palette* palette) const
{
  return set_pixel_format_palette(native_, palette->native());
}

[[nodiscard]]
inline std::expected<pixel_format, std::string> make_pixel_format(const pixel_format_type type)
{
  pixel_format result(type);
  if (!result.native())
    return std::unexpected(get_error());
  return result;
}
[[nodiscard]]
inline std::expected<pixel_format, std::string> make_pixel_format(const std::array<std::uint8_t, 4>& values)
{
  pixel_format result(values);
  if (!result.native())
    return std::unexpected(get_error());
  return result;
}
[[nodiscard]]
inline std::expected<pixel_format, std::string> make_pixel_format(const pixel_type type, const pixel_order order, const packed_layout layout, const std::uint8_t bits, const std::uint8_t bytes)
{
  pixel_format result(type, order, layout, bits, bytes);
  if (!result.native())
    return std::unexpected(get_error());
  return result;
}
[[nodiscard]]
inline std::expected<palette     , std::string> make_palette     (const std::int32_t num_colors)
{
  palette result(num_colors);
  if (!result.native())
    return std::unexpected(get_error());
  return result;
}
}