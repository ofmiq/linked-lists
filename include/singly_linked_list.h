#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <stddef.h>

#define SLL_ERROR ((char)-1)
#define SLL_OK ((char)0)

/**
 * @brief Structure representing a node in a singly linked list
 */
typedef struct singly_node {
  double val;
  struct singly_node* next;
} singly_node;

/**
 * @brief Structure representing a singly linked list
 */
typedef struct {
  singly_node* begin;
  singly_node* current;
} singly_linked_list;

/**
 * @brief Creates an empty singly linked list
 * @return Pointer to the newly created list
 */
singly_linked_list* sll_create_empty(void);

/**
 * @brief Creates a singly linked list filled with random values
 * @param size The number of elements in the list
 * @return Pointer to the newly created list
 */
singly_linked_list* sll_create_random(size_t size);

/**
 * @brief Destroys the singly linked list and frees allocated memory
 * @param list Pointer to the list to be deleted
 */
void sll_destroy(singly_linked_list* list);

/**
 * @brief Prints the contents of the singly linked list
 * @param list Pointer to the list
 */
void sll_print(singly_linked_list* list);

/**
 * @brief Moves the cursor one element to the right
 * @param list Pointer to the list
 * @return Status code
 */
char sll_curr_step_right(singly_linked_list* list);

/**
 * @brief Moves the cursor one element to the left
 * @note In a singly linked list, this operation is O(n)
 * @param list Pointer to the list
 * @return Status code
 */
char sll_curr_step_left(singly_linked_list* list);

/**
 * @brief Inserts a new element to the right of the cursor
 * @param list Pointer to the list
 * @param val The value to be inserted
 * @return Pointer to the newly inserted node
 */
singly_node* sll_insert_right(singly_linked_list* list, double val);

/**
 * @brief Inserts a new element to the left of the cursor
 * @param list Pointer to the list
 * @param val The value to be inserted
 * @return Pointer to the newly inserted node
 */
singly_node* sll_insert_left(singly_linked_list* list, double val);

/**
 * @brief Deletes the node at the current cursor position
 * @note If the deleted node had a successor, it becomes the new cursor;
 * otherwise, the predecessor becomes the new cursor
 * @param list Pointer to the list
 * @return Status code
 */
char sll_delete(singly_linked_list* list);

/**
 * @brief Swaps the cursor node with its left neighbor
 * @param list Pointer to the list
 * @return Status code (SLL_OK or error code)
 */
char sll_swap_cursor_left(singly_linked_list* list);

/**
 * @brief Swaps the cursor node with its right neighbor
 * @param list Pointer to the list
 * @return Status code (SLL_OK or error code)
 */
char sll_swap_cursor_right(singly_linked_list* list);

/**
 * @brief Creates a copy of a given singly linked list
 * @param list Pointer to the list will be copied
 * @return Pointer to the copy of a given list 
 */
singly_linked_list* sll_create_copy(singly_linked_list* list);

/**
 * @brief Concatenates list b to list a from the right
 * @param a Pointer to the first list
 * @param b Pointer to the second list
 * @note List b is destroyed by this operation, list a is extended
 */
void sll_concatenate(singly_linked_list* a, singly_linked_list* b);

/**
 * @brief Divide a given singly linked list into two
 * @param list Pointer to the list will be splitted
 * @return Pointer to the new list created by dividing
 * @note List will be divide to the right of cursor 
 */
singly_linked_list* sll_divide(singly_linked_list* list);

/**
 * @brief Computes a size of a given singly linked list
 * @param list Pointer to the list
 * @return Length of a given singly linked list
 */
size_t sll_get_size(singly_linked_list* list);

#endif