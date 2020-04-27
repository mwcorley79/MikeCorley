///////////////////////////////////////////////////////////////////////////
//  derived1.cpp - provides protocol details for derived1 class          //
//                                                                       //
//  this file is not visible to client, who has access only to the       //
//  compiled derived1.dll and protocol header file                       //
//                                                                       //
//  Jim Fawcett, CSE 687 - Object Oriented Design, Spring 2007           //
///////////////////////////////////////////////////////////////////////////
//  Important:                                                           //
//    Please see notes in the Protocol.h file                            //
///////////////////////////////////////////////////////////////////////////

#define IN_DLL
#include <iostream>
#include <string>
#include "protocol.h"
using namespace std;

class derived1 : public protocol {

  public:
    DLL_DECL int getInt() {
      cout << "\n  calling derived1::getInt()"; return 0;
    }
    DLL_DECL void putInt(int) {
      cout << "\n  calling derived1::putInt()";
    }
    DLL_DECL string passVal(string s) {
      s += ": a copy inside derived1";
      return s;
    }
    DLL_DECL string passRef(string &s) {
      s += ": a reference inside derived1";
      return s;
    }
};

DLL_DECL protocol* protocol::makeObj() {
  std::cout << "\n  calling protocol::makeObj() from derived1.dll";
  return new derived1;
}

DLL_DECL protocol* gMakeObj()
{
  std::cout << "\n  calling gMakeObj() from derived1.dll";
  return new derived1;
}