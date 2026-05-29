#include <string>
#include <stb_image.h>

#include "color.h"

typedef class Texture
{
private:
    color_t *map;

public:
    int width, height;

    Texture(std::string filename);
    ~Texture();

    color_t get_color(double u, double v);
} texture_t;