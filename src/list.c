#include <stdlib.h>
#include <string.h>

#include "list.h"

// Creates a new list with a given initial capacity
struct List *initList(int initialSize) {
    List *list = malloc(sizeof(List));

    list -> size = initialSize;
    list -> items = 0;
    list -> data = malloc(sizeof(void*) * initialSize);

    return list;
}

// Returns an item of the given index from the given list
void *getFromList(List *list, int index) {
    if (index >= list -> items) {
        return NULL;
    }

    return list -> data[index];
}

// Add an item to the given list
void addToList(List *list, void *item) {
    if (list -> items == list -> size) {
        void **newData =  malloc(sizeof(void*) * list -> size * 2);
        memcpy(newData, list -> data, sizeof(void*) * list -> size);

        free(list -> data);

        list -> data = newData;
        list -> size *= 2;
    }

    list -> data[list -> items] = item;
    list -> items += 1;
}

// Removes given item (once or all occurrences) from the given list
void removeFromList(List *list, void *item, int removeAll) {
    int i = 0;
    for (; i < list -> items; i++) {
        if (list -> data[i] == item) {
            removeFromListByIndex(list, i--);

            if (!removeAll) {
                return;
            }
        }
    }
}

// Removes an item of the given index from the given list
void removeFromListByIndex(List *list, int index) {
    if (index >= list -> items) {
        return;
    }

    int i = index;
    for (; i < list -> items - 1; i++) {
        list -> data[i] = list -> data[i + 1];
    }

    list -> items -= 1;
}

// Sets an item under the given index in the given list
void setInListByIndex(List *list, int index, void *item) {
    if (index >= list -> items) {
        return;
    }

    list -> data[index] = item;
}

// Clears the given list, could also free the items memory
void clearList(List *list, int freeData) {
    if (freeData) {
        int i = 0;

        for (; i < list -> items; i++) {
            free((list -> data)[i]);
        }
    }

    list -> items = 0;
}

// Frees the given list memory, could also free the items memory
void freeList(List *list, int freeData) {
    if (freeData) {
        clearList(list, 1);
    }

    free(list);
}