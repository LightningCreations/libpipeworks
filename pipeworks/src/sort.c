#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "thing.h"
#include "sort.h"
#include "ll.h"

static size_t pw_internal_sort_floor_power_of_two(size_t x) {
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
#if defined(UINT32_MAX) && SIZE_MAX > UINT32_MAX
    x |= x >> 32;
#endif
#if defined(UINT64_MAX) && SIZE_MAX > UINT64_MAX
    x |= x >> 64; // Futureproofing
#endif
    return x - (x >> 1);
}

static void pw_internal_sort_reverse(pw_thing **array, size_t start, size_t end) {
    for(size_t i = 0; i < (end-start)/2; i++) {
        pw_thing *tmp = array[i+start];
        array[i+start] = array[end-i-1];
        array[end-i-1] = tmp;
    }
}

static void pw_internal_sort_rotate(pw_thing **array, size_t size, size_t start, size_t end) {
    pw_internal_sort_reverse(array, start, end);
    pw_internal_sort_reverse(array, start, start+size);
    pw_internal_sort_reverse(array, start+size, end);
}

// Code based on the insertion sort algorithm; adapted to sorting from a linked list to an array
static void pw_internal_sort_insertion_sort(ll_node **curNode, pw_thing **result, size_t start, size_t end) {
    size_t numItems = end - start;
    for(size_t i = 0; i < numItems; i++) {
        if(*curNode == NULL) return; // In case of concurrent modification, get the heck out
        pw_thing *curThing = (pw_thing*) ((*curNode)->value);
        size_t insertIndex;
        for(insertIndex = 0; insertIndex < i; insertIndex++) {
            if(result[start+insertIndex]->depth < curThing->depth) break;
        }
        for(; insertIndex < i + 1; insertIndex++) {
            pw_thing *tmp = result[start+insertIndex];
            result[start+insertIndex] = curThing;
            curThing = tmp;
        }
        *curNode = (*curNode)->next;
    }
}

static void pw_internal_sort_merge(pw_thing **array, size_t size, size_t start, size_t end) {
    pw_thing **tmpArray = malloc(sizeof(pw_thing*)*(end-start));
    size_t leftPos = start;
    size_t rightPos = start + size;
    for(size_t i = 0; i < (end-start); i++) {
        if(array[leftPos]->depth <= array[rightPos]->depth)
            tmpArray[i] = array[leftPos++];
        else
            tmpArray[i] = array[rightPos++];
        if(leftPos == start + size)
            for(; i < (end-start); i++) tmpArray[i] = array[rightPos++];
        else if(rightPos == end)
            for(; i < (end-start); i++) tmpArray[i] = array[leftPos++];
    }
    for(size_t i = 0; i < (end-start); i++)
        array[start+i] = tmpArray[i]; // Should get optimized to memcpy
}

// Code translated from Wikipedia: https://en.wikipedia.org/wiki/Block_sort
ll* pw_depth_sort(ll *things) {
    size_t size = atomic_load(&things->size); // Get this sooner than later so racing is less of a problem

    pw_thing **array = malloc(sizeof(pw_thing*)*size);

    size_t powerOfTwo = pw_internal_sort_floor_power_of_two(size);
    double scale = ((double)size)/powerOfTwo;

    ll_node *curNode = things->first;

    for(size_t merge = 0; merge < powerOfTwo; merge += 16) {
        if(curNode == NULL) { free(array); return NULL; } // In case of concurrent modification, get the heck out to avoid a segfault
        size_t start = (size_t) (merge * scale);
        size_t end = (size_t) (start + 16 * scale);
        pw_internal_sort_insertion_sort(&curNode, array, start, end);
    }
    if((curNode != NULL) || (atomic_load(&things->size) != size)) { // Final concurrent modification checks.
        free(array); // To summarize: Concurrent modification means that our sorting is invalid, and artifacts will appear.
        return NULL; // To get around this, we exit as soon as we catch it and give the engine/layer a fresh chance to rerender.
    }                // After this though, the linked list has already finished getting copied

    for(size_t length = 0; length < powerOfTwo; length += length) {
        for(size_t merge = 0; merge < powerOfTwo; merge += length * 2) {
            size_t start = (size_t) (merge * scale);
            size_t mid = (size_t) ((merge + length) * scale);
            size_t end = (size_t) ((merge + length * 2) * scale);
            if(array[end-1]->depth < array[start]->depth)
                pw_internal_sort_rotate(array, mid - start, start, end);
            else if(array[mid-1]->depth > array[mid]->depth)
                pw_internal_sort_merge(array, mid - start, start, end);
        }
    }

    // Now that we've made an array, we need to convert back into a new linked list.
    ll *result = ll_init();
    for(size_t i = 0; i < size; i++) {
        ll_push(result, array[i]);
    }
    free(array);
    return result;
}
