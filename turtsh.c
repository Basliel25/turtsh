#include "turtsh.h"

char *turtsh_read(){

   char *prompt = malloc(128); 
   char *buf = prompt;
   int c;

   printf(">");
   while(((c = fgetc(stdin)) != '\n') && c != EOF) {
        *prompt++ = c;
        int position = prompt - buf;
        if(position >= 128) 
            prompt = realloc(prompt, strlen(buf)*2);
   }
   *prompt = '\0';
   return buf;
}
