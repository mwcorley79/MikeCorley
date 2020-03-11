#ifndef _MYBOOKS_H
#define _MYBOOKS_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
extern void ListCollection(FILE* f, const BookCollection* collection);
extern int  CollectionLength(const BookCollection* collection);
extern int  ReadCollectionItems(FILE* stream, BookCollection* collection);
extern void DisplayBook(FILE* f, const Book* book);

// HW # 5: excercise: write a function to Find a book in the collection based on its Id
// the function definition should be placed in books.c
Book FindBook(BookCollection* collection, int id); 

// HW # 5: exercise: write a function to Delete a book based on its Id, 
// the function definition should be placed in books.c
bool DeleteBook(BookCollection* collection, int id);  


#endif
