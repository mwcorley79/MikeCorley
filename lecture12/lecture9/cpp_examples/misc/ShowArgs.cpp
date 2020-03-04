#include<iostream>

int main(int argc, char* argv[])
{

   for(int i = 0; i < argc; ++i)
   {
       std::cout << *(argv + i) << std::endl;
       std::cout << std::string(argv[i]).length() << std::endl;
		      
   }

   return 0;
}
