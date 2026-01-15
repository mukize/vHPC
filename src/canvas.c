#include "../include/canvas.h"
#include "../include/node.h"
#include <assert.h>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <stddef.h>

void Canvas_Init(Canvas *canvas) {
  assert(canvas != NULL);

  *canvas = (Canvas){0};
  canvas->camera.zoom = 1.0f;
  NodeList_Init(&canvas->nodes);

  return;
}

void Canvas_Draw(const Canvas *canvas) {
  assert(canvas != NULL);

  BeginMode2D(canvas->camera);
  // Draw the 3d grid, rotated 90 degrees and centered around 0,0
  // just so we have something in the XY plane
  rlPushMatrix();
  rlTranslatef(0, 25 * 50, 0);
  rlRotatef(90, 1, 0, 0);
  DrawGrid(100, 50);
  rlPopMatrix();

  // Draw a reference circle
  DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 50, MAROON);
  for (size_t i = 0; i < canvas->nodes.count; i++) {
    Node_Draw(&canvas->nodes.items[i]);
  }

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
              (Vector2){100, 100}, RED);
    NodeList_Push(&canvas->nodes, node);
  }
  // ------------------------------------------------------------

  float wheel = GetMouseWheelMove();
  if (wheel != 0) {
    Vector2 mouseWorldPos =
        GetScreenToWorld2D(GetMousePosition(), *canvas_camera);
    canvas_camera->offset = GetMousePosition();
    canvas_camera->target = mouseWorldPos;

    float scale = 0.2f * wheel;
    canvas_camera->zoom =
        Clamp(expf(logf(canvas_camera->zoom) + scale), 0.125f, 64.0f);
  }
}
