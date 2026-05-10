#pragma once

#include "Polygon.h"
#include "PolygonList.h"

class Mesh
{
private:
    int poly_count;
    PolygonList *polychain;

public:
    Mesh();

    inline void add_polygon(polygon_t *poly) { polychain->add(poly); }

    inline polylistitem_t *get_head() {return polychain->head;};
    inline polylistitem_t *get_tail() {return polychain->tail;};
};