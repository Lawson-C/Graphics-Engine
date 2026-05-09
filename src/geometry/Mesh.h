#pragma once

#include<list>

#include "Polygon.h"

class Mesh {
    int polyCount;
    PolygonItem *polychain;
};

/*
* Each mesh is a linkedlist of polygons, which is a subsets of the engine's global mesh 
*/
struct PolygonItem {
    Polygon *polygon;
    PolygonItem *next;
};