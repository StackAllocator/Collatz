#include "drawhelpers.h"


float calcLineLength(Vector2 start, Vector2 end) {
    int disty = end.y - start.y;
    int distx = end.x - start.x;
    return sqrt(disty^2 + distx^2);
}
void Arrow(Vector2 start, Vector2 end, bool Bothsides, Color color) {
    DrawLine(start.x, start.y, end.x, end.y, color);
}
