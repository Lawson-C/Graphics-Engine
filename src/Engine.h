#pragma once

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
    PolygonList *global_mesh;

    Window *window;
};