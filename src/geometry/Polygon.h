#pragma once

#include <matrixmath>

class Polygon
{
private:
    Vector3 Point[3];

public:
    Polygon(double data[9]);
    Polygon(double data[3][3]);
    Polygon(Vector3 points[3]);
    Polygon(Vector3 point1, Vector3 point2, Vector3 point3);
};