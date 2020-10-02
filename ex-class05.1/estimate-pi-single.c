#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

int randomizePoint(int pts) {

  srand(time(0)); // Define time as seed

  int myNc = 0;

  for(int i = 0; i < pts; i++) {

    double x = (double)(rand() % 100 + 1) / (double)100;
    double y = (double)(rand() % 100 + 1) / (double)100;

    if ((x*x + y*y) <= 1) {
        // printf("%f\n", x*x + y*y);
        myNc++;
    }
  }

  return myNc;
}

int main(void) {

  int nc = 0; // Number of points inside the circle
  double pi; // PI
  int pts = 1000000; // Total number of points
  srand(time(0)); // Define time as seed
  
  printf("Estimating PI: \n");

  nc = randomizePoint(pts);

  printf("%d\n", nc);
  pi = 4 * (double) nc / (double) pts;
  printf("%f\n", pi);
  return 0;
}
