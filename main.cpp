#include "raylib.h"
#include "button.h"
#include "drawall.h"
#include "Collatz.h"
#include "drawhelpers.h"
#include "algo.h"
#include "Coordinatesystem.h"
#include <iostream>
#include <list>

void checkInputs(int &fps, int &distanceX, int &distanceY,
                 int &zoomMultX, int &zoomMultY, int &offsetX, int &offsetY,
                 int &start, int &animationSpeed, int &colorVal, int &sequenz, Vector2& wpadding, bool& pause);

enum class DrawOneStates
{
    GET_NUMBER = 1,
    DRAW_ALL = 2,
    DRAW_ALGO = 3,
    END_SCREEN = 3,
};

void setAlgo();
void increaseMode1();
void increaseMode2();

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int txtpos = 200;
Button buttons[10];
Color alg_c = {100, 100, 100, 255};
Button algo = {0, 0, 150, 50, "Algorithm", alg_c, setAlgo};
Button modeb1 = {350, 0, 150, 50, "MODE1 : AIMD", alg_c, increaseMode1};
Button modeb2 = {500, 0, 150, 50, "MODE2 : MIMD", alg_c, increaseMode2};
modes mode1{modes::AIMD};
modes mode2{modes::MIMD};
DrawOneStates drawOneState;
Vector2 AIADf{2, 2};
Vector2 AIMDf{2, 2};
Vector2 MIADf{2, 2};
Vector2 MIMDf{2, 2};
int it{0};
Coordinatesystem sys{100.0f, 80.0f, 1000, 1000};
Coordinatesystem sys2{0, 0, GetScreenWidth(), GetScreenHeight()};
auto main() -> int
{
    sys2.setLabelX("Iteration");
    buttons[0] = algo;
    buttons[1] = modeb1;
    buttons[2] = modeb2;
    int screenWidth = 1920;
    int screenHeight = 1080;
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Collatz Conjecture Visualization");
    SetTargetFPS(120); // Set our game to run at 60 frames-per-second

    // Initialization
    //--------------------------------------------------------------------------------------
    sys2.setHeight(GetScreenHeight());
    sys2.setWidth(GetScreenWidth());
    Vector2 wpadding;
    wpadding.x = 30;
    wpadding.y = 30;
    int distanceX = 40;
    int distanceY = 40;
    int colorVal = 200;

    // set default DrawOneStates value in case only one series should be drawn
    drawOneState = DrawOneStates::GET_NUMBER;
    int numToCheckOnCollatz{};
    int key = 0;
    int count = 0;
    std::string inputString = "";

    // Buttons -----------------------------------------------------------------

    //--------------------------------------------------------------------------------------
    int fps = 0;
    int sequenz = 1;
    bool all = false;
    int sequenzItem = 1;
    Color colors[colorVal * 100];
    int zoomMultX = 1.0f;
    int zoomMultY = 1.0f;
    int offsetX = 0.0f;
    int offsetY = 0.0f;
    int start = sequenz;
    int animationSpeed = 1;
    Rectangle drawOneRect = {150, 0, 200, 50};
    Color rectCol = RED;
    bool drawOne = false;
    int animTest{0};
    bool pause{false};
    int num = 1;
    int startAlgox = 10;
    int startAlgoy = 5;
    int K = 20;
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        sys.update();
        sys2.update();
        // sys.draw();
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();
        
        if (drawOneState == DrawOneStates::DRAW_ALGO) {
            if (!pause) {
                it++;
            }
            DrawText(TextFormat("%i", pause), 200, 100, 30, BLACK);
            if (IsKeyDown(KEY_UP) && IsKeyDown(KEY_LEFT_CONTROL)) {
                startAlgoy++;
                it = 1;
            } else if (IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_LEFT_CONTROL)) {
                startAlgoy--;
                if (startAlgoy < 0) {
                    startAlgoy = 0;
                }
                it = 1;
            }
            if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_LEFT_CONTROL)) {
                startAlgox++;
                it = 1;
            } else if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_LEFT_CONTROL)) {
                startAlgox--;
                if (startAlgox < 0) {
                    startAlgox = 0;
                }
                it = 1;
            }
            if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_UP)) {
                K++;
                it = 1;
            } else if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyDown(KEY_DOWN)) {
                K--;
                if (K < 1) {
                    K = 1;
                }
                it = 1;
            }
            draw(startAlgox, startAlgoy, K, it, mode1, mode2, AIADf, AIMDf, MIADf, MIMDf, sys);
        }
        // Update
        //----------------------------------------------------------------------------------
        fps = ++fps % 1;
        //----------------------------------------------------------------------------------
        Vector2 currentMousePos = {static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY())};
        if (currentMousePos.x >= drawOneRect.x && currentMousePos.x <= drawOneRect.x + drawOneRect.width && currentMousePos.y >= drawOneRect.y && currentMousePos.y <= drawOneRect.y + drawOneRect.height)
        {
            rectCol = BLUE;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                rectCol = GREEN;
                drawOne = true;
                drawOneState = DrawOneStates::GET_NUMBER;
            }
        }
        else
        {
            rectCol = RED;
        }
        DrawRectangleRec(drawOneRect, rectCol);
        DrawText("Press me!", drawOneRect.x + 5, drawOneRect.y + 12, 30, BLACK);

        checkInputs(fps, distanceX, distanceY, zoomMultX, zoomMultY, offsetX, offsetY, start, animationSpeed, colorVal, sequenz, wpadding, pause);
        BeginDrawing();

        ClearBackground(RAYWHITE);

        Vector2 pos;
        pos.x = 30;
        pos.y = screenHeight - 30;
        Color col;
        col.r = (255 - sequenzItem * 3) % 256;
        col.g = sequenzItem % 256;
        col.b = (sequenzItem * 2) % 256;
        col.a = 255; // alpha value

        // if (sequenz < sizeof(colors)/sizeof(col)) {
            colors[sequenz] = col;
        // } else {
        //    colors.push_back(col);
        //}

        if (drawOneState == DrawOneStates::DRAW_ALL)
        {
            sys2.update();
            drawall(num, sequenz, sequenzItem, start, colorVal, animationSpeed, pause, colors, sys2);

        }

        else
        {
            switch (drawOneState)
            {
                // get user input
            case DrawOneStates::GET_NUMBER:
                // numToCheckOnCollatz;
                key = GetKeyPressed();

                DrawText(TextFormat("key: %i", key), screenWidth - 500, 50, 20, BLACK);
                if (key >= KEY_ZERO && key <= KEY_NINE)
                {
                    inputString += key;
                    ++count;
                }
                else if (key == KEY_ENTER)
                {
                    drawOneState = DrawOneStates::DRAW_ALL;
                }
                break;
                // case where one number gets drawn
            case DrawOneStates::DRAW_ALL:
                [[likely]]

                // numToCheckOnCollatz = std::atoi(inputString);
                if (numToCheckOnCollatz == 1)
                {
                    drawOneState = DrawOneStates::END_SCREEN;
                }
                break;
            case DrawOneStates::END_SCREEN:
                break;
            default:
                break;
            }
        }

        DrawText(TextFormat("Mode: %i", drawOneState), screenWidth - 500, 600, 20, BLACK);
        // -----------------------------------------------------------------------------------------------------------------------------------
        // display test

        // -----------------------------------------------------------------------------------------------------------------------------------
        for (int i = 0; i < 3; i++) {
            buttons[i].draw();
            buttons[i].checkMouse();
        }
        // algo.draw();
        // modeb1.draw();
        // modeb2.draw();
        // algo.checkMouse();
        // modeb1.checkMouse();
        // modeb2.checkMouse();
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

