#include <iostream>

#include "display/Window.h"
#include "display/Color.h"

Window *render_window;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int main()
{
    render_window = new Window("Software Renderer", 800, 800);

    int &width = render_window->width;
    int &height = render_window->height;

    int count = 0;

    render_window->start_window(WindowProc);

    std::cout << "starting window loop" << std::endl;

    while (render_window->process_messages())
    {
        render_window->background({0x000000});

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {

                uint8_t r = x % 255;
                uint8_t g = y % 255;
                uint8_t b = 128;
                
                render_window->set(x, y, r, g, b);
            }
        }

        render_window->render();
        count++;
    }

    std::cout << "count: " << count << std::endl;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    int w = LOWORD(lParam);
    int h = HIWORD(lParam);
    switch (uMsg)
    {
    case WM_SIZE:
        if (w != render_window->width || h != render_window->height)
            render_window->resize(w, h);
            break;
    case WM_DESTROY:
        std::cout << "bailing" << std::endl;
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}