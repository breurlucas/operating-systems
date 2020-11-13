#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void *count_words(void *); // Function prototype

int main(int argc, char *argv[]) {

    int n = argc - 1; // The number of files passed through as arguments
    pthread_t t[n];     // Thread vector sized 'n'

    // Loop through the 'n' files passed as parameters and create a separate thread for each one
    for(int i=0; i<n; i++) {
        pthread_create(&t[i], NULL, count_words, argv[i+1]);
    }

    // Wait for the 'n' threads to finish
    for(int i=0; i<n; i++) {
        pthread_join(t[i], NULL);
    }
    
    exit(EXIT_SUCCESS);
}

// Wordcount function to be executed by the threads
void *count_words(void *arg) {

    FILE *file; // File pointer    
    char head; // Tracks reading head position (STACK, unique for each thread)
    int wordcount = 0; // Initializes the wordcount variable (STACK, unique for each thread)

    char *filename = (char *) arg; // Cast (void *) to (char *)

    file = fopen(filename, "r"); // Open the file in read-only mode

    // Check if a valid file was found
    if(file == NULL) {
        printf("The requested file does not exist or could not be found\n");
        exit(EXIT_FAILURE);
    }

    // Checks if the file has at least one character/word. If the first character is 'EOF', the wordcount will be zero.
    head = getc(file);

    // Read each character one by one till the end of the file is reached
    while(head != EOF) {
        head = getc(file);
        if(head == ' ' || head == '\n' || head == EOF) { wordcount++; }
    }

    fclose(file); // Closes the file after reading

    printf("%s: %d words\n", filename, wordcount); // Print the result

    return NULL;
}