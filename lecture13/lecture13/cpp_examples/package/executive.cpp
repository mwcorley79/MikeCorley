#include<iostream>
#include <exception>

#include "books.h"


char DisplayMenu()
{
   std::string input;
   std::cout << "\n\nA - Add a Book\n";
   std::cout << "L - List Books\n";
   std::cout << "R - Read from file\n";
   std::cout << "F - Find a Book by Id\n";
   std::cout << "D - Delete a Book by Id\n";
   std::cout << "Q - Quit\n";
   std::cout << "Enter Choice: -> ";
   getline(std::cin, input);
   return std::tolower(input[0]);
}

void ReadFile(const std::string& filename, BookCollection& collection)
{
  std::ifstream f(filename.c_str());
  if(f.is_open())
  {
    std::cout << "\n Reading Books records from: " << filename << "\n";
    while(f.good())
    {
      collection.ReadCollectionItems(f);
    }
    
    f.close();
    std::cout << "complete\n";
  }
  else
    std::cout << "\n Can't open file: " << filename << std::endl;
}

void ProcessMenu(BookCollection& collection)
{
     char ch = DisplayMenu();
     while(ch != 'q')
     {
       try
       {
         switch(ch)
         {
            case 'a':
              collection.ReadCollectionItems(std::cin);
	      std::cout << "Success, Collection contains: " 
		        << collection.CollectionLength() 
		        << " books" << std::endl;
              
            break;

            case 'l':
            case 'L':
              std::cout << "\nThe collection list is:" <<" \n";
              collection.ListCollection();
            break;

            case 'r':
	    {
              std::string filename;
	      std::cout << "\nPlease enter a filename (type: data.txt) ";
	      getline(std::cin, filename);
              ReadFile(filename, collection);
	    }
            break;

            case 'f':
            { 
              std::cout << "Enter the Id the Book to Find: ";
	          std::string sid;
	          getline(std::cin, sid);
	          int id = stoi(sid);

	          Book b = collection.FindBook(id);
	          if(b.BookId() != -1)
	          {
                 std::cout << " *** Found id: *** " << b.BookId() << std::endl;
	             //and now display the book
	             std::cout << b << std::endl;
              }
              else
              {
                std::cout << " *** Book id: *** " << id << " not found in the collection " << std::endl;
	          }
            }
            break;
	        case 'd':
            {
              std::cout << "Enter the Id of the Book to delete: ";
              std::string sid;
              getline(std::cin, sid);
              int id = stoi(sid);

              bool deleted = collection.DeleteBook(id);
              if(deleted)
                std::cout << " *** Deleted book with Id: *** " << id << std::endl;
              else
                std::cout << " *** Book id: *** " << id << " not found in the collection " << std::endl;
            }
            break;

        
            default:
              if(ch != 'q')
                std::cerr << "Invalid option:" << ch << std::endl;
        }
        ch = DisplayMenu();
     }
     catch(std::exception& ex)
     {
       std::cerr << "oops! an error occurred, but I caught it! " << ex.what() << std::endl;
     }
  }    
}


int main()
{
   BookCollection collection;
   ProcessMenu(collection);
   return 0;
}
