#pragma once

#include "Polygon.h"

/*
 * Each mesh is a linkedlist of polygons, which is a subsets of the engine's global mesh
 */
typedef struct Item
{
    polygon_t *polygon;
    Item *next;
    Item *prev;
} polylistitem_t;

class PolygonList
{
public:
    polylistitem_t *head;
    polylistitem_t *tail;

    PolygonList();
    ~PolygonList();

    polylistitem_t *add(polygon_t *poly);

    void remove(polylistitem_t *pi);
};