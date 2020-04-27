///////////////////////////////////////////////////////////////////////////
//  client-ExpLoad.cpp - demonstrate use of protocol language            //
//                       implemented in explicitly loaded DLL            //
//                                                                       //
//  this file represents client code, which knows only about the         //
//  protocol class, e.g., the protocol language and the names, but       //
//  not the details, of the derived classes                              //
//                                                                       //
//  Jim Fawcett, CSE 687 - Object Oriented Design, Spring 2007           //
///////////////////////////////////////////////////////////////////////////
//  Important:                                                           //
//    Please see notes in the Protocol.h file concerning required        //
//    compiler options.                                                  //
///////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <iostream>
#include <string>
#include "protocol.h"   // note that the client only needs the base class
                        // header file, not headers from derived classes
using namespace std;

void main() {

  cout << "\n"
       << " Test protocol with explicitly loaded library\n"
       << "===============================================\n";

  HMODULE hmod = LoadLibrary(L"../client_ImpLoad/derived.dll");
  if(!hmod)
  {
    std::cout << "\n  failed to load derived.dll\n\n";
    return;
  }
  typedef protocol* (*gMO)();
  gMO gMakeObj = (gMO)GetProcAddress(hmod,"gMakeObj");
  if(!gMakeObj)
  {
    std::cout << "\n  GetProcAddress failed for gMakeObj\n\n";
    return;
  }
  int i=0;
  protocol* bptr = gMakeObj();    // global factory function creates
                                  // derived object - which one depends
                                  // on which dll is loaded

  bptr->getInt();                 // derived class functions
  bptr->putInt(i);                // use base class interface
  std::string s = "\n  string from client";
  std::cout << (bptr->passVal(s)).c_str();
  std::cout << (bptr->passRef(s)).c_str() << endl;

  delete bptr;
  FreeLibrary(hmod);
  std::cout << endl;

}
