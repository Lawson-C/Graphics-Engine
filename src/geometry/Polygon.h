#pragma once

#include <matrixmath>

#include "../display/Color.h"

class Polygon
{
private:
    Vector3 normal;
    Vector3 *point;
    color_t *texture;

public:
    inline Polygon(double data[9], color_t color0, color_t color1, color_t color2);
    inline Polygon(double data[3][3], color_t color0, color_t color1, color_t color2);
    inline Polygon(Vector3 points[3], color_t color0, color_t color1, color_t color2);
    inline Polygon(Vector3 &point0, Vector3 &point1, Vector3 &point2, color_t color0, color_t color1, color_t color2);
    inline ~Polygon();

    color_t get_color(Vector3 &point);
    color_t get_color(double x, double y, double z);

    void set_normal(Vector3 &normal);
    void set_normal(double x, double y, double z);

    void align_normal(int x, int y, int z);
};

typedef class Polygon polygon_t;