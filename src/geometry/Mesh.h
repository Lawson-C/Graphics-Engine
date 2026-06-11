#pragma once

#include "Polygon.h"
#include "List.h"

class Mesh
{
private:
    int poly_count;
    polygonlist_t *polychain;

    friend class Engine;

public:
    Mesh() { *(polychain) = {}; }

    inline void add_polygon(polygon_t *poly) { polychain->add(poly); }

    inline polylistitem_t *get_head() { return polychain->head; };
    inline polylistitem_t *get_tail() { return polychain->tail; };
};