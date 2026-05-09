#pragma once

#include <windows.h>
#include <stdint.h>

#define COLOR(r, g, b) ((255 << 24) | ((r % 255) << 16) | ((g % 255) << 8) | (b % 255))
#define COLOR_ALPHA(r, g, b, a) (((a % 255) << 24) | ((r % 255) << 16) | ((g % 255) << 8) | ((b % 255) % 255))

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

    void background(uint32_t color);

    inline uint32_t get(int x, int y) { return framebuffer[(x + width * y) * (x >= 0 && x < width && y >= 0 && y < height)] * (x >= 0 && x < width && y >= 0 && y < height); }

    inline uint32_t set(int x, int y, uint8_t g) { return (x < 0 || x >= width || y < 0 || y >= height) ? 0 : (framebuffer[x + width * y] = COLOR(g, g, g)); }
    inline uint32_t set(int x, int y, uint8_t r, uint8_t g, uint8_t b) { return (x < 0 || x >= width || y < 0 || y >= height) ? 0 : (framebuffer[x + width * y] = COLOR(r, g, b)); }
    inline uint32_t set(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) { return (x < 0 || x >= width || y < 0 || y >= height) ? 0 : (framebuffer[x + width * y] = COLOR_ALPHA(r, g, b, a)); }

private:
    const char *title;

    HWND hwnd;

    uint32_t *framebuffer;

    BITMAPINFO bitmapInfo;
};

#undef COLOR
#undef COLOR_ALPHA