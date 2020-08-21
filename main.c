#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  char *data;
  struct node *next;
} _node;

void printList (_node *ll) {
   if (ll != NULL) {
      printf ("%s\n", ll->data);
      printList (ll->next);
      free(ll);
   }
}

void insertNode (char *d, _node *n)
{
   _node *newNode;
   newNode = malloc(sizeof(_node));
   newNode->data = d;
   newNode->next = n->next;
   n->next = newNode;
}

int main(void) {

  _node *head;
  char *temp;
  head = malloc (sizeof(_node));
  head->next = NULL;
  
  printf("Enter a list of your favorite names: \n");
  
  while (1) {
    temp = malloc(sizeof(temp));
    scanf("%s", temp);
    if(strcmp(temp,"END") == 0) {
      break;
    }
    else {
      insertNode(temp, head);
    }
  }

  printList(head->next);
  free(temp);

  return 0;
}