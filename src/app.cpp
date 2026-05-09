#include "Window.h"

const static int width = 800, height = 800;

Window *renderWindow;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
    renderWindow = new Window(width, height, "render view", hInstance);

    while (renderWindow->getMSG()->message != WM_QUIT)
    {
        while (PeekMessage(renderWindow->getMSG(), nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(renderWindow->getMSG());
            DispatchMessage(renderWindow->getMSG());
        }

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                renderWindow->set(x, y, 255, 0, 255);
            }
        }

        renderWindow->renderFrame();
    }

    return 0;
}