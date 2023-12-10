#include <math.h>
#include <iostream>
#include "perlin.hpp"
#include <windows.h>

#define GRID_SIZE 60

typedef struct Coord {
    int x;
    int y;
    float val;
} Coord;

typedef struct ColorRGB {
    int red;
    int green;
    int blue;
} ColorRGB;

ColorRGB interpolate_RGB(ColorRGB, ColorRGB, float);

int main() {

    ColorRGB color_source = {255, 0, 0};
    ColorRGB color_destination = {255, 255, 255};

    Coord grid[GRID_SIZE*GRID_SIZE];
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            Perlin perlin((float)j/GRID_SIZE, (float)i/GRID_SIZE);
            float value = perlin.perlin();
            value = (value * 0.5) + 0.5;
            Coord coord = {i, j, value};
            grid[i+j] = coord;
            ColorRGB result_color = interpolate_RGB(color_source, color_destination, value);
            printf("\x1b[38;2;%i;%i;%im0\x1b[0m", result_color.red, result_color.green, result_color.blue);
        }
        printf("\n");
    }
    return 0;
}

ColorRGB interpolate_RGB(ColorRGB c_source, ColorRGB c_dest, float t) {
    ColorRGB color;
    color.red = c_source.red + (c_dest.red - c_source.red) * t;
    color.green = c_source.green + (c_dest.green - c_source.green) * t;
    color.blue = c_source.blue + (c_dest.blue - c_source.blue) * t;
    return color;
}