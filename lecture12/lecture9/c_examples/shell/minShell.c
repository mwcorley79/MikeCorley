#include <unistd.h> // fork and exec defined in this system header
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


// read a line from a FGILE stream, stdin etc.
// this should move into a separate package utils.h/.c etc.
void mygetline(FILE* stream, char line[], char delim, int max)
{
   int ch;
   int count = 0;
   while(  ((ch = fgetc(stream)) != EOF) && ch != delim && count < (max-1))
       line[count++] = ch;
   line[count] = '\0';

   // consume the remaining part of the line, but don't buffer it
    while(ch != EOF && ch != delim)
    {
      ch = fgetc(stream);
    }
}


int main(int argc, char * argv[])
{
  char* args[] = {" ", NULL} ;
  const int max = 200;
  char cmdline[max];
  pid_t c_pid, pid;
  int status;

  while(1)
  {
     // 1. display prompt and get user input
     printf("minShell$");
     
     // 2. get user input
     mygetline(stdin, cmdline, '\n', max);

     // 3.***  parse command, not done
       
     // create child process (fork is a system call 
     // returns twice, once in the parent process, and once in the child process
     c_pid = fork(); // use man fork to get details for fork

      // check the return value from fork(), 0 is the child, no zero is the parent 
      if (c_pid == 0)
      {
        // this is the child: so exec (load) the command entered by the user 
	// this overwrites the child process image with that of the command specified in cmdline    
        execv(cmdline, args);  // use man exec for details on exec 
        // only get here if exec failed
	// perror("execve failed");
      }
      else if (c_pid > 0)
      {
        // return from fork is non zero, so this is parent
	// all we do in the parent is wait for the child to process to exit
        if( (pid = wait(&status)) < 0)
	{
           perror("wait");
           _exit(1);
        }
      }
      else
      {
         perror("fork failed");
         _exit(1);
      }
  }

  return 0; //return success
}
