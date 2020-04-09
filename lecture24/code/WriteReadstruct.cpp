// demo serialize and deserialize user defined types and persist to files  
// demo RAII (Resource Acquistion is Initialization) -- allocate resources in 
//            in constructor, and deallocste in destructor
// Compiler Command: g++ WriteReadstruct.cpp 
// Run Command: ./a.out
#include<iostream>
#include<fstream>
#include<cstring>

// user defined type in C++
// structs in C++ are very different than structs in C
// C++ structs are essentially classes (with constructors etc), except members public by default
struct Book
{
   int BookId;
   char author[50];
   char title[50];
   int copyright;
   int rating;
   bool available;
   char* buf;

   Book():  BookId(0), author("\0"), title("\0"), copyright(-1), rating(0), available(false)
   {
      std::cout << "Hello from Book default constructor" << std::endl;
      buf = new char[10];
   }

   ~Book()  
    { 
       std::cout << " Hello from Book destructor " << std::endl;
       delete buf;
    }
};


void WriteStruct(const std::string& dest_filename, struct Book& b)
{
   std::ofstream df;  //c++ output stream
   typedef char* Byte;

   // open the file for binary output
   df.open(dest_filename, std::ios::out | std::ios::binary);
   if(!df.is_open())
      throw std::runtime_error("File: " + dest_filename + " could not be written");

   // cast Book b as a stream of Bytes (serialize) and persist to disk 
   df.write( (Byte) &b, sizeof(b));
   df.close();   
}

void ReadStruct(const std::string& source_filename, struct Book& b)
{  
   std::ifstream sf; // C++ input stream

   // open the file for input  
   sf.open(source_filename, std::ios::in | std::ios::binary);
   if(!sf.is_open())
      throw std::runtime_error("File: " + source_filename + " could not be opened");
   
   //(deserialize) read stream of bytes from disk into object (Book) instance b
   sf.read( (char*) &b, sizeof(b));
   sf.close();
}


//pass b as pointer (for fun): changes to b are visiable in the caller scope: (struct Book& b)
void printBytes(struct Book* b)
{
   int BookSize = sizeof(struct Book);
   int bSize = sizeof(*b);
   std::cout << "Size of Book: " << BookSize << std::endl;
   std::cout << "Size of b   : " << bSize << std::endl;

   std::cout << "First character: " << *(((char*) b) + sizeof(int)) << std::endl;
   std::cout << "Title: " << (((char*) b) + sizeof(int)) << std::endl; 
}


int main()
{
   struct Book b1;
   b1.BookId = 1000;
   strcpy(b1.author, "Mike");
   strcpy(b1.title, "Some Good book");
   b1.copyright = 2000;
   b1.rating = 9;
   b1.available = true;

   //pass b by reference, serialize and persist to file1.dat
   std::cout << "Serialize b1 to byte stream and persist to file1.dat " << std::endl;   
   WriteStruct("./file1.dat", b1); //note: b1 is passed tp WriteStruct by reference
   std::cout << "b1's book Id: " << b1.BookId << " b1's book author: " << b1.author << std::endl;
   
  // pass b2 by reference, deserialize to file1.dat to b2 object
   Book b2;
   std::cout << "Read byte stream from file1.dat and deserialize to b2 " << std::endl;   
   ReadStruct("./file1.dat", b2);  //note: b2 is passed to ReadStruct by reference 
   std::cout << "b2's book Id: " << b2.BookId << " b2's book author: " << b2.author << std::endl;

  //pass pointer to b2  
   printBytes(&b2);
   return 0;
}
