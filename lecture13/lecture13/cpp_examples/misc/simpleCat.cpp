#include <iostream>
#include <fstream>


void DisplayFile(const char* filename)
{
    // attempt tp open the file for reading
    std::ifstream ins;
    std::istream* is_;

    if(filename != nullptr)
      ins.open (filename, std::ifstream::in);
    
    if(ins.is_open())
       is_= &ins;      
    else
       is_ = &std::cin;
    
    
    char ch = is_->get();
    while(is_->good())
    {  
      std::cout << ch;
      ch = is_->get();
    }
    
    // if ins is not std::cin, then close the stream
    if(is_ != &std::cin)
        ins.close();
}


int main(int argc, char* argv[])
{
    // argc is the argument count:  argv is the array of command
    // args passed to the program:  argv[0] is the name of the program
    if(argc < 2)
    {
        DisplayFile(nullptr);
    }

    for(int i = 1; i < argc; ++i)
    {
        DisplayFile(argv[i]);
    }
    
    return 0;
}
