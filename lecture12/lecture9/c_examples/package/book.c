#include "books.h"
#include "bookutils.h"
#include <stdlib.h>
#include <ctype.h>

int InitCollection(BookCollection** collection, int num_collections)
{
   *collection = (BookCollection*) malloc (num_collections * sizeof(BookCollection));
   if(*collection != NULL) 
   {
      for(int i = 0; i < num_collections; ++i)
      {
	    collection[i]->len = 0;
	    collection[i]->startID = 1000;
      }
   
      return 1;
   }
   return 0;
}

void FreeCollection(BookCollection** collection)
{
     free(*collection);
}

int ReadCollectionItems(FILE* stream, BookCollection* collection)
{
   Book temp;
   char temp_str[MAX_STRING];
   
   if(stream == stdin) printf("Enter Author Full Name: ");
   mygetline(stream, temp.author, '\n', MAX_STRING);

   if(stream == stdin) printf("Enter Book Title      : ");
   mygetline(stream, temp.title, '\n', MAX_STRING);

   if(stream == stdin) printf("Enter Copyright (year): ");
   mygetline(stream, temp_str, '\n', MAX_STRING);
   temp.copyright = atoi(temp_str);

   if(stream == stdin) printf("Enter Rating (1-10)   : ");
   mygetline(stream, temp_str, '\n', MAX_STRING);
   temp.rating = atoi(temp_str);

   if(stream == stdin) printf("Book Available? (Y/N) : ");
   mygetline(stream, temp_str, '\n', MAX_STRING);
   if(tolower(*temp_str) == 'y')
     temp.available = true;
   else
     temp.available = false;

   temp.BookId = (collection->startID + CollectionLength(collection));

   return AddToCollection(collection, &temp); 
}


int AddToCollection(BookCollection* collection, const Book* book)
{
   if(collection == NULL)
     return -1;

   if(collection->len < MAX_BOOKS)
   {
     collection->books[collection->len++] = *book;
     return 1;
   }

   return 0;
}


int CollectionLength(const BookCollection* collection)
{
   if(collection == NULL)
     return -1;

   return collection->len;
}

void DisplayBook(const Book* book)
{
  if(book != NULL)
  {
     printf("BookID   : %d\n", book->BookId);
     printf("Author   : %s\n", book->author);
     printf("Title    : %s\n", book->title);
     printf("Copyright: %d\n", book->copyright);
     printf("Rating   : %d\n", book->rating);
     if(book->available)
     {
	printf("Available\n\n");
     }
     else
     {
         printf("Not available\n\n");
     }
  }
}

void ListCollection(const BookCollection* collection)
{
  if(collection != NULL)
  {
    for(int i = 0; i < collection->len; ++i)
    {
       DisplayBook(collection->books + i);
    }
  }    
}

