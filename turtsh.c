#include "turtsh.h"

char *turtsh_read(){
   char *buf = malloc(32); 
   char *prompt = buf;
   int c;
   while(*prompt != '\n') {
        *prompt++ = fgetc(stdin);
   }
   printf("%c", *prompt);
   return prompt;
}
