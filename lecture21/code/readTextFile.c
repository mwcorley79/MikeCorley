/*
 * File:   readTextFile.c
 * Author: Mike
 * Description: Read/write text file line by line and parse
 *
 * Compiler build command: gcc -o readTextFileCProg ./readTextFile.c 
 * Run command           : ./readTextFileCProg
*/
 
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 1000

int mygetline(FILE* stream, char line[], char delim, int max)
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

   // return 1 when EOF indicator true
   return (ch != EOF);
}


void WriteTextFile(const char* filename)
{
   FILE *fp;
   char* names[]= { "Mike", "Joe", "Jim", "Wayne", "Joy", "Carla" };
   
   // open file for reading
   fp = fopen(filename, "w");

   // if fp not open successfully
   if(fp == NULL)
   {
      printf("Could not open file %s",filename);
      exit(EXIT_FAILURE);
   }

   for(int i = 0; i < 10; ++i)
   {
      fprintf(fp, "%s,%d,%d\n", names[(rand() % 6)], i+1, (rand() % 100));     
   }

   fclose(fp);
}

char** ParseEntry(char str[], char delim[], int maxlen )
{
   char** parsedEntry = (char**) malloc(3 * sizeof(char*));
   int count = 0;
  
   // get the first the token (Name)
   char* ptr = strtok(str, delim);
   while(ptr != NULL && count < 3)
   {
     //allocate memory to store the parsed name
     parsedEntry[count] = (char*) malloc(strlen(ptr) * sizeof(char)); 
     strcpy(parsedEntry[count], ptr); ;
     count++;
     //get the next token
     ptr = strtok(NULL, delim);
   }

   return parsedEntry;
}

void FreeEntry(char** array, int len)
{
   // Note: only (and always) call free on memory you allocated with malloc.
   
   // give each string elemenbt back to the heap
   for(int i = 0; i < len; ++i)
   {
      free(array[i]);
   }

   // give the array itself back to the heap
   free(array);
}

int main() 
{
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "test.txt";
 
    // generate pseudo-random number
    srand(time(NULL));   // seed srand

    /* write a Text file with the following format:  Name,Id,age */
    WriteTextFile(filename);

    // open file for reading
    fp = fopen(filename, "r");
    
    // if fp not open successfully
    if (fp == NULL)
    {
        printf("Could not open file %s",filename);
        return 1;
    }

    // read line by line 
    while (mygetline(fp, str,'\n', MAXCHAR))
    {
       printf("File entry:-> %s\n", str);
       char** toks = ParseEntry(str, ",", MAXCHAR);
       printf("%s\t\%d\t%d\n", toks[0], atoi(toks[1]), atoi(toks[2])); 
       
       //done using memory so return to the heap 
       FreeEntry(toks, 3);
    }
    
    fclose(fp);
    return 0;
}
