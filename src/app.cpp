#include <iostream>

#include "display/Window.h"
#include "display/Color.h"
#include "geometry/Polygon.h"
#include "Engine.h"

Window *render_window;
Engine *engine;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int main()
{
    render_window = new Window("Software Renderer", 800, 800);
    engine->attach_window(render_window);

    int &width = render_window->width;
    int &height = render_window->height;

    int count = 0;

    render_window->start_window(WindowProc);

    std::cout << "starting window loop" << std::endl;

    while (render_window->process_messages())
    {
        engine->render_scene();
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