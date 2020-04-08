//Compiler command: g++ stringDemo.cpp
//Run Command: ./a.out

#include<iostream>
#include<string>

int main()
{
  std::string astr = "a literal string1";
  std::string bstr = astr; //note: this a copy NOT a reference

  std::cout << "the string a is: " << astr << std::endl;
  std::cout << "the string b is: " << bstr << std::endl;

  //char* aastr  = "a string literal";
  const char* aastr  = "a string literal";

  std::string cstr = aastr;
  cstr[0] = 'b';
  std::cout << "the string c is: " << cstr << std::endl;

  if(astr == bstr)
    printf("They are equal\n");

  return 0;
}
