#ifndef _LIST_H_IS_INCLUDED_
#define _LIST_H_IS_INCLUDED_

// A pointer array based list
typedef struct List {
    int size;
    int items;
    void **data;
} List;

// Creates a new list with a given initial capacity
struct List *initList(int initialSize);

// Returns an item of the given index from the given list
void *getFromList(List *list, int index);

// Add an item to the given list
void addToList(List *list, void *item);

// Removes given item (once or all occurrences) from the given list
void removeFromList(List *list, void *item, int removeAll);

// Removes an item of the given index from the given list
void removeFromListByIndex(List *list, int index);

// Sets an item under the given index in the given list
void setInListByIndex(List *list, int index, void *item);

// Clears the given list, could also free the items memory
void clearList(List *list, int freeData);

// Frees the given list memory, could also free the items memory
void freeList(List *list, int freeData);

#endif