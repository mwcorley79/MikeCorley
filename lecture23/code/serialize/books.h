#ifndef _MYBOOKS_H
#define _MYBOOKS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Book
{
   public:
     friend class BookCollection;
     friend std::ostream& operator << (std::ostream& outs, const Book& b);

     Book(); // default ctor

     //initialization ctor
     Book(int id, 
          const std::string& title, 
          const std::string& author,
          int copyright,
          int rating,
          bool availabe);
  
     int BookId() const; 
     void BookId(int id);
     std::string author() const;
     std::string title() const;
     int  copyright() const;
     int  rating() const;
     bool available() const;
   private:
     int BookId_;
     std::string author_;
     std::string title_;
     int copyright_;
     int rating_;
     bool avail_;
}; 

inline Book::Book(): BookId_(-1), 
	                 author_(""), 
		             title_(""), 
		             copyright_(0),
		             rating_(0),
 		             avail_(false)
{}


inline Book::Book(int id, 
          const std::string& title, 
          const std::string& author,
          int copyright,
          int rating,
          bool available):
                 BookId_(id), 
	             author_(author), 
		         title_(title), 
		         copyright_(copyright),
		         rating_(rating),
		         avail_(available)
{} 

inline void Book::BookId(int id)
{
   BookId_ = id;
}

inline int Book::BookId() const
{
   return BookId_;
}

inline std::string Book::author() const
{
   return author_;
}

inline std::string Book::title() const
{
   return title_;
}
 
inline int Book::copyright() const
{
   return copyright_;
}

inline int Book::rating() const
{
   return rating_;
}

inline bool Book::available() const
{
   return avail_;
}

class BookCollection
{
   public:
     friend std::ostream& operator << (std::ostream& outs, const Book& b);
     BookCollection(); //default constructor
     void AddToCollection(const Book& book);
     void ListCollection();
     int CollectionLength();
     
     // HW # 5: excercise: write a memmber function to Find a book in the collection based on its Id
     // the function definition should be placed in books.cpp
     Book FindBook(int id); 

     // HW # 5: excercise: write a memmber function to Delete a book based on its Id, 
     // the function definition should be placed in books.cpp
     bool DeleteBook(int id);  

     void ReadCollectionItems(std::istream& ins);
  private:
      std::vector<Book> books;
      int startId_;
};
#endif
