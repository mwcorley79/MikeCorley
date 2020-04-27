#ifndef PROTOCOL_H
#define PROTOCOL_H
///////////////////////////////////////////////////////////////////////////
//  protocol.h - define protocol class                                   //
//                                                                       //
//  this is all the client knows about the protocol, e.g., the language  //
//                                                                       //
//  Jim Fawcett, CSE791 - Distributed Objects, Demonstration             //
///////////////////////////////////////////////////////////////////////////
/*

   design note:
   ------------
   Protocol class hierarchies (sometimes called homeomorphic
   class structures) consist of an abstract base class and
   usually a single layer of derived classes.  The base class
   provides a language, or protocol, for client access to all
   the derived classes.  Clients know only the protocol, but
   not any of the details which distinguish one class from
   another.

   The derived classes provide all of the real functionality.
   The client code, however, does not need to know how any of
   the derived classes do their business.

   In this demonstration the member functions getInt() and
   putInt() are pure virtual functions so protocol class is an
   abstract base class.

   No protocol objects can be created.  Only objects of derived
   classes which give definitions for both the pure virtual
   functions are concrete and can create objects.

   However, since the makeObj() protocol member function is
   static clients don't need objects to invoke it.  Client
   code can do that with the syntax protocol::makeObj(), etc.
   So, we can invoke static members of an abstract class.  We
   do just that in the client code in protocol.cpp

   This project builds derived1.cpp into derived.dll and derived.lib,
   the dynamic link library and exports definition file.  Since they
   both name the output library the same, the client will load the
   last one built.

   Note that the derived classes in derived1.cpp and derived2.cpp
   create an object of their class type, so the one you get depends
   on the library that is loaded, e.g., the last one built.

                            +-----------+
                            | protocol  |
                            +-----+-----+
                                  |
                                 / \
                   +--------------+--------------+
                   |              |              |
             +-----+-----+  +-----+-----+  +-----+-----+
             | derived1  |  | derived2  |  | more der  |
             +-----------+  +-----------+  +-----------+

/*
//
/*
    Implementation Issues:
    ======================
    For this project to work correctly you must:
    - Use the DLL version of the C/C++ library for both client 
      and DLLS (that ensures that both client and DLLs will 
      use the same heap) - that now is the default setting in VS.
    - You do that by going to the project settings \ C/C++ tab
      and in the category combo box set Code Generation.  Then
      in the Use Run-time Library combo box select one of the 
      DLL libraries, e.g., either Multi-Threaded DLL or Debug
      Multi-threaded DLL.  Do this for client and all DLLs.
    - Set Properties for each derived (dll) project:
        Configuration, General, output directory to ..\client
        Linker, General, output file to ..\derived.dll
        Linker, Advanced, import library to ..\client\derived.lib
      These settings cause the build for either library to place
      the dynamic link library and its exports definition file
      where the client will load them, e.g., same directory as
      client.vcproj.
    - To build from the command line you can use:
          cl /EHsc /LDd /MDd /Foderived derived1.cpp
            or
          cl /EHsc /LDd /MDd /Foderived derived2.cpp
          cl /EHsc /MDd client.cpp derived.lib
    - Alternately, you can use:
          devenv derived1.vcproj /make /rebuild
            or
          devenv derived2.vcproj /make /rebuild
            that copies derived.dll and derived.lib
            into client project dir
          devenv client.vcproj   /make /rebuild
      with project settings as described above.

    - NOTE: order is important in the above builds.

*/

#ifdef IN_DLL
  #define DLL_DECL __declspec(dllexport)
#else
  #define DLL_DECL __declspec(dllimport)
#endif

typedef std::string stdStr;

class protocol {  // interface for derived1 and derived2 classes

  public:
    virtual DLL_DECL int getInt()     = 0;
    virtual DLL_DECL void putInt(int) = 0;
    virtual DLL_DECL std::string passVal(std::string s)  = 0;
    virtual DLL_DECL std::string passRef(std::string &s) = 0;
    static  DLL_DECL protocol* makeObj();  // static member object factory
};

extern "C" { DLL_DECL protocol* gMakeObj(); }  // global object factory
#endif
