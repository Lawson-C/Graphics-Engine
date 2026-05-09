#include "Window.h"
#include <d3dcompiler.h>
#include <string.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

// ------------------------------------------------------------
// Window procedure
// ------------------------------------------------------------

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_DESTROY)
    {
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------

Window::Window(int width, int height, const char *title, HINSTANCE hInstance)
{
    m_width = width;
    m_height = height;
    m_framebuffer = new uint32_t[m_width * m_height];

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = "DX11Window";

    RegisterClass(&wc);

    m_hwnd = CreateWindowEx(
        0,
        wc.lpszClassName,
        "DX11 Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        m_width,
        m_height,
        nullptr,
        nullptr,
        hInstance,
        nullptr);

    if (!m_hwnd)
        msg = {.message = WM_QUIT};

    ShowWindow(m_hwnd, SW_SHOW);
    if (!(initD3D() && createTexture() && createShaders() && createQuad()))
        msg = {.message = WM_QUIT};
}

Window::~Window() {
    cleanD3D();
}

// ------------------------------------------------------------
// D3D11 init
// ------------------------------------------------------------

bool Window::initD3D()
{
    DXGI_SWAP_CHAIN_DESC scd = {};
    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = m_hwnd;
    scd.SampleDesc.Count = 1;
    scd.Windowed = TRUE;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &scd,
        &m_swapChain,
        &m_device,
        nullptr,
        &m_context);

    if (FAILED(hr))
        return false;

    ID3D11Texture2D *backBuffer = nullptr;
    m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void **)&backBuffer);

    m_device->CreateRenderTargetView(backBuffer, nullptr, &m_rtv);
    backBuffer->Release();

    m_context->OMSetRenderTargets(1, &m_rtv, nullptr);

    return true;
}

// ------------------------------------------------------------
// Texture (CPU → GPU buffer)
// ------------------------------------------------------------

bool Window::createTexture()
{
    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = m_width;
    desc.Height = m_height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    HRESULT hr = m_device->CreateTexture2D(&desc, nullptr, &m_texture);
    if (FAILED(hr))
        return false;

    hr = m_device->CreateShaderResourceView(m_texture, nullptr, &m_srv);
    return SUCCEEDED(hr);
}

// ------------------------------------------------------------
// Minimal shaders (just display texture)
// ------------------------------------------------------------

bool Window::createShaders()
{
    const char *vs =
        "struct V{float2 p:POSITION;float2 u:TEXCOORD;};"
        "struct O{float4 p:SV_POSITION;float2 u:TEXCOORD;};"
        "O main(V i){O o;o.p=float4(i.p,0,1);o.u=i.u;return o;}";

    const char *ps =
        "Texture2D tex:register(t0);"
        "float4 main(float2 u:TEXCOORD):SV_TARGET"
        "{return tex.Load(int3(u*float2(800,600),0));}";

    ID3DBlob *vsBlob;
    ID3DBlob *psBlob;

    if (FAILED(D3DCompile(vs, strlen(vs), nullptr, nullptr, nullptr,
                          "main", "vs_5_0", 0, 0, &vsBlob, nullptr)))
        return false;

    if (FAILED(D3DCompile(ps, strlen(ps), nullptr, nullptr, nullptr,
                          "main", "ps_5_0", 0, 0, &psBlob, nullptr)))
        return false;

    m_device->CreateVertexShader(vsBlob->GetBufferPointer(),
                                 vsBlob->GetBufferSize(), nullptr, &m_vs);

    m_device->CreatePixelShader(psBlob->GetBufferPointer(),
                                psBlob->GetBufferSize(), nullptr, &m_ps);

    D3D11_INPUT_ELEMENT_DESC layout[] =
        {
            {"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0,
             D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 8,
             D3D11_INPUT_PER_VERTEX_DATA, 0},
        };

    m_device->CreateInputLayout(layout, 2,
                                vsBlob->GetBufferPointer(),
                                vsBlob->GetBufferSize(),
                                &m_layout);

    vsBlob->Release();
    psBlob->Release();

    return true;
}

// ------------------------------------------------------------
// Fullscreen quad
// ------------------------------------------------------------

bool Window::createQuad()
{
    Vertex v[] =
        {
            {-1, -1, 0, 1},
            {-1, 1, 0, 0},
            {1, -1, 1, 1},
            {1, -1, 1, 1},
            {-1, 1, 0, 0},
            {1, 1, 1, 0},
        };

    D3D11_BUFFER_DESC bd = {};
    bd.ByteWidth = sizeof(v);
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA data = {};
    data.pSysMem = v;

    return SUCCEEDED(
        m_device->CreateBuffer(&bd, &data, &m_vb));
}

// ------------------------------------------------------------
// Render loop
// ------------------------------------------------------------

void Window::renderFrame()
{
    D3D11_MAPPED_SUBRESOURCE mapped;

    m_context->Map(m_texture, 0,
                   D3D11_MAP_WRITE_DISCARD, 0, &mapped);

    memcpy(mapped.pData, m_framebuffer,
           m_width * m_height * 4);

    m_context->Unmap(m_texture, 0);

    float clear[4] = {0, 0, 0, 1};
    m_context->ClearRenderTargetView(m_rtv, clear);

    UINT stride = sizeof(Vertex);
    UINT offset = 0;

    m_context->IASetVertexBuffers(0, 1, &m_vb, &stride, &offset);
    m_context->IASetInputLayout(m_layout);
    m_context->IASetPrimitiveTopology(
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    m_context->VSSetShader(m_vs, nullptr, 0);
    m_context->PSSetShader(m_ps, nullptr, 0);
    m_context->PSSetShaderResources(0, 1, &m_srv);

    m_context->Draw(6, 0);

    m_swapChain->Present(1, 0);
}

// ------------------------------------------------------------
// Clean up Direct3D
// ------------------------------------------------------------
void Window::cleanD3D()
{
    m_swapChain->Release();
    m_rtv->Release();
    m_device->Release();
    m_context->Release();
}