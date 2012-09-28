/*
 * Greg Billetdeaux
 * CS 3841
 * Lab 2
 * 9/18/2012
 * 
 * This is the header file for Linkedlist.h. It implements a doubly linked list array
 * for storing data. It contains proper memory management as well as an iterator.
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdint.h>
#include <stdbool.h>

/*
 * Represents an index in the double linked list.
 * Holds references to the data, dataSize, and the 
 *  indexes before and after it in the list.
 */
struct listNode
{
  void *data;
  uint32_t dataSize;
  struct listNode *nextNode;
  struct listNode *prevNode;
};

/*
 * Represents a doubly linked list
 * Has references to the first and last
 *  indexes of the list
 */
struct linkedList
{
  uint32_t size;
  struct listNode *head;
  struct listNode *tail;
};

/*
 * Used to iterate through a linked list
 * Has reference to the current index of the list
 */
struct linkedListIterator
{
  struct listNode *current;
};

/*
 * ll_add
 * This Method will add an item to the end of the list
 *
 * Parameters:
 * struct linkedList * - A pointer to an instance of a linkedlist struct
 * void * - A pointer to the data to be stored in this index
 * uint32_t - Size of the data being stored.
 * 
 * Returns:
 * bool - True if added, false otherwise
 */
bool ll_add(struct linkedList *list, const void *data, uint32_t dataSize);

/*
 * ll_addIndex
 * This Method will add an item to the specified index of the list
 *
 * Parameters:
 * struct linkedList * - A pointer to an instance of a linkedlist struct
 * void * - A pointer to the data to be stored in this index
 * uint32_t - Size of the data being stored.
 * uint32_t - Index to add the data to
 * 
 * Returns:
 * bool - True if added, false otherwise
 */
bool ll_addIndex(struct linkedList *list, const void *data, uint32_t dataSize, uint32_t index);

/*
 * ll_clear
 * This Method will clear the list
 *
 * Parameters:
 * struct linkedList * - A pointer to an instance of a linkedlist struct
 */
void ll_clear(struct linkedList *list);

/*
 * ll_get
 * This Method will return the data at the index in the list provided
 *
 * Parameters:
 * struct linkedList * - A pointer to an instance of a linkedlist struct
 * uint32_t - Index of the data to retrieve
 *
 * Returns:
 * void * - Data at the index specified
 */
void* ll_get(struct linkedList *list, uint32_t index);

/*
 * ll_getIterator
 * This Method will return an iterator for navigating through the linkedlist struct
 *
 * Parameters:
 * struct linkedList * - A pointer to an instance of a linkedlist struct
 *
 * Returns:
 * linkedListIterator * - An instance of a linkedListIterator struct pointing to the first element
 */
struct linkedListIterator* ll_getIterator(struct linkedList *list);

/*
 * ll_hasNext
 * This Method will return true if there is another value to get
 *
 * Parameters:
 * struct linkedListIterator * - A pointer to an instance of a linkedlistIterator struct
 *
 * Return:
 * bool True if another index exists, false otherwise
 */
bool ll_hasNext(struct linkedListIterator *iterator);

/*
 * ll_init
 * This Method will properly instantiate an instance of the linked listStruct
 *
 * Parameters:
 * struct linkedList * - A pointer to an instance of a linkedlist struct
 */
void ll_init(struct linkedList *list);

/*
 * ll_next
 * This Method will get the next piece of data in the list using a supplied iterator
 *
 * Parameters:
 * struct linkedList * - A pointer to an instance of a linkedlistIterator struct
 *
 * Returns:
 * void * - Data contained in the next index of the list
 */
void* ll_next(struct linkedListIterator *iterator);

/*
 * ll_remove
 * This Method will remove an item from the list at the specified index
 *
 * Parameters:
 * struct linkedList * - A pointer to an instance of a linkedlist struct
 * uint32_t - Index of the data to remove
 * 
 * Returns:
 * bool - True if succesfully removed, false otherwise
 */
bool ll_remove(struct linkedList *list, uint32_t index);

/*
 * ll_size
 * This Method will return the size of the linked list
 *
 * Parameters:
 * struct linkedList * - A pointer to an instance of a linkedlist struct
 *
 * Returns:
 * uint32_t - Size of the list
 */
uint32_t ll_size(struct linkedList *list);

#endif
