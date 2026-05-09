#include "Window.h"

#include <string>
#include <iostream>

Window::Window(const char *title, int width, int height) : width(width), height(height), title(title)
{
    std::cout << "creating window " << title << " of size " << width << " x " << height << std::endl;

    framebuffer = new uint32_t[width * height];

    std::cout << "frame buffer initialization " << ((framebuffer == nullptr) ? "failed" : "success") << std::endl;

    bitmapInfo = {};

    bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfo.bmiHeader.biWidth = width;
    bitmapInfo.bmiHeader.biHeight = -height;
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biBitCount = 32;
    bitmapInfo.bmiHeader.biCompression = BI_RGB;
}

Window::~Window()
{
    std::cout << "killing window" << std::endl;
    delete[] framebuffer;
}

bool Window::start_window(WNDPROC WindowProc)
{
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = "SoftwareRendererWindowClass";

    RegisterClass(&wc);

    hwnd = CreateWindowEx(
        0,
        wc.lpszClassName,
        title,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        width,
        height,
        nullptr,
        nullptr,
        wc.hInstance,
        this);

    std::cout << "hwnd initialization " << ((hwnd == nullptr) ? "failed" : "success") << std::endl;

    SetWindowLongPtr(
        hwnd,
        GWLP_USERDATA,
        (LONG_PTR)this);

    return hwnd;
}

bool Window::process_messages()
{
    MSG msg;

    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            std::cout << "WM_QUIT -> exiting loop\n";
            return false;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return true;
}

void Window::render()
{
    HDC hdc = GetDC(hwnd);

    StretchDIBits(
        hdc,
        0,
        0,
        width,
        height,

        0,
        0,
        width,
        height,

        framebuffer,
        &bitmapInfo,
        DIB_RGB_COLORS,
        SRCCOPY);

    ReleaseDC(hwnd, hdc);
}

void Window::background(uint32_t color)
{
    for (int i = 0; i < width * height; i++)
    {
        framebuffer[i] = color;
    }
}

bool Window::resize(int w, int h)
{
    this->width = w;
    this->height = h;

    delete[] framebuffer;
    framebuffer = new uint32_t[w * h];

    bitmapInfo.bmiHeader.biWidth = w;
    bitmapInfo.bmiHeader.biHeight = -h;

    std::cout << "frame buffer resize " << ((framebuffer == nullptr) ? "failed" : "success") << std::endl;

    return framebuffer == nullptr;
}