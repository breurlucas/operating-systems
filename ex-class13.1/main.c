#include <stdio.h>
#include "memory.h"

// int main(void) {
//     int *p = (int *) malloc(sizeof(int));
//     *p = 100;
//     free(p);
// }

int main(void) {

    startupMemory();
    int *p = (int *) allocate(sizeof(int));
    *p = 100;
    printf("Address pointed by p: '%d'\n", p);
    printf("Content of p: '%d'\n", *p);

    liberate(p);
}