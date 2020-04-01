/* This demo: fork_exec_example.c - demonstrates process creation with the fork and exec system calls
"fork" spawns a child process (an exact copy of the parent process). 
"exec" is a process loader, and used to load a different process image, into context of the 
       created child process.

uses the GNU readline project (https://tiswww.case.edu/php/chet/readline/rltop.html). 
You need to install readline by typing: sudo apt-get install libreadline-dev 
Compiler Command: gcc -o simpleShell fork_exec_example.c -lreadline
Run Command: ./simpleShell
*/

#include <unistd.h> // fork and exec defined in this system header
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>


char** ParseCommandLine(char str[], char* delim, int max_args, int* num)
{
  char** args = (char**) malloc(max_args * sizeof(char**));  
  int init_size = strlen(str);
  char* ptr = strtok(str, delim);
  int count = 0; 
  while(ptr != NULL && count < max_args-1)
  {
	  args[count++] = ptr;
	  /* 
     * strtok modifies the original string. It puts NULL characters ('\0') at the 
	   * delimiter position after every call to strtok so that tokens can be tracked. 
	   * strtok also internally remembers the next token's starting position 
    */
	  ptr = strtok(NULL, delim);
  }
  
  args[count] = NULL;
  *num = count;
  return args;
}


int main(int argc, char * argv[])
{
  const int MAX_STR = 200;  /* max length of a command line */
  const int MAX_ARGS = 50;  /* max number of args that can be sent to child process command line */
  int num_args;  /* number ofd args passed to child process */
  char cmdline[MAX_STR]; /* command line buffer */
  pid_t c_pid, pid;  /* process ids */
  int status;

  printf("Simple Shell: v. 0.9 Type Ctrl-C to exit\n");
  while(1)
  {
      // 1. display prompt and get user input
      
      char prompt[]="msh$";
     
      // 2. get user input
      char* cmdline_ptr = readline(prompt);
      
      // add to the history
      if(strlen(cmdline_ptr))
      {
         add_history(cmdline_ptr);
      }
      
      // 3.***  parse command, not done
      char** args = ParseCommandLine(cmdline_ptr, " ", MAX_ARGS, &num_args);
      
      // 4. create child process (fork is a system call 
      // returns twice, once in the parent process, and once in the child process
      c_pid = fork(); // use man fork to get details for fork

      // 5. (load child process images specifed in cmdline) 
      // check the return value from fork(), 0 is the child, no zero is the parent 
      if (c_pid == 0)
      {
        // this is the child: so exec (load) the command entered by the user 
	      // this overwrites the child process image with that of the command specified in cmdline    
        execv(args[0], args);  // use man exec for details on exec 
        // only get here if exec failed
    	  // perror("execve failed");
      }
      else if (c_pid > 0)
      {
        // return from fork is non zero, so this is parent
	      // 6. all we do in the parent is wait for the child to process to exit
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

      //free memory for the command line buffer allocated by readline
      free(cmdline_ptr);
  }

  return 0; //return success
}
