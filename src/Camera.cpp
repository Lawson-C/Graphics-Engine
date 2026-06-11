#include "Camera.h"

Camera::Camera(Engine *engine, double x, double y, double z) : engine(engine), screen_space(), position(Vector3(x, y, z)), yaw(0), pitch(0), roll(0)
{
    update_view_matrix();
    update_projection_matrix(0.1, 1000, -1, 1, 1, -1);
    update_viewport_transform();
    reset_color_buffer();
    reset_depth_buffer();
}

Camera::Camera(Engine *engine, Vector3 pos) : engine(engine), screen_space(), position(Vector3(pos.x(), pos.y(), pos.z())), yaw(0), pitch(0), roll(0)
{
    update_view_matrix();
    update_projection_matrix(0.1, 1000, -1, 1, 1, -1);
    update_viewport_transform();
    reset_color_buffer();
    reset_depth_buffer();
}

Camera::~Camera()
{
    if (color_buffer)
    {
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                free(color_buffer + x * width + y);
            }
        }
        free(color_buffer);
    }
    if (depth_buffer)
    {
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                DepthElement *current = depth_buffer + x * width + y;
                while (current)
                {
                    DepthElement *next = current->next;
                    free(current);
                    current = next;
                }
            }
        }
        free(depth_buffer);
    }
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
               X[0], X[1], X[2], -(X[0] * position.x() + X[1] * position.y() + X[2] * position.z()),
               Y[0], Y[1], Y[2], -(Y[0] * position.x() + Y[1] * position.y() + Y[2] * position.z()),
               Z[0], Z[1], Z[2], -(Z[0] * position.x() + Z[1] * position.y() + Z[2] * position.z()),
               0, 0, 0, 1});
}

Matrix44 &Camera::update_projection_matrix(double n, double f, double l, double r, double t, double b)
{
    return projection_transform = Matrix44(new double[16]{
               2 * n / (r - l), 0, (l - r) / (r - l), 0,
               0, 2 * n / (t - b), (b - t) / (t - b), 0,
               0, 0, (f + n) / (f - n), 2 * f * n / (n - f),
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

Vector3 *Camera::convert_to_screen_space(Vector3 &point)
{
    Vector4 point4d = Vector4(point.x(), point.y(), point.z(), 1);
    Vector4 view_space_point = view_transform * point4d;
    Vector4 clip_space_point = projection_transform * view_space_point;
    if (clip_space_point.w() != 0)
    {
        clip_space_point /= clip_space_point.w();
    }
    Vector4 screen_space_point = viewport_transform * clip_space_point;
    return new Vector3((int)screen_space_point.x(),
                       (int)screen_space_point.y(),
                       screen_space_point.z());
}

polygon_t *Camera::convert_to_screen_space(polygon_t &polygon)
{
}

void Camera::create_fragments(polygon_t &polygon) {

}

Fragment **Camera::update_color_buffer(PolygonList *polygon_list)
{
    if (!color_buffer)
        color_buffer = (Fragment **)malloc(width * height * sizeof(Fragment *));
    for (polylistitem_t *current = polygon_list->head; current->next; current = current->next)
    {
        if (current->polygon == nullptr)
            continue;
        Fragment &point0 = *convert_to_screen_space(*(current->polygon->vertices[0].vector));
        Fragment &point1 = *convert_to_screen_space(*(current->polygon->vertices[1].vector));
        Fragment &point2 = *convert_to_screen_space(*(current->polygon->vertices[2].vector));
        Vector2 vertices[] = {
            Vector2(point0.x, point0.y),
            Vector2(point1.x, point1.y),
            Vector2(point2.x, point2.y)};
        Vector2 upper = vertices[1] - vertices[0];
        Vector2 lower = vertices[2] - vertices[0];
        double u_len = upper.magnitude();
        double l_len = lower.magnitude();
        Vector2 u_diff = upper / u_len;
        Vector2 l_diff = lower / l_len;
        for (int i = 0; i < u_len; i++)
        {
            Vector2 l = l_diff * i;
            Vector2 u = u_diff * i;
            Vector2 e = l - u;
            double e_len = e.magnitude();
            e /= e_len;
            for (int j = 0; j < e_len; j++)
            {
                Vector2 pix = vertices[0] + u;
                pix + (e *= j);
                if (pix.x() >= 0 && pix.x() > width && pix.y() >= 0 && pix.y() < height)
                {
                    color_buffer[(int)pix.x() * height + (int)pix.y()] = new Fragment{
                        .x = (int)pix.x(),
                        .y = (int)pix.y(),
                        .z = 0,
                        .color = current->polygon->get_color(pix.x(), pix.y(), 0)};
                }
                e /= j;
            }
        }
        return color_buffer;
    }
}