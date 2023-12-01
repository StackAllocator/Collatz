#include "drawall.h"
Vector2 pos{};
Color col{};

void drawall(int &num, int &sequenz, int &sequenzItem, int &start, int &colorVal, int &animationSpeed, bool &pause, Color colors[], Coordinatesystem sys)
{
    sys.draw();
    int txtposition = 200;
    if (num == 1 && sequenz < colorVal && !pause)
    {
        sequenz++;
        sequenzItem = 0;
    }

    if (animationSpeed > 0)
    {
        sequenzItem += animationSpeed;
        DrawText(TextFormat("sequenzItem: %i", sequenzItem), GetScreenWidth() - txtposition * 2, 50, 20, BLACK);

        DrawText(TextFormat("animationSpeed: %i", animationSpeed), GetScreenWidth() - txtposition * 2, 100, 20, BLACK);
    }
    else
    {
        sequenzItem = sequenzItem - 1 / animationSpeed;
        DrawText(TextFormat("sequenzItem: 1/%i", -sequenzItem), GetScreenWidth() - txtposition * 2, 50, 20, BLACK);

        DrawText(TextFormat("animationSpeed: %i", animationSpeed), GetScreenWidth() - txtposition * 2, 100, 20, BLACK);
    }
    for (int i = start; i < sequenz; i++)
    {
        num = i;
        int count = 0;
        int old_y = sys.adjust(num, false);
        int old_x = sys.adjust(0, true);
        pos.y = old_y;
        pos.x = old_x;
        do
        {
            num = Collatz::next(num);
            count++;
            old_x = pos.x;
            old_y = pos.y;
            pos.y = sys.adjust(num, false);
            pos.x = sys.adjust(count, true);
            DrawLine(old_x, old_y, pos.x, pos.y, colors[i]);
        } while ((num > 1));
        DrawText(TextFormat("num: %i", num), GetScreenWidth() - 500, 650, 20, BLACK);
    }
    if (sequenz > 0)
    {
        num = sequenz;
        int count = 0;
        int old_y = sys.adjust(num, false);
        int old_x = sys.adjust(0, true);
        pos.y = old_y;
        pos.x = old_x;
        while (num > 1 && count < sequenzItem - 1)
        {
            num = Collatz::next(num);
            count++;
            old_x = pos.x;
            old_y = pos.y;
            pos.y = sys.adjust(num, false);
            pos.x = sys.adjust(count, true);
            DrawLine(old_x, old_y, pos.x, pos.y, colors[sequenz]);
        }
    }       
    for (int i = start; i < sequenz; i++)
    {
        num = i;
        int count = 0;
        pos.x = sys.adjust(0, true);
        pos.y = sys.adjust(num, false);
        do
        {
            num = Collatz::next(num);
            count++;
            DrawCircle(pos.x, pos.y, 3, colors[i]);
            pos.y = sys.adjust(num, false);
            pos.x = sys.adjust(count, true);
        } while ((num > 1));
        DrawCircle(pos.x, pos.y, 3, colors[i]);
    }
    if (sequenz >= 1)
    {
        num = sequenz;
        int count = 0;
        pos.x = sys.adjust(0, true);
        pos.y = sys.adjust(num, false);
        while (num > 1 && count < sequenzItem - 1)
        {
            num = Collatz::next(num);
            count++;
            DrawCircle(pos.x, pos.y, 3, colors[sequenz]);
            pos.y = sys.adjust(num, false);
            pos.x = sys.adjust(count, true);
        }
        // std::cout << num << ", ";
    }
    // if (num == 1) {
    //     std::cout << std::endl;
    // }
    // DrawLine(wpadding.x, 0, wpadding.x, screenHeight, BLACK);
    // for (int i = 0; i <= screenHeight - wpadding.y; i += distanceY)
    // {
    //     int n = (int)((i * zoomMultY) / distanceY) + (offsetY);
    //     DrawText(TextFormat("%i", n), 5, screenHeight - wpadding.y - i, 15, BLUE);
    //     DrawLine(wpadding.x - 5, screenHeight - wpadding.y - i,
    //              wpadding.x + 5, screenHeight - wpadding.y - i, BLACK);
    //     DrawLine(0, screenHeight - wpadding.y, screenWidth,
    //              screenHeight - wpadding.y, BLACK);
    // }
    // for (int i = 0; i < screenWidth; i += distanceX)
    // {
    //     int n = (i * zoomMultX) / distanceX + (offsetX);
    //     DrawText(TextFormat("%i", n), wpadding.x + i,
    //              screenHeight - wpadding.y + 10, 15, BLACK);
    //     DrawLine(wpadding.x + i, screenHeight - wpadding.y + 5,
    //              wpadding.x + i, screenHeight - wpadding.y - 5, BLACK);
    // }
    // sys.update();

    DrawLine(sys.getX0(), sys.adjust(0, false), sys.adjust(0, true), sys.adjust(0, false), GRAY);
    DrawLine(sys.adjust(0, true), sys.getY0(), sys.adjust(0, true), sys.adjust(0, false), GRAY);
    // DrawText(TextFormat("FPS: %i", fps), screenWidth - txtposition, 50, 20, BLACK);
    // DrawText(TextFormat("sequenzItem: %i", sequenzItem), screenWidth - txtposition, 100, 20, BLACK);
    // DrawText(TextFormat("sequenz: %i/%i", sequenz, colorVal), screenWidth - txtposition, 150, 20, BLACK);
    // DrawText(TextFormat("start: %i <> %i", start, colorVal), screenWidth - txtposition, 200, 20, BLACK);
    // DrawText(TextFormat("zoomMultX: %i", zoomMultX), screenWidth - txtposition, 250, 20, BLACK);
    // DrawText(TextFormat("zoomMultY: %i", zoomMultY), screenWidth - txtposition, 300, 20, BLACK);
    // DrawText(TextFormat("offsetX: %i", offsetX), screenWidth - txtposition, 350, 20, BLACK);
    // DrawText(TextFormat("offsetY: %i", offsetY), screenWidth - txtposition, 400, 20, BLACK);
    // DrawText(TextFormat("color: (%d, %d, %d)", col.r, col.g, col.b), screenWidth - txtposition, 450, 20, BLACK);
    // DrawText(TextFormat("num: %i", num), screenWidth - txtposition, 500, 20, BLACK);
    // DrawText(TextFormat("Speed: %i", animationSpeed), screenWidth - txtposition, 550, 20, BLACK);
}