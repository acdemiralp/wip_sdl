#pragma once

#include <cstdint>
#include <cstring>
#include <string>

#include <SDL_stdinc.h>

namespace sdl
{
// Memory allocation functions
inline void* malloc(const std::size_t size)
{
  return SDL_malloc(size);
}
inline void* calloc(const std::size_t count, const std::size_t size)
{
  return SDL_calloc(count, size);
}
inline void* realloc(void* pointer, const std::size_t size)
{
  return SDL_realloc(pointer, size);
}
inline void free(void* pointer)
{
  SDL_free(pointer);
}

// String functions
inline std::size_t strlen(const char* string)
{
  return SDL_strlen(string);
}
inline std::size_t strlcpy(char* destination, const char* source, const std::size_t size)
{
  return SDL_strlcpy(destination, source, size);
}
inline std::size_t utf8strlcpy(char* destination, const char* source, const std::size_t size)
{
  return SDL_utf8strlcpy(destination, source, size);
}
inline std::size_t strlcat(char* destination, const char* source, const std::size_t size)
{
  return SDL_strlcat(destination, source, size);
}
inline char* strdup(const char* string)
{
  return SDL_strdup(string);
}
inline char* strrev(char* string)
{
  return SDL_strrev(string);
}
inline char* strupr(char* string)
{
  return SDL_strupr(string);
}
inline char* strlwr(char* string)
{
  return SDL_strlwr(string);
}
inline char* strchr(const char* string, const int character)
{
  return SDL_strchr(string, character);
}
inline char* strrchr(const char* string, const int character)
{
  return SDL_strrchr(string, character);
}
inline char* strstr(const char* haystack, const char* needle)
{
  return SDL_strstr(haystack, needle);
}
inline char* strtokr(char* string, const char* delimiters, char** context)
{
  return SDL_strtokr(string, delimiters, context);
}
inline std::size_t utf8strlen(const char* string)
{
  return SDL_utf8strlen(string);
}

inline int strcmp(const char* string1, const char* string2)
{
  return SDL_strcmp(string1, string2);
}
inline int strncmp(const char* string1, const char* string2, const std::size_t count)
{
  return SDL_strncmp(string1, string2, count);
}
inline int strcasecmp(const char* string1, const char* string2)
{
  return SDL_strcasecmp(string1, string2);
}
inline int strncasecmp(const char* string1, const char* string2, const std::size_t count)
{
  return SDL_strncasecmp(string1, string2, count);
}

inline int sscanf(const char* string, const char* format, ...)
{
  va_list args;
  va_start(args, format);
  const int result = SDL_vsscanf(string, format, args);
  va_end(args);
  return result;
}
inline int vsscanf(const char* string, const char* format, va_list args)
{
  return SDL_vsscanf(string, format, args);
}
inline int snprintf(char* string, const std::size_t size, const char* format, ...)
{
  va_list args;
  va_start(args, format);
  const int result = SDL_vsnprintf(string, size, format, args);
  va_end(args);
  return result;
}
inline int vsnprintf(char* string, const std::size_t size, const char* format, va_list args)
{
  return SDL_vsnprintf(string, size, format, args);
}
inline int asprintf(char** string, const char* format, ...)
{
  va_list args;
  va_start(args, format);
  const int result = SDL_vasprintf(string, format, args);
  va_end(args);
  return result;
}
inline int vasprintf(char** string, const char* format, va_list args)
{
  return SDL_vasprintf(string, format, args);
}

// Math functions
inline double acos(const double x)
{
  return SDL_acos(x);
}
inline float acosf(const float x)
{
  return SDL_acosf(x);
}
inline double asin(const double x)
{
  return SDL_asin(x);
}
inline float asinf(const float x)
{
  return SDL_asinf(x);
}
inline double atan(const double x)
{
  return SDL_atan(x);
}
inline float atanf(const float x)
{
  return SDL_atanf(x);
}
inline double atan2(const double y, const double x)
{
  return SDL_atan2(y, x);
}
inline float atan2f(const float y, const float x)
{
  return SDL_atan2f(y, x);
}
inline double ceil(const double x)
{
  return SDL_ceil(x);
}
inline float ceilf(const float x)
{
  return SDL_ceilf(x);
}
inline double copysign(const double x, const double y)
{
  return SDL_copysign(x, y);
}
inline float copysignf(const float x, const float y)
{
  return SDL_copysignf(x, y);
}
inline double cos(const double x)
{
  return SDL_cos(x);
}
inline float cosf(const float x)
{
  return SDL_cosf(x);
}
inline double exp(const double x)
{
  return SDL_exp(x);
}
inline float expf(const float x)
{
  return SDL_expf(x);
}
inline double fabs(const double x)
{
  return SDL_fabs(x);
}
inline float fabsf(const float x)
{
  return SDL_fabsf(x);
}
inline double floor(const double x)
{
  return SDL_floor(x);
}
inline float floorf(const float x)
{
  return SDL_floorf(x);
}
inline double trunc(const double x)
{
  return SDL_trunc(x);
}
inline float truncf(const float x)
{
  return SDL_truncf(x);
}
inline double fmod(const double x, const double y)
{
  return SDL_fmod(x, y);
}
inline float fmodf(const float x, const float y)
{
  return SDL_fmodf(x, y);
}
inline double log(const double x)
{
  return SDL_log(x);
}
inline float logf(const float x)
{
  return SDL_logf(x);
}
inline double log10(const double x)
{
  return SDL_log10(x);
}
inline float log10f(const float x)
{
  return SDL_log10f(x);
}
inline double pow(const double x, const double y)
{
  return SDL_pow(x, y);
}
inline float powf(const float x, const float y)
{
  return SDL_powf(x, y);
}
inline double round(const double x)
{
  return SDL_round(x);
}
inline float roundf(const float x)
{
  return SDL_roundf(x);
}
inline long lround(const double x)
{
  return SDL_lround(x);
}
inline long lroundf(const float x)
{
  return SDL_lroundf(x);
}
inline double scalbn(const double x, const int n)
{
  return SDL_scalbn(x, n);
}
inline float scalbnf(const float x, const int n)
{
  return SDL_scalbnf(x, n);
}
inline double sin(const double x)
{
  return SDL_sin(x);
}
inline float sinf(const float x)
{
  return SDL_sinf(x);
}
inline double sqrt(const double x)
{
  return SDL_sqrt(x);
}
inline float sqrtf(const float x)
{
  return SDL_sqrtf(x);
}
inline double tan(const double x)
{
  return SDL_tan(x);
}
inline float tanf(const float x)
{
  return SDL_tanf(x);
}

// Conversion functions
inline int atoi(const char* string)
{
  return SDL_atoi(string);
}
inline double atof(const char* string)
{
  return SDL_atof(string);
}
inline long strtol(const char* string, char** endp, const int base)
{
  return SDL_strtol(string, endp, base);
}
inline unsigned long strtoul(const char* string, char** endp, const int base)
{
  return SDL_strtoul(string, endp, base);
}
inline long long strtoll(const char* string, char** endp, const int base)
{
  return SDL_strtoll(string, endp, base);
}
inline unsigned long long strtoull(const char* string, char** endp, const int base)
{
  return SDL_strtoull(string, endp, base);
}
inline double strtod(const char* string, char** endp)
{
  return SDL_strtod(string, endp);
}

// Character classification
inline int isalpha(const int x)
{
  return SDL_isalpha(x);
}
inline int isalnum(const int x)
{
  return SDL_isalnum(x);
}
inline int isblank(const int x)
{
  return SDL_isblank(x);
}
inline int iscntrl(const int x)
{
  return SDL_iscntrl(x);
}
inline int isdigit(const int x)
{
  return SDL_isdigit(x);
}
inline int isxdigit(const int x)
{
  return SDL_isxdigit(x);
}
inline int ispunct(const int x)
{
  return SDL_ispunct(x);
}
inline int isspace(const int x)
{
  return SDL_isspace(x);
}
inline int isupper(const int x)
{
  return SDL_isupper(x);
}
inline int islower(const int x)
{
  return SDL_islower(x);
}
inline int isprint(const int x)
{
  return SDL_isprint(x);
}
inline int isgraph(const int x)
{
  return SDL_isgraph(x);
}
inline int toupper(const int x)
{
  return SDL_toupper(x);
}
inline int tolower(const int x)
{
  return SDL_tolower(x);
}

// Memory utilities
inline void* memset(void* destination, const int value, const std::size_t size)
{
  return SDL_memset(destination, value, size);
}
inline void* memcpy(void* destination, const void* source, const std::size_t size)
{
  return SDL_memcpy(destination, source, size);
}
inline void* memmove(void* destination, const void* source, const std::size_t size)
{
  return SDL_memmove(destination, source, size);
}
inline int memcmp(const void* s1, const void* s2, const std::size_t size)
{
  return SDL_memcmp(s1, s2, size);
}

inline std::size_t wcslen(const wchar_t* string)
{
  return SDL_wcslen(string);
}
inline std::size_t wcslcpy(wchar_t* destination, const wchar_t* source, const std::size_t size)
{
  return SDL_wcslcpy(destination, source, size);
}
inline std::size_t wcslcat(wchar_t* destination, const wchar_t* source, const std::size_t size)
{
  return SDL_wcslcat(destination, source, size);
}
inline wchar_t* wcsdup(const wchar_t* string)
{
  return SDL_wcsdup(string);
}
inline wchar_t* wcsstr(const wchar_t* haystack, const wchar_t* needle)
{
  return SDL_wcsstr(haystack, needle);
}
inline int wcscmp(const wchar_t* string1, const wchar_t* string2)
{
  return SDL_wcscmp(string1, string2);
}
inline int wcsncmp(const wchar_t* string1, const wchar_t* string2, const std::size_t count)
{
  return SDL_wcsncmp(string1, string2, count);
}
inline int wcscasecmp(const wchar_t* string1, const wchar_t* string2)
{
  return SDL_wcscasecmp(string1, string2);
}
inline int wcsncasecmp(const wchar_t* string1, const wchar_t* string2, const std::size_t count)
{
  return SDL_wcsncasecmp(string1, string2, count);
}

inline long wcstol(const wchar_t* string, wchar_t** endp, const int base)
{
  return SDL_wcstol(string, endp, base);
}
}
