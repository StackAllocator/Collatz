#include "algo.h"

void draw(int sx, int sy, int K, int it, modes mode1, modes mode2, Vector2 AIADf, Vector2 AIMDf, Vector2 MIADf, Vector2 MIMDf, Coordinatesystem sys) {
    // offsetX--;
    // offsetY--;
    sys.draw(true);
    // DrawLine(wpadding.x, 0, wpadding.x, screenHeight, BLACK);
    // for (int i = 0; i <= screenHeight - wpadding.y; i += distanceY)
    // {
    //     int n = (int)((i * zoomMultY) / distanceY) + (offsetY);
    //     DrawText(TextFormat("%i", n), 5, screenHeight - wpadding.y - i, 15, BLUE);
    //     DrawLine(wpadding.x - 5, screenHeight - wpadding.y - i,
    //              screenWidth, screenHeight - wpadding.y - i, BLACK);
    // }
    //     DrawLine(0, screenHeight - wpadding.y, screenWidth,
    //              screenHeight - wpadding.y, BLACK);
    // for (int i = 0; i < screenWidth; i += distanceX)
    // {
    //     int n = (i * zoomMultX) / distanceX + (offsetX);
    //     DrawText(TextFormat("%i", n), wpadding.x + i,
    //              screenHeight - wpadding.y + 10, 15, BLACK);
    //     DrawLine(wpadding.x + i, 0,
    //              wpadding.x + i, screenHeight - wpadding.y - 5, BLACK);
    // }
    DrawLine(sys.adjust(0, true), sys.adjust(0, false), sys.adjust(10, true), sys.adjust(10, false), DARKBLUE);
    DrawLineEx(Vector2{sys.adjust(0, true), sys.adjust(K, false)}, Vector2{sys.adjust(K, true), sys.adjust(0, false)}, 3, DARKGREEN);
    //Arrow(Vector2{facx + (oldx + 1) * distanceX / zoomMultX, facy - (oldy + 1) * distanceY / zoomMultY}, Vector2{facx + (posx + 1) * distanceX / zoomMultX, facy - (posy + 1) * distanceY / zoomMultY}, false, GREEN);

    DrawLineEx(Vector2{sys.adjust(0, true), sys.adjust(0, false)}, Vector2{sys.adjust(K, true), sys.adjust(K, false)}, 3, RED);

    // DrawLineEx(Vector2{wpadding.x - offsetX * distanceX, screenHeight - wpadding.y + offsetY * distanceY}, Vector2{wpadding.x + K * distanceX * zoomMultX - offsetX * distanceX, screenHeight - wpadding.y - K * distanceY * zoomMultY + offsetY * distanceY}, 3, RED);

    DrawGame(sx, sy, it, K, mode1, mode2, AIADf, AIMDf, MIADf, MIMDf, sys);

}

void conjAvoid(int& x, int& y, modes mode1, modes mode2, int K, Vector2 AIADf, Vector2 AIMDf, Vector2 MIADf, Vector2 MIMDf) {
    int oldx = x;
    switch(mode1){
        case modes::AIAD:
            x = AIAD(x, y, K, true, AIADf); 
            break;
        case modes::AIMD:
            x = AIMD(x, y, K, true, AIMDf);
            break;
        case modes::MIAD:
            x = MIAD(x, y, K, true, MIADf);
            break;
        case modes::MIMD:
            x = MIMD(x, y, K, true, MIMDf);
            break;
        default:
            x = x + 1;
    }
    switch(mode2){
        case modes::AIAD:
            y = AIAD(oldx, y, K, false, AIADf); 
            break;
        case modes::AIMD:
            y = AIMD(oldx, y, K, false, AIMDf);
            break;
        case modes::MIAD:
            y = MIAD(oldx, y, K, false, MIADf);
            break;
        case modes::MIMD:
            y = MIMD(oldx, y, K, false, MIMDf);
            break;
        default:
            y = y + 1;
    }
}

void DrawGame(int startx, int starty, int it, int K, modes mode1, modes mode2, Vector2 AIADf, Vector2 AIMDf, Vector2 MIADf, Vector2 MIMDf, Coordinatesystem sys) {
    int facx = sys.adjust(0, true);
    int facy = sys.adjust(0, false); 
    int posx = startx; 
    int posy = starty;
    int oldx = posx;
    int oldy = posy;
    for (int i = 0; i < it; i++) {
        conjAvoid(posx, posy, mode1, mode2, K, AIADf, AIMDf, MIADf, MIMDf);
        // if (posy > K - posx) {
        //     posx = (posx - 2); 
        //     posy = (posy - 2);
        //     //DrawLine(facx + oldx * distanceX, facy - oldy * distanceY, facx + posx * distanceX, facy - posy * distanceY, RED);
        DrawLineEx(Vector2{sys.adjust(oldx, true), sys.adjust(oldy, false)}, Vector2{sys.adjust(posx, true), sys.adjust(posy, false)}, 2, BLUE);
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

int AIAD(int start1, int start2, int K, bool xy, Vector2 AIADf) {
    int ret = 0;
    if (xy) {
        ret = start1;
    } else {
        ret = start2;
    }
    if (start2 <= K - start1) {
        return ret + AIADf.x;
    } else {
        return max(0, ret - AIADf.y);
    }
}

int AIMD(int start1, int start2, int K, bool xy, Vector2 AIMDf) {
    int ret = 0;
    if (xy) {
        ret = start1;
    } else {
        ret = start2;
    }
    if (start2 <= K - start1) {
        return ret + AIMDf.x;
    } else {
        return static_cast<int>(ceil(static_cast<float>(ret) / AIMDf.y));
    }
}

int MIAD(int start1, int start2, int K, bool xy, Vector2 MIADf) {
    int ret = 0;
    if (xy) {
        ret = start1;
    } else {
        ret = start2;
    }
    if (start2 <= K - start1) {
        return max(1, ret * MIADf.x);
    } else {
        return max(0, ret - MIADf.y);
    }
}

int MIMD(int start1, int start2, int K, bool xy, Vector2 MIMDf) {
    int ret = 0;
    if (xy) {
        ret = start1;
    } else {
        ret = start2;
    }
    if (start2 <= K - start1) {
        return max(1, ret * MIMDf.x);
    } else {
        return static_cast<int>(ceil(ret / MIMDf.y));
    }
}