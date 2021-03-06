#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

/* Return true (non-zero) if c is a whitespace characer
   ('\t' or ' ').  
   Zero terminators are not printable (therefore false) */
int space_char(char c) {
  if(c == ' ') return 1;
  if(c == '\t') return 1;
  return 0;
}

/* Return true (non-zero) if c is a non-whitespace 
   character (not tab or space).  
   Zero terminators are not printable (therefore false) */ 
int non_space_char(char c) {
  if(c == ' ') return 0;
  if(c == '\t') return 0;
  if(c == 0) return 0;
  return 1;
}

/* Returns a pointer to the first character of the next 
   space-separated word in zero-terminated str.  Return a zero pointer if 
   str does not contain any words. */
char *word_start(char *str) {
  while(space_char(*str)) {
    str++;
  }
  return str;
}

/* Returns a pointer terminator char following *word */
char *word_terminator(char *word) {
  while(non_space_char(*word)) {
    word++;
  }
  return word;
}

/* Counts the number of words in the string argument. */
int count_words(char *str) {
  int count = 0;
  str = word_start(str);
  while(*str) {
    str = word_terminator(str);
    count++;
    str = word_start(str);
  }
  return count;
}

/* Returns a fresly allocated new zero-terminated string 
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len) {
  char *copy = malloc(sizeof(char) * (len+1));
  int i;
  for(i = 0; i<len; i++) {
    *(copy+i) = *(inStr+i);
  }
  *(copy+i) = '\0';
  return copy;
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated 
   space-separated tokens from zero-terminated str.

   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string" 
     tokens[3] = 0
*/
char **tokenize(char* str) {
  int wordCount = count_words(str);
  char **tokens = malloc((wordCount+1) * sizeof(char *));
  wordCount = 0;
  while(*str) {
    tokens[wordCount] = copy_str(word_start(str), word_terminator(str) - word_start(str));
    str = word_terminator(str);
    str = word_start(str);
    wordCount++;
  }
  *(tokens+wordCount) = 0;
  return tokens;
}

/* Prints all tokens. */
void print_tokens(char **tokens) {
  while(*tokens) {
    printf("\n%s",*tokens);
    tokens++;
  }
}

/* Frees all tokens and the vector containing themx. */
void free_tokens(char **tokens) {
  int i=0;
  while(tokens[i]) {
    free(tokens[i]);
    i++;
  }
  free(tokens);
}
