#ifndef STATE_H
#define STATE_H

#include <raylib.h>
#include "canvas.h"

typedef struct App {
  Canvas* canvas;
  Font* fonts;
} App;

typedef enum App_Fonts {
  APP_FONT_DEFAULT,
} App_Fonts;

#define TO_CLAY_COLOR(c) (Clay_Color){ .r = (float)c.r, .g = (float)c.g, .b = (float)c.b, .a = (float)c.a }

// Catpuccin Macchiato
static const Color THEME_BASE = {36, 39, 58, 255};
static const Color THEME_SURFACE = {54, 58, 79, 255};
static const Color THEME_OVERLAY = {110, 115, 141, 255};
static const Color THEME_CRUST = {24, 25, 38, 255};
static const Color THEME_TEXT = {202, 211, 245, 255};
static const Color THEME_MAUVE = {198, 160, 246, 255};

#endif
