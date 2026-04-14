#include "singly_linked_list.h"
#include <stdio.h>

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

int main() {
  test_create();
  return 0;
}