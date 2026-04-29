#include "singly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

static double create_random_double_number(int min, int max) {
  if (min >= max) {
    return (double)min;
  }
  double range = (double)(max - min);
  return min + ((double)rand() / RAND_MAX) * range;
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

static double calculate_mean_value(double a, double b) { return (a + b) / 2.0; }

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

  singly_node* predecessor = (list->current == list->begin)
                                 ? NULL
                                 : find_predecessor(list, list->current);

  new_node->next = list->current;

  if (predecessor) {
    predecessor->next = new_node;
  } else {
    list->begin = new_node;
  }

  return new_node;
}

char sll_delete(singly_linked_list* list) {
  if (!list || !list->begin || !list->current) {
    return SLL_ERROR;
  }

  singly_node* to_delete = list->current;
  singly_node* predecessor = (list->current == list->begin)
                                 ? NULL
                                 : find_predecessor(list, list->current);

  if (to_delete->next) {
    list->current = to_delete->next;
  } else {
    list->current = predecessor;
  }

  if (predecessor) {
    predecessor->next = to_delete->next;
  } else {
    list->begin = to_delete->next;
  }

  free(to_delete);
  return SLL_OK;
}

char sll_swap_cursor_left(singly_linked_list* list) {
  if (!list || !list->begin || !list->current) {
    return SLL_ERROR;
  }
  if (list->current == list->begin) {
    return SLL_ERROR;
  }

  singly_node* predecessor = find_predecessor(list, list->current);

  double tmp = predecessor->val;
  predecessor->val = list->current->val;
  list->current->val = tmp;

  return SLL_OK;
}

char sll_swap_cursor_right(singly_linked_list* list) {
  if (!list || !list->begin || !list->current || !list->current->next) {
    return SLL_ERROR;
  }

  double tmp = list->current->next->val;
  list->current->next->val = list->current->val;
  list->current->val = tmp;

  return SLL_OK;
}

singly_linked_list* sll_create_copy(singly_linked_list* list) {
  if (!list || !list->begin || !list->current) {
    return NULL;
  }

  singly_linked_list* copy = sll_create_empty();
  if (!copy) {
    return NULL;
  }

  singly_node* tail = NULL;

  singly_node* it = list->begin;
  while (it) {
    singly_node* node = create_singly_node(it->val);

    if (!node) {
      sll_destroy(copy);
      return NULL;
    }

    if (!tail) {
      copy->begin = node;
    } else {
      tail->next = node;
    }
    tail = node;

    if (it == list->current) {
      copy->current = node;
    }

    it = it->next;
  }

  return copy;
}

void sll_concatenate(singly_linked_list* a, singly_linked_list* b) {
  if (!b->begin) {
    free(b);
    return;
  }

  if (!a->begin) {
    a->begin = b->begin;
    a->current = b->current;
    free(b);
    return;
  }

  singly_node* tail = a->begin;
  while (tail->next) {
    tail = tail->next;
  }

  tail->next = b->begin;

  free(b);
}

singly_linked_list* sll_divide(singly_linked_list* list) {
  if (!list || !list->begin || !list->current) {
    return NULL;
  }

  if (!list->current->next) {
    return NULL;
  }

  singly_linked_list* new_list = sll_create_empty();
  if (!new_list) {
    return NULL;
  }

  new_list->begin = new_list->current = list->current->next;
  list->current->next = NULL;

  return new_list;
}

size_t sll_get_size(singly_linked_list* list) {
  if (!list) {
    return 0;
  }

  singly_node* it = list->begin;
  size_t size = 0;

  while (it) {
    ++size;
    it = it->next;
  }

  return size;
}

void sll_inversion(singly_linked_list* list) {
  if (!list || !list->begin) {
    return;
  }

  singly_node* prev = NULL;
  singly_node* curr = list->begin;
  singly_node* next = NULL;

  while (curr) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  list->begin = prev;
}

char sll_interpolate_linear(singly_linked_list* list) {
  if (!list || !list->begin) {
    return SLL_ERROR;
  }

  singly_node* it = list->begin;

  while (it && it->next) {
    double mean_val = calculate_mean_value(it->val, it->next->val);
    singly_node* new_node = create_singly_node(mean_val);
    if (!new_node) {
      return SLL_ERROR;
    }
    new_node->next = it->next;
    it->next = new_node;
    it = it->next->next;
  }

  return SLL_OK;
}
