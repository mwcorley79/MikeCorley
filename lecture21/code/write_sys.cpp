// demo write system call and standard file streams
// compiler command: g++ write_sys.cpp
// Test stdout -> ./a.out "some message" 1 > out
// Test stderr -> ./a.out "some message" 2 2> out

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
     fprintf(stderr, "usage: prog_name (a.out)  message  file_descriptor");
     return 0;
  }

  // use man 2 write
  int fd = atoi(argv[2]);
  char* message = argv[1];
  
  if(fd == 1)
  {
     printf("%s\n", message); // C library - libc) stdout
     fprintf(stdout, "%s\n", message); // C library - libc) explict stdout
     std::cout << message << std::endl;  // C++ (iostream)   console out
     ssize_t bytes = write(fd, argv[1], strlen(argv[1])); // POSIX write system call (fd == 1) 
  }
  else if (fd == 2)
  {
     fprintf(stderr, "%s\n", message); // C library - libc) explict stderr
     std::cerr << message << std::endl; // C++ (iostream)   console error
     ssize_t bytes = write(fd, argv[1], strlen(argv[1])); // POSIX write system call (fd == 1) 
  }
  else
  {
     // stream/file descriptor not open
  }

  return 0;
}
