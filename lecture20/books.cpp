#include "books.h"

#include<algorithm> // need for sl

BookCollection::BookCollection(): startId_(1000)
{}


// HW # 5:  solution 1 excercise: write a member function to Find a book in the collection based on its Id
// iterate over the collection, and find the index of the item
Book BookCollection::FindBook(int id)
{
   Book b; 
   for(int i = 0; i < books.size(); ++i)
   {
       if(books[i].BookId() == id)
         return books[i]; //return found
   }
   return b; // not found
}


/*
// HW # 5:  solution 2 excercise: write a member function to Find a book based on ID using std:find algorithm,
// note: std::find assumes operator == is defined for class Book, see Book class above
Book BookCollection::FindBook(int id)
{
   Book b; // the default with id == -1 for not found case
   std::vector<Book>::iterator it;
  
   //a temporary book object with Id set for searching
   Book target_book;
   target_book.BookId(id);

   // uses the std::find algorithm with iterators to search for book with the target id
   it = std::find(books.begin(), books.end(), target_book);

   //if book found, return the book referenced by the iterator
   if(it != books.end())
       return *it;
   else
     return b; // else return not found
}
*/


//HW # 5: solution 1 excercise: write a memmber function to Delete a book based on its Id
bool BookCollection::DeleteBook(int id)
{
   int i;
   for(i = 0; i < books.size(); ++i)
   {
       if(books[i].BookId() == id)
       {
           //shift elements back by one, overwriting the target
           for(int j = i; j < books.size()-1; j++)
	   {
              books[j] = books[j+1];
	   }
	   
           books.pop_back(); //delete the last elemenet 
           return true;
       }
   }
   return false;
}

// HW # 5: solution 2 excercise: write a memmber function to Delete a book based on its Id
// note: std::find assumes operator == is defined for class Book, see Book class above

/* 
bool BookCollection::DeleteBook(int id)
{
   // temporary book set with target book Id that we're searching for 
   Book target_book;
   target_book.BookId(id);

   // uses the std::find algorithm with iterators to search for book with the target id
   std::vector<Book>::iterator it = std::find(books.begin(), books.end(), target_book);

   //if book found, then use vector erase
   if(it != books.end())
   {
      // use vector::erase with iterator argument
      books.erase(it);
      return true;
   }
   else
   {
      return false;
   }
}
*/


void BookCollection::AddToCollection(const Book& book)
{
   books.push_back(book);
}

int BookCollection::CollectionLength() 
{
   return books.size();
}

std::ostream& operator << (std::ostream& outs, const Book& book)
{
   outs << "BookId   : " << book.BookId() << std::endl;
   outs << "Author   : " << book.author() << std::endl;
   outs << "Title    : " << book.title()  << std::endl;
   outs << "copyright: " << book.copyright() << std::endl;
   outs << "rating   : " << book.rating() << std::endl;
   if(book.available())
     outs << "Available" << std::endl;
   else
     outs << "Not Available" << std::endl;

   return outs;
}


void BookCollection::ListCollection()
{
   for(int i = 0; i < books.size(); ++i)
   {
     std::cout << books[i] << std::endl;
   }
}


void BookCollection::ReadCollectionItems(std::istream& ins)
{
   try
   {
      Book b;
    
      if(&ins == &std::cin) std::cout << "Enter Author Full Name: ";
      getline(ins, b.author_);

      if(&ins == &std::cin) std::cout << "Enter Book Title      : ";
      getline(ins, b.title_);
  
      std::string temp;
      if(&ins == &std::cin) std::cout << "Enter Copyright (year): ";
      getline(ins, temp);
      b.copyright_ = std::stoi(temp);
   
      if(&ins == &std::cin) std::cout << "Enter Rating (1-10)   : ";
      getline(ins, temp);
      b.rating_ = std::stoi(temp);

      if(&ins == &std::cin) std::cout << "Is Book available?    : ";
      getline(ins, temp);
      if(std::tolower(*temp.c_str()) == 'y')
        b.avail_ = true;
      else
        b.avail_ = false;

       //generate the bookID and add to the collection
       b.BookId(startId_ + books.size());
       AddToCollection(b);
    }
    catch(...)
    {
      //swallow all exceptions for now
    }
}


#ifdef _TEST_BOOK_COLLECTION

int main()
{
   //test code for the package should go here: the test stub
   return 0;
}

#endif 





