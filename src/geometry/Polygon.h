#pragma once

#include "Vertex.h"

#include "../display/Color.h"

struct Polygon
{
    Vector3 normal;

    vertex_t *vertices[3];

    Polygon(vertex_t *p0, vertex_t *p1, vertex_t *p2);
    Polygon(Vector3 *p0, Vector3 *p1, Vector3 *p2, color_t color0, color_t color1, color_t color2);
    ~Polygon();

    vertex_t get_vertex(uint8_t i) { return *(vertices[i]); };

    color_t get_color(Vector3 &point);
    inline color_t get_color(double x, double y, double z)
    {
        Vector3 p(x, y, z);
        return get_color(p);
    }

    void set_normal(double x, double y, double z);
    inline void set_normal(Vector3 &normal) { set_normal(normal.x(), normal.y(), normal.z()); };

    void realign_normal(int x, int y, int z);

} typedef polygon_t;