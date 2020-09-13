#include <stdlib.h>

#include "memory.h"

// this is where we'll do all memory management - simpler and allows
// for adding garbage collection as we go
void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
    // free memory if newSize is zero
    if(newSize == 0) {
        free(pointer);
        return NULL;
    }

    // otherwise delegate to realloc, which functions like malloc if
    // newSize is zero
    void* result = realloc(pointer, newSize);
    if(result == NULL) {
        // allocation _can_ fail and there's no useful way to recover
        exit(1);
    }

    return result;
}
