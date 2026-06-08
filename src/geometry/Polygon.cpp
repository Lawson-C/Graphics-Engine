#include "Polygon.h"

Polygon::Polygon(Vector3 *p0, Vector3 *p1, Vector3 *p2, color_t color0, color_t color1, color_t color2)
{
    vertices[0].vector = p0;
    vertices[1].vector = p1;
    vertices[2].vector = p2;

    vertices[0].color = color0;
    vertices[1].color = color1;
    vertices[2].color = color2;
}

Polygon::~Polygon()
{
    delete[] vertices;
}

color_t Polygon::get_color(Vector3 &p)
{
    Vector3 v0 = *(vertices[1].vector) - *(vertices[0].vector);
    Vector3 v1 = *(vertices[2].vector) - *(vertices[0].vector);
    Vector3 v2 = p - *(vertices[0].vector);

    double d00 = v0 * v0;
    double d01 = v0 * v1;
    double d11 = v1 * v1;
    double d20 = v2 * v0;
    double d21 = v2 * v1;

    double factor = 1.0 / (d00 * d11 - d01 * d01);

    double v = (d11 * d20 - d01 * d21) * factor;
    double w = (d00 * d21 - d01 * d20) * factor;
    double u = 1.0 - v - w;

    return u * vertices[0].color + v * vertices[1].color + w * vertices[2].color;
}

void Polygon::set_normal(double x, double y, double z)
{
    normal.x = x;
    normal.y = y;
    normal.z = z;
    normal.normalize();
}

void Polygon::realign_normal(int x, int y, int z)
{
    normal.x *= (x >> 31) | 1;
    normal.y *= (y >> 31) | 1;
    normal.z *= (z >> 31) | 1;
}