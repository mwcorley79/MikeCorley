#include <stdio.h>

void DisplayFile(const char* filename)
{
    // attempt tp open the file for reading
    FILE* fp = NULL;

    if(filename != NULL)
      fp = fopen(filename, "r");
   
     if(fp == NULL)
         fp = stdin;
    
    
    int ch;
    if(fp != NULL)
    {
       while( (ch = fgetc(fp)) != EOF)
       {  
         printf("%c", ch);
       }
    
       // if fp is not stdin, that close the stream
       if(fp != stdin)
       {
         fclose(fp);
       }
    }
}


int main(int argc, char* argv[])
{
    // argc is the argument count:  argv is the array of command
    // args passed to the program:  argv[0] is the name of the program
    if(argc < 2)
    {
        DisplayFile(NULL);
    }

    for(int i = 1; i < argc; ++i)
    {
        DisplayFile(argv[i]);
    }
    
    return 0;
}
