#ifndef NODE_H
#define NODE_H

#include <raylib.h>
#include <stddef.h>

typedef struct {
  char name[255];
  Vector2 position;
  Vector2 size;
  Color color;
} Node;

void Node_Init(Node *node, const char *name, const Vector2 position, const Vector2 size, const Color color);

void Node_Draw(const Node *node);

void Node_Update(Node *node);

#endif
