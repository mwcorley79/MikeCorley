#include "bookutils.h"

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
