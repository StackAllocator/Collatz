#include "raylib.h"

int Collatz(int num) {
    if (num == 1) {
        return num;
    } else if (num % 2 == 0) {
        return num / 2;
    } else {
        return 3 * num + 1;
    }
}
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    constexpr int screenWidth = 2000;
    constexpr int screenHeight = 1400;
    int distanceX = 20;
    int distanceY = 20;
    int a = 60;
    
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(1);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    int fps = 0;
    int anim = 2;
    bool all = false;
    int s_max = 1;
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        DrawText(TextFormat("fps: %i",fps), 100, 50, 20, BLACK);
        DrawText(TextFormat("s_max: %i",s_max), 100, 100, 20, BLACK);
        DrawText(TextFormat("anim: %i/%i",anim, a), 250, 100, 20, BLACK);
        
        
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        fps = ++fps % 2;
        // Draw
        //----------------------------------------------------------------------------------
            if (IsKeyDown(KEY_UP) && fps == 0) {
                distanceX++;
            } else if (IsKeyDown(KEY_DOWN) && fps == 0) {
                distanceX--;
            }
            if (IsKeyDown(KEY_RIGHT) && fps == 0) {
                distanceY++;
            } else if (IsKeyDown(KEY_LEFT) && fps == 0) {
                distanceY--;
            }
            BeginDrawing();
                
                ClearBackground(RAYWHITE);
                DrawLine(30, 0, 30, screenHeight, BLACK);
                for (int i = screenHeight - 30; i >= 0; i-=distanceX) {
                    int n = (int)(screenHeight-30)/distanceX-i/distanceX;     
                    DrawText(TextFormat("%i", n), 5, i-5, 15, BLACK);
                    DrawLine(25, i, 35, i, BLACK);
                   
                }
                DrawLine(0, screenHeight - 30, screenWidth, screenHeight - 30, BLACK);
                for (int i = 0; i < screenWidth; i+=distanceY) {
                    int n = (int)i/distanceY;     
                    DrawText(TextFormat("%i", n), i-5 + 30, screenHeight - 20, 15, BLACK);
                    DrawLine(i + 30, screenHeight-25, i + 30, screenHeight-30, BLACK);
                }
                
                Vector2 pos;
                pos.x = 30;
                pos.y = screenHeight-30;
                int num = 0;
                for (int i = 1; i < anim; i++) {
                    num = i;
                    int count = 0;
                    int old_x = pos.x;
                    int old_y = pos.y;
                    do {
                        num = Collatz(num);
                        count++;
                        pos.y = screenHeight - 30 - distanceX * num;
                        pos.x = 30 + count * distanceY;
                        DrawLine(old_x, old_y, pos.x, pos.y, BLUE);
                    } while ((num > 1) && ((count < s_max) || (i < anim - 1)));
                    
                }
                DrawText(TextFormat("num: %i",num), 300, 150, 20, BLACK);
                if (num == 1 && anim < a) {
                    anim++;
                    s_max = 0;
                }
                pos.x = 30;
                pos.y = screenHeight-30;
                for (int i = 1; i < anim; i++) {
                    num = i;
                    int count = 0;
                    do {
                        num = Collatz(num);
                        count++;
                        pos.y = screenHeight - 30 - distanceX * num;
                        pos.x = 30 + count * distanceY;
                        DrawCircle(pos.x, pos.y, 3, BLACK);
                        
                    } while ((num > 1) && ((count < s_max) || (i < anim - 1))); 
                }
                s_max++;
            EndDrawing();
        //----------------------------------------------------------------------------------
    }
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
