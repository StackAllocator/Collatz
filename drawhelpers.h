#ifndef DRAWHELPERS_H
#define DRAWHELPERS_H
#include "raylib.h"
#include "math.h"

void Arrow(Vector2 start, Vector2 end, bool Bothsides, Color color);
float calcLineLength(Vector2 start, Vector2 end);

#endif