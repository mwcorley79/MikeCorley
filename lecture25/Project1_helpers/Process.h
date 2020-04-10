//////////////////////////////////////////////////////////////////////////////////////////
// Process.h -  package interface for process creation in Linux (Unix/POSIX compliant)  //                                                           //
// Language:    gcc/g++ v7.4.0                                                          //
// Platform:    Dell Precision Mobile Workstation m7200                                 //
//              Linux Mint 19.3 (64-bit)                                                //
// Application: CSE384 (Spring 2020), Project 1 Helper                                  //
// Author:      Mike Corley, CST 4-232, Syracuse University                             //
//              mwcorley@syr.edu                                                        //
//////////////////////////////////////////////////////////////////////////////////////////

/*
 * Module Operations:
 * ==================
 * This package provides a facility for creating processes on POSIX compliant
 * Unix systems.  The Start() method is convenient wrapper around the low-level 
 * fork and exec system calls.  See Public Interface (below) and
 * and Test stub in Process.cpp for example usage   
 * 
 * Public Interface:
 * =================
 * // example tokenized command: command_tokens
 * std::vector<std::string> command_tokens {"ls", "-l", "/bin"};
 * CSE384::Process p;
 * // search path variable if set
 * CSE384::CommandManager commandManager;
 * commandManager.SetShellVariable("path", "./:/usr/bin:/bin");
 * std::string absolute_path = commandManager.SearchPath(command_tokens[0]);
 * // if command is found in the search path (e.g. ls), then execute the command
 * if(absolute_path != "")
 * {
 *   // make a copy of the command tokens, and and set the command (tok[0]) 
 *   // to its absolute path. i.e. "ls" -> "/bin/ls" 
 *   std::vector<std::string> temp_tokens(command_tokens);
 *   temp_tokens[0] = absolute_path;
 *   // start the process, (passing the command and the argument tokens)
 *   p.Start(temp_tokens, true);
 *  }
 *  else
 *  {
 *     std::cerr << command_tokens[0] << " command not found" << std::endl;
 *     if(commandManager.GetShellVariable("path") == "")
 *       std::cerr << "path variable not set" << std::endl;
 *  }
 
 * Required Files:
 * ===============
 * Process.h, Process.cpp, CommandManager.h, CommandManager.cpp
 *
 * Build Command: (compiles the test stub)
 * =============
 * g++ -DTEST_PROCESS -o ProcessTest Process.cpp CommandManager.cpp 
 * 
 * Test Stub Run Command:
 * ============
 * ./ProcessTest
 *
 * Maintenance History:
 * ===================
 * ver 1.0 : 17 Mar 2020
 * - first release
 */

#ifndef _MYSHELL_H_
#define _MYSHELL_H_

#include<string>
#include<vector>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

namespace CSE384
{
  class Process
  {
    public:
      Process(); // default ctor 
      void Start(const std::vector<std::string>& command_tokens, bool wait=true);
      // prevent users from making copies of the Process object instances 
      Process(const Process&) = delete;                 // deleted copy constructor
      Process& operator = (const Process&) = delete;   // deleted copy assignment operator
    private:
      pid_t c_pid, pid;
      int status;
      bool created;
      void Wait();      
  };
}

#endif
   

