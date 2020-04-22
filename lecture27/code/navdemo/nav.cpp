/*
 * nav.cpp
 *
 *  Created on: May 29, 2011
 *      Author: jim
 */

#include "nav.h"
#include <iostream>
#include <vector>
#include <string.h>
#include <unistd.h>

void navigate::walk(const std::string& path)
{
  _pProc->dirProc(path);
  DIR* dir = opendir(path.c_str());
  if(dir == 0)
  {
    std::cout << "\n  can't open directory: " << path;
    return;
  }
  dirent* dp;
  std::vector<std::string> dirs;

  // display files on path
  do {
    dp = readdir(dir);
    if(dp == 0)
      break;
    if(dp->d_type == 8)
      _pProc->fileProc(dp->d_name);
    if(dp->d_type == 4)
    {
      if(strcmp(dp->d_name,".") != 0
      && strcmp(dp->d_name,"..") != 0
      && strcmp(dp->d_name,".metadata") != 0)  // hidden metadata folders are huge
      {
        std::string subpath = std::string(path) + std::string("/")
                            + std::string(dp->d_name);
        dirs.push_back(subpath);
      }
    }
  } while (dp != 0);
  closedir(dir);

  // recursively walk subdirs
  for(size_t i=0; i<dirs.size(); ++i)
    walk(dirs[i].c_str());
}

class navProc : public INavProc
{
public:
  void fileProc(const std::string& filename)
  {
    std::cout << "\n  file:" << filename;
  }
  void dirProc(const std::string& dirname)
  {
    std::cout << "\n  path: " << dirname;
  }
};

int main(int argc, char* argv[])
{
  std::cout << "\n  Navigating Directories";
  std::cout << "\n ========================";

  const char* path = "..";
  try
  {
    if(argc >1)
    {
      path = argv[1];
    }
    chdir(path);
    const char* newPath = get_current_dir_name();
    navProc nproc;
    navigate nav(&nproc);
    nav.walk(newPath);
  }
  catch(std::exception& ex)
  {
    std::cout << "\n  " << ex.what() << "\n\n";
    return 1;
  }
  return 0;
}
