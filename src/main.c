#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

int main(int argc, char **argv) {
  List *list = init_history();
  char *inputBuffer = NULL;
  char **tokens = NULL;
  int historyID = 0;
  int recalling = 0;
  printf("Enter \"q\" to quit, or !<n> to see nth entry.");

  while(1) {
    inputBuffer = malloc(sizeof(char) * 50);
    printf("\n > ");
    fgets(inputBuffer, 50, stdin);
    if(*inputBuffer == '!') {
      recalling = 1;
      historyID = *(inputBuffer+1) - '0';
      printf("%d",historyID);
      
      free(inputBuffer);
      inputBuffer = get_history(list, historyID);
      printf("%s",inputBuffer);
    }
    if((*inputBuffer == 'q') && (*(inputBuffer+1) == 10)) break;
    if(!recalling){
      tokens = tokenize(inputBuffer);
      print_tokens(tokens);
    }
    free(inputBuffer);
    recalling = 0;
  }
  return 0;
}
