#ifndef ALGO_H
#define ALGO_H
#include "Coordinatesystem.h"
#include "raylib.h"
#include "drawhelpers.h"
#include <math.h>
#include <iostream>

enum class modes {
    AIAD = 0,
    AIMD = 1,
    MIAD = 2,
    MIMD = 3
};

void DrawGame(int startx, int starty, int it, int K, modes mode1, modes mode2, Vector2 AIADf, Vector2 AIMDf, Vector2 MIADf, Vector2 MIMDf, Coordinatesystem sys);

void draw(int sx, int sy, int K, int it, modes mode1, modes mode2, Vector2 AIADf, Vector2 AIMDf, Vector2 MIADf, Vector2 MIMDf, Coordinatesystem sys);

//void AIAD(int startx, int starty, int it, Vector2 wpadding, int screenHeight, int screenWidth, int offsetX, int offsetY, int zoomMultX, int zoomMultY, int distanceX, int distanceY, int K);

void conjAvoid(int& x, int& y, modes mode1, modes mode2, int K, Vector2 AIADf, Vector2 AIMDf, Vector2 MIADf, Vector2 MIMDf);

int max(int x, int y);

int AIAD(int start1, int start2, int K, bool xy, Vector2 AIADf);
int AIMD(int start1, int start2, int K, bool xy, Vector2 AIMDf);
int MIAD(int start1, int start2, int K, bool xy, Vector2 MIADf);
int MIMD(int start1, int start2, int K, bool xy, Vector2 MIMDf);


#endif