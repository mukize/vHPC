#include "../include/theme.h"
#include "../vendor/clay/clay.h"
#include "raylib.h"
#include <string.h>

static Clay_String ToClayString(const char *format) {
  return (Clay_String){.length = strlen(format), .chars = format};
}

void UI_Update(void) {
  Vector2 mousePos = GetMousePosition();
  Clay_SetLayoutDimensions(
      (Clay_Dimensions){(float)GetScreenWidth(), (float)GetScreenHeight()});
  Clay_SetPointerState((Clay_Vector2){mousePos.x, mousePos.y},
                       IsMouseButtonDown(MOUSE_LEFT_BUTTON));

  if (IsKeyPressed(KEY_F1)) {
    Clay_SetDebugModeEnabled(!Clay_IsDebugModeEnabled());
  }
}

// clang-format off
Clay_RenderCommandArray UI_Draw(void) {
  Clay_BeginLayout();
  Clay_TextElementConfig* defaultRightSidebarTextConfig = CLAY_TEXT_CONFIG({
    .fontId = 0,
    .fontSize = 24,
    .textAlignment = CLAY_TEXT_ALIGN_CENTER,
    .textColor = THEME_TO_CLAY_COLOR(THEME_TEXT),
  });
  CLAY(CLAY_ID("Body"), {
    .layout = {
      .layoutDirection = CLAY_LEFT_TO_RIGHT,
      .sizing = {
        .height = CLAY_SIZING_GROW(0),
        .width = CLAY_SIZING_GROW(0),
      },
      .padding = CLAY_PADDING_ALL(16),
      .childAlignment = CLAY_ALIGN_X_RIGHT,
    },
  }) {
    CLAY(CLAY_ID("RightSidebar"), {
       .layout = {
         .layoutDirection = CLAY_TOP_TO_BOTTOM,
          .sizing = {
            .height = CLAY_SIZING_GROW(0),
            .width = CLAY_SIZING_PERCENT(0.2),
          },
          .padding = CLAY_PADDING_ALL(8),
          .childAlignment = CLAY_ALIGN_X_CENTER,
         .childGap = 8,
       },
       .backgroundColor = THEME_TO_CLAY_COLOR(THEME_SURFACE),
       .cornerRadius = CLAY_CORNER_RADIUS(8),
    }) {
      CLAY_TEXT(CLAY_STRING("Debug"), defaultRightSidebarTextConfig);
      CLAY_AUTO_ID({
        .border = {
          .color = THEME_TO_CLAY_COLOR(THEME_TEXT),
          .width = 1
        },
        .layout = {
          .sizing = {
            .width = CLAY_SIZING_GROW(0),
            .height = CLAY_SIZING_FIXED(2)}
        },
        .backgroundColor = THEME_TO_CLAY_COLOR(THEME_TEXT),
        .cornerRadius = CLAY_CORNER_RADIUS(25),
      }){}
      CLAY_TEXT(
        ToClayString(TextFormat("%ix%i", GetScreenWidth(), GetScreenHeight())),
        defaultRightSidebarTextConfig
      );
    }
  };
  return Clay_EndLayout();
}
// clang-format on
