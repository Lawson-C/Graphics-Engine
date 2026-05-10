#include "Engine.h"

Engine::Engine()
{
    global_mesh = new PolygonList{};
}

Engine::~Engine()
{
	delete global_mesh;
}

void Engine::render_scene()
{
    Window *window = get_instance().render_target;
    window->background({0x000000});

    for (int y = 0; y < window->height; y++)
    {
        for (int x = 0; x < window->width; x++)
        {

            uint8_t r = x % 255;
            uint8_t g = y % 255;
            uint8_t b = 128;

            window->set(x, y, r, g, b);
        }
    }

    window->render();
}