#include "../include/workspace.h"
#include "../include/node.h"
#include <assert.h>
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <stddef.h>

void Workspace_Init(Workspace *ws) {
  assert(ws != NULL);

  *ws = (Workspace){0};
  ws->camera.zoom = 1.0f;
  NodeList_Init(&ws->nodes);

  return;
}

void Workspace_Draw(const Workspace *ws) {
  assert(ws != NULL);

  BeginMode2D(ws->camera);
  // Draw the 3d grid, rotated 90 degrees and centered around 0,0
  // just so we have something in the XY plane
  rlPushMatrix();
  rlTranslatef(0, 25 * 50, 0);
  rlRotatef(90, 1, 0, 0);
  DrawGrid(100, 50);
  rlPopMatrix();

  // Draw a reference circle
  DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 50, MAROON);
  for (size_t i = 0; i < ws->nodes.count; i++) {
    Node_Draw(&ws->nodes.items[i]);
  }

  EndMode2D();
}

void Workspace_Update(Workspace *ws) {
  assert(ws != NULL);

  Camera2D *ws_camera = &ws->camera;

  // Panning
  // ------------------------------------------------------------
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    Vector2 delta = GetMouseDelta();
    delta = Vector2Scale(delta, -1.0f / ws_camera->zoom);
    ws_camera->target = Vector2Add(ws_camera->target, delta);
  }
  // ------------------------------------------------------------

  // Adding Nodes to the workspace
  // ------------------------------------------------------------
  if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
    Node node;
    Node_Init(&node, "test", GetScreenToWorld2D(GetMousePosition(), *ws_camera),
              (Vector2){100, 100}, RED);
    NodeList_Push(&ws->nodes, node);
  }
  // ------------------------------------------------------------

  float wheel = GetMouseWheelMove();
  if (wheel != 0) {
    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), *ws_camera);
    ws_camera->offset = GetMousePosition();
    ws_camera->target = mouseWorldPos;

    float scale = 0.2f * wheel;
    ws_camera->zoom = Clamp(expf(logf(ws_camera->zoom) + scale), 0.125f, 64.0f);
  }
}
