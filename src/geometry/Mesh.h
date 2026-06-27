#pragma once

#include "Polygon.h"
#include "../List.h"

class Mesh
{
private:
    polygonlist_t polychain;
    vertexlist_t vertexchain;

public:
    friend class Engine;

    Mesh();
    ~Mesh();

    void add_polygon(polygon_t *poly) { polychain.add(poly); };
    void add_vertex(vertex_t *vertex) { vertexchain.add(vertex); }

    inline polylistitem_t *get_mesh_head() { return polychain.head; };
    inline polylistitem_t *get_mesh_tail() { return polychain.tail; };

    inline vertexlistitem_t *get_vertex_head() { return vertexchain.head; };
    inline vertexlistitem_t *get_vertex_tail() { return vertexchain.tail; };
};