#define STB_IMAGE_IMPLEMENTATION
#include "Texture.h"

Texture::Texture(std::string filename)
{
    int channels;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &channels, 0);

    if (data)
    {
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                map[x + y * width] = {.raw = (uint32_t)*(data + (y * width + x) * channels)};
            }
        }
        if (channels == 3)
        {
            for (int i = 0; i < width * height; i++)
            {
                map[i].alpha = 255;
            }
        }
        stbi_image_free(data);
    }
    else
    {
        map = new color_t{.raw = WHITE.raw};
    }
}

Texture::~Texture()
{
    delete[] map;
}

color_t Texture::get_color(double u, double v)
{
    int x = (int)(u * width);
    int y = (int)(v * height);
    if (x < 0 || x >= width || y < 0 || y >= height)
    {
        return BLACK;
    }
    return map[x + y * width];
}