#include "../include/ui.h"
#include "../include/app.h"
#include "../vendor/clay/clay.h"
#include "../vendor/stb_ds.h"
#include "raylib.h"
#include <string.h>

bool isModalOpen = true;
const int16_t UI_OVERLAY_ZINDEX = 101;
const int16_t UI_MODAL_ZINDEX = 102;

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

void LineBreakComponent() {
  CLAY_AUTO_ID({
      .border = {.color = TO_CLAY_COLOR(THEME_TEXT), .width = 1},
      .layout = {.sizing = {.width = CLAY_SIZING_GROW(0),
                            .height = CLAY_SIZING_FIXED(2)}},
      .backgroundColor = TO_CLAY_COLOR(THEME_TEXT),
      .cornerRadius = CLAY_CORNER_RADIUS(25),
  }) {}
}

void RenderCloseModalButton() {
  CLAY_AUTO_ID({
      .layout = {.padding =
                     {
                         .top = 8,
                         .bottom = 8,
                         .left = 16,
                         .right = 16,
                     }},
      .backgroundColor = Clay_Hovered() ? TO_CLAY_COLOR(THEME_OVERLAY)
                                        : TO_CLAY_COLOR(THEME_BASE),
      .cornerRadius = CLAY_CORNER_RADIUS(8),
  }) {
    if (Clay_Hovered()) {
      SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && Clay_Hovered()) {
      isModalOpen = false;
    }
    CLAY_TEXT(CLAY_STRING("Close Modal"),
              CLAY_TEXT_CONFIG({
                  .fontId = 0,
                  .fontSize = 16,
                  .textAlignment = CLAY_TEXT_ALIGN_CENTER,
                  .textColor = TO_CLAY_COLOR(THEME_TEXT),
              }));
  };
}

void RenderOpenModalButton() {
  CLAY_AUTO_ID({
      .layout = {.padding =
                     {
                         .top = 8,
                         .bottom = 8,
                         .left = 16,
                         .right = 16,
                     }},
      .backgroundColor = Clay_Hovered() ? TO_CLAY_COLOR(THEME_OVERLAY)
                                        : TO_CLAY_COLOR(THEME_BASE),
      .cornerRadius = CLAY_CORNER_RADIUS(8),
  }) {
    if (Clay_Hovered()) {
      SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    }
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && Clay_Hovered()) {
      isModalOpen = true;
    }
    CLAY_TEXT(CLAY_STRING("Open Modal"),
              CLAY_TEXT_CONFIG({
                  .fontId = 0,
                  .fontSize = 16,
                  .textAlignment = CLAY_TEXT_ALIGN_CENTER,
                  .textColor = TO_CLAY_COLOR(THEME_TEXT),
              }));
  };
}

void ModalComponent() {
  CLAY_AUTO_ID({
      .floating = {.attachPoints = {.parent = CLAY_ATTACH_POINT_CENTER_CENTER,
                                    .element = CLAY_ATTACH_POINT_CENTER_CENTER},
                   .zIndex = UI_OVERLAY_ZINDEX,
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
                        .zIndex = UI_MODAL_ZINDEX,
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
    RenderCloseModalButton();
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
    if (isModalOpen) {
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
      LineBreakComponent();

      RenderOpenModalButton();

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
