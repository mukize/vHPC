#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <raylib.h>
#include "node.h"

typedef struct Workspace {
  Camera2D camera;
  NodeList nodes;
} Workspace;

void Workspace_Init(Workspace *ws);

void Workspace_Update(Workspace *ws);

void Workspace_Draw(const Workspace *ws);

#endif
