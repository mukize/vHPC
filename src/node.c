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
  DrawRectangleV(node->position, node->size, node->color);
};

void Node_Update(Node *node);

void NodeList_Init(NodeList *list) {
  assert(list != NULL);

  list->count = 0;
  list->capacity = 4;
  list->items = malloc(list->capacity * sizeof(Node));
};

void NodeList_Push(NodeList *list, Node node) {
  assert(list != NULL);

  if (list->count >= list->capacity) {
    list->capacity *= 2;
    list->items = realloc(list->items, list->capacity * sizeof(Node));
    assert(list->items != NULL);
  }

  list->items[list->count++] = node;
};
