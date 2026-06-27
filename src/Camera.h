#pragma once

#define _USE_MATH_DEFINES

#include <cmath>
#include <algorithm>

#include "display/Color.h"
#include "display/Fragment.h"
#include "Engine.h"
#include "geometry/Polygon.h"
#include "List.h"

class Camera
{
private:
    Engine *engine;

    int width = 1920, height = 1080;

    Vector3 position;

    double yaw;
    double pitch;
    double roll;

    Matrix44 view_transform;
    Matrix44 projection_transform;
    Matrix44 viewport_transform;

    polygonlist_t screen_space;

    Fragment **color_buffer;
    struct DepthElement
    {
        Fragment *fragment;
        DepthElement *next;
    } *depth_buffer;

    Fragment **reset_color_buffer()
    {
        if (color_buffer)
            free(color_buffer);
        return color_buffer = (Fragment**) malloc(width * height * sizeof(Fragment *));
    };

    DepthElement *reset_depth_buffer()
    {
        if (depth_buffer)
            free(depth_buffer);
        return depth_buffer = (DepthElement*) malloc(width * height * sizeof(DepthElement));
    };

public:
    Camera(Engine *engine, Vector3 position);
    Camera(Engine *engine, double x, double y, double z);
    ~Camera();

    inline int get_width() { return width; }
    inline int get_height() { return height; }

    inline void set_resolution(int width, int height)
    {
        this->width = width;
        this->height = height;
    }

    inline void move(double x, double y, double z)
    {
        position.replace(x, y, z);
    }

    inline void rotate(double yaw, double pitch)
    {
        this->yaw = std::clamp(this->yaw + yaw, -M_PI, M_PI);
        this->pitch = std::clamp(this->pitch + pitch, -M_PI_2, M_PI_2);
    }

    Matrix44 &getViewMatrix() { return view_transform; };
    Matrix44 &update_view_matrix();

    Matrix44 &get_projection_matrix() { return projection_transform; }
    Matrix44 &update_projection_matrix(double near, double far, double left, double right, double top, double bottom);

    Matrix44 &get_viewport_transform() { return viewport_transform; }
    Matrix44 &update_viewport_transform();

    polygonlist_t *convert_to_screen_space(polygonlist_t &mesh);
    Vector3 *convert_to_screen_space(Vector3 &polygon);
    polygon_t *convert_to_screen_space(polygon_t &polygon);
    void create_fragments(polygon_t &polygon);

    Fragment **get_color_buffer() { return color_buffer; }
    Fragment **update_color_buffer(polygonlist_t *polygon_list);

    DepthElement *get_depth_buffer() { return depth_buffer; }
    DepthElement *update_depth_buffer(polygonlist_t *polygon_list);
};