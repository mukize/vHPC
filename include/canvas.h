#ifndef CANVAS_H
#define CANVAS_H

#include <raylib.h>
#include "node.h"

typedef struct Canvas {
  Camera2D camera;
  Node* nodes;
  int dragNodeIndex;
} Canvas;

void Canvas_Init(Canvas *ws);

void Canvas_Update(Canvas *ws);

void Canvas_Draw(const Canvas *ws);

#endif
