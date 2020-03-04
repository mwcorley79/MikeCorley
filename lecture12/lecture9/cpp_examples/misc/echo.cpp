#include<iostream>

int main()
{
  char ch = std::cin.get();

   while(std::cin.good() )
   {
      std::cout << ch;
      ch = std::cin.get();
   }

  return 0;
}


