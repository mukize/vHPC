#include "../include/canvas.h"
#include "../include/node.h"
#include "../vendor/stb_ds.h"
#include <assert.h>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <stddef.h>

static const float ZOOM_MAX = 1.f;
static const float ZOOM_MIN = .5f;
static const float ZOOM_DEFAULT = 1.f;
static const int GRID_DOT_SIZE = 3;
static const int GRID_DOT_DELTA = 50;

void Canvas_Init(Canvas *canvas) {
  assert(canvas != NULL);

  *canvas = (Canvas){0};
  canvas->camera.zoom = ZOOM_DEFAULT;
  canvas->size = (Vector2){2000, 2000};

  return;
}

void Canvas_Draw(const Canvas *canvas) {
  assert(canvas != NULL);

  BeginMode2D(canvas->camera);

  // Grid
  for (size_t i = 0; i < canvas->size.x; i += GRID_DOT_DELTA) {
    for (size_t j = 0; j < canvas->size.y; j += GRID_DOT_DELTA) {
      Vector2 pos = {i, j};
      DrawCircleV(pos, GRID_DOT_SIZE, LIGHTGRAY);
    }
  }

  // Nodes
  for (size_t i = 0; i < arrlen(canvas->nodes); i++) {
    Node_Draw(&canvas->nodes[i]);
  }

  // Center reference
  DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 50, MAROON);

  EndMode2D();
}

void Canvas_Update(Canvas *canvas) {
  assert(canvas != NULL);

  Camera2D *canvas_camera = &canvas->camera;

  // Panning
  // ------------------------------------------------------------
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    Vector2 delta = GetMouseDelta();
    delta = Vector2Scale(delta, -1.0f / canvas_camera->zoom);
    canvas_camera->target = Vector2Add(canvas_camera->target, delta);
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
