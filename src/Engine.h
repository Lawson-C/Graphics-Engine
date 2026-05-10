#pragma once

#include "geometry/Mesh.h"
#include "display/Window.h"

class Engine
{
public:
    Engine(const Engine &) = delete;
    void operator=(const Engine &) = delete;

    inline static Engine &get_instance()
    {
        static Engine instance;
        return instance;
    }

    inline void add_mesh(Mesh *m) { get_instance().global_mesh->tail->prev->next = m->get_head(); }

    inline void attach_window(Window *window) { get_instance().render_target = window; }

    static void render_scene();

private:
    // linkedlist containing all polygons
    PolygonList *global_mesh;

    Window *render_target;

    Engine();
    ~Engine();
};