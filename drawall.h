#ifndef DRAWALL_H
#define DRAWALL_H
#include "raylib.h"
#include "Collatz.h"
#include "Coordinatesystem.h"
#include <iostream>

void drawall(int &num, int &sequenz, int &sequenzItem, int &start, int &colorVal, int &animationSpeed, bool &pause, Color colors[], Coordinatesystem sys);

#endif