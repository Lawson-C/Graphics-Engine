#include "Polygon.h"

Polygon::Polygon(Vertex *v0, Vertex *v1, Vertex *v2)
{
    vertices[0] = v0;
    vertices[1] = v1;
    vertices[2] = v2;
}

Polygon::Polygon(Vector3 *p0, Vector3 *p1, Vector3 *p2, color_t color0, color_t color1, color_t color2)
{
    vertices[0] = new vertex_t{
        .vector = p0,
        .color = color0,
        .screen_space = 0};
    vertices[1] = new vertex_t{
        .vector = p0,
        .color = color0,
        .screen_space = 0};

    vertices[2] = new vertex_t{
        .vector = p0,
        .color = color0,
        .screen_space = 0};
}

Polygon::~Polygon()
{
    if (vertices[0])
        delete vertices[0];
    if (vertices[0])
        delete vertices[1];
    if (vertices[0])
        delete vertices[2];
}

color_t Polygon::get_color(Vector3 &p)
{
    Vector3 v0 = *(get_vertex(1).vector) - *(get_vertex(0).vector);
    Vector3 v1 = *(get_vertex(2).vector) - *(get_vertex(0).vector);
    Vector3 v2 = p - *(get_vertex(0).vector);

    double d00 = v0 * v0;
    double d01 = v0 * v1;
    double d11 = v1 * v1;
    double d20 = v2 * v0;
    double d21 = v2 * v1;

    double factor = 1.0 / (d00 * d11 - d01 * d01);

    double v = (d11 * d20 - d01 * d21) * factor;
    double w = (d00 * d21 - d01 * d20) * factor;
    double u = 1.0 - v - w;

    return u * get_vertex(0).color + v * get_vertex(1).color + w * get_vertex(2).color;
}

void Polygon::set_normal(double x, double y, double z)
{
    normal.x() = x;
    normal.y() = y;
    normal.z() = z;
    normal.normalize();
}

void Polygon::realign_normal(int x, int y, int z)
{
    normal.x() *= (x >> 31) | 1;
    normal.y() *= (y >> 31) | 1;
    normal.z() *= (z >> 31) | 1;
}