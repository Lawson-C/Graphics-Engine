#include "Polygon.h"

Polygon::Polygon(double data[9], color_t color0, color_t color1, color_t color2) : point(new Vector3[]{Vector3(data), Vector3(data + 3), Vector3(data + 6)}),
                                                                                   texture(new color_t[]{color0, color1, color2})
{
    Vector3 v0 = point[1] - point[0];
    Vector3 v1 = point[2] - point[0];
    normal = (v0).cross(v1).normalize();
}

Polygon::Polygon(double data[3][3], color_t color0, color_t color1, color_t color2) : point(new Vector3[]{Vector3(data[0]), Vector3(data[1]), Vector3(data[2])}),
                                                                                      texture(new color_t[]{color0, color1, color2})
{
    Vector3 v0 = point[1] - point[0];
    Vector3 v1 = point[2] - point[0];
    normal = (v0).cross(v1).normalize();
}

Polygon::Polygon(Vector3 points[3], color_t color0, color_t color1, color_t color2) : point(new Vector3[]{points[0], points[1], points[2]}),
                                                                                      texture(new color_t[]{color0, color1, color2})
{
    Vector3 v0 = point[1] - point[0];
    Vector3 v1 = point[2] - point[0];
    normal = (v0).cross(v1).normalize();
}

Polygon::Polygon(Vector3 &point0, Vector3 &point1, Vector3 &point2, color_t color0, color_t color1, color_t color2) : point(new Vector3[]{point0, point1, point2}),
                                                                                                                      texture(new color_t[]{color0, color1, color2})
{
    Vector3 v0 = point[1] - point[0];
    Vector3 v1 = point[2] - point[0];
    normal = (v0).cross(v1).normalize();
}

Polygon::~Polygon()
{
    delete[] point;
    delete[] texture;
}

color_t Polygon::get_color(Vector3 &point)
{
    Vector3 v0 = this->point[1] - this->point[0];
    Vector3 v1 = this->point[2] - this->point[0];
    Vector3 v2 = point - this->point[0];

    double d00 = v0 * v0;
    double d01 = v0 * v1;
    double d11 = v1 * v1;
    double d20 = v2 * v0;
    double d21 = v2 * v1;

    double factor = 1.0 / (d00 * d11 - d01 * d01);

    double v = (d11 * d20 - d01 * d21) * factor;
    double w = (d00 * d21 - d01 * d20) * factor;
    double u = 1.0 - v - w;

    return u * texture[0] + v * texture[1] + w * texture[2];
}

// Barycentric interpolation between the three vertex colors based on the position of the point within the triangle
color_t Polygon::get_color(double x, double y, double z)
{
    Vector3 p(x, y, z);
    return get_color(p);
}

void Polygon::set_normal(Vector3 &normal)
{
    set_normal(normal.x, normal.y, normal.z);
}

void Polygon::set_normal(double x, double y, double z)
{
    normal.x = x;
    normal.y = y;
    normal.z = z;
    normal.normalize();
}

void Polygon::align_normal(int x, int y, int z)
{
    normal.x *= (x >= 0) * 2 - 1;
    normal.y *= (y >= 0) * 2 - 1;
    normal.z *= (z >= 0) * 2 - 1;
}