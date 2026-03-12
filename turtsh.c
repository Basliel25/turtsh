#include "turtsh.h"

char *turtsh_read(){
   char *prompt = malloc(128); 
   char *buf = prompt;
   int c;
   printf(">");
   while(((c = fgetc(stdin)) != '\n') && c != EOF) {
        *prompt++ = c;
   }
   *prompt = '\0';
   return buf;
}