void setAlgo() {
    drawOneState = DrawOneStates::DRAW_ALGO;
}

void increaseMode1() {
    it = 1;
    switch(mode1){
        case modes::AIAD:
            mode1 = modes::AIMD;
            modeb1.setContent("MODE : AIMD");
            break;
        case modes::AIMD:
            mode1 = modes::MIAD;
            modeb1.setContent("MODE : MIAD");
            break;
        case modes::MIAD:
            mode1 = modes::MIMD;
            modeb1.setContent("MODE : MIMD");
            break;
        case modes::MIMD:
            mode1 = modes::AIAD;
            modeb1.setContent("MODE : AIAD");
            break;
        default:
            std::cout << "something did not work";
    }
}

void increaseMode2() {
     it = 1;
    switch(mode2){
        case modes::AIAD:
            mode2 = modes::AIMD;
            modeb2.setContent("MODE : AIMD");
            break;
        case modes::AIMD:
            mode2 = modes::MIAD;
            modeb2.setContent("MODE : MIAD");
            break;
        case modes::MIAD:
            mode2 = modes::MIMD;
            modeb2.setContent("MODE : MIMD");
            break;
        case modes::MIMD:
            mode2 = modes::AIAD;
            modeb2.setContent("MODE : AIAD");
            break;
        default:
            std::cout << "something did not work";
    }
}

