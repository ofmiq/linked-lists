#include "singly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

static double create_random_double_number(int min, int max) {
  double range = (max - min);
  double div = RAND_MAX / range;
  return min + (rand() / div);
}

static singly_node* create_singly_node(double val) {
  singly_node* node = (singly_node*)malloc(sizeof(singly_node));
  if (!node) {
    return NULL;
  }
  node->val = val;
  node->next = NULL;
  return node;
}

static singly_node* find_predecessor(singly_linked_list* list,
                                     singly_node* target) {
  if (!list || !target) {
    return NULL;
  }

  singly_node* it = list->begin;
  while (it) {
    if (it->next == target) {
      return it;
    }
    it = it->next;
  }

  return NULL;
}

singly_linked_list* sll_create_empty(void) {
  singly_linked_list* list =
      (singly_linked_list*)malloc(sizeof(singly_linked_list));
  if (!list) {
    return NULL;
  }

  list->begin = NULL;
  list->current = NULL;

  return list;
}

singly_linked_list* sll_create_random(size_t size) {
  singly_linked_list* list = sll_create_empty();
  if (!list) {
    return NULL;
  }

  singly_node* tail = NULL;

  for (size_t i = 0; i < size; ++i) {
    singly_node* node =
        create_singly_node(create_random_double_number(-10, 10));

    if (!node) {
      sll_destroy(list);
      return NULL;
    }

    if (!tail) {
      list->begin = list->current = node;
    } else {
      tail->next = node;
    }
    tail = node;
  }

  return list;
}

void sll_destroy(singly_linked_list* list) {
  if (!list) {
    return;
  }

  singly_node* it = list->begin;
  while (it) {
    singly_node* next = it->next;
    free(it);
    it = next;
  }

  free(list);
}

void sll_print(singly_linked_list* list) {
  if (!list) {
    return;
  }

  singly_node* it = list->begin;
  while (it) {
    printf("%f ", it->val);
    it = it->next;
  }

  printf("\n");
}

char sll_curr_step_right(singly_linked_list* list) {
  if (!list || !list->begin || !list->current || !list->current->next) {
    return SLL_ERROR;
  }

  list->current = list->current->next;
  return SLL_OK;
}

char sll_curr_step_left(singly_linked_list* list) {
  if (!list || !list->begin || !list->current) {
    return SLL_ERROR;
  }

  list->current = find_predecessor(list, list->current);
  return list->current ? SLL_OK : SLL_ERROR;
}

singly_node* sll_insert_right(singly_linked_list* list, double val) {
  if (!list) {
    return NULL;
  }

  singly_node* new_node = create_singly_node(val);
  if (!new_node) {
    return NULL;
  }

  if (!list->begin) {
    list->begin = list->current = new_node;
    return new_node;
  }

  if (!list->current) {
    free(new_node);
    return NULL;
  }

  new_node->next = list->current->next;
  list->current->next = new_node;

  return new_node;
}

singly_node* sll_insert_left(singly_linked_list* list, double val) {
  if (!list || !list->current) {
    return NULL;
  }

  singly_node* new_node = create_singly_node(val);
  if (!new_node) {
    return NULL;
  }

  if (!list->begin) {
    list->begin = list->current = new_node;
    return new_node;
  }

  if (!list->current) {
    free(new_node);
    return NULL;
  }

  singly_node* predecessor = find_predecessor(list, list->current);
  new_node->next = list->current;

  if (predecessor) {
    predecessor->next = new_node;
  } else {
    list->begin = new_node;
  }

  return new_node;
}
