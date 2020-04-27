#ifndef _ANIMAL_H
#define _ANIMAL_H

// abstract interface for defining and creating concrete anaimal types
class Animal
{
  public:
    virtual void speak() = 0;
    virtual ~Animal() {} ;
};

// global factory creational function: defined in each library
extern "C"  // need to disable C++ name mangling  
{ 
  Animal* Create();
}

#endif
