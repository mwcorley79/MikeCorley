#include<stdio.h>
#include<ctype.h>

#include "books.h"
#include "bookutils.h"

char DisplayMenu()
{
   char input[MAX_STRING];
   printf("\n\nA - Add a Book\n");
   printf("L - List Books\n");
   printf("R - Read from file\n");
   printf("Q - Quit\n");
   printf("Enter Choice: -> ");
   mygetline(stdin, input, '\n', MAX_STRING);
   return tolower(input[0]);
}

void ReadFile(const char* filename, BookCollection* collection)
{
  FILE* f = fopen(filename, "r");
  if(f)
  {
    printf("\n Reading Books records from: %s\n",filename);
    while(!feof(f))
    {
       ReadCollectionItems(f, collection);
    }
    fclose(f);
    printf("complete\n");
  }
  else
    printf("\n Can't open file:  %s\n", "data.txt");
}


void ProcessMenu(BookCollection* collection)
{
   char ch = DisplayMenu();
   while(ch != 'q')
   {
     switch(ch)
     {
       case 'a':
         if(ReadCollectionItems(stdin, collection))
         {
	    printf("Success, Collection contains: %d books\n", CollectionLength(collection)); 
         }
       break;

       case 'l':
       case 'L':
          printf("\nThe collect list is:\n");
          ListCollection(collection);
       break;

       case 'r':
       {
          char filename[100];
	  printf("\nPlease enter a filename: ");
	  mygetline(stdin, filename, '\n', 100);
          ReadFile(filename, collection);
       }
       break;

       default:
          if(ch != 'q')
             printf("Invalid option: %c ", ch);
     }

     ch = DisplayMenu();
   }      
}


int main()
{
   BookCollection* collection;
   
   InitCollection(&collection,1);

   ProcessMenu(collection);

   FreeCollection(&collection);
   return 0;
}
