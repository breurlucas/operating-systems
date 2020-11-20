#include memory.h

int main(void) {
    int *p = (int *) malloc(sizeof(int));
    *p = 100;
    free(p);
}
