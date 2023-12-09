#include "perlin.hpp"
#include <cmath>

float dot_grid_gradient(int, int, float, float);
float interpolate(float, float, float, Smoothness);
Vec_2 random_gradient(int, int);

Perlin::Perlin() {
    this->m_x = 0.0f;
    this->m_y = 0.0f;
}

Perlin::Perlin(float x, float y) : m_x(x), m_y(y) {};

Perlin::~Perlin() {};

float Perlin::perlin () {
    int x_0 = (int) floor(this->m_x);
    int x_1 = x_0 + 1;
    int y_0 = (int) floor(this->m_y);
    int y_1 = y_0 + 1;

    float s_x = this->m_x - (float)x_0;
    float s_y = this->m_y - (float)y_0;

    float n_0, n_1, ix_0, ix_1, value;

    n_0 = dot_grid_gradient(x_0, y_0, this->m_x, this->m_y);
    n_1 = dot_grid_gradient(x_1, y_0, this->m_x, this->m_y);
    ix_0 = interpolate(n_0, n_1, s_x, Smoothness::NORMAL);

    n_0 = dot_grid_gradient(x_0, y_1, this->m_x, this->m_y);
    n_1 = dot_grid_gradient(x_1, y_1, this->m_x, this->m_y);
    ix_1 = interpolate(n_0, n_1, s_x, Smoothness::NORMAL);

    value = interpolate(ix_0, ix_1, s_y, Smoothness::NORMAL);
    return value;
}

Vec_2 random_gradient(int ix, int iy) {
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2;
    unsigned a = ix, b = iy;
    a *= 3284157443;
    b ^= a << s | a >> (w - s);
    b *= 1911520717;
    a ^= b << s | b >> (w - s);
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1));
    Vec_2 v;
    v.x = cos(random);
    v.y = sin(random);
    return v;
}

float dot_grid_gradient(int ix, int iy, float x, float y){
    Vec_2 gradient = random_gradient(ix, iy);
    float d_x = x - (float)ix;
    float d_y = y - (float)iy;
    return (d_x*gradient.x + d_y*gradient.y);
}

float interpolate(float a0, float a1, float w, Smoothness smooth){
    switch (smooth)
    {
    case Smoothness::NORMAL:
        return (a1 - a0) * w + a0;
        break;
    case Smoothness::SMOOTH:
        return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
    case Smoothness::SMOOTHER:
        return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
    default:
        return (a1 - a0) * w + a0;
    }
}