#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

// Compile using std=c17

int main(int argc, char *argv[]) {

    FILE *file;
    int words;

    // for(int i=1; i<argc; i++) {
    //     file = fopen(argv[i], "r")
    // }

    file = fopen(argv[1], "r");

    if(file == NULL) {
        printf("The requested file does not exist");
        return 1;
    }

    words = 0;

    words = count_words(file, words);

    printf("%d\n", words); 

}

int count_words(FILE *file, int words) {

    char head; // Tracks reading head position

    // Checks if the file has at least one character/word. If the first character is 'EOF', the wordcount will be zero.
    head = getc(file);

    // Read each character one by one till the end of the file is reached
    while(head != EOF) {
        head = getc(file);
        if(head == ' ' || head == '\n' || head == EOF) { words++; }
    }

    // Closes the file after reading
    fclose(file);  
    return words;
}