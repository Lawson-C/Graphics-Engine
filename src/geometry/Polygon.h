#pragma once

#include <matrixmath>

class Polygon
{
private:
    Vector3 *Point;

public:
    inline Polygon(double data[9]) : Point(new Vector3[]{Vector3(data), Vector3(data + 3), Vector3(data + 6)}) {}
    inline Polygon(double data[3][3]) : Point(new Vector3[]{Vector3(data[0]), Vector3(data[1]), Vector3(data[2])}) {}
    inline Polygon(Vector3 points[3]) : Point(new Vector3[]{points[0], points[1], points[2]}) {}
    inline Polygon(Vector3 &point0, Vector3 &point1, Vector3 &point2) : Point(new Vector3[]{point0, point1, point2}) {}
    inline ~Polygon() { delete[] Point; }
};