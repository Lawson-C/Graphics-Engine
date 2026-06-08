#include "Camera.h"

Camera::Camera(Engine *engine, double x, double y, double z) : engine(engine), position(Vector3(x, y, z)), yaw(0), pitch(0), roll(0)
{
    update_view_matrix();
    update_projection_matrix(0.1, 1000, -1, 1, 1, -1);
    update_viewport_transform();
}

Camera::Camera(Engine *engine, Vector3 pos) : engine(engine), position(Vector3(pos.x, pos.y, pos.z)), yaw(0), pitch(0), roll(0)
{
    update_view_matrix();
    update_projection_matrix(0.1, 1000, -1, 1, 1, -1);
    update_viewport_transform();
}

Matrix44 &Camera::update_view_matrix()
{
    double cos_yaw = cos(yaw);
    double sin_yaw = sin(yaw);
    double cos_pitch = cos(pitch);
    double sin_pitch = sin(pitch);
    double cos_roll = cos(roll);
    double sin_roll = sin(roll);
    double X[3] = {cos_yaw * cos_roll + sin_pitch * sin_yaw * sin_roll, -cos_pitch * sin_roll, sin_yaw * cos_roll - sin_pitch * cos_yaw * sin_roll};
    double Y[3] = {-cos_yaw * sin_roll + sin_pitch * sin_yaw * cos_roll, cos_pitch * cos_roll, sin_yaw * sin_roll + sin_pitch * cos_yaw * cos_roll};
    double Z[3] = {-cos_pitch * sin_yaw, sin_pitch, -cos_yaw * cos_pitch};
    return view_transform = Matrix44(new double[16]{
               X[0], X[1], X[2], -(X[0] * position.x + X[1] * position.y + X[2] * position.z),
               Y[0], Y[1], Y[2], -(Y[0] * position.x + Y[1] * position.y + Y[2] * position.z),
               Z[0], Z[1], Z[2], -(Z[0] * position.x + Z[1] * position.y + Z[2] * position.z),
               0, 0, 0, 1});
}

Matrix44 &Camera::update_projection_matrix(double near, double far, double left, double right, double top, double bottom)
{
    return projection_transform = Matrix44(new double[16]{
               2 * near / (right - left), 0, (left - right) / (right - left), 0,
               0, 2 * near / (top - bottom), (bottom - top) / (top - bottom), 0,
               0, 0, (far + near) / (far - near), 2 * far * near / (near - far),
               0, 0, 1, 0});
}

Matrix44 &Camera::update_viewport_transform()
{
    return viewport_transform = Matrix44(new double[16]{
               (double)width / 2, 0, 0, ((double)width - 1) / 2,
               0, (double)height / -2, 0, ((double)height - 1) / 2,
               0, 0, 1, 0,
               0, 0, 0, 1});
}

Vector4 Camera::translate_to_screen_space(Vector3 &point)
{
    Vector4 point4d = Vector4(point.x, point.y, point.z, 1);
    Vector4 view_space_point = view_transform * point4d;
    Vector4 clip_space_point = projection_transform * view_space_point;
    if (clip_space_point.w != 0)
    {
        clip_space_point.x /= clip_space_point.w;
        clip_space_point.y /= clip_space_point.w;
        clip_space_point.z /= clip_space_point.w;
    }
    Vector4 screen_space_point = viewport_transform * clip_space_point;
    return screen_space_point;
}