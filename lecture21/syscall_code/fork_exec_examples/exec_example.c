/* This demo: exec_example.c - demonstrates the exec system call
  "exec" is a process loader, and used to load a different process image, into context of the 
         created child process.  This examples load the /bin/ls process image into the "exec_example" 

   Compiler/Build command: gcc -o exec_example exec_example.c
   Run Command: ./exec_example
*/

#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h>

int main() 
{ 
    // A null terminated array of character pointers 
    char* args[]={"/bin/ls",NULL}; 
        
    printf("You will see this message\n");
    
    // load the the /bin/ls process image
    execvp(args[0],args); 
      
    /*
        All statements are ignored after execvp() call as this whole  
        process(exec_example) is replaced by another process (/bin/ls) 
    */
    printf("You won't see this message because the process was replaced"); 
      
    return 0; 
} 

