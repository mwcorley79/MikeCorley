
////////////////////////////////////////////////////////////////////////////////
// CommandMananger.h - package interface to create and manage shell variables //                                                         //
// Language:    gcc/g++ v7.4.0                                                //
// Platform:    Dell Precision Mobile Workstation m7200                       //
//              Linux Mint 19.3 (64-bit)                                      //
// Application: CSE384 (Spring 2020), Project 1 Helper                        //
// Author:      Mike Corley, CST 4-232, Syracuse University                   //
//              mwcorley@syr.edu                                              //
////////////////////////////////////////////////////////////////////////////////

/*
 * Module Operations:
 * ==================
 * This package provides facilities for managing variables as would be
 * used by a command shell implementation.  variables are stored in an
 * unordered_map (a hashtable key/value pair data structure).
 * The SearchPath methods assumes a variable "path"  was created, and searches
 * for a builds the absolute path for a specified executable
 * 
 * Public Interface:
 * =================
 * std::cout << "test command manager" << std::endl;   
   CommandManager  commandManager;
   // test set a shell variable: name=Mike 
   commandManager.SetShellVariable("name", "Mike");
  
   // test get the shell variable
   std::string val = commandManager.GetShellVariable("name");
   std::cout << "value is: " << val << std::endl;
   
   std::cout << "Test searching path for command: \"ls\" no path set " << std::endl;
   // search for the specified  "ls" executable in the search path
   std::string absolute_path = commandManager.SearchPath("ls");
   
   // if the path variable is not set or the executable ("ls") is not found,
   // SearchPath returns the empty string "".  If the executable is found,
   // the then the abosolute path is returned. e.g. /bin/ls 
   if(absolute_path == "")
      std::cout << "Path variable or executable not found" << std::endl;
   else
     std::cout << "absolute path of  \"ls\" is: " << absolute_path << std::endl; 

   commandManager.SetShellVariable("path", "./:/usr/bin:/bin");

   std::cout << "Test searching path for command: \"ls\" path=./:/usr/bin:/bin" << std::endl;
   absolute_path = commandManager.SearchPath("ls");
   
   if(absolute_path == "")
      std::cout << "Path variable or executable not found" << std::endl;
   else
     std::cout << "absolute path of  \"ls\" is: " << absolute_path << std::endl;

   std::cout << "Test searching path for command: \"/bin/ls\" " << std::endl;
   absolute_path = commandManager.SearchPath("/bin/ls");
   if(absolute_path == "")
      std::cout << "Path variable or executable not found" << std::endl;
   else
     std::cout << "absolute path of  \"ls\" is: " << absolute_path << std::endl;

   std::cout << "Test searching path for command: \"lss\" -- a command that doesn't exist" << std::endl;
   absolute_path = commandManager.SearchPath("lss");
   if(absolute_path == "")
      std::cout << "Path variable or executable not found" << std::endl;
   else
     std::cout << "absolute path of  \"ls\" is: " << absolute_path << std::endl;
 
 * Required Files:
 * ===============
 * CommandManager.h, CommandManager.cpp
 *
 * Build Command: (compiles the test stub)
 * =============
 * g++ -DTEST_COMMAND -o CommandTest CommandManager.cpp 
 * 
 * Run Command:
 * ============
 * ./CommandTest
 *
 * Maintenance History:
 * ===================
 * ver 1.0 : 16 Mar 2020
 * - first release
 */

#ifndef _COMMANDMANAGER
#define _COMMANDMANAGER

#include <string>
#include <unordered_map>
#include <vector>

namespace CSE384
{
   using VariableTable = std::unordered_map<std::string, std::string>;
   using PathList = std::vector<std::string>;

   class CommandManager
   {
     public:
       void SetShellVariable(const std::string& var_name, const std::string value);
       std::string GetShellVariable(const std::string& var_name);
       std::string SearchPath(const std::string& command);
     private:
       std::vector<std::string> ParseString(const std::string& str, char delim);
       VariableTable varTable;
       PathList pathList;
   };
}
#endif 
