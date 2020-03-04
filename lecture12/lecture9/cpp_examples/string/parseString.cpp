#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include<vector>
#include<list>


template <typename Container>
void split(const std::string& str, Container& cont, char delim = ' ')
{
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) 
    {
        cont.push_back(token);
    }
}


int main()
{
   // #1 split strings with a std::vector
   std::string str = "This a string that I would like to split into other strings";
   std::vector<std::string> myStringVec;
   
   // split the string, placing parsed strings into a vector
   split(str, myStringVec, ' ');
  
   std::cout << "\nListing the strings in vector " << std::endl;
   for(const std::string& str :  myStringVec)
   {
      std::cout << str << std::endl;
   }



   // #2 split strings with a std::list
   std::list<std::string> myStringList;

   // split the string, placing parsed strings in the vector
   split(str, myStringList, ' ');

   std::cout << "\nListing the strings in list " << std::endl;
   for(const std::string& str :  myStringList)
   {
      std::cout << str << std::endl;
   }

   return 0;
}
