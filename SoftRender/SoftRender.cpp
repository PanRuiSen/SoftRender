#include <iostream>
#include <algorithm>
#include "BMP.h"
#include "Vector.h"

#define OUTPUT_PATH_NAME ("out.bmp")

constexpr int ImageWidth = 800;
constexpr int ImageHeight = 600;

BMP g_bmp(ImageWidth, ImageHeight, false);


inline float Clamp(float value, float min, float max)
{
    if (value < min)
        value = min;
    else if (value > max)
        value = max;
    return value;
}

void WriteColor(int x, int y, const Vec3f& color)
{
    if (x >= ImageWidth)
        return;
    if (y >= ImageHeight)
        return;

    int r = Clamp(color.r * 255.999, 0, 255);
    int g = Clamp(color.g * 255.999, 0, 255);
    int b = Clamp(color.b * 255.999, 0, 255);


    g_bmp.set_pixel(x, (ImageHeight - 1) - y, b, g, r, 255);
}

float CalcEdge(const Vec2i& v0, const Vec2i& v1, const Vec2i& v2)
{
    Vec2f a = v1 - v0;
    Vec2f b = v2 - v0;

    return a.x * b.y - b.x * a.y;
}


void DrawTriangle(const Vec2i& v0, const Vec2i& v1, const Vec2i& v2, const Vec3f& c0, const Vec3f& c1, const Vec3f& c2)
{
    Vec2i min(v0);
    Vec2i max(v2);

    min.x = std::min(min.x, v1.x);
    min.x = std::min(min.x, v2.x);

    min.y = std::min(min.y, v1.y);
    min.y = std::min(min.y, v2.y);

    max.x = std::max(max.x, v0.x);
    max.x = std::max(max.x, v1.x);

    max.y = std::max(max.y, v0.y);
    max.y = std::max(max.y, v1.y);

    float area = CalcEdge(v0, v1, v2);

    for (int i = min.x; i <= max.x; ++i)
    {
        for (int j = min.y; j <= max.y; ++j)
        {
            float w0 = CalcEdge(Vec2i(i, j), v1, v2);
            float w1 = CalcEdge(Vec2i(i, j), v2, v0);
            float w2 = CalcEdge(Vec2i(i, j), v0, v1);

            if (w0 >= 0 && w1 >= 0 && w2 >= 0)
            {
                w0 /= area;
                w1 /= area;
                w2 /= area;

                Vec3f c = w0 * c0 + w1 * c1 + w2 * c2;

                WriteColor(i, j, c);
            }
        }
    }

}



int main()
{
    Vec2i vert[] =
    {
        Vec2i(300, 300),
        Vec2i(300, 100),
        Vec2i(500, 300),
    };

    Vec3f colors[] =
    {
        Vec3f(1, 0, 0),
        Vec3f(0, 1, 0),
        Vec3f(0, 0, 1),
    };


    DrawTriangle(vert[0], vert[1], vert[2], colors[0], colors[1], colors[2]);


    g_bmp.write(OUTPUT_PATH_NAME);

    system(OUTPUT_PATH_NAME);

    std::cout << "Hello World!\n";
}