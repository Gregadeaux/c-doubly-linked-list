/*
 * Greg Billetdeaux
 * CS 3841
 * Lab 2
 * 9/18/2012
 * 
 * This is the implementation file for Linkedlist.h. It implements a doubly linked list array
 * for storing data. It contains proper memory management as well as an iterator.
 */

#include "linkedlist.h"
#include <stdlib.h>
#include <string.h>

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
bool ll_add(struct linkedList *list, const void *data, uint32_t dataSize)
{
  if(list != NULL && data != NULL && dataSize > 0)
  {
    // Creates a new listNode for the new entry in the list
    struct listNode *node = malloc(sizeof(struct listNode));
    node->data = malloc(dataSize);

    // Assigns the data to the node
    memcpy(node->data, data, dataSize);

    // Assigns the data size to the node
    node->dataSize = dataSize;

    // Makes the next node NULL
    node->nextNode = NULL;

    if(list->size == (uint32_t)0)
    {
      list->head = node;
    } else 
    {
      // Makes the next node for the current list tail, this new node
      list->tail->nextNode = node;

      // Makes the previous node, the current list tail
      node->prevNode = list->tail;
    }
    // Make the new node, the new list tail
    list->tail = node;

    // Incremement the size
    list->size = list->size+1;

    return true;
  }
  return false;
}

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
bool ll_addIndex(struct linkedList *list, const void *data, uint32_t dataSize, uint32_t index)
{
  if(list != NULL && data != NULL && dataSize > 0 && (index >= 0 && index <= list->size))
  {
    struct listNode *node;
    struct listNode *newNode = malloc(sizeof(struct listNode));
    newNode->data = malloc(dataSize);
  
    memcpy(newNode->data, data, dataSize);
    newNode->dataSize = dataSize;
    

    if(list->size == 0)
    {
      list->head = newNode;
      list->tail = newNode;
      list->size = 1;
      newNode->nextNode = NULL;
      newNode->prevNode = NULL;
      return true;
    }else if(index == 0)
    {
      newNode->nextNode = list->head;
      list->head->prevNode = newNode;
      list->head = newNode;
      list->head->prevNode = NULL;
      list->size = list->size + 1;
      return true;
    }else if(index == list->size)
    {
      newNode->prevNode = list->tail;
      list->tail->nextNode = newNode;
      list->tail = newNode;
      list->tail->nextNode = NULL;
      list->size = list->size + 1;
      return true;
    }else
    {
      if(index > list->size/2)
	{
	  index = list->size - index;
	  node = list->tail;
	  while(index != 0)
	    {
	      node = node->prevNode;
	      index--;
	    }
	} else
	{
	  node = list->head;
	  while(index != 0)
	    {
	      node = node->nextNode;
	      index--;
	    }
	}
    
        // If true, this should be the head
        if(node->prevNode == NULL)
  	{
  	  list->head = newNode;
	  newNode->nextNode = node;
	}else
	{
	  newNode->nextNode = node;
   	  newNode->prevNode = node->prevNode;
	  node->prevNode->nextNode = newNode;
	}
	node->prevNode = newNode;
        list->size = list->size + 1;
    }
    return true;
  }
  return false;
}

/*
 * ll_clear
 * This Method will clear the list
 *
 * Parameters:
 * struct linkedList * - A pointer to an instance of a linkedlist struct
 */
void ll_clear(struct linkedList *list)
{
  if(list != NULL)
  {
    if(list->size == 1)
    {
      free(list->head->data);
      free(list->head);
      list->head == NULL;
      list->tail == NULL;
      list->size = 0;
    }else if(list->size > 1)
    {
      // Assigns node to the head;
      struct listNode *node = list->head;
      
      // Assigns the head to the next node
      list->head = node->nextNode;
      list->head->prevNode = NULL;
      
      list->size = list->size - 1;
      
      // Frees the node data
      free(node->data);
      
      // Frees the original head
      free(node);
      
      // Recursive call to continue freeing
      ll_clear(list);
      }
    if(list->size == 0)
    {
      list->head = NULL;
      list->tail = NULL;
    }

  }
}

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
void* ll_get(struct linkedList *list, uint32_t index)
{
  struct listNode *node;
  if(list != NULL && index >= 0 && index < list->size)
  {
    if(index > (list->size-1)/2)
      {
	index = list->size - index - 1;
	node = list->tail;
	while(index != 0)
	  {
	    node = node->prevNode;
	    index--;
	  }
      } else
      {
	node = list->head;
	while(index != 0)
	  {
	    node = node->nextNode;
	    index--;
	  }
      }

    return node->data;
  }
  return NULL;
}

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
struct linkedListIterator* ll_getIterator(struct linkedList *list)
{
  if(list != NULL)
  {
    struct linkedListIterator *iterator = malloc(sizeof(struct linkedListIterator));
    iterator->current = list->head;
    return iterator;
  }

  return NULL;
}

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
bool ll_hasNext(struct linkedListIterator *iterator)
{
  bool hasNext = false;
  if(iterator != NULL && iterator->current != NULL)
  {
    hasNext = true;
  }
  
  return hasNext;
}

/*
 * ll_init
 * This Method will properly instantiate an instance of the linked listStruct
 *
 * Parameters:
 * struct linkedList * - A pointer to an instance of a linkedlist struct
 */
void ll_init(struct linkedList *list)
{
  if(list != NULL)
  {
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
  }
}

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
void* ll_next(struct linkedListIterator *iterator)
{
  if(iterator != NULL && iterator->current != NULL)
  {
    struct listNode *node = iterator->current;
    iterator->current = node->nextNode;
    return node->data;
  }
  return NULL;
}

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
bool ll_remove(struct linkedList *list, uint32_t index)
{
  struct listNode *node;

  if(list != NULL && index >= 0 && index < list->size)
  {
    if(index == 0)
    {
      node = list->head;
      if(list->size > 1)
      {
	list->head = node->nextNode;
	list->head->prevNode = NULL;
      }else
      {
	list->head = NULL;
	list->tail = NULL;
      }
      free(node->data);
      free(node);
      list->size = list->size - 1;
      return true;
      }else if(index == list->size-1)
      {
	node = list->tail;
	list->tail = node->prevNode;
	list->tail->nextNode = NULL;
	free(node->data);
	free(node);
	list->size = list->size - 1;
	return true;
      }else
      {
	if(index > list->size/2)
	  {
	    index = list->size - index;
	    node = list->tail;
	    while(index != 0)
	      {
		node = node->prevNode;
		index--;
	      }
	  } else
	  {
	    node = list->head;
	    while(index != 0)
	      {
		node = node->nextNode;
		index--;
	      }
	  }

	if(node != NULL)
	  {
	    node->prevNode->nextNode = node->nextNode;
	    node->nextNode->prevNode = node->prevNode;
	    list->size = list->size - 1;
	    free(node->data);
	    free(node);
	    return true;
	  }
      }
  }
  return false;
}

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
uint32_t ll_size(struct linkedList *list)
{
  if(list != NULL)
  {
    return list->size;
  }
  return 0;
}
