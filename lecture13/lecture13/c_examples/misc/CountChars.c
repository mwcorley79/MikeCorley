#include<stdio.h>


int main()
{
   int chars,lines;
   chars = lines = 0; 
   char ch;

   while( (ch = getchar()) != EOF)
   {
      if(ch != '\n')
        chars++;
      else
        lines++;
   }

   printf("There are %d lines in the input \n", lines);
   printf("There are %d chars in the input\n", chars);

   return 0;
 }
