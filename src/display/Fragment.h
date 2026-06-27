#pragma once

#include <matrixmath>

#include "Color.h"

struct Fragment {
    int x;
    int y;
    double z;

    color_t color;
} typedef fragment_t;