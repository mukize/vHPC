#include "../include/app.h"
#include "../include/canvas.h"
#include <assert.h>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <stddef.h>

#define STB_DS_IMPLEMENTATION
#include "../vendor/stb_ds.h"

static void update(App *app) {
  if (app->canvas != NULL)
    Canvas_Update(app->canvas);
}

static void draw(App *app) {
  ClearBackground(RAYWHITE);

  if (app->canvas != NULL)
    Canvas_Draw(app->canvas);

  Vector2 mousePos = GetMousePosition();
  DrawCircleV(mousePos, 5, GRAY);

  DrawTextEx(GetFontDefault(), TextFormat("[%i, %i]", GetMouseX(), GetMouseY()),
             Vector2Add(mousePos, (Vector2){-44, -24}), 20, 2, BLACK);
}

int main(void) {

  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED);

  InitWindow(0, 0, "vHPC");
  SetTargetFPS(60);

  App app = {0};
  app.canvas = &((Canvas){0});
  Canvas_Init(app.canvas);

  while (!WindowShouldClose()) {

    update(&app);

    BeginDrawing();
    draw(&app);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
