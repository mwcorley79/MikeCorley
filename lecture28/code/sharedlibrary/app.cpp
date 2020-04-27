#include <dlfcn.h>
#include <iostream>
#include "Animal.h"
#include <thread>
#include <chrono>

Animal* CreateAnimal(void* library_handle)
{
   // define a function pointer to point to a function with signature: Animal* (*) ()
   // this is a function that can return pointer to Animal type and takes no arguments
   // note:  look at the creational function: Animal* Create() in the each of the library code
   typedef Animal* (*cptr)(); 
   
   //find the Create (object factory) method in the current loaded library
   cptr create =  (cptr) dlsym(library_handle, "Create");

   // call the object factory Create(), to create an instance of the concrete animal
   Animal* animal = (Animal*) (*create)();

   // check for errors and retur accordingly
   const char *dlsym_error = dlerror();    
   
   if(dlsym_error)         
     return nullptr;
   else
     return animal;
}


int main(int argc, char * argv[])
{ 
   int i = 0;
  while(true)
  {
    // load the shared object library: ** note libAnimal.so is symbolic link to manage versioning
    void* lib_handle = dlopen("libAnimal.so", RTLD_LAZY);
    
    if(lib_handle != NULL)
    {
      // create animal by calling the instance of the Create function defined in library currently loaded 
      Animal* animal = CreateAnimal(lib_handle);
      
      if(animal != nullptr)
      {
         std::cout << ++i << ": ";
         //use animal through the interface: app knows nothing about Dog and Cat types!
         animal->speak();
      }
      else
        std::cerr << "instance of \"Animal\" not created" << std::endl;
 
      // close the loaded library
      dlclose(lib_handle);
    }
    else
    {
       std::cerr << "error loading library" << std::endl;
    }
    
    //sleep for one second
    std::this_thread::sleep_for(std::chrono::seconds(1));
  } 
  return 0;
}
