#include "../include/ui.h"
#include "../include/app.h"
#include "../vendor/stb_ds.h"
#include "raylib.h"
#include <stdio.h>
#include <string.h>

// Raylib's TextFormat only has about 2 buffers spaces for formatting and we
// will need to format a lot of times in a frame.
static Clay_String ClayStrFormat(const char *string, ...) {
  static char buffers[16][256];
  static int bufferIndex = 0;

  char *buf = buffers[bufferIndex];
  bufferIndex = (bufferIndex + 1) % 16;

  va_list args;
  va_start(args, string);
  int length = vsnprintf(buf, 256, string, args);
  va_end(args);

  return (Clay_String){.length = length, .chars = buf};
}

static Clay_String ClayStr(const char *text) {
  return (Clay_String){
      .isStaticallyAllocated = true, .length = strlen(text), .chars = text};
}

void UI_Update(App *app) {
  Vector2 mousePos = GetMousePosition();
  Clay_SetLayoutDimensions(
      (Clay_Dimensions){(float)GetScreenWidth(), (float)GetScreenHeight()});
  Clay_SetPointerState((Clay_Vector2){mousePos.x, mousePos.y},
                       IsMouseButtonDown(MOUSE_LEFT_BUTTON));

  if (IsKeyPressed(KEY_F1)) {
    Clay_SetDebugModeEnabled(!Clay_IsDebugModeEnabled());
  }

  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
    if (Clay_PointerOver(CLAY_ID("OpenModalButton")))
      app->ui->isModalOpen = true;

    if (Clay_PointerOver(CLAY_ID("CloseModalButton")))
      app->ui->isModalOpen = false;
  }
}

void RenderLineBreak() {
  CLAY_AUTO_ID({
      .border = {.color = TO_CLAY_COLOR(THEME_TEXT), .width = 1},
      .layout = {.sizing = {.width = CLAY_SIZING_GROW(0),
                            .height = CLAY_SIZING_FIXED(2)}},
      .backgroundColor = TO_CLAY_COLOR(THEME_TEXT),
      .cornerRadius = CLAY_CORNER_RADIUS(25),
  }) {}
}

void RenderButton(const char *id, const char *content) {
  CLAY(CLAY_SID(ClayStr(id)),
       {
           .layout =
               {.padding = {.top = 8, .bottom = 8, .left = 16, .right = 16}},
           .backgroundColor = Clay_Hovered() ? TO_CLAY_COLOR(THEME_OVERLAY)
                                             : TO_CLAY_COLOR(THEME_BASE),
           .cornerRadius = CLAY_CORNER_RADIUS(8),
       }) {
    if (Clay_Hovered()) {
      SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }

    CLAY_TEXT(ClayStr(content),
              CLAY_TEXT_CONFIG({.fontId = 0,
                                .fontSize = 16,
                                .textAlignment = CLAY_TEXT_ALIGN_CENTER,
                                .textColor = TO_CLAY_COLOR(THEME_TEXT)}));
  };
}

void ModalComponent() {
  CLAY_AUTO_ID({
      .floating = {.attachPoints = {.parent = CLAY_ATTACH_POINT_CENTER_CENTER,
                                    .element = CLAY_ATTACH_POINT_CENTER_CENTER},
                   .zIndex = 100,
                   .attachTo = CLAY_ATTACH_TO_ROOT},
      .layout = {.sizing =
                     {
                         .width = CLAY_SIZING_GROW(0),
                         .height = CLAY_SIZING_GROW(0),
                     }},
      .backgroundColor = TO_CLAY_COLOR(ColorAlpha(THEME_BASE, 0.7)),

  });
  CLAY(CLAY_ID("Modal"),
       {
           .floating = {.attachPoints =
                            {
                                .parent = CLAY_ATTACH_POINT_CENTER_CENTER,
                                .element = CLAY_ATTACH_POINT_CENTER_CENTER,
                            },
                        .zIndex = 101,
                        .attachTo = CLAY_ATTACH_TO_ROOT},
           .layout =
               {
                   .sizing = {.width = CLAY_SIZING_PERCENT(0.5),
                              .height = CLAY_SIZING_PERCENT(0.6)},
                   .childGap = 8,
                   .padding = CLAY_PADDING_ALL(16),
               },
           .backgroundColor = TO_CLAY_COLOR(THEME_SURFACE),
           .cornerRadius = CLAY_CORNER_RADIUS(25),
       }) {
    RenderButton("CloseModalButton", "Close");
  };
}

Clay_RenderCommandArray UI_Draw(const App *app) {
  Clay_TextElementConfig *defaultRightSidebarTextConfig = CLAY_TEXT_CONFIG({
      .fontId = 0,
      .fontSize = 16,
      .textAlignment = CLAY_TEXT_ALIGN_CENTER,
      .textColor = TO_CLAY_COLOR(THEME_TEXT),
  });

  Clay_BeginLayout();
  // clang-format off
  CLAY(CLAY_ID("Body"), {
    .layout = {
      .layoutDirection = CLAY_LEFT_TO_RIGHT,
      .sizing = {
        .height = CLAY_SIZING_GROW(0),
        .width = CLAY_SIZING_GROW(0),
      },
      // .padding = CLAY_PADDING_ALL(16),
      .childAlignment = CLAY_ALIGN_X_RIGHT,
    },
  }) {
    if (app->ui->isModalOpen) {
      ModalComponent();
    }
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
      CLAY_TEXT(CLAY_STRING("Debug Info"), defaultRightSidebarTextConfig);
      RenderLineBreak();

      RenderButton("OpenModalButton", "Open Modal");

      CLAY_TEXT(
        ClayStrFormat("Dimensions: %ix%i", GetScreenWidth(), GetScreenHeight()),
        defaultRightSidebarTextConfig
      );
      CLAY_TEXT(
         ClayStrFormat("Mouse Delta: %.3fx%.3f", GetMouseDelta().x, GetMouseDelta().y),
        defaultRightSidebarTextConfig
      );
      CLAY_TEXT(
         ClayStrFormat("Drag Index: %i", app->canvas->dragNodeIndex),
        defaultRightSidebarTextConfig
      );
      RenderLineBreak();

      CLAY_TEXT(
        ClayStrFormat("Nodes", GetScreenWidth(), GetScreenHeight()),
        defaultRightSidebarTextConfig
      );
      RenderLineBreak();

      for (size_t i = 0; i < arrlen(app->canvas->nodes); i++) {
         CLAY_TEXT(ClayStr(app->canvas->nodes[i].name), defaultRightSidebarTextConfig);
      }

    }
  };
  return Clay_EndLayout();
}
// clang-format on
