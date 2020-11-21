#include <stdio.h>
#include <string.h>
#include "memory.h"

// int main(void) {
//     int *p = (int *) malloc(sizeof(int));
//     *p = 100;
//     free(p);
// }

int main(void) {

    startupMemory(); // Initialize memory

    int *p = (int *) allocate(sizeof(int));
    printSections(); // Print the current memory sections
    printf("\n");
    *p = 500;

    char *q = (char *) allocate(1024);
    printSections(); // Print the current memory sections
    printf("\n");
    strcpy(q, "This is being stored through our simulated memory");

    printf("Address pointed by p: '%p'\n", (void *)p);
    printf("Address pointed by q: '%p'\n", (void *)q);

    liberate(q);
    liberate(p);
}