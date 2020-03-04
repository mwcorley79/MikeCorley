///////////////////////////////////////////////////////////////
// Vector.cpp - demonstrating STL std::vector<T> container   //
//                                                           //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2014 //
///////////////////////////////////////////////////////////////

#include <vector>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include "../Utilities/Utilities.h"

using namespace std;

int main()
{
  /*---------------------------------------------------------*/
  std::cout << title("vector<string>");
  /*
  * Has a single block of contiguous memory which fills from the back.
  * So operations on the back are constant time while operations on
  * the front are linear time.
  *
  * If you push_back or insert into a full vector (size == capacity)
  * a new block of memory twice as large as the former will be allocated
  * and elements copied before push_back or insert.
  *
  * Traits: value_type, iterator, ...
  */
  vector<string> vecStr{ "first", "second", "third" };
  
  cout << "Printing the vector:" << endl;
  for(int i = 0; i < vecStr.size(); ++i)
  {
     cout << "cout: " << vecStr[i] << endl;
     printf("printf: %s\n", vecStr[i].c_str() ); // *** Don't use printf in C++ *** 
  }

  cout << "Filling the vector with 10 integer " << endl;
  vector<int> numvec(10);
  for(int i = 0; i < 10; i++)
    numvec[i] = i;

  cout << "Printing the contents of the vector" << endl; 
  for(int i = 0; i < 10; i++)
    cout << numvec[i] << endl;


  return 0;
  
  //std::cout << show(vecStr);
  std::cout << "\n  vector size = " << vecStr.size();
  std::cout << ", vector capacity = " << vecStr.capacity();
  std::cout << "\n  first element = " << vecStr.front() << ", last element = " << vecStr.back();
  std::cout << "\n  second element = " << vecStr[1];
  std::cout << "\n  removing last element: ";
  vecStr.pop_back();
  std::cout << show(vecStr);
  std::cout << "\n  removing first element: ";
  vecStr.erase(begin(vecStr));
  std::cout << show(vecStr);
  std::cout << "\n  vector size = " << vecStr.size();
  std::cout << ", vector capacity = " << vecStr.capacity() << std::endl;

  /* sorting and searching vectors */
  std::cout << "\n  sorting vector:";
  std::vector<int> vint { 1, 0, -5, 2, 15, -205, -1, 2 };
  std::cout << show(vint);
  std::sort(begin(vint), end(vint));
  std::cout << show(vint);
  int element = 2;
  /* it's in there somewhere */
  if (std::binary_search(begin(vint), end(vint), element))
    std::cout << "\n  found " << element;
  else
    std::cout << "\n  couldn't find " << element;
  /* it's at location p */
  std::vector<int>::iterator iter = std::lower_bound(begin(vint), end(vint), element);
  if (iter != end(vint))
    std::cout << "\n  found " << *iter << " at location " << std::distance(begin(vint), iter);
  else
    std::cout << "\n  couldn't find " << element;

  std::cout << "\n\n";
}
