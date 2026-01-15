#include "../include/node.h"
#include <assert.h>
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void Node_Init(Node *node, const char *name, const Vector2 position,
               const Vector2 size, const Color color) {

  assert(node != NULL);

  snprintf(node->name, sizeof(node->name), "%s", name);
  node->position = position;
  node->size = size;
  node->color = color;
}

void Node_Draw(const Node *node) {
  Rectangle rect = {node->position.x, node->position.y, node->size.x,
                    node->size.y};
  Vector2 origin = {node->size.x / 2, node->size.y / 2};
  DrawRectanglePro(rect, origin, 0, node->color);
};

void Node_Update(Node *node);
