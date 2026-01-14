#include "../include/workspace.h"
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

int main(void) {

  const int screenWidth = 1000;
  const int screenHeight = 1000;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, "vHPC");
  SetTargetFPS(60);

  Workspace workspace;
  Workspace_Init(&workspace);

  while (!WindowShouldClose()) {
    Workspace_Update(&workspace);

    BeginDrawing();

    ClearBackground(RAYWHITE);
    Workspace_Draw(&workspace);

    DrawCircleV(GetMousePosition(), 4, DARKGRAY);
    DrawTextEx(
        GetFontDefault(), TextFormat("[%i, %i]", GetMouseX(), GetMouseY()),
        Vector2Add(GetMousePosition(), (Vector2){-44, -24}), 20, 2, BLACK);

    EndDrawing();
    //----------------------------------------------------------------------------------
  }

  CloseWindow();

  return 0;
}
