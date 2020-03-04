#ifndef _MYBOOKS_H
#define _MYBOOKS_H

#include <stdbool.h>
#include <stdio.h>

/* preprocessor directive: replace MAX_STRING with 50 */  
/* #define MAX_STRING = 50 */
//const int MAX_STRING = 256;  -- doesn't work in C
enum {MAX_STRING=50};
enum {MAX_BOOKS=1000};

/* No boolean in C. #include<stdbool.h> or define like this */
// typedef enum _boolean {false,true} bool;

typedef struct book
{
   int BookId;
   char author[MAX_STRING];
   char title[MAX_STRING];
   int  copyright;
   int  rating;
   bool available;
} Book;


typedef struct bookCollection
{
   Book books[MAX_BOOKS];
   int len;
   int startID;
} BookCollection;


extern int  InitCollection(BookCollection** collection, int num_collections);
extern void FreeCollection(BookCollection** collection);
extern int  AddToCollection(BookCollection* collection, const Book* book);
extern void ListCollection(const BookCollection* collection);
extern int  CollectionLength(const BookCollection* collection);
extern int  ReadCollectionItems(FILE* stream, BookCollection* collection);


#endif
