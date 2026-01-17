#include "../include/canvas.h"
#include "../include/theme.h"
#include "../include/ui.h"
#include <assert.h>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <stddef.h>

#define STB_DS_IMPLEMENTATION
#include "../vendor/stb_ds.h"

#define CLAY_IMPLEMENTATION
#include "../vendor/clay/clay.h"
#include "../vendor/clay/renderers/raylib/clay_renderer_raylib.c"

// Clay
// ------------------------------------------------------------------
bool reinitializeClay = false;
void HandleClayErrors(Clay_ErrorData errorData) {
  printf("%s", errorData.errorText.chars);
  if (errorData.errorType == CLAY_ERROR_TYPE_ELEMENTS_CAPACITY_EXCEEDED) {
    reinitializeClay = true;
    Clay_SetMaxElementCount(Clay_GetMaxElementCount() * 2);
  } else if (errorData.errorType ==
             CLAY_ERROR_TYPE_TEXT_MEASUREMENT_CAPACITY_EXCEEDED) {
    reinitializeClay = true;
    Clay_SetMaxMeasureTextCacheWordCount(
        Clay_GetMaxMeasureTextCacheWordCount() * 2);
  }
}
// ------------------------------------------------------------------

int main(void) {

  // Initialize clay and raylib
  // ------------------------------------------------------------------
  uint64_t totalMemorySize = Clay_MinMemorySize();
  Clay_Arena clayMemory = Clay_CreateArenaWithCapacityAndMemory(
      totalMemorySize, malloc(totalMemorySize));
  Clay_Initialize(clayMemory,
                  (Clay_Dimensions){GetScreenWidth(), GetScreenHeight()},
                  (Clay_ErrorHandler){HandleClayErrors, 0});
  Clay_Raylib_Initialize(
      GetScreenWidth(), GetScreenHeight(), "Clay - Raylib Renderer Example",
      FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED | FLAG_WINDOW_HIGHDPI);
  SetTargetFPS(60);
  // ------------------------------------------------------------------

  // Initialize app state
  // ------------------------------------------------------------------
  Canvas canvas = (Canvas){0};
  Canvas_Init(&canvas);
  Font iosevka = LoadFontEx("resources/IosevkaNerdFont-Regular.ttf", 48, 0, 0);
  Font fonts[1] = {iosevka};
  SetTextureFilter(fonts[0].texture, TEXTURE_FILTER_BILINEAR);
  Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);
  // ------------------------------------------------------------------

  while (!WindowShouldClose()) {

    // Update
    // ------------------------------------------------------------------

    if (reinitializeClay) {
      Clay_SetMaxElementCount(8192);
      totalMemorySize = Clay_MinMemorySize();
      clayMemory = Clay_CreateArenaWithCapacityAndMemory(
          totalMemorySize, malloc(totalMemorySize));
      Clay_Initialize(
          clayMemory,
          (Clay_Dimensions){(float)GetScreenWidth(), (float)GetScreenHeight()},
          (Clay_ErrorHandler){HandleClayErrors, 0});
      reinitializeClay = false;
    }

    Canvas_Update(&canvas);
    UI_Update();
    // ------------------------------------------------------------------

    // Draw
    // ------------------------------------------------------------------
    Clay_RenderCommandArray commands = UI_Draw();
    BeginDrawing();
    ClearBackground(RAYWHITE);

    Canvas_Draw(&canvas);
    Clay_Raylib_Render(commands, fonts);

    Vector2 mousePos = GetMousePosition();
    DrawCircleV(mousePos, 5, THEME_SURFACE);
    EndDrawing();
    // ------------------------------------------------------------------
  }

  Clay_Raylib_Close();

  return 0;
}
