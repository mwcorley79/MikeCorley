/*
 * nav.h - navigate a directory tree starting from a specified path
 *
 *  Author: jim fawcett
 *
 *  version 3: 01/23/2012
 *  - added command line input
 *  version 2: 06/15/2011
 *  - converted to navigate class
 *  version 1: 05/29/2011
 *  - first release
 *
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
