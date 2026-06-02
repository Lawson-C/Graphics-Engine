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

// Links this list to another by replacing the head of this list with the tail of the other list
void PolygonList::link_head(PolygonList *list)
{
    list->tail->next = head->next;
    head->next->prev = list->tail;
    delete head;
    head = list->tail;
}

// Links this list to another by replacing the tail of this list with the head of the other list
void PolygonList::link_tail(PolygonList *list)
{
    list->head->prev = tail;
    tail->prev->next = list->head;
    delete tail;
    tail = list->head;
}