#include "Polygon.h"

Polygon::Polygon(double data[9])
{
    Point[0] = Vector3(data);
    Point[1] = Vector3(data + 3);
    Point[2] = Vector3(data + 6);
}

Polygon::Polygon(double data[3][3])
{
    Point[0] = Vector3(data[0]);
    Point[1] = Vector3(data[1]);
    Point[2] = Vector3(data[2]);
}

Polygon::Polygon(Vector3 points[3])
{
    Point[0] = points[0];
    Point[1] = points[1];
    Point[2] = points[2];
}

Polygon::Polygon(Vector3 point0, Vector3 point1, Vector3 point2)
{
    Point[0] = point0;
    Point[1] = point1;
    Point[2] = point2;
}