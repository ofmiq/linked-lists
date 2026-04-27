#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "singly_linked_list.h"

void test_create() {
  singly_linked_list* empty_sll = sll_create_empty();
  if (!empty_sll) {
    printf("sll_create_empty error\n");
  }
  printf("1. empty list was created successfully\n");

  singly_linked_list* random_sll = sll_create_random(10);
  if (!random_sll) {
    printf("sll_create_random error\n");
  }
  printf("2. random list was created successfully\n");

  printf("elements of random singly linked list:\n");
  sll_print(random_sll);

  sll_destroy(empty_sll);
  sll_destroy(random_sll);

  printf("3. lists were destroyed successfully\n");

  return;
}

void test_steps() {
  singly_linked_list* random_sll = sll_create_random(10);
  if (!random_sll) {
    return;
  }

  printf("list was created\nElements:");
  sll_print(random_sll);

  printf("current val: %lf\n", random_sll->current->val);

  if (sll_curr_step_right(random_sll) == SLL_OK) {
    printf("cursor was moved one element right, val: %lf\n",
           random_sll->current->val);
  } else {
    printf("error: cursor was'nt moved\n");
  }

  if (sll_curr_step_left(random_sll) == SLL_OK) {
    printf("cursor was moved one element left, val: %lf\n",
           random_sll->current->val);
  } else {
    printf("error: cursor was'nt moved\n");
  }

  if (sll_curr_step_left(random_sll) == SLL_OK) {
    printf("cursor was moved one element left, val: %lf\n",
           random_sll->current->val);
  } else {
    printf("error: cursor was'nt moved\n");
  }

  sll_destroy(random_sll);

  return;
}

void test_insert() {
  singly_linked_list* random_sll = sll_create_random(5);
  if (!random_sll) {
    return;
  }

  printf("list was created\nelements: ");
  sll_print(random_sll);

  sll_insert_left(random_sll, -1);
  printf("list was updated, elements: ");
  sll_print(random_sll);

  random_sll->current = sll_insert_right(random_sll, 10);
  printf("list was updated, elements: ");
  sll_print(random_sll);

  sll_insert_left(random_sll, 5);
  printf("list was updated, elements: ");
  sll_print(random_sll);

  sll_destroy(random_sll);
}

void test_delete() {
  singly_linked_list* random_sll = sll_create_random(5);
  if (!random_sll) {
    return;
  }

  printf("list was created\nelements: ");
  sll_print(random_sll);

  sll_delete(random_sll);
  printf("element was deleted, elements: ");
  sll_print(random_sll);

  sll_destroy(random_sll);
}

void test_swaps() {
  singly_linked_list* random_sll = sll_create_random(5);
  if (!random_sll) {
    return;
  }

  printf("list was created\nelements: ");
  sll_print(random_sll);

  if (sll_swap_cursor_left(random_sll) == SLL_OK) {
    printf("left swap was processed\nelements: ");
    sll_print(random_sll);
  } else {
    printf("error: swap was'nt processed (expected)\n");
  }

  sll_curr_step_right(random_sll);
  sll_curr_step_right(random_sll);

  sll_swap_cursor_left(random_sll);
  printf("left swap was processed\nelements: ");
  sll_print(random_sll);

  sll_swap_cursor_right(random_sll);
  printf("right swap was processed\nelements: ");
  sll_print(random_sll);

  sll_curr_step_right(random_sll);
  sll_curr_step_right(random_sll);

  if (sll_swap_cursor_right(random_sll) == SLL_OK) {
    printf("left swap was processed\nelements: ");
    sll_print(random_sll);
  } else {
    printf("error: swap was'nt processed (expected)\n");
  }

  sll_destroy(random_sll);
}

void test_copy() {
  singly_linked_list* random_sll = sll_create_random(5);
  if (!random_sll) {
    return;
  }

  printf("list was created\nelements: ");
  sll_print(random_sll);
  printf("address of original list: %p\n", (void*)random_sll);

  singly_linked_list* copy_sll = sll_create_copy(random_sll);
  if (!copy_sll) {
    sll_destroy(random_sll);
    return;
  }

  printf("copy was created\nelements: ");
  sll_print(copy_sll);
  printf("address of copy list: %p\n", (void*)copy_sll);

  sll_destroy(random_sll);
  sll_destroy(copy_sll);
}

int main() {
  srand(time(NULL));
  test_create();
  test_steps();
  test_insert();
  test_delete();
  test_swaps();
  test_copy();
  return 0;
}