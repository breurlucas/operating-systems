#include <stdio.h>
#include <stddef.h>
#include "memory.h"

// Point the sections linked list at the start of the memory. At the start, we have only one large section.
_section *memorySections = (void *)memory;

void startupMemory() {
    memorySections->isFree = 1;
    memorySections->size = sizeof(memory) - sizeof(_section); // Account for the first section allocation
    memorySections->next = NULL;
}

void *allocate(size_t nBytes) {
    // Find the first available free section with enough space
    _section *current;
    current = memorySections;
    // While there are no free or large enough sections, go to the next if available
    while(current->size < nBytes || (current->isFree == 0 && current->next != NULL)) { 
        current = current->next;
    }

    if(current->size > nBytes) { // Exacly enough space in the section
        current->isFree = 0; // Allocate
        void *location = current++; // Return address of the first allocated byte
        printf("Allocated section: '%d'\n", location);
        return location; // Cast to (void *)
    }

    return NULL;
}

void liberate(void *p) {
    // Check whether the given address lies whithin the memory
    if(p >= (void *) memory && p <= (void *) (memory + sizeof(memory))) {
        _section *current = p; // Points to the section to be freed
        printf("Liberated section: '%d'\n", current);
        current--; // Get to the section header
        current->isFree = 1; // Frees the section
    } else {
        printf("Invalid pointer\n");
    }
}
