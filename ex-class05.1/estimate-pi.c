#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h> 

int randomizePoint();
void estimatePI();
void child1();
void parent();

// Global variables
int pts = 1000000; // Total number of points to be simulated
int nc; // Total number of points inside the circle (Sum of the partial calculations done by the children)

// The variable below is needed for the pipe
// File descriptors. fd[0]: READ; fd[1]: WRITE
int fd[2];

int main(void) {

  // The pipe is used in order to transfer a value from the child to the parent.
  // In this case the simulated number of points inside the circle is passed from child to parent.
  if (pipe(fd) == -1) {
    printf("Pipe could not be created");
    return 1;
  }

  // Our process is forked
  pid_t pid = fork();

  if ( pid == -1 ) {
    perror("Process could not be forked!");
    exit(EXIT_FAILURE);
  } else if ( pid == 0 ) {  // If the pid is equal to 0 we are executing the child
    child1();
  } else { // If the pid is not negative nor 0 we are executing the parent
    parent();
  }

  return 0;
}

// This function is used by the parent in order to estimate PI with the points simulated by the children
void estimatePI(int pts_circle) {

  double pi; // PI  

  printf("I am parent and I am estimating PI... \n");

  printf("Total points inside the circle: %d\n", pts_circle);

  pi = 4 * (double) pts_circle / (double) pts;

  printf("PI is approximately equal to: %f\n", pi);
}

// This function is used by the children in order to simulate the points which fall inside the circle
int randomizePoint() {

  srand(time(0)); // Define time as seed

  int counter = 0;

  for(int i = 0; i < pts; i++) {

    double x = (double)(rand() % 100 + 1) / (double)100; // Define random x coordinate
    double y = (double)(rand() % 100 + 1) / (double)100; // Define random y coordinate

    // Check if the points falls within the circle
    if ((x*x + y*y) <= 1) {
        counter++;
    }
  }

  // printf("Hi I ran\n");
  return counter;
}

void child1() {

  int x;
  x = randomizePoint();

  close(fd[0]); // Close the reading end of the pipe
  if (write(fd[1], &x, sizeof(int)) == -1){ // Write the value found to the pipe
    printf("Could not write");
  }
  close(fd[1]); // Close the writing end of the pipe
  // printf("Wrote in pipe: %d\n", x);
  printf("Hi I'm child 1 and I have written a total of %d simulated points to the pipe.\n", x);
  exit(EXIT_SUCCESS);

}

void parent() {

  int status;
  wait(&status);

  int y = 0;
  close(fd[1]); // Close the writing end of the pipe
  read(fd[0], &y, sizeof(int)); // Read the value from the pipe
  close(fd[0]); // Close the reading end of the pipe
  estimatePI(y);

  exit(EXIT_SUCCESS);

}
