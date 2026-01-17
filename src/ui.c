#include "../include/theme.h"
#include "../vendor/clay/clay.h"
#include "raylib.h"

void UI_Update(void) {
  Clay_SetLayoutDimensions(
      (Clay_Dimensions){(float)GetScreenWidth(), (float)GetScreenHeight()});

  if (IsKeyPressed(KEY_F1)) {
    Clay_SetDebugModeEnabled(!Clay_IsDebugModeEnabled());
  }
}

Clay_RenderCommandArray UI_Draw(void) {
  Clay_BeginLayout();
  // clang-format off
  CLAY(CLAY_ID("Body"), {
    .layout = {
      .sizing = {
        .height = CLAY__SIZING_TYPE_GROW,
        .width = CLAY__SIZING_TYPE_GROW,
      }
    },
    .backgroundColor = THEME_TO_CLAY_COLOR(THEME_SURFACE),
  });
  // clang-format on

  return Clay_EndLayout();
}
