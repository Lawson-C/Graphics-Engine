#pragma once

#include <windows.h>
#include <stdint.h>

#include "Color.h"

class Window
{
public:
    int width;
    int height;

    Window(const char *title, int width, int height);

    ~Window();

    bool start_window(WNDPROC WindowProc);

    bool process_messages();

    bool resize(int w, int h);

    void render();

    void background(color_t color);

    inline color_t get(int x, int y) { return framebuffer[(x + width * y) * (x >= 0 && x < width && y >= 0 && y < height)] * (double) (x >= 0 && x < width && y >= 0 && y < height); }

    inline color_t set(int x, int y, uint8_t g) { return color_t {(x < 0 || x >= width || y < 0 || y >= height) ? BLANK : (framebuffer[x + width * y] = color(g, g, g))}; }
    inline color_t set(int x, int y, uint8_t r, uint8_t g, uint8_t b) { return (x < 0 || x >= width || y < 0 || y >= height) ? BLANK : (framebuffer[x + width * y] = color(r, g, b)); }
    inline color_t set(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) { return (x < 0 || x >= width || y < 0 || y >= height) ? BLANK : (framebuffer[x + width * y] = color(r, g, b, a)); }

private:
    const char *title;

    HWND hwnd;

    color_t *framebuffer;

    BITMAPINFO bitmapInfo;
};