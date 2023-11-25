#ifndef ALGO_H
#define ALGO_H
#include "Coordinatesystem.h"
#include "raylib.h"
#include <math.h>
#include <iostream>

enum class modes {
    AIAD = 0,
    AIMD = 1,
    MIAD = 2,
    MIMD = 3
};

void DrawGame(int startx, int starty, int it, Vector2 wpadding, int screenHeight, int screenWidth, int offsetX, int offsetY, int zoomMultX, int zoomMultY, int distanceX, int distanceY, int K, modes mode1, modes mode2);

void draw(int sx, int sy, Vector2 wpadding, int screenHeight, int screenWidth, int offsetX, int offsetY, int zoomMultX, int zoomMultY, int distanceX, int distanceY, int K, int it, modes mode1, modes mode2);


void AIAD(int startx, int starty, int it, Vector2 wpadding, int screenHeight, int screenWidth, int offsetX, int offsetY, int zoomMultX, int zoomMultY, int distanceX, int distanceY, int K);

void conjAvoid(int& x, int& y, modes mode1, modes mode2, int K);

int max(int x, int y);

int AIAD(int start1, int start2, int K, bool xy);
int AIMD(int start1, int start2, int K, bool xy);
int MIAD(int start1, int start2, int K, bool xy);
int MIMD(int start1, int start2, int K, bool xy);


#endif