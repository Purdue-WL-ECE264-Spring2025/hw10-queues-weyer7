#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) { return NULL; }

void insert_at_head(struct linked_list *list, size_t value) {
  struct list_node *new_node = (struct list_node *)malloc(sizeof(struct list_node));

  new_node->value = value; //assign the value to the new node
  new_node->next = list->head; //point the new node's next to the current head
  list->head = new_node; //update the list's head to point to the new node
}

void insert_at_tail(struct linked_list *list, size_t value) {
  struct list_node *new_node = (struct list_node *)malloc(sizeof(struct list_node));

  new_node->value = value;
  new_node->next = NULL;

  if(!list->head) { //case for when list is empty
    list->head = new_node;
  }
  struct list_node *current = list->head;
  while (current->next) {
    current = current->next;
  }
  current->next = new_node;
}

size_t remove_from_head(struct linked_list *list) { 
  if (!list->head) {
    return 0; //empty list
  }
  struct list_node *temp = list->head;
  // size_t value = temp->value;
  list->head = temp->next;
  free(temp);
  return 0; 
}

size_t remove_from_tail(struct linked_list *list) { 
  if (!list->head) {
    return 0; //empty list
  }
  struct list_node *current = list->head;
  struct list_node *prev = NULL;
  while (current->next) {
    prev = current;
    current = current->next;
  }
  // size_t value = current->value;
  free(current);

  if (prev) {
    prev->next = NULL;
  } else {
    list->head = NULL; //if only one node
  }
  return 0; 
}

void free_list(struct linked_list list) {
  struct list_node *current = list.head;
  while (current) {
    struct list_node *temp = current;
    current = current->next;
    free(temp);
  }
  list.head = NULL;
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
