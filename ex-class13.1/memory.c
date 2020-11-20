#include <stdio.h>
#include <stddef.h>

char memory[50*1024*1024]; // The memory representation as an array

// Struct which defines an allocated/free memory section. Its has a 'size_t' in bytes,
typedef struct section {
  int isFree; // Bool for checking if the section is free
  size_t size; // Section size in bytes
  struct section *next; // Pointer to the next section of memory in the linked list
} _section;

// Point the sections linked list at the start of the memory. At the start, we have only one large section.
_section *memorySections = (void *)memory;

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

// void liberate(void *p) {

// }

int main(void) {
    memorySections->isFree = 1;
    memorySections->size = sizeof(memory) - sizeof(_section); // Account for the first section allocation
    memorySections->next = NULL;

    int *p = (int *) allocate(sizeof(int));
    *p = 100;
    printf("Address pointed by p: '%d'\n", p);
    printf("Content of p: '%d'\n", *p);
}