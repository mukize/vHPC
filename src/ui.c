#include "../include/ui.h"
#include "../include/app.h"
#include "../vendor/clay/clay.h"
#include "../vendor/stb_ds.h"
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
void LineBreakComponent() {
 CLAY_AUTO_ID({
   .border = {
     .color = TO_CLAY_COLOR(THEME_TEXT),
     .width = 1
   },
   .layout = {
     .sizing = {
       .width = CLAY_SIZING_GROW(0),
       .height = CLAY_SIZING_FIXED(2)}
     },
   .backgroundColor = TO_CLAY_COLOR(THEME_TEXT),
   .cornerRadius = CLAY_CORNER_RADIUS(25),
  }){}
}
Clay_RenderCommandArray UI_Draw(const App* app) {
  Clay_BeginLayout();
  Clay_TextElementConfig* defaultRightSidebarTextConfig = CLAY_TEXT_CONFIG({
    .fontId = 0,
    .fontSize = 16,
    .textAlignment = CLAY_TEXT_ALIGN_CENTER,
    .textColor = TO_CLAY_COLOR(THEME_TEXT),
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
       .backgroundColor = TO_CLAY_COLOR(THEME_SURFACE),
       .cornerRadius = CLAY_CORNER_RADIUS(8),
    }) {
      LineBreakComponent();
      CLAY_TEXT(CLAY_STRING("Debug"), defaultRightSidebarTextConfig);
      LineBreakComponent();
      CLAY_TEXT(
        ToClayString(TextFormat("Dimensions: %ix%i", GetScreenWidth(), GetScreenHeight())),
        defaultRightSidebarTextConfig
      );
      LineBreakComponent();
      CLAY_TEXT(
        ToClayString(TextFormat("Nodes", GetScreenWidth(), GetScreenHeight())),
        defaultRightSidebarTextConfig
      );
      LineBreakComponent();
      for (size_t i = 0; i < arrlen(app->canvas->nodes); i++) {
         CLAY_TEXT(ToClayString(app->canvas->nodes[i].name), defaultRightSidebarTextConfig);
      }
    }
  };
  return Clay_EndLayout();
}
// clang-format on
