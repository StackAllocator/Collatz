#include "drawhelpers.h"

float calcLineLength(Vector2 start, Vector2 end)
{
    long int disty = abs(end.y - start.y);
    long int distx = abs(end.x - start.x);
    std::cout << distx << " " << disty << std::endl;
    return sqrt(disty ^ 2 + distx ^ 2);
}

float min(float x, float y)
{
    if (x < y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

void Arrow(Vector2 start, Vector2 end, bool Bothsides, Color color)
{
    int distx = end.x - start.x;
    int disty = end.y - start.y;
    DrawLineEx(start, end, 2, color);
    DrawLineEx(end, Vector2{end.x - sin((tan(disty / distx) - 20)) * min(1, calcLineLength(start, end)), GetScreenHeight() - end.y + cos((tan(disty / distx) - 20)) * min(1, calcLineLength(start, end))}, 2, color);
    std::cout << (1/tan(disty / distx) * 180 / 3.1415926);
    DrawLineEx(end, Vector2{end.x - sin((tan(disty / distx) * 180 / 3.1415926 + 20) ) * min(1.0f, calcLineLength(start, end)), GetScreenHeight() - end.y + cos((tan(disty / distx) * 180 / 3.1415926 + 20)) * min(1.0f, calcLineLength(start, end))}, 2, color);
    DrawCircle(end.x - sin((1/tan(disty / distx) * 180 / 3.1415926 + 20) ) * min(1.0f, calcLineLength(start, end)), GetScreenHeight() - end.y + cos((1/tan(disty / distx) * 180 / 3.1415926 + 20)) * min(1.0f, calcLineLength(start, end)), 10, GREEN);
    DrawCircle(end.x - sin((1/tan(disty / distx) * 180 / 3.1415926 - 20) ) * min(1.0f, calcLineLength(start, end)), GetScreenHeight() - end.y + cos((1/tan(disty / distx) * 180 / 3.1415926 - 20)) * min(1.0f, calcLineLength(start, end)), 10, RED);
}
