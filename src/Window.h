#pragma once

#include <windows.h>
#include <d3d11.h>
#include <stdint.h>

#define COLOR(r, g, b) ((255 << 24) | ((r % 255) << 16) | ((g % 255) << 8) | (b % 255))
#define COLOR_ALPHA(r, g, b, a) (((a % 255) << 24) | ((r % 255) << 16) | ((g % 255) << 8) | ((b % 255) % 255))

class Window
{
public:
    int m_width;
    int m_height;

    Window(int width, int height, const char *title, HINSTANCE hInstance);
    ~Window();

    inline MSG *getMSG() { return &msg; };

    inline int get(int x, int y) { return m_framebuffer[x + m_width * y]; }

    inline void set(int x, int y, uint8_t g) { m_framebuffer[x + m_width * y] = COLOR(g, g, g); }
    inline void set(int x, int y, uint8_t r, uint8_t g, uint8_t b) { m_framebuffer[x + m_width * y] = COLOR(r, g, b); }
    inline void set(int x, int y, uint8_t r, uint8_t g, uint8_t b, uint8_t a) { m_framebuffer[x + m_width * y] = COLOR_ALPHA(r, g, b, a); }

    void renderFrame();

private:
    bool initWindow(HINSTANCE hInstance);
    bool initD3D();
    bool createTexture();
    bool createShaders();
    bool createQuad();
    void present();
    void cleanD3D();

    HWND m_hwnd = nullptr;

    // DirectX
    ID3D11Device *m_device = nullptr;
    ID3D11DeviceContext *m_context = nullptr;
    IDXGISwapChain *m_swapChain = nullptr;
    ID3D11RenderTargetView *m_rtv = nullptr;

    ID3D11Texture2D *m_texture = nullptr;
    ID3D11ShaderResourceView *m_srv = nullptr;

    ID3D11VertexShader *m_vs = nullptr;
    ID3D11PixelShader *m_ps = nullptr;
    ID3D11InputLayout *m_layout = nullptr;
    ID3D11Buffer *m_vb = nullptr;

    MSG msg;

    struct Vertex
    {
        float x, y;
        float u, v;
    };

    uint32_t *m_framebuffer = nullptr;
};

#undef COLOR
#undef COLOR_ALPHA