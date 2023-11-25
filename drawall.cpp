#include "drawall.h"
Vector2 pos{};
Color col{};

void drawall(int &num, int &sequenz, int &sequenzItem, int &start, int &colorVal, int &animationSpeed, int &screenWidth, int &screenHeight, bool &pause, int &distanceX, int &distanceY, int &zoomMultX, int &zoomMultY, int &offsetX, int &offsetY, Color colors[], Vector2 wpadding, Coordinatesystem sys)
{
    int txtposition = 200;
    if (num == 1 && sequenz < colorVal && !pause)
    {
        sequenz++;
        sequenzItem = 0;
    }

    if (animationSpeed > 0)
    {
        sequenzItem += animationSpeed;
        DrawText(TextFormat("sequenzItem: %i", sequenzItem), screenWidth - txtposition * 2, 50, 20, BLACK);

        DrawText(TextFormat("animationSpeed: %i", animationSpeed), screenWidth - txtposition * 2, 100, 20, BLACK);
    }
    else
    {
        sequenzItem = sequenzItem - 1 / animationSpeed;
        DrawText(TextFormat("sequenzItem: 1/%i", -sequenzItem), screenWidth - txtposition * 2, 50, 20, BLACK);

        DrawText(TextFormat("animationSpeed: %i", animationSpeed), screenWidth - txtposition * 2, 100, 20, BLACK);
    }
    for (int i = start; i < sequenz; i++)
    {
        num = i;
        int count = 0;
        int old_y = screenHeight - wpadding.y - num * distanceY / zoomMultY + (distanceY * offsetY / zoomMultY);
        int old_x = wpadding.x - (distanceX * offsetX / zoomMultX);
        pos.y = old_y;
        pos.x = old_x;
        do
        {
            num = Collatz::next(num);
            count++;
            old_x = pos.x;
            old_y = pos.y;
            pos.y = screenHeight - wpadding.y - distanceY * num / zoomMultY + (offsetY * distanceY / zoomMultY);
            pos.x = wpadding.x + count * distanceX / zoomMultX - (offsetX * distanceX / zoomMultX);
            DrawLine(old_x, old_y, pos.x, pos.y, colors[i]);
        } while ((num > 1));
        DrawText(TextFormat("num: %i", num), screenWidth - 500, 650, 20, BLACK);
    }
    if (sequenz > 0)
    {
        num = sequenz;
        int count = 0;
        int old_y = screenHeight - wpadding.y - num * distanceY / zoomMultY + (distanceY * offsetY / zoomMultY);
        int old_x = wpadding.x - (distanceX * offsetX / zoomMultX);
        pos.y = old_y;
        pos.x = old_x;
        while (num > 1 && count < sequenzItem - 1)
        {
            num = Collatz::next(num);
            count++;
            old_x = pos.x;
            old_y = pos.y;
            pos.y = screenHeight - wpadding.y - distanceY * num / zoomMultY + (offsetY * distanceY / zoomMultY);
            pos.x = wpadding.x + count * distanceX / zoomMultX - (offsetX * distanceX / zoomMultX);
            DrawLine(old_x, old_y, pos.x, pos.y, colors[sequenz]);
        }
    }

    pos.x = wpadding.x;
    pos.y = wpadding.y - 30;
    for (int i = start; i < sequenz; i++)
    {
        num = i;
        int count = 0;
        pos.x = wpadding.x - ((offsetX)*distanceX / zoomMultX);
        pos.y = screenHeight - wpadding.y - num * distanceY / zoomMultY + (offsetY * distanceY / zoomMultY);
        do
        {
            num = Collatz::next(num);
            count++;
            DrawCircle(pos.x, pos.y, 3, colors[i]);
            pos.y = screenHeight - wpadding.y - distanceY * num / zoomMultY + (offsetY * distanceY / zoomMultY);
            pos.x = wpadding.x + count * distanceX / zoomMultX - (offsetX * distanceX / zoomMultX);
        } while ((num > 1));
        DrawCircle(pos.x, pos.y, 3, colors[i]);
    }
    if (sequenz >= 1)
    {
        num = sequenz;
        int count = 0;
        pos.x = wpadding.x - ((offsetX)*distanceX / zoomMultX);
        pos.y = screenHeight - wpadding.y - num * distanceY / zoomMultY + (offsetY * distanceY / zoomMultY);
        while (num > 1 && count < sequenzItem - 1)
        {
            num = Collatz::next(num);
            count++;
            DrawCircle(pos.x, pos.y, 3, colors[sequenz]);
            pos.y = screenHeight - wpadding.y - distanceY * num / zoomMultY + (offsetY * distanceY / zoomMultY);
            pos.x = wpadding.x + count * distanceX / zoomMultX - (offsetX * distanceX / zoomMultX);
        }
        // std::cout << num << ", ";
    }
    // if (num == 1) {
    //     std::cout << std::endl;
    // }
    DrawLine(wpadding.x, 0, wpadding.x, screenHeight, BLACK);
    for (int i = 0; i <= screenHeight - wpadding.y; i += distanceY)
    {
        int n = (int)((i * zoomMultY) / distanceY) + (offsetY);
        DrawText(TextFormat("%i", n), 5, screenHeight - wpadding.y - i, 15, BLUE);
        DrawLine(wpadding.x - 5, screenHeight - wpadding.y - i,
                 wpadding.x + 5, screenHeight - wpadding.y - i, BLACK);
        DrawLine(0, screenHeight - wpadding.y, screenWidth,
                 screenHeight - wpadding.y, BLACK);
    }
    for (int i = 0; i < screenWidth; i += distanceX)
    {
        int n = (i * zoomMultX) / distanceX + (offsetX);
        DrawText(TextFormat("%i", n), wpadding.x + i,
                 screenHeight - wpadding.y + 10, 15, BLACK);
        DrawLine(wpadding.x + i, screenHeight - wpadding.y + 5,
                 wpadding.x + i, screenHeight - wpadding.y - 5, BLACK);
    }
    // sys.update();

    DrawLine(wpadding.x, screenHeight - wpadding.y + offsetY * distanceY, wpadding.x - offsetX * distanceX, screenHeight - wpadding.y + offsetY * distanceY, GRAY);
    DrawLine(wpadding.x - offsetX * distanceX, screenHeight - wpadding.y, wpadding.x - offsetX * distanceX, screenHeight - wpadding.y + offsetY * distanceY, GRAY);
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