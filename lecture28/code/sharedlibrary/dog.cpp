#ifndef _DOG_H
#define _DOG_H

#include "Animal.h"
#include <iostream>

//define Dog by implementing Animal
class Dog : public Animal
{
    virtual void speak()
    {
       std::cout << "Bark!" << std::endl;
    }
};
// creational function for constructing Dog instances
Animal* Create() 
{ 
   return new Dog(); 
} 

#endif
