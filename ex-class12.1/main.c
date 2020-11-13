#include <stdio.h>

// Baseline local: 65-70MiB/s

// int main() {
//     while(1) {
//         printf("*\n");
//     }
// }

// Most throughput local
// Swapped printf for puts: 85-90 MiB/s
int main() {
    while(1) {
        puts("*\n");
    }
}