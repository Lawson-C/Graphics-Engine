#include "PolygonList.h"

polylistitem_t *PolygonList::add(polygon_t *poly)
{
    polylistitem_t *pi = new polylistitem_t{
        .polygon = poly,
        .next = tail,
        .prev = tail->prev};
    tail->prev->next = pi;
    tail->prev = pi;
    return pi;
}

void PolygonList::remove(polylistitem_t *pi)
{
    pi->prev->next = pi->next;
    delete pi;
}

PolygonList::PolygonList()
{
    head = new polylistitem_t{
            .polygon = nullptr,
            .next = tail,
            .prev = nullptr};
    tail = new polylistitem_t{
        .polygon = nullptr,
        .next = nullptr,
        .prev = head};
}

PolygonList::~PolygonList()
{
    while (tail->prev != head)
    {
        remove(head->next);
    }
    delete head;
    delete tail;
}