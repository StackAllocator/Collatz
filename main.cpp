#include <iostream>
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
void checkInputs(int &fps, float &distanceX, float &distanceY,
    float &zoomMultX, float &zoomMultY, float &offsetX, float &offsetY,
    int &start, float &speed, int &colorVal, int &anim);


enum class DrawOneStates {
  GET_NUMBER,
  DRAW_LINE,
  END_SCREEN,
};

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
auto main() -> int {
    // Initialization
    //--------------------------------------------------------------------------------------
    constexpr int screenWidth = 1920;
    constexpr int screenHeight = 1080;
    float distanceX = 20;
    float distanceY = 20;
    int colorVal = 200;

	// set default DrawOneStates value in case only one series should be drawn
	DrawOneStates drawOneState = DrawOneStates::GET_NUMBER;
	int numToCheckOnCollatz{};
	int key = 0;
	int count = 0;
	std::string inputString = "";

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Collatz Conjecture Visualization");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    int fps = 0;
    int anim = 2;
    bool all = false;
    int s_max = 1;
    Color colors[colorVal * 10];
    float zoomMultX = 1;
    float zoomMultY = 1;
    float offsetX = 0;
    float offsetY = 0;
    int start = 1;
    float speed = 1.f;
    Rectangle drawOneRect = {screenWidth - 200, screenHeight - 300, 150, 50};
    Color rectCol = RED;
	bool drawOne = false;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {        
        // Update
        //----------------------------------------------------------------------------------
        fps = ++fps % 1;
        //----------------------------------------------------------------------------------

		Vector2 currentMousePos = { static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY()) };
        if (currentMousePos.x >= drawOneRect.x && currentMousePos.x <= drawOneRect.x + drawOneRect.width
            && currentMousePos.y >= drawOneRect.y && currentMousePos.y <= drawOneRect.y + drawOneRect.height) {
          rectCol = BLUE;
		  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			drawOne = true;
		  }
        }
        else {
          rectCol = RED;
        }
        DrawRectangleRec(drawOneRect, rectCol);
		DrawText("Press me!", drawOneRect.x + 5, drawOneRect.y + 12, 30, BLACK);

        checkInputs(fps, distanceX, distanceY, zoomMultX, zoomMultY, offsetX, offsetY, start, speed, colorVal, anim);
            BeginDrawing();
                
                ClearBackground(RAYWHITE);
                DrawLine(30, 0, 30, screenHeight, BLACK);

                for (int i = screenHeight - 30; i >= 0; i -= distanceX) {
                    int n = (int)((screenHeight-30) * zoomMultX)/distanceX - (i * zoomMultX)/distanceX + (offsetY * zoomMultX);     
                    DrawText(TextFormat("%d", n), 5, i - 5, 15, BLACK);
                    DrawLine(25, i, 35, i, BLACK);

                }
                DrawLine(0, screenHeight - 30, screenWidth, screenHeight - 30, BLACK);
                for (int i = 0; i < screenWidth; i+=distanceY) {
                    int n = (int)((i * zoomMultY)/distanceY) + (offsetX * zoomMultY);     
                    DrawText(TextFormat("%d", n), i-5 + 30, screenHeight - 20, 15, BLACK);
                    DrawLine(i + 30, screenHeight-25, i + 30, screenHeight-30, BLACK);
                }
                
                Vector2 pos;
                pos.x = 30;
                pos.y = screenHeight - 30;
                int num = 0;
                Color col;
                col.r = GetRandomValue(0, 255);
                col.g = GetRandomValue(0, 255);
                col.b = GetRandomValue(0, 255);
                col.a = 255; // alpha value

                colors[anim] = col;

				if (!drawOne) {
				  for (int i = start; i < anim; i++) {
                    num = i;
                    int count = 0;
                    int old_x = 30 - (distanceY * offsetX / zoomMultY);
                    int old_y = screenHeight - 30 - num * distanceX / zoomMultX + (distanceX * offsetY / zoomMultX);
                    pos.y = old_y;
                    pos.x = old_x;
                    do {
                        num = Collatz(num);
                        count++;
                        old_x = pos.x;
                        old_y = pos.y;
                        pos.y = screenHeight - 30 - distanceX * num / zoomMultX + (offsetY * distanceX / zoomMultX);
                        pos.x = 30 + count * distanceY / zoomMultY - (offsetX * distanceY / zoomMultY);
                        DrawLine(old_x, old_y, pos.x, pos.y, colors[i]);
                    } while ((num > 1) && ((count < s_max) || (i < anim - 1)));
                    
				  }
                
				  if (num == 1 && anim < colorVal) {
                    anim++;
                    s_max = 0;
				  }
				  pos.x = 30;
				  pos.y = screenHeight-30;
				  for (int i = start; i < anim; i++) {
                    num = i;
                    int count = 0;
                    pos.x = 30 - ((offsetX) * distanceY / zoomMultY);
                    pos.y = screenHeight - 30 - num * distanceX / zoomMultX + (offsetY * distanceX / zoomMultX);
                    do {
                        num = Collatz(num);
                        count++;
                        DrawCircle(pos.x, pos.y, 3, colors[i]);
                        pos.y = screenHeight - 30 - distanceX * num / zoomMultX + (offsetY * distanceX / zoomMultX);
                        pos.x = 30 + count * distanceY / zoomMultY - (offsetX * distanceY / zoomMultY);
                        
                        
                    } while ((num > 1) && ((count < s_max) || (i < anim - 1))); 
                    DrawCircle(pos.x, pos.y, 3, colors[i]);
				  }
                
				  DrawLine(30, 0, 30, screenHeight, BLACK);
				  for (int i = screenHeight - 30; i >= 0; i-=distanceX) {
                    int n = static_cast<int>((screenHeight-30) * zoomMultX)/distanceX-(i * zoomMultX)/distanceX + (offsetY * zoomMultX);     
                    DrawText(TextFormat("%i", n), 5, i-5, 15, BLACK);
                    DrawLine(25, i, 35, i, BLACK);
                   
				  }
				  DrawLine(0, screenHeight - 30, screenWidth, screenHeight - 30, BLACK);
				  for (int i = 0; i < screenWidth; i+=distanceY) {
                    int n = (int)((i * zoomMultY)/distanceY) + (offsetX * zoomMultY);     
                    DrawText(TextFormat("%i", n), i-5 + 30, screenHeight - 20, 15, BLACK);
                    DrawLine(i + 30, screenHeight-25, i + 30, screenHeight-30, BLACK);
				  }
				}

				else {
				  switch(drawOneState) {
					// get user input
				  case DrawOneStates::GET_NUMBER:
					// numToCheckOnCollatz;
					while (key != KEY_ENTER) {
					  key = GetKeyPressed();
					  if (key >= KEY_ZERO && key <= KEY_NINE) {
						inputString += key;
						++count;
					  }
					}
					break;
					// case where one number gets drawn
				  case DrawOneStates::DRAW_LINE: [[likely]]

					// numToCheckOnCollatz = std::atoi(inputString);
					if (numToCheckOnCollatz == 1) {
					  drawOneState = DrawOneStates::END_SCREEN;
					}
					break;
				  case DrawOneStates::END_SCREEN:
					break;
				  default:
					break;
				  }
				}

                s_max+=speed;
                int txtpos = 200;

				// -----------------------------------------------------------------------------------------------------------------------------------
				// display test
                DrawText(TextFormat("FPS: %i", fps), screenWidth - txtpos, 50, 20, BLACK);
                DrawText(TextFormat("s_max: %i", s_max), screenWidth - txtpos, 100, 20, BLACK);
                DrawText(TextFormat("anim: %i/%i", anim, colorVal), screenWidth - txtpos, 150, 20, BLACK);
                DrawText(TextFormat("start: %i <> %i", start, colorVal), screenWidth - txtpos, 200, 20, BLACK);
                DrawText(TextFormat("zoomMultX: %i", zoomMultX), screenWidth - txtpos, 250, 20, BLACK);
                DrawText(TextFormat("zoomMultY: %i", zoomMultY), screenWidth - txtpos, 300, 20, BLACK);
                DrawText(TextFormat("offsetX: %i", offsetX), screenWidth - txtpos, 350, 20, BLACK);
                DrawText(TextFormat("offsetY: %i", offsetY), screenWidth - txtpos, 400, 20, BLACK);
                DrawText(TextFormat("color: (%d, %d, %d)", col.r, col.g, col.b), screenWidth - txtpos, 450, 20, BLACK);
                DrawText(TextFormat("num: %i", num), screenWidth - txtpos, 500, 20, BLACK);
                DrawText(TextFormat("Speed: %i", speed), screenWidth - txtpos, 550, 20, BLACK);
				// -----------------------------------------------------------------------------------------------------------------------------------

            EndDrawing();
        //----------------------------------------------------------------------------------
    }
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


void checkInputs(int &fps, float &distanceX, float &distanceY,
    float &zoomMultX, float &zoomMultY, float &offsetX, float &offsetY,
    int &start, float &speed, int &colorVal, int &anim) {
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
                
        // Draw
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
            if (IsKeyDown(KEY_PERIOD) && !IsKeyDown(KEY_LEFT_CONTROL) && colorVal > 1) {
                colorVal--;
            }
            if (IsKeyDown(KEY_COMMA) && !IsKeyDown(KEY_LEFT_CONTROL)) {
                colorVal++;
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
}
