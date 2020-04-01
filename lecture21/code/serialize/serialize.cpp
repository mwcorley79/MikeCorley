///////////////////////////////////////////////////////////////////////
// serialize.cpp - provides example use of serialization             //
// ver 1.0                                                           //
// Language:    g++, ver 7.4                                         //
// Platform:    Dell Precison m7720, Linux Mint 19.1                 //
// Application: Demonstrate serialization, CSE 384                   //
// Author:      Mike Corley, CST 4-232, Syracuse University          //
//              (315) XXX-XXXX , mwcorley@syr.edu                    //
///////////////////////////////////////////////////////////////////////

//Compiler command:  g++ -o serialize_cpp serialize.cpp books.cpp 
//Run Command     :  ./serialize

#include <string>
#include <sstream>

#include "books.h"
/* std::ostream& operator << (std::ostream& outs, const Book& book)
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
*/

	
template <typename T>
std::string ToString(const T& t)
{
   std::ostringstream out;
   out << t;
   return out.str();
}

template <typename T>
T FromString(const std::string &s)
{
  T t;
  std::istringstream in(s);
  in >> t;
  return t;
}


int main()
{
   int x = 10;
   float pi = 3.14159;
   Book *b = new Book(1000, "Friends Forever", "Joy Corley", 2020, 10, true);
   
   std::cout << "Serialize x " << x << " -> " <<  ToString(x) << std::endl;
   int y =  FromString<int>(ToString(x));
   std::cout << "Deserialize x as y" << y << std::endl << std::endl;

   std::cout << "Serialize pi " << x << " -> " <<  ToString(pi) << std::endl;
   float pi2  =  FromString<float>(ToString(pi));              
   std::cout << "Deserialize pi as p2 :" << pi2 << std::endl << std::endl;

   std::string book_str = ToString(*b);
   std::cout << "Serialize user defined type (Book): "  << book_str << std::endl;
   // Book b2  =  FromString(ToString(*b));  won't work yet becuase I need to define extraction operator for Book

   return 0;
}
