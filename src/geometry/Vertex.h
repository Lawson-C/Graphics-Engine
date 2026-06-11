#pragma once

#include <matrixmath>

#include "Color.h"

struct Vertex
{
    Vector3 *vector;
    color_t color;
    bool screen_space = false;
} typedef vertex_t;