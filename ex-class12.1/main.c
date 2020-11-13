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

// Most throughput local: 150-160 MiB/s

void *flush_buffer();

int main() {

    char buffer[BUF_SIZE];

    memset(buffer, '\0', BUF_SIZE); // Set all entries of the buffer to null '\0'

    // Set stdout to the buffer created. The buffer outputs automatically when full (_IOFBF MODE)
    setvbuf(stdout, buffer, _IOFBF, BUF_SIZE);

    while(1) {
        fwrite("*\n", 1, 3, stdout); // Fwrite adds buffering on top of write (syscall)  
    }

    return(0);
}
