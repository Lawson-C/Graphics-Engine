#pragma once

#include <cstdint>
#include <tmmintrin.h>

typedef union
{
    uint32_t raw;
    struct
    {
        uint8_t alpha, red, green, blue;
    };
} color_t;

inline color_t color(uint8_t g) { return {.alpha = 255, .red = g, .green = g, .blue = g}; }
inline color_t color(uint8_t r, uint8_t g, uint8_t b) { return {.alpha = 255, .red = r, .green = g, .blue = b}; }
inline color_t color(uint8_t a, uint8_t r, uint8_t g, uint8_t b) { return {.alpha = a, .red = r, .green = g, .blue = b}; }

// ADD colors

inline color_t operator+(color_t a, color_t b)
{
    __m128i a_vec = _mm_cvtsi32_si128(a.raw);
    __m128i b_vec = _mm_cvtsi32_si128(b.raw);

    __m128i result_vec = _mm_adds_epu8(a_vec, b_vec);

    return color_t{.raw = (uint32_t)_mm_cvtsi128_si32(result_vec)};
}

inline color_t operator+=(color_t &a, color_t b)
{
    __m128i a_vec = _mm_cvtsi32_si128(a.raw);
    __m128i b_vec = _mm_cvtsi32_si128(b.raw);

    __m128i result_vec = _mm_adds_epu8(a_vec, b_vec);

    return a = {.raw = (uint32_t)_mm_cvtsi128_si32(result_vec)};
}

// SUB colors

inline color_t operator-(color_t a, color_t b)
{
    __m128i a_vec = _mm_cvtsi32_si128(a.raw);
    __m128i b_vec = _mm_cvtsi32_si128(b.raw);

    __m128i result_vec = _mm_subs_epu8(a_vec, b_vec);

    return color_t{.raw = (uint32_t)_mm_cvtsi128_si32(result_vec)};
}

inline color_t operator-=(color_t &a, color_t b)
{
    __m128i a_vec = _mm_cvtsi32_si128(a.raw);
    __m128i b_vec = _mm_cvtsi32_si128(b.raw);

    __m128i result_vec = _mm_subs_epu8(a_vec, b_vec);

    return a = {.raw = (uint32_t)_mm_cvtsi128_si32(result_vec)};
}

// MULT colors

inline color_t operator*(double k, color_t c) { return color_t{.red = (uint8_t)(c.red * k), .green = (uint8_t)(c.green * k), .blue = (uint8_t)(c.blue * k)}; }
inline color_t operator*(color_t c, double k) { return color_t{.red = (uint8_t)(c.red * k), .green = (uint8_t)(c.green * k), .blue = (uint8_t)(c.blue * k)}; }
inline color_t operator*=(color_t &c, double k) { return c = {.red = (uint8_t)(c.red * k), .green = (uint8_t)(c.green * k), .blue = (uint8_t)(c.blue * k)}; }

// static colors

#ifndef BLANK
#define BLANK color_t{0x00000000}
#endif

#ifndef BLACK
#define BLACK color_t{0xFF000000}
#endif

#ifndef WHITE
#define WHITE color_t{0xFFFFFFFF}
#endif

#ifndef RED
#define RED color_t{0xFFFF0000}
#endif

#ifndef GREEN
#define GREEN color_t{0xFF00FF00}
#endif

#ifndef BLUE
#define BLUE color_t{0xFF0000FF}
#endif