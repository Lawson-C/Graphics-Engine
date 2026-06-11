#pragma once

#include "List.h"
#include "geometry/Mesh.h"
#include "display/Window.h"

class Engine
{
public:
    Engine(Window *window);

    ~Engine();

    void add_mesh(Mesh *m);

    void render_scene();

private:
    // linkedlist containing all polygons
    polygonlist_t *global_mesh;

    Window *window;
};