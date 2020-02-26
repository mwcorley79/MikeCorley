// https://www.programiz.com/c-programming/c-arrays

#include <stdio.h>
#include <stdlib.h>

void mygetline(FILE* stream, char line[], char delim, int max)
{
   int ch;
   int count = 0;
   while(  ((ch = fgetc(stream)) != EOF) && ch != delim && count < (max-1))
       line[count++] = ch;
   line[count] = '\0';

   // consume the remaining part of the line, but don't buffer it
   while(ch != EOF && ch != delim)
   {
       ch = fgetc(stream);
   }
}

int main()
{
     int marks[10], i, n, sum = 0, average;
     char temp[25];
     printf("Enter number of elements: ");
     //scanf("%d", &n);
     mygetline(stdin, temp, '\n', 25);
     n = atof(temp);

     for(i=0; i<n; ++i)
     {
          printf("Enter number%d: ",i+1);
          scanf("%d", &marks[i]);
          
          // adding integers entered by the user to the sum variable
          sum += marks[i];
     }
     average = sum/n;
     printf("Average = %d", average);
     return 0;
}

