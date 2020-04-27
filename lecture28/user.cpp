#include "libs.h"
#include <dlfcn.h>
#include <iostream>

int main(int argc, char * argv[]){

  void * lib_handle = dlopen("libs.so", RTLD_LAZY);
  if(lib_handle == NULL){
    std::cout << "can't open libs.so" << std::endl;
    return 0;
  }

  void (*fptr1)() = (void (*)()) dlsym(lib_handle, "say0");
  void (*fptr2)() = (void (*)()) dlsym(lib_handle, "say1");

  fptr1();
  fptr2();

  return 0;
}
