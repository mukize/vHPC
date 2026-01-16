#ifndef NODE_H
#define NODE_H

#include <raylib.h>
#include <stddef.h>

typedef struct {
  char name[255];
  Rectangle bounds;
} Node;

void Node_Init(Node *node, const char *name, Rectangle bounds);

void Node_Draw(const Node *node);

void Node_Update(Node *node);

#endif
