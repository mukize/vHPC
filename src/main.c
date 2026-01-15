#include "../include/app.h"
#include "../include/canvas.h"
#include <assert.h>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <stddef.h>

static void update(App *app) {
  if (app->canvas != NULL)
    Canvas_Update(app->canvas);
}

static void draw(App *app) {
  ClearBackground(WHITE);

  if (app->canvas != NULL)
    Canvas_Draw(app->canvas);

  DrawCircleV(GetMousePosition(), 4, DARKGRAY);
  DrawTextEx(GetFontDefault(), TextFormat("[%i, %i]", GetMouseX(), GetMouseY()),
             Vector2Add(GetMousePosition(), (Vector2){-44, -24}), 20, 2, BLACK);
}

static void init(App *app) {
  assert(app != NULL);
  app->canvas = &((Canvas){0});
  Canvas_Init(app->canvas);
}

int main(void) {

  const int screenWidth = 1000;
  const int screenHeight = 1000;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(screenWidth, screenHeight, "vHPC");
  SetTargetFPS(60);

  App app = {0};
  init(&app);

  while (!WindowShouldClose()) {
    update(&app);

    BeginDrawing();
    draw(&app);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
