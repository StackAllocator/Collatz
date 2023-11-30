#ifndef DRAWHELPERS_H
#define DRAWHELPERS_H
#include "math.h"
#include "raylib.h"
#include <iostream>


void Arrow(Vector2 start, Vector2 end, bool Bothsides, Color color);
float calcLineLength(Vector2 start, Vector2 end);
float min(float x, float y);



#endif