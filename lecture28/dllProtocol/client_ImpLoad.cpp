///////////////////////////////////////////////////////////////////////////
//  client-ImpLoad.cpp - demonstrate use of protocol language            //
//                       implemented in implicitly loaded DLL            //
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

#include <iostream>
#include <string>
#include "protocol.h"   // note that the client only needs the base class
                        // header file, not headers from derived classes
using namespace std;

void main() {

  cout << "\n"
       << " Test protocol with implicitly loaded library\n"
       << "===============================================\n";

  int i=0;

// note that clients can not make a protocol object, but factory functions
// make anonymous derived class objects and give client access to them 
// through a base class protocol pointer.


///////////////////////////////////////////////////////////////////////////
//  client uses the first derived class, knowing only the protocol       //
//         language and how to call its object factory                   //
///////////////////////////////////////////////////////////////////////////

  protocol *bptr = protocol::makeObj();
                                  // static member factory function creates
                                  // creates derived object - which one 
                                  // depends on which dll is loaded

  bptr->getInt();                 // derived class functions
  bptr->putInt(i);                // use base class interface
  string s = "\n  string from client";
  cout << (bptr->passVal(s)).c_str();
  cout << (bptr->passRef(s)).c_str() << endl;

  delete bptr;

  bptr = gMakeObj();              // global factory function creates
                                  // derived object - which one depends
                                  // on which dll is loaded

  bptr->getInt();                 // derived class functions
  bptr->putInt(i);                // use base class interface
  s = "\n  string from client";
  cout << (bptr->passVal(s)).c_str();
  cout << (bptr->passRef(s)).c_str() << endl;

  delete bptr;
  cout << endl;

}
