// demo pass args by reference and by value
// Compiler Command: g++ PassByRefByVal.cpp
// Run Command     : ./a.out

#include <iostream>
using namespace std; 

//C++, pass by ref
void swapByRef(int& a, int& b)
{
  int temp;
  temp = a;
  a = b;
  b = temp;
   cout << "swapByRef: a=" << a << "  b=" << b << endl;
}

// C++, pass by ref
void swapByVal(int a, int b)
{       
  int temp;
  temp = a;
  a = b;
  b = temp;
  cout << "swapByVal: a=" << a << "  b=" << b << endl;
}

// C style, pass by ref (via pointers)
void swapByRefPtr(int* a, int* b)
{
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
  cout << "swapByRefPtr: a=" << *a << "  b=" << *b << endl;
}

void PtrTest1(char* buf)
{
   printf("In PtrTest1 :-> Buf: %s\n", buf);
   buf=NULL;
   printf("In PtrTest1 :-> Buf: %s\n", buf);
}

// pass pointer 
void PtrTest2(char** buf)
{
   printf("In PtrTest2 :-> Buf: %s\n", *buf);
   *buf=NULL; //ug oh???
   printf("In PtrTest2 :-> Buf: %s\n", *buf);
}

// pass pointer by reference: C++ only  
void PtrTest3(char*& buf)
{
   printf("In PtrTest2 :-> Buf: %s\n", buf);
   buf=NULL; //ug oh???
   printf("In PtrTest2 :-> Buf: %s\n", buf);
}

int main()
{
   int a = 10;
   int b = 20;
   cout << "Main: a=" << a << "  b=" << b << endl;
   //pass by val
   swapByVal(a,b);
   cout << "Main: a=" << a << "  b=" << b << endl;

   swapByRef(a,b);
   cout << "Main: a=" << a << "  b=" << b << endl;

   swapByRefPtr(&a,&b);
   cout << "Main: a=" << a << "  b=" << b << endl;

   char* buf = new char[4];  
   buf[0] = 'M'; buf[1] = 'i'; buf[2] = 'k'; buf[3] = 'e';
   
   PtrTest1(buf);
   printf("In Main :-> Buf: %s\n", buf);

   PtrTest2(&buf);
   printf("In Main :-> Buf: %s\n", buf);

   buf = new char[4];  // do this is segfault. why?
   buf[0] = 'M'; buf[1] = 'i'; buf[2] = 'k'; buf[3] = 'e';
   PtrTest3(buf);
   printf("In Main :-> Buf: %s\n", buf);

   return 0;
}
