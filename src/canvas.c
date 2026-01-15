#include "../include/canvas.h"
#include "../include/node.h"
#include "../vendor/stb_ds.h"
#include <assert.h>
#include <math.h> // Required for floor()
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <stddef.h>
#include <stdio.h>

static const float ZOOM_MAX = 1.f;
static const float ZOOM_MIN = .5f;
static const float ZOOM_DEFAULT = .5f;
static const Vector2 GRID_SIZE_MAX = {3000, 3000};
static const Vector2 GRID_SIZE_MIN = {-3000, -3000};
static const int GRID_DOT_SIZE = 3;
static const Color GRID_DOT_COLOR = LIGHTGRAY;
static const int GRID_DOT_SPACING = 50;

void Canvas_Init(Canvas *canvas) {
  assert(canvas != NULL);

  *canvas = (Canvas){0};
  canvas->camera.zoom = ZOOM_DEFAULT;
  canvas->camera.target = (Vector2){0, 0};

  return;
}

void Canvas_Draw(const Canvas *canvas) {
  assert(canvas != NULL);

  BeginMode2D(canvas->camera);

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

  // Center reference
  DrawCircle(0, 0, 50, MAROON);

  EndMode2D();
}

void Canvas_Update(Canvas *canvas) {
  assert(canvas != NULL);

  Camera2D *canvas_camera = &canvas->camera;

  // Panning
  // ------------------------------------------------------------
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    Vector2 delta = Vector2Scale(GetMouseDelta(), -1.0f / canvas_camera->zoom);
    Vector2 center = (Vector2){GetScreenWidth() / 2.f, GetScreenHeight() / 2.f};
    Vector2 newTarget = Vector2Add(canvas_camera->target, delta);
    Vector2 minTarget = Vector2Add(GRID_SIZE_MIN, center);
    Vector2 maxTarget = Vector2Subtract(GRID_SIZE_MAX, center);
    // canvas_camera->target = newTarget;
    canvas_camera->target = Vector2Clamp(newTarget, minTarget, maxTarget);
    printf("target: %f, %f\n", canvas_camera->target.x,
           canvas_camera->target.y);
  }
  // ------------------------------------------------------------

  // Adding Nodes to the workspace
  // ------------------------------------------------------------
  if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
    Node node;
    Node_Init(&node, "test",
              GetScreenToWorld2D(GetMousePosition(), *canvas_camera),
              (Vector2){50, 50}, MAROON);
    arrpush(canvas->nodes, node);
  }
  // ------------------------------------------------------------

  // Handle zooming
  // ------------------------------------------------------------
  float wheel = GetMouseWheelMove();
  if (wheel != 0) {
    Vector2 mouseWorldPos =
        GetScreenToWorld2D(GetMousePosition(), *canvas_camera);
    canvas_camera->offset = GetMousePosition();
    canvas_camera->target = mouseWorldPos;

    float scale = 0.2f * wheel;
    canvas_camera->zoom =
        Clamp(expf(logf(canvas_camera->zoom) + scale), ZOOM_MIN, ZOOM_MAX);
  }
  // ------------------------------------------------------------
}
