#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

// Double link
struct Link
{
	TYPE value;
	struct Link* next;
	struct Link* prev;
};

// Double linked list with front and back sentinels
struct LinkedList
{
	int size;
	struct Link* frontSentinel;
	struct Link* backSentinel;
};

/**
 * Allocates the list's sentinel and sets the size to 0.
 * The sentinels' next and prev should point to eachother or NULL
 * as appropriate.
 */
static void init(struct LinkedList* list) {
	// FIXME: you must write this
	assert(list != NULL);

	struct Link *front = malloc(sizeof(struct Link));
	struct Link *back = malloc(sizeof(struct Link));

	list->frontSentinel = front;
	list->backSentinel = back;

	back->value = 0;
	front->value = 0;
	front->prev = NULL;
	back->next = NULL;

	front->next = list->backSentinel;
	back->prev = list->frontSentinel;

	list->size = 0;
}

/**
 * Adds a new link with the given value before the given link and
 * increments the list's size.
 */
static void addLinkBefore(struct LinkedList* list, struct Link* link, TYPE value)
{
	// FIXME: you must write this
	assert(list != NULL);
	assert(link != NULL);

	struct Link *addBefore = (struct Link *)malloc(sizeof(struct Link));

	addBefore->value = value;

	struct Link *add = link->prev;
	link->prev = addBefore;
	addBefore->next = link;

	add->next = addBefore;
	addBefore->prev = add;

	list->size++;
}

/**
 * Removes the given link from the list and
 * decrements the list's size.
 */
static void removeLink(struct LinkedList* list, struct Link* link)
{
	// FIXME: you must write this
	assert(list != NULL);
	assert(link != NULL);

	link->prev->next = link->next;
	link->next->prev = link->prev;

	free(link);
	list->size--;
}

/**
 * Allocates and initializes a list.
 */
struct LinkedList* linkedListCreate()
{
	struct LinkedList* newDeque = malloc(sizeof(struct LinkedList));
	init(newDeque);
	return newDeque;
}

/**
 * Deallocates every link in the list including the sentinels,
 * and frees the list itself.
 */
void linkedListDestroy(struct LinkedList* list)
{
	while (!linkedListIsEmpty(list))
	{
		linkedListRemoveFront(list);
	}
	free(list->frontSentinel);
	free(list->backSentinel);
	free(list);
}

/**
 * Adds a new link with the given value to the front of the deque.
 */
void linkedListAddFront(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list != NULL);

    struct Link *frontAdd = malloc(sizeof(struct Link));
    frontAdd->value = value;

    struct Link *tempAdd = list->frontSentinel->next;

    list->frontSentinel->next = frontAdd;
    frontAdd->prev = list->frontSentinel;
    tempAdd->prev = frontAdd;
    frontAdd->next = tempAdd;
    list->size++;
}

/**
 * Adds a new link with the given value to the back of the deque.
 */
void linkedListAddBack(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list != NULL);

	struct Link *backAdd = malloc(sizeof (struct Link));
	backAdd->value = value;

	struct Link *tempAdd = list->backSentinel->prev;

	list->backSentinel->prev = backAdd;
	tempAdd->next = backAdd;
	backAdd->prev = tempAdd;
	backAdd->next = list->backSentinel;
	list->size++;
}

/**
 * Returns the value of the link at the front of the deque.
 */
TYPE linkedListFront(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != NULL);
	assert(list->size != 0);

	return list->frontSentinel->next->value;
}

/**
 * Returns the value of the link at the back of the deque.
 */
TYPE linkedListBack(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != NULL);
	assert(list->size != 0);

	return list->backSentinel->prev->value;
}

/**
 * Removes the link at the front of the deque.
 */
void linkedListRemoveFront(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != NULL);

	struct Link *fTemp = list->frontSentinel->next;

	list->frontSentinel->next = fTemp->next;
	fTemp->next->prev = list->frontSentinel;
	list->size--;
}

/**
 * Removes the link at the back of the deque.
 */
void linkedListRemoveBack(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != NULL);

	struct Link *bTemp = list->backSentinel->prev;
	list->backSentinel->prev = bTemp->prev;
	bTemp->prev->next = list->backSentinel;
}

/**
 * Returns 1 if the deque is empty and 0 otherwise.
 */
int linkedListIsEmpty(struct LinkedList* list)
{
	// FIXME: you must write this
	if (list->size == 0) {
        return 1;
	}
	else {
        return 0;
	}
}

/**
 * Prints the values of the links in the deque from front to back.
 */
void linkedListPrint(struct LinkedList* list)
{
	// FIXME: you must write this
	assert(list != NULL);
    struct Link* holder = list->frontSentinel->next;
    do{
        printf("%d \n", holder->value);
        holder = holder->next;
    } while (holder!= list->backSentinel);
}

/**
 * Adds a link with the given value to the bag.
 */
void linkedListAdd(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list != NULL);

	linkedListAddFront(list, value);
}

/**
 * Returns 1 if a link with the value is in the bag and 0 otherwise.
 */
int linkedListContains(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list->size != 0);
	assert(list != NULL);

	struct Link *holder = list->frontSentinel->next;

	while(!EQ(holder->value, value) && holder != list->backSentinel) {
        holder = holder->next;
	}
	if (holder == list->backSentinel) {
        return 0;
	}
	else {
        return 1;
	}
}

/**
 * Removes the first occurrence of a link with the given value.
 */
void linkedListRemove(struct LinkedList* list, TYPE value)
{
	// FIXME: you must write this
	assert(list->size != 0);
	assert(list != NULL);

	struct Link *rem = list->frontSentinel->next;

	while (!EQ(rem->value, value) && rem != list->backSentinel) {
        rem = rem->next;
	}
	if (rem != list->backSentinel) {
        removeLink(list, rem);
	}
}
