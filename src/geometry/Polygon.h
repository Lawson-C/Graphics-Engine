#pragma once

#include <matrixmath>

#include "../display/Color.h"

struct Polygon
{
    Vector3 normal;

    struct
    {
        Vector3 *vector;
        color_t color;
    } vertices[3];

    inline Polygon(Vector3 *p0, Vector3 *p1, Vector3 *p2, color_t color0, color_t color1, color_t color2);
    inline ~Polygon();

    color_t get_color(Vector3 &point);
    color_t get_color(double x, double y, double z)
    {
        Vector3 p(x, y, z);
        return get_color(p);
    }

    void set_normal(double x, double y, double z);
    void set_normal(Vector3 &normal)
    {
        set_normal(normal.x(), normal.y(), normal.z());
    };

    void realign_normal(int x, int y, int z);

} typedef polygon_t;