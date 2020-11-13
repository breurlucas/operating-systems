#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#define BUF_SIZE 64000 // Sets the buffer size

/*

 Lucas Breur 13-11-2020, São Paulo

*/

// Baseline local: 65-70MiB/s

// int main() {
//     while(1) {
//         printf("*\n");
//     }
// }

// Max throughput local: 4 GiB/s

void *flush();

int main() {

    // Flushing thread, unlocked
    pthread_t t1;
    pthread_create(&t1, NULL, flush, NULL);

    char *buffer = (char *) malloc(BUF_SIZE);

    memset(buffer, '\0', BUF_SIZE); // Set all entries of the buffer to null '\0'

    /* Set stdout to the buffer created. The buffer outputs automatically when full (_IOFBF MODE). However, we do not wan't that
    to happen. A full buffer means that the writing would stop. That is why we need a large enough buffer to ensure our throughput is
    maxxed out; id est, our flushing thread can keep up with the writing thread. */
    setvbuf(stdout, buffer, _IOFBF, BUF_SIZE);

    // Writing thread (main), unlocked
    while(1) {
        fwrite_unlocked("*\n", 1, 3, stdout); // Fwrite adds buffering on top of write (syscall)  
    }

    return(0);
}

// Flushes the written data immediately
void *flush() {

    while(1) {
        fflush_unlocked(stdout);
    }

    return NULL;
}

