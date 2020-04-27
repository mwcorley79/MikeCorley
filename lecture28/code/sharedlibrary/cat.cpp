#ifndef _CAT_H
#define _CAT_H

#include "Animal.h"
#include <iostream>

//define Cat by implementing Animal
class Cat : public Animal
{
    virtual void speak()
    {
       std::cout << "Meow!" << std::endl;
    }
};

// creational function for constructing Cat instances
Animal* Create() 
{ 
   return new Cat(); 
} 

#endif
