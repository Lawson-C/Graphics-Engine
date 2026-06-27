#pragma once

#include "geometry/Polygon.h"

/*
 * Each mesh is a linkedlist of polygons, which is a subsets of the engine's global mesh
 */
template <typename T>
struct ListItem
{
    T item;
    ListItem *next;
    ListItem *prev;
};

typedef ListItem<polygon_t *> polylistitem_t;
typedef ListItem<vertex_t *> vertexlistitem_t;

template <typename T>
class List
{
public:
    ListItem<T> *head;
    ListItem<T> *tail;

    List()
    {
        head = new ListItem<T>{
            .next = tail,
            .prev = nullptr};
        tail = new ListItem<T>{
            .next = nullptr,
            .prev = head};
    }

    ~List()
    {
        while (tail->prev != head)
        {
            remove(head->next);
        }
        if (head->prev)
        {
            remove(tail);
        }
        else if (tail->next)
        {
            remove(head);
        }
        else
        {
            delete head;
            delete tail;
        }
    }

    T *add(T item)
    {
        ListItem<T> *pi = new ListItem<T>{
            .item = item,
            .next = tail,
            .prev = tail->prev};
        tail->prev->next = pi;
        tail->prev = pi;
        return &pi->item;
    }

    void remove(ListItem<T> *pi)
    {
        pi->prev->next = pi->next;
        delete pi;
    }

    void link_head(List<T> &list)
    {
        list.tail->next = head->next;
        head->next->prev = list.tail;
        delete head;
        head = list.tail;
    }

    void link_tail(List<T> &list)
    {
        list.head->prev = tail;
        tail->prev->next = list.head;
        delete tail;
        tail = list.head;
    }
};

typedef List<polygon_t *> polygonlist_t;
typedef List<vertex_t *> vertexlist_t;