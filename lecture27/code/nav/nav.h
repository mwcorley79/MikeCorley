//////////////////////////////////////////////////////////////////////////
//Note: The documentation for this package header was modified by Mike C. 4/22/20
//////////////////////////////////////////////////////////////////////
/*
 * nav.h - navigate a directory tree starting from a specified path
 *
 *  Created on: May 29, 2011
 *  Revised on: Jun 15, 2011
 *    - converted to navigate class
 *
 *  Author: jim fawcett
 *
/////////////////////////////////////////////////////////////////
//  nav.h    --    recursively walk a directory tree           //
//  ver 1.9        starting at a specified path                //
//                                                             //
//  Language:      Visual C++, ver 7.1                         //
//  Platform:      Dell Precision T7400, Vista Ultimate, SP1   //
//  Application:   CSE775 Project #1, Spring 2009              //
//  Author:        Jim Fawcett, Syracuse University CST 4-187  //
//                 (315) 443-3948, jfawcett@twcny.rr.com       //
/////////////////////////////////////////////////////////////////
/*
    class navig Operations:
    -----------------------
    An object of the navig class walks a directory (sub)tree,
    processing files and directories encountered along the walk.
    Root of the walk is passed to member function start.  The 
    root can be any valid path including "." and ".."

      userProc udp;      construct a user defined proc object
      navig nav(udp);    construct a navigator object
      nav.walk(root);   start a recursive walk at root

    When the walk is completed the starting directory will be
    restored.  Note that you will have to define the userProc
    class.  See the test stub in nav.cpp for an example of
    how to do that.
*/
///////////////////////////////////////////////////////////////
//                      maintenance page                     //
///////////////////////////////////////////////////////////////
//  Build Process                                            //
//                                                           //
//  Files Required: nav.h, nav.cpp                           //
//                                                           //
//  Compiler command: g++ -o navigateTest nav.cpp            //
//  Run Command:      ./navigateTest specify-path            //
//                                                           //
//                                                           //
//                                                           //
///////////////////////////////////////////////////////////////
/*
    Maintenance History
    ===================
    ver 1.9 : 14 Feb 2011
      - fixed build errors reported by Shawn Mueller
      - made Navig::getPath an inline function to avoid multiple
        definitions of this function at link time.
      - getPath return type changed to stdStr
      - included fileInfo header
    ver 1.8 : 18 Jan 2009
      - fixed bug in navig::walk(path,pattern)
      - cosmetic fixes to manual page
    ver 1.7 : 13 Jan 2009
      - added namespace Win32Tools
    ver 1.6 : 19 Jan 2006
      - added getPath()
    ver 1.5 : 14 Mar 2005
      - added using relationship arrow to diagram below.
    ver 1.4 : 17 Jan 2005
      - simplified processing in walk function
    ver 1.3 : 30 Jan 2000
      - incorporated use of fileInfo objects to simplify
        navig processing
      - changed default and user defined processing objects
        to eliminate requirement for them to be allocated
        on the heap, e.g., dynamically
    ver 1.2 : 27 Apr 1999
      - cosmetic changes to these pages
    ver 1.1 : 22 Apr 1999
      - cosmetic changes to walk and start functions
    ver 1.0 : 30 Jan 1998
      - first release


    Design Notes:
    =============
    The navigate object provides all the
    intelligence about extracting file information from a directory.
    Navigates's job is simply to do a depth-first traversal of the dir
    structure rooted at the path provided its start function.

                                         The navigate object holds
     +-------+             +----------+   a reference to a object 
     |       |-----------> | INavProc |   that implements INavProc
     | navig |             +----------+   
     |       |                  |        
     +-------+                 / \        The reference is obtained
                                |         by passing one when the object
                           +----------+   is constructed.
                           | userProc |
                           +----------+   

    An example of how to implement custom processing by defining
    a userProc class is presented in the test stub.  That should be
    enough to show you how to implement your own processing.

*/



#ifndef NAV_H_
#define NAV_H_

#include <sys/types.h>
#include <dirent.h>
#include <sys/syscall.h>
#include <string>

class INavProc
{
public:
	virtual ~INavProc() {}
	virtual void fileProc(const std::string& filename)=0;
	virtual void dirProc(const std::string& directory)=0;
};

class navigate
{
public:
	navigate(INavProc* pProc) { _pProc = pProc; }
	void walk(const std::string& path);
private:
	INavProc* _pProc;
};

#endif /* NAV_H_ */
