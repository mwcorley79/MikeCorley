#ifndef _MYSHELL_H_
#define _MYSHELL_H_

#include<iostream>
#include<string>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


namespace CSE384
{

  class StartInfo
  {
     std::string Filename() const;
     void Filename(const std::string& filename);
  }


  class Process
  {
    public:
      Process(); 
      Process(StartInfo* start_info);
      void Start();
      void Wait();      
      StartInfo StartInfo();
    private:
      StartInfo* start_info;
      pid_t c_pid, pid;
      int status;
      bool created;
  }

  Process::Process(): start_info(new StartInfo())
  {
  
  }
   

