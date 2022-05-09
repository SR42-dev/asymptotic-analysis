// Name: Sriram R
// SRN: PES1UG20CS435

#include "heap.h"
#include <stdlib.h>

/*
 ** Do not use global variables.
 ** Mark any functions that you declare in this file that are not in the header
 *as static
 ** Do not use static variables
 ** All occurences of count_ptr indicate that the number of comparison
 ** operations need to be stored in the location pointed by it
 ** The implementation can assume it is initialized to 0.
 */

// Initialise heap
// Set heap size to 0
// Set heap max_size to paramter max_size
// Allocate memory of max_size to the array
void init_heap(heap_t *heap, int max_size) 
{
    heap->size = 0;
    heap->max_size = max_size;
    heap->arr = (int*)malloc(sizeof(int) * max_size);
}

// Insert element "key" to heap "heap"
// and store the number of key comparisons made in the
// location pointed to by count_ptr.
void insert(heap_t *heap, int key, int *count_ptr) 
{
    int c;
    int p;
    int elt;

    // insertion
    if (heap->size == heap->max_size)
    {
        return;
    }
    heap->size++;
    heap->arr[heap->size - 1] = key;
    
    // heapification
    for (int i = 1; i < heap->size; i++)
    {
        elt = heap->arr[i];
        c = i;
        p = (c - 1) / 2;

        while (c > 0 && heap->arr[p] < elt)
        {
            *count_ptr++;
            heap->arr[c] = heap->arr[p];
            c = p;
            p = (c - 1) / 2;
        }

        heap->arr[c] = elt;
    }
}

// *Removes and Returns* the maximum element in the heap
// and store the number of key comparisons made in the
// location pointed to by count_ptr.
int extract_max(heap_t *heap, int *count_ptr) 
{
    int c;
    int p;
    int elt;

    // max element extraction
    int max = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size];
    heap->size--;

    // heapification
    for (int i = 1; i < heap->size; i++)
    {
        elt = heap->arr[i];
        c = i;
        p = (c - 1) / 2;

        while (c > 0 && heap->arr[p] < elt)
        {
            *count_ptr++;
            heap->arr[c] = heap->arr[p];
            c = p;
            p = (c - 1) / 2;
        }

        heap->arr[c] = elt;
    }

    return max;
}

// Searches for the element key in the heap
// Returns the element if found, else -1
int search(const heap_t *heap, int key, int *count_ptr) 
{
    int res = -1;

    for (int i = 0; i < heap->size; i++)
    {
        if (heap->arr[i] == key) res = heap->arr[i];
        *count_ptr++;
    }

    return res;
}

// Returns the maximum value of the element in the heap
// and store the number of key comparisons made in the
// location pointed to by count_ptr.
int find_max(const heap_t *heap, int *count_ptr) 
{
    return heap->arr[0];
}

// Returns the minimum value in the heap
int find_min(const heap_t *heap, int *count_ptr) 
{
    int min = 100000;

    for (int i = (heap->size) / 2; i < (heap->size); i++)
    {
        if (heap->arr[i] < min) min = heap->arr[i];
        *count_ptr++;
    }

    return min;
}

// Clears the heap for reuse
void clear_heap(heap_t *heap) 
{
    heap->size = 0;
}

// Frees all resources acquired to initialize heap
void free_heap(heap_t *heap) 
{
    free(heap);
}
