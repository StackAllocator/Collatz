#ifndef DRAWALL_H
#define DRAWALL_H
#include "raylib.h"
#include "Collatz.h"
#include "Coordinatesystem.h"

void drawall(int &num, int &sequenz, int &sequenzItem, int &start, int &colorVal, int &animationSpeed, int &screenWidth, int &screenHeight, bool &pause, int &distanceX, int &distanceY, int &zoomMultX, int &zoomMultY, int &offsetX, int &offsetY, Color colors[], Vector2 wpadding, Coordinatesystem sys);

#endif