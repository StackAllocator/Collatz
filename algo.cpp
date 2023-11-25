#include "algo.h"

void draw(int sx, int sy, Vector2 wpadding, int screenHeight, int screenWidth, int offsetX, int offsetY, int zoomMultX, int zoomMultY, int distanceX, int distanceY, int K, int it, modes mode1, modes mode2) {
    offsetX--;
    offsetY--;
    DrawLine(wpadding.x, 0, wpadding.x, screenHeight, BLACK);
    for (int i = 0; i <= screenHeight - wpadding.y; i += distanceY)
    {
        int n = (int)((i * zoomMultY) / distanceY) + (offsetY);
        DrawText(TextFormat("%i", n), 5, screenHeight - wpadding.y - i, 15, BLUE);
        DrawLine(wpadding.x - 5, screenHeight - wpadding.y - i,
                 screenWidth, screenHeight - wpadding.y - i, BLACK);
    }
        DrawLine(0, screenHeight - wpadding.y, screenWidth,
                 screenHeight - wpadding.y, BLACK);
    for (int i = 0; i < screenWidth; i += distanceX)
    {
        int n = (i * zoomMultX) / distanceX + (offsetX);
        DrawText(TextFormat("%i", n), wpadding.x + i,
                 screenHeight - wpadding.y + 10, 15, BLACK);
        DrawLine(wpadding.x + i, 0,
                 wpadding.x + i, screenHeight - wpadding.y - 5, BLACK);
    }
    DrawLineEx(Vector2{wpadding.x - offsetX * distanceX / zoomMultX, screenHeight - wpadding.y - K * distanceY / zoomMultY + offsetY * distanceY / zoomMultY}, Vector2{wpadding.x + K * distanceX / zoomMultX - offsetX * distanceX / zoomMultX, screenHeight - wpadding.y + offsetY * distanceY / zoomMultY}, 3, DARKGREEN);

    DrawLineEx(Vector2{wpadding.x - offsetX * distanceX, screenHeight - wpadding.y + offsetY * distanceY}, Vector2{wpadding.x + K * distanceX * zoomMultX - offsetX * distanceX, screenHeight - wpadding.y - K * distanceY * zoomMultY + offsetY * distanceY}, 3, RED);

    DrawGame(sx, sy, it, wpadding, screenHeight, screenWidth, offsetX, offsetY, zoomMultX, zoomMultY, distanceX, distanceY, K, mode1, mode2);

}

void conjAvoid(int& x, int& y, modes mode1, modes mode2, int K) {
    int oldx = x;
    switch(mode1){
        case modes::AIAD:
            x = AIAD(x, y, K, true); 
            break;
        case modes::AIMD:
            x = AIMD(x, y, K, true);
            break;
        case modes::MIAD:
            x = MIAD(x, y, K, true);
            break;
        case modes::MIMD:
            x = MIMD(x, y, K, true);
            break;
        default:
            x = x + 1;
    }
    switch(mode2){
        case modes::AIAD:
            y = AIAD(oldx, y, K, false); 
            break;
        case modes::AIMD:
            y = AIMD(oldx, y, K, false);
            break;
        case modes::MIAD:
            y = MIAD(oldx, y, K, false);
            break;
        case modes::MIMD:
            y = MIMD(oldx, y, K, false);
            break;
        default:
            y = y + 1;
    }
}

void DrawGame(int startx, int starty, int it, Vector2 wpadding, int screenHeight, int screenWidth, int offsetX, int offsetY, int zoomMultX, int zoomMultY, int distanceX, int distanceY, int K, modes mode1, modes mode2) {
    int facx = wpadding.x;
    int facy = screenHeight - wpadding.y; 
    int posx = startx; 
    int posy = starty;
    int oldx = posx;
    int oldy = posy;
    for (int i = 0; i < it; i++) {
        conjAvoid(posx, posy, mode1, mode2, K);
        // if (posy > K - posx) {
        //     posx = (posx - 2); 
        //     posy = (posy - 2);
        //     //DrawLine(facx + oldx * distanceX, facy - oldy * distanceY, facx + posx * distanceX, facy - posy * distanceY, RED);
        DrawLineEx(Vector2{facx + (oldx + 1) * distanceX / zoomMultX, facy - (oldy + 1) * distanceY / zoomMultY}, Vector2{facx + (posx + 1) * distanceX / zoomMultX, facy - (posy + 1) * distanceY / zoomMultY}, 2, RED);
        oldx = posx;
        oldy = posy;
        // }
        // else {
        //     posx = (posx + 2); 
        //     posy = (posy + 2);
        //     DrawLineEx(Vector2{facx + oldx * distanceX, facy - oldy * distanceY}, Vector2{facx + posx * distanceX, facy - posy * distanceY}, 2, DARKGREEN);
        //     oldx = posx;
        //     oldy = posy;
        // }
    }
    DrawText(TextFormat("%i, %i", oldx, oldy), 100, 100, 20, BLACK);
}

int max(int x, int y) {
    if (x > y) {
        return x;
    } else {
        return y;
    }
}

int AIAD(int start1, int start2, int K, bool xy) {
    int ret = 0;
    if (xy) {
        ret = start1;
    } else {
        ret = start2;
    }
    if (start2 <= K - start1) {
        return ret + 2;
    } else {
        return max(0, ret - 2);
    }
}

int AIMD(int start1, int start2, int K, bool xy) {
    int ret = 0;
    if (xy) {
        ret = start1;
    } else {
        ret = start2;
    }
    if (start2 <= K - start1) {
        return ret + 2;
    } else {
        return static_cast<int>(ceil(static_cast<float>(ret) / 2.0f));
    }
}

int MIAD(int start1, int start2, int K, bool xy) {
    int ret = 0;
    if (xy) {
        ret = start1;
    } else {
        ret = start2;
    }
    if (start2 <= K - start1) {
        return max(1, ret * 2);
    } else {
        return max(0, ret - 2);
    }
}

int MIMD(int start1, int start2, int K, bool xy) {
    int ret = 0;
    if (xy) {
        ret = start1;
    } else {
        ret = start2;
    }
    if (start2 <= K - start1) {
        return max(1, ret * 2);
    } else {
        return static_cast<int>(ceil(ret / 2.0f));
    }
}