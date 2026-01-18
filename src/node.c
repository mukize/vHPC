#include "../include/node.h"
#include "../include/theme.h"
#include <assert.h>
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void Node_Init(Node *node, const char *name, Rectangle bounds) {
  assert(node != NULL);
  snprintf(node->name, sizeof(node->name), "%s", name);
  node->bounds = bounds;
}

void Node_Draw(const Node *node) {
  // Icon
  Vector2 origin = {node->bounds.width / 2, node->bounds.height / 2};
  DrawRectanglePro(node->bounds, origin, 0, THEME_MAUVE);

  // Text
  // Font font = GetFontDefault();
  // int fontSize = font.baseSize;
  // float spacing = font.baseSize / 2.f;
  // Vector2 textSize = MeasureTextEx(font, node->name, fontSize, spacing);
  // Vector2 textPosition = {node->bounds.x + node->bounds.width / 2,
  //                         node->bounds.y + node->bounds.height};
  // DrawTextPro(font, node->name, textPosition, (Vector2){textSize.x / 2.f,
  // textSize.y / 2.f },  0, fontSize, spacing, BLACK);
};

void Node_Update(Node *node);
