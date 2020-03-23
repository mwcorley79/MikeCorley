/////////////////////////////////////////////////////////////////////////////////////////////////
// Description: MinShell: CSE 384 (spring 2020) Project 1 starter code (you may use this).     //
// This a minimal shell implemention capable of basic commands:                                //  
// setting/displaying shell variables, shell history, and running external programs            //
// Dependencies:                                                                               // 
//   GNU readline:           https://tiswww.case.edu/php/chet/readline/rltop.html              //
//   Installation:           sudo apt-get install libreadline-dev                              //
//     Build/Compiler command:                                                                 //
//          g++ -o msh minShell.cpp CommandManager.cpp Process.cpp -lreadline                  //
//     Run Command:                                                                            // 
//         ./msh                                                                               //
/////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <vector>
#include <signal.h>
#include <sstream>
#include "Process.h"
#include "CommandManager.h"
#include <readline/readline.h>
#include <readline/history.h>


// read command line from the user 
std::string getlineSh(const std::string& prompt)
{
  char* buf = readline(prompt.c_str());
  if(buf != nullptr)
  {
    std::string cmdLine = std::string(buf);
    free(buf);

    if(cmdLine.length() > 0)
    {
       add_history(cmdLine.c_str());
    }
    return cmdLine;
  }
  return "";
}

// static keywords gives handler function "internal linkage" (not visible outside this file)
// signal handler: catch Ctrl-C at keyboard
static void handle_sigint(int sig) 
{ 
   std::cerr << "Caught signal " << sig << std::endl; 
} 

// turn a std::string (a command line) into tokens
// e.g. "ls -l /usr/bin" -> "ls"  "-l"  "/usr/bin"
std::vector<std::string> TokenizeString(const std::string& str, char delim)
{
    std::vector<std::string> toks;
    std::stringstream ss(str);
    std::string token;

    while(std::getline(ss, token, delim))
    {
        toks.push_back(token);
    }

    return toks;
}

// prints the message for the built-in command: "help"
static void DisplayHelp()
{
   std::cout << "(cse384 Spring 2020) msh, version 1.0-release (x86_64-pc-linux-gnu)" << std::endl;
   std::cout << "These shell commands are defined internally.  Type `help' to see this list. " << std::endl;
   std::cout << "help              -- display this message" << std::endl;  
   std::cout << "set varname=path  -- set a shell variable (e.g.) set path=./:/bin" << std::endl; 
   std::cout << "show varname      -- display a shell variable (e.g.) show path" << std::endl;
   std::cout << "exit              -- terminate the shell " << std::endl;
}

// *** Complete this function to implement executing external programs ***
// *** Must support the following types of commands:  
// 1. absolute path :  (example: /bin/ls -l /usr/bin)
// 2. relative path:  (example: ./someprogname [args] )
// 3. search the path variable for a specified external program: ls -l /usr/bin
//    search the path variable for "ls"    
void DoProcessExternalCommand(const std::vector<std::string>& command_tokens, 
		                        CSE384::CommandManager& commandManager)
{
   std::cout << "Implement: Should run command -> " << command_tokens[0] << std::endl;
}


//  *** Complete this function to implement shell built-in commands: set/show shell variables ***  
//  function returns true to indicate that shell session should terminate (e.g. user types exit), and
//  false in all other cases
bool DoProcessBuiltInCommand(const std::vector<std::string>& command_tokens, 
		                       CSE384::CommandManager& commandManager)
{
  if(command_tokens[0] == "exit")
  {
     std::cout << "exiting" << std::endl;
     return true;
  }

  if(command_tokens[0] == "help")
  {
    DisplayHelp();
    return false;
  }

  
  // default case 
  return false;
}

bool ParseCommand(const std::vector<std::string>& tokens, 
	           	   CSE384::CommandManager& commandManager)
{
   if(tokens.size() > 0)
   {
      // check for the shell built-in 
     if(tokens[0] == "set"  || tokens[0] == "show" || 
        tokens[0] == "exit" || tokens[0] == "help")
     {
       // process and run built in shell command
       return DoProcessBuiltInCommand(tokens, commandManager);
     }
     else
     {
        // process and run external command
        DoProcessExternalCommand(tokens, commandManager);
     }  
   }

   return false;
}

int main()
{
   //uncomment this if you want to handle signals (Ctrl-C etc.)
   //signal(SIGINT, handle_sigint);
   std::cout << "Type \"help\" to list the (min) shell commands" << std::endl;
   
   // provides facilities for managing (get/set) shell variables, and searching path 
   // See interface: CommandManager.h 
   CSE384::CommandManager commandManager;

   std::string shellPrompt = "msh$";
   bool exit_sh = false;
   while(!exit_sh)
   {
     // a wrapper around gnu getline  to read the command line from the user
     std::string cmdline = getlineSh(shellPrompt);
     
     // tokenize the command line provided by the user
     std::vector<std::string> cmdlineToks = TokenizeString(cmdline, ' ' );
     
     // parse and process the the tokenized command line
     exit_sh = ParseCommand(cmdlineToks, commandManager);
   }

   return 0;
}
