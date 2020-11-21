#include <stdio.h>
#include <stddef.h>
#include "memory.h"

// Point the sections linked list at the start of the memory. At the start, there is only one large section.
_section *memorySections = (void *)memory;

void startupMemory() {
    memorySections->isFree = 1;
    memorySections->size = sizeof(memory) - sizeof(_section); // Account for the first section allocation
    memorySections->next = NULL;
}

void *allocate(size_t nBytes) {
    /*
     *  Find the first available free section with enough space. While there are no free or large enough sections, 
     *  go to the next section, if there is any.
     */
    _section *current;
    current = memorySections; // From the start
    while((current->size < nBytes || current->isFree == 0) && current->next != NULL) { 
        current = current->next;
    }

    /*************************************************
     * 
     *  CASE 1: THE SECTION HAS EXACTLY ENOUGH SPACE
     * 
     *************************************************/
    if(current->size == nBytes) {
        current->isFree = 0; // Allocate
        void *location = ++current; // Return address of the first allocated byte
        printf("Allocated section starting at usable memory position: '%p'\n", location);
        return location; // Cast to (void *)

    /***************************************************
     * 
     *  CASE 2: THE SECTION HAS MORE SPACE THAN NEEDED
     * 
     ***************************************************/
    } else if(current->size > nBytes) { // Block has more space than necessary, a split is executed

        /*
         *   SPLITTING A SECTION
         * 
         *   STEP 1: Create a new section sized as to encompass the remaining space.
         * 
         *   The new section will be the next memory section available after the current section has been shrinked to fit the input 
         *   'nBytes'. In order to do this, the first step is to set the pointer 'newSection' to the correct memory position, 
         *   which is equal to:
         *   
         *       The current memory position + the size of the metadata + the amount of bytes to be stored
         */
        _section *newSection = (void *)(current + sizeof(_section) + nBytes); 
        newSection->isFree = 1; // Not allocated
        /* 
         *  The size of the new section is equal to: 
         *      Total size before the split (current->size) - the size of the metadata - the amount of bytes to be stored
         */
        newSection->size = current->size - sizeof(_section) - nBytes;
        newSection->next = current->next; // Set up the new section 'next' pointer

        /* 
         *  STEP 2: Allocate the reserved space in the current section.
         */
        current->isFree = 0; // Allocated
        current->size = nBytes + sizeof(_section); // 'nBytes' + metadata '_section'
        current->next = newSection; 

        void *location = ++current; // Return address of the first allocated byte
        printf("Allocated section starting at usable memory position: '%p'\n", location);
        return location; // Cast to (void *)

    } else {
        printf("No memory space available\n");
        return NULL;
    }
}

void liberate(void *p) {
    // Check whether the given address lies whithin the memory
    if(p >= (void *) memory && p <= (void *) (memory + sizeof(memory))) {
        _section *current = p; // Points to the section to be freed
        printf("Liberated section starting at usable memory position: '%p'\n", (void *)current);
        current--; // Get to the section header
        current->isFree = 1; // Frees the section
    } else {
        printf("Invalid pointer\n");
    }
}

void printSections() {
    _section *section = memorySections;
    int counter = 1;
    while (section != NULL) {
        printf("Section %d has size: %lu (isFree: %d)\n", counter, section->size, section->isFree);
        section = section->next;
        counter++;
    }
}
