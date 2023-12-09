#include <math.h>
#include <iostream>
#include "perlin.hpp"
#include <windows.h>

#define GRID_SIZE 30

typedef struct Coord {
    int x;
    int y;
    float val;
} Coord;

int main() {

    HANDLE hConsole;
    int k;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD wAttributes = 

    SetConsoleTextAttribute(hConsole, 4);
    printf("%3d %s\n", 4, "Sample text");
    SetConsoleTextAttribute(hConsole, 0);

    Coord grid[GRID_SIZE*GRID_SIZE];
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            Perlin perlin((float)j/GRID_SIZE, (float)i/GRID_SIZE);
            float value = perlin.perlin();
            value = (value * 0.5) + 0.5;
            Coord coord = {i, j, value};
            grid[i+j] = coord;
            std::cout << "Value is: " << value << std::endl;
        }
    }
    return 0;
}