#include "../include/canvas.h"
#include "../include/node.h"
#include "../include/theme.h"
#include "../vendor/stb_ds.h"
#include <assert.h>
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <stddef.h>
#include <stdio.h>

static const float ZOOM_MAX = 1.f;
static const float ZOOM_MIN = .5f;
static const float ZOOM_DEFAULT = 1.f;
static const Vector2 GRID_SIZE_MAX = {3000, 3000};
static const Vector2 GRID_SIZE_MIN = {-3000, -3000};
static const int GRID_DOT_SIZE = 3;
static const Color GRID_DOT_COLOR = THEME_OVERLAY;
static const int GRID_DOT_SPACING = 50;

void Canvas_Init(Canvas *canvas) {
  assert(canvas != NULL);

  *canvas = (Canvas){0};
  canvas->camera.zoom = ZOOM_DEFAULT;
  canvas->dragNodeIndex = -1;

  return;
}

void Canvas_Draw(const Canvas *canvas) {
  assert(canvas != NULL);

  BeginMode2D(canvas->camera);
  ClearBackground(THEME_BASE);

  // Grid
  // ------------------------------------------------------------
  Vector2 tL = GetScreenToWorld2D((Vector2){0, 0}, canvas->camera);
  Vector2 bR = GetScreenToWorld2D(
      (Vector2){GetScreenWidth(), GetScreenHeight()}, canvas->camera);

  float startX = floor(tL.x / GRID_DOT_SPACING) * GRID_DOT_SPACING;
  float startY = floor(tL.y / GRID_DOT_SPACING) * GRID_DOT_SPACING;

  for (float x = startX; x < bR.x + GRID_DOT_SPACING; x += GRID_DOT_SPACING) {
    for (float y = startY; y < bR.y + GRID_DOT_SPACING; y += GRID_DOT_SPACING) {

      if (canvas->camera.zoom < 0.1f)
        continue;

      DrawCircle(x, y, 3, GRID_DOT_COLOR);
    }
  }
  // ------------------------------------------------------------

  // Nodes
  for (size_t i = 0; i < arrlen(canvas->nodes); i++) {
    Node_Draw(&canvas->nodes[i]);
  }

  EndMode2D();
}

void Canvas_Update(Canvas *canvas) {
  assert(canvas != NULL);

  Camera2D *canvas_camera = &canvas->camera;

  // Bounding target
  // ------------------------------------------------------------
  // Vector2 center = (Vector2){GetScreenWidth() / 2.f, GetScreenHeight()
  // / 2.f}; Vector2 minTarget = Vector2Add(GRID_SIZE_MIN, center); Vector2
  // maxTarget = Vector2Subtract(GRID_SIZE_MAX, center);
  // ------------------------------------------------------------

  // Dragging
  // ------------------------------------------------------------
  // Toggle that canvas is being dragged
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    Vector2 mouseWorldPos =
        GetScreenToWorld2D(GetMousePosition(), *canvas_camera);
    if (canvas->dragNodeIndex == -1) {
      for (size_t i = 0; i < arrlen(canvas->nodes); i++) {
        if (CheckCollisionPointRec(mouseWorldPos, canvas->nodes[i].bounds)) {
          canvas->dragNodeIndex = i;
          break;
        }
      }
    }
  }
  // Do actual dragging
  if (canvas->dragNodeIndex != -1) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      Node *node = &canvas->nodes[canvas->dragNodeIndex];
      Vector2 dragDelta =
          Vector2Scale(GetMouseDelta(), 1.0f / canvas_camera->zoom);
      node->bounds.x += dragDelta.x;
      node->bounds.y += dragDelta.y;
    } else
      canvas->dragNodeIndex = -1;
  }
  // ------------------------------------------------------------

  // Panning
  // ------------------------------------------------------------
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    if (canvas->dragNodeIndex == -1) {
      // Vector2 delta = Vector2Scale(GetMouseDelta(), -1.0f /
      // canvas_camera->zoom); Vector2 newTarget =
      // Vector2Add(canvas_camera->target, delta); canvas_camera->target =
      // Vector2Clamp(newTarget, minTarget, maxTarget);
    }
  }
  // ------------------------------------------------------------

  // Adding Nodes to the workspace
  // ------------------------------------------------------------
  if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
    Node node;
    Vector2 mouseWorldPos =
        GetScreenToWorld2D(GetMousePosition(), *canvas_camera);
    Vector2 size = (Vector2){50, 50};
    Node_Init(&node, "test",
              (Rectangle){mouseWorldPos.x, mouseWorldPos.y, 50, 50});
    arrpush(canvas->nodes, node);
  }
  // ------------------------------------------------------------

  // Handle zooming
  // ------------------------------------------------------------
  // float wheel = GetMouseWheelMove();
  // if (wheel != 0) {
  //   Vector2 mouseWorldPos =
  //       GetScreenToWorld2D(GetMousePosition(), *canvas_camera);
  //   canvas_camera->offset = GetMousePosition();
  //   canvas_camera->target = Vector2Clamp(mouseWorldPos, minTarget,
  //   maxTarget); canvas_camera->target = Vector2Clamp(mouseWorldPos,
  //   minTarget, maxTarget);
  //
  //   float scale = 0.2f * wheel;
  //   canvas_camera->zoom =
  //       Clamp(expf(logf(canvas_camera->zoom) + scale), ZOOM_MIN, ZOOM_MAX);
  // }
  // ------------------------------------------------------------
}
