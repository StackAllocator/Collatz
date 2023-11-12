#include "raylib.h"
#include <stdio.h>

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
    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;
    int distanceX = 20;
    int distanceY = 20;
    int a = 200;
    
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    int fps = 0;
    int anim = 2;
    bool all = false;
    int s_max = 1;
    Color colors[a*10];
    int zoomMultX = 1;
    int zoomMultY = 1;
    int offsetX = 0;
    int offsetY = 0;
    int start = 1;
    int speed = 1;
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {        
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        fps = ++fps % 1;
        // Draw
        //----------------------------------------------------------------------------------
            if (IsKeyDown(KEY_UP) && fps == 0) {
                distanceX++;
                if (distanceX >= 80 && zoomMultX > 1) {
                    distanceX = 40;
                    zoomMultX /= 2;
                }
                
                if (zoomMultX < 1) {
                    zoomMultX = 1;
                    distanceX = 80;
                }
                
            } else if (IsKeyDown(KEY_DOWN) && fps == 0) {
                distanceX--;
                if (distanceX <= 40) {
                    distanceX = 80;
                    zoomMultX *= 2;
                }
            }
            if (IsKeyDown(KEY_RIGHT) && fps == 0) {
                distanceY++;
                if (distanceY >= 80 && zoomMultY > 1) {
                    distanceY = 40;
                    zoomMultY /= 2;
                }
                
                if (zoomMultY < 1) {
                    zoomMultY = 1;
                    distanceY = 80;
                }
                
            } else if (IsKeyDown(KEY_LEFT) && fps == 0) {
                distanceY--;
                if (distanceY <= 40) {
                    distanceY = 80;
                    zoomMultY *= 2;
                }
            }
            if (IsKeyDown(KEY_PERIOD) && !IsKeyDown(KEY_LEFT_CONTROL) && a > 1) {
                a--;
            }
            if (IsKeyDown(KEY_COMMA) && !IsKeyDown(KEY_LEFT_CONTROL)) {
                a++;
            }
            if (IsKeyDown(KEY_PERIOD) && IsKeyDown(KEY_LEFT_CONTROL) && start > 1) {
                start--;
            }
            if (IsKeyDown(KEY_COMMA) && IsKeyDown(KEY_LEFT_CONTROL) && start < anim - 1) {
                start++;
            }
            
            if (IsKeyDown(KEY_D)) {
                offsetX++;
            }
            if (IsKeyDown(KEY_A) && offsetX > 0) {
                offsetX--;
            }
            if (IsKeyDown(KEY_L)) {
                speed++;
            }
            if (IsKeyDown(KEY_H) && speed > 1) {
                speed--;
            }
            
            if (IsKeyDown(KEY_W)) {
                offsetY++;
            }
            if (IsKeyDown(KEY_S) && offsetY > 0) {
                offsetY--;
            }
            BeginDrawing();
                
                ClearBackground(RAYWHITE);
                DrawLine(30, 0, 30, screenHeight, BLACK);
                for (int i = screenHeight - 30; i >= 0; i-=distanceX) {
                    int n = (int)((screenHeight-30) * zoomMultX)/distanceX-(i * zoomMultX)/distanceX + (offsetY * zoomMultX);     
                    DrawText(TextFormat("%i", n), 5, i-5, 15, BLACK);
                    DrawLine(25, i, 35, i, BLACK);
                   
                }
                DrawLine(0, screenHeight - 30, screenWidth, screenHeight - 30, BLACK);
                for (int i = 0; i < screenWidth; i+=distanceY) {
                    int n = (int)((i * zoomMultY)/distanceY) + (offsetX * zoomMultY);     
                    DrawText(TextFormat("%i", n), i-5 + 30, screenHeight - 20, 15, BLACK);
                    DrawLine(i + 30, screenHeight-25, i + 30, screenHeight-30, BLACK);
                }
                
                Vector2 pos;
                pos.x = 30;
                pos.y = screenHeight-30;
                int num = 0;
                Color col;
                col.r = GetRandomValue(0, 255);
                col.g = GetRandomValue(0, 255);
                col.b = GetRandomValue(0, 255);
                col.a = 255;
                colors[anim] = col;
                for (int i = start; i < anim; i++) {
                    num = i;
                    int count = 0;
                    int old_x = 30  + distanceY / zoomMultY - (distanceY * offsetX);
                    int old_y = screenHeight - 30 - num * distanceX / zoomMultX + (distanceX * offsetY);
                    pos.y = old_y;
                    pos.x = old_x;
                    
                    
                    do {
                        num = Collatz(num);
                        count++;
                        old_x = pos.x;
                        old_y = pos.y;
                        pos.y = screenHeight - 30 - distanceX * num / zoomMultX + (zoomMultX * offsetY * distanceX);
                        pos.x = 30 + count * distanceY / zoomMultY - (zoomMultY * offsetX * distanceY);
                        DrawLine(old_x, old_y, pos.x, pos.y, colors[i]);
                    } while ((num > 1) && ((count < s_max) || (i < anim - 1)));
                    
                }
                
                if (num == 1 && anim < a) {
                    anim++;
                    s_max = 0;
                }
                pos.x = 30;
                pos.y = screenHeight-30;
                for (int i = start; i < anim; i++) {
                    num = i;
                    int count = 0;
                    pos.x = 30 + distanceY / zoomMultY - (offsetX * zoomMultY * distanceY);
                    pos.y = screenHeight - 30 - num * distanceX / zoomMultX + (offsetY * zoomMultX * distanceX);
                    do {
                        num = Collatz(num);
                        count++;
                        pos.y = screenHeight - 30 - distanceX * num / zoomMultX + (offsetY * zoomMultX * distanceX);
                        pos.x = 30 + count * distanceY / zoomMultY - (offsetX * zoomMultY * distanceY);
                        DrawCircle(pos.x, pos.y, 3, colors[i]);
                        
                    } while ((num > 1) && ((count < s_max) || (i < anim - 1))); 
                }
                s_max+=speed;
                DrawText(TextFormat("fps: %i",fps), 1300, 50, 20, BLACK);
                DrawText(TextFormat("s_max: %i",s_max), 1300, 100, 20, BLACK);
                DrawText(TextFormat("anim: %i/%i",anim, a), 1300, 150, 20, BLACK);
                DrawText(TextFormat("start: %i <> %i",start, a), 1300, 200, 20, BLACK);
                DrawText(TextFormat("zoomMultX: %i",zoomMultX), 1300, 250, 20, BLACK);
                DrawText(TextFormat("zoomMultY: %i",zoomMultY), 1300, 300, 20, BLACK);
                DrawText(TextFormat("offsetX: %i",offsetX), 1300, 350, 20, BLACK);
                DrawText(TextFormat("offsetY: %i",offsetY), 1300, 400, 20, BLACK);
                DrawText(TextFormat("color: %i, %i, %i", col.r, col.g, col.b), 1300, 450, 20, BLACK);
                DrawText(TextFormat("num: %i",num), 1300, 500, 20, BLACK);
                DrawText(TextFormat("speed: %i",speed), 1300, 550, 20, BLACK);
            EndDrawing();
        //----------------------------------------------------------------------------------
    }
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
