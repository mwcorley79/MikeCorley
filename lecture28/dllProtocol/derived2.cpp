///////////////////////////////////////////////////////////////////////////
//  derived2.cpp - provides protocol details for derived2 class          //
//                                                                       //
//  this file is not visible to client, who has access only to the       //
//  compiled derived.dll and protocol header file                        //
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

class derived2 : public protocol {

  public:
    DLL_DECL int getInt() {
      cout << "\n  calling derived2::getInt()"; return 0;
    }
    DLL_DECL void putInt(int) {
      cout << "\n  calling derived2::putInt()";
    }
    DLL_DECL string passVal(string s) {
      s += ": a copy inside derived2";
      return s;
    }
    DLL_DECL string passRef(string &s) {
      s += ": a reference inside derived2";
      return s;
    }
};

DLL_DECL protocol* protocol::makeObj() {
  cout << "\n  calling protocal::makeObj from derived2.dll";
  return new derived2;
}

DLL_DECL protocol* gMakeObj()
{
  std::cout << "\n  calling gMakeObj() from derived2.dll";
  return new derived2;
}
