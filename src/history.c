#include <stdio.h>
#include <stdlib.h>

typedef struct s_Item {
  int id;
  char *str;
  struct s_Item *next;
} Item;

typedef struct s_List {
  struct s_Item *root;
} List;

/* Initialize the linked list to keep the history. */
List* init_history() {
  List* history = malloc(sizeof(List));
  history->root = NULL;
  return(history);
}

/* Add a history item to the end of the list.
   List* list - the linked list
   char* str - the string to store
*/
void add_history(List *list, char *str) {
  Item *newItem = malloc(sizeof(Item));
  newItem->str = str; //should copy string instead
  if(list->root == NULL) {
    newItem->id = 1;
    list->root = newItem;
    return;
  }
  Item *traversal = list->root;
  int newID = 2;
  while(traversal->next != NULL) {
    newID = 1 + traversal->next->id;
    traversal = traversal->next;
  }
  newItem->id = newID;
  newItem->next = NULL;
  traversal->next = newItem;
}
  

/* Retrieve the string stored in the node where Item->id == id.
   List* list - the linked list
   int id - the id of the Item to find */
char *get_history(List *list, int id) {
  Item *traversal = list->root;
  while(traversal->next != NULL) {
    if(id==traversal->id) return traversal->str;
    traversal = traversal->next;
  }
  return("String not found.");
}

/*Print the entire contents of the list. */
void print_history(List *list) {
  Item *traversal = list->root;
  while(traversal->next != NULL) {
    printf("\n%s",traversal->str);
    traversal = traversal->next;
  }
  printf("\n%s",traversal->str);
}

/*Free the history list and the strings it references. */
void free_history(List *list) {
  Item *traversal = list->root;
  Item *deletionTarget = NULL;
  while(traversal->next != NULL) {
    free(traversal->str);
    deletionTarget = traversal;
    traversal = traversal->next;
    free(deletionTarget);
  }
  free(traversal->str);
  free(traversal);
  free(list);
}