void checkInputs(int &fps, int &distanceX, int &distanceY,
                 int &zoomMultX, int &zoomMultY, int &offsetX, int &offsetY,
                 int &start, int &animationSpeed, int &colorVal, int &sequenz, Vector2& wpadding, bool& pause)
{
    // Zoom y-direction
    // if (IsKeyDown(KEY_UP) && !IsKeyDown(KEY_LEFT_CONTROL) &&!IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_X) && !IsKeyDown(KEY_Y) && fps == 0)
    // {
    //     sys.setDistanceY(sys.getDistance().y+1);
    //     distanceY++;
    //     if (distanceY >= 40 && zoomMultY > 1 || sys.getDistance().y >= 40 && sys.getZoom().y > 1)
    //     {
    //         sys.setDistanceY(20);
    //         sys.setZoomY(sys.getZoom().y / 2);
    //         distanceY = 20;
    //         zoomMultY /= 2;
    //     }

    //     if (zoomMultY < 1 || sys.getZoom().y < 1)
    //     {
    //         sys.setDistanceY(20);
    //         sys.setZoomY(1);
    //         zoomMultY = 1;
    //         distanceY = 20;
    //     }
    // }
    // else if (IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_LEFT_CONTROL) && !IsKeyDown(KEY_LEFT_SHIFT) && !IsKeyDown(KEY_X) && !IsKeyDown(KEY_Y) && fps == 0)
    // {
    //     sys.setDistanceY(sys.getDistance().y - 1);
    //     distanceY--;
    //     if (distanceY <= 20 || sys.getDistance().y <= 20)
    //     {
    //         sys.setDistanceY(40);
    //         sys.setZoomY(sys.getZoom().y * 2);
    //         distanceY = 40;
    //         zoomMultY *= 2;
    //     }
    // }
    // // Zoom x-direction
    // if (IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT_CONTROL) && !IsKeyDown(KEY_LEFT_SHIFT) && fps == 0)
    // {
    //     sys.setDistanceX(sys.getDistance().x + 1);
    //     distanceX++;
    //     if (distanceX >= 40 && zoomMultX > 1)
    //     {
    //         sys.setDistanceX(20);
    //         sys.setZoomX(sys.getZoom().x / 2);
    //         distanceX = 20;
    //         zoomMultX /= 2;
    //     }

    //     if (zoomMultX < 1)
    //     {
    //         sys.setDistanceX(40);
    //         sys.setZoomX(1);
    //         zoomMultX = 1;
    //         distanceX = 40;
    //     }
    // }
    // else if (IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_LEFT_CONTROL) && !IsKeyDown(KEY_LEFT_SHIFT) && fps == 0)
    // {
    //     sys.setDistanceX(sys.getDistance().x - 1);
    //     distanceX--;
    //     if (distanceX <= 20)
    //     {
    //         sys.setDistanceX(40);
    //         sys.setZoomX(sys.getZoom().x * 2);
    //         distanceX = 40;
    //         zoomMultX *= 2;
    //     }
    // }
    // adjust maximum number for sequenzes
    if (IsKeyDown(KEY_PERIOD) && !IsKeyDown(KEY_LEFT_CONTROL) && colorVal > 1)
    {
        colorVal--;
    }
    if (IsKeyDown(KEY_COMMA) && !IsKeyDown(KEY_LEFT_CONTROL))
    {
        colorVal++;
    }

    // adjust minimum number for sequenzes
    if (IsKeyDown(KEY_PERIOD) && IsKeyDown(KEY_LEFT_CONTROL) && start > 1)
    {
        start--;
    }
    if (IsKeyDown(KEY_COMMA) && IsKeyDown(KEY_LEFT_CONTROL) && start < sequenz - 1)
    {
        start++;
    }

    // // Move Graph in x-direction
    // if (IsKeyDown(KEY_D))
    // {
    //     sys.setOffsetX(sys.getOffset().x + sys.getZoom().x);
    //     offsetX += zoomMultX;
    // }
    // if (IsKeyDown(KEY_A))
    // {
    //     sys.setOffsetX(sys.getOffset().x - sys.getZoom().x);
    //     offsetX -= zoomMultX;
    // }
    // // Move Graph in y-direction
    // if (IsKeyDown(KEY_W))
    // {
    //     sys.setOffsetY(sys.getOffset().y + sys.getZoom().y);
    //     offsetY += zoomMultY;
    // }
    // if (IsKeyDown(KEY_S))
    // {
    //     sys.setOffsetY(sys.getOffset().y - sys.getZoom().y);
    //     offsetY -= zoomMultY;
    // }

    // change speed for animation
    if (IsKeyDown(KEY_L))
    {
        animationSpeed++;
        if (animationSpeed == 0)
        {
            animationSpeed = 1;
        }

        DrawText(TextFormat("animationSpeed: %i", animationSpeed + 1), 400, 150, 20, BLACK);
    }
    if (IsKeyDown(KEY_H))
    {
        animationSpeed -= 1;
        if (animationSpeed == 0)
        {
            animationSpeed = -2;
        }

        DrawText(TextFormat("animationSpeed: %i", animationSpeed + 1), 400, 150, 20, BLACK);
    }
    // Adjust padding
    // if (IsKeyDown(KEY_X) && IsKeyDown(KEY_UP))
    // {
    //     sys.setPaddingX(sys.getPadding().x + sys.getDistance().x);
    //     wpadding.x += distanceX;
    // }
    // if (IsKeyDown(KEY_X) && IsKeyDown(KEY_DOWN) && wpadding.x >= 0)
    // {
    //     sys.setPaddingX(sys.getPadding().x - sys.getDistance().x);
    //     wpadding.x -= distanceX;
    // }
    // if (IsKeyDown(KEY_Y) && IsKeyDown(KEY_UP))
    // {
    //     sys.setPaddingY(sys.getPadding().y + sys.getDistance().y);
    //     wpadding.y += static_cast<float>(distanceY);
    // }
    // if (IsKeyDown(KEY_Y) && IsKeyDown(KEY_DOWN) && wpadding.y >= 0)
    // {
    //     sys.setPaddingY(sys.getPadding().y - sys.getDistance().y);
    //     wpadding.y -= distanceY;
    // }
    if (IsKeyDown(KEY_SPACE))
    {
        std::cout << "hey";
        pause = !pause;
        std::cout << pause;
    }
}
