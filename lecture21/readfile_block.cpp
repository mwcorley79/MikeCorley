// Note: This is the C++ solution to HW # 8: 
// File: readfile_block.cpp
// Compiler command: g++ -o block_cp readfile_block.cpp
// Run Command:    ./block_cp  source-file  dest-file  block-size


#include <iostream>
#include <fstream>

std::string CopyFileByBlock(const std::string& source_file, 
		     std::string dest_file, 
		     size_t block_size, 
		     bool v)
{
   char* buf = nullptr;
   std::string retmsg;
   std::ifstream sf;
   std::ofstream df;
   int block_count = 0;
   try
   {
      // allocate buffer of block_size bytes
      buf = new char[block_size];

      // open the source file
      sf.open(source_file, std::ios::in | std::ios::binary);
      if(!sf.is_open())
	    throw std::runtime_error("File: " + source_file + " not found");
      
      // open the dest file
      df.open(dest_file, std::ios::out | std::ios::binary);
      if(!df.is_open())
	    throw std::runtime_error("File: " + dest_file + " could not be not opened");

      if(v)
        std::cout << "block size: " << block_size << std::endl;
      
      // attempt to read block size bytes
      sf.read(buf, block_size);
      while(sf.gcount() > 0)
      {
   	    if(v)
	      std::cout << "wrote block" << ":" << ++block_count << " size-> "  << sf.gcount() << std::endl; 
         
        // write what was actually read
	    df.write(buf,sf.gcount());
        
        // attempt to read another block_size buffer of bytes
        sf.read(buf, block_size);
      }
   }
   catch(std::exception& ex)
   {
      retmsg = ex.what();
   } 
 
   if(sf.is_open()) 
      sf.close();

   if(df.is_open())
      df.close();
   
   delete buf; // return memory to the heap
   retmsg = dest_file + " written successfully";
   return retmsg;
}


std::string CopyFile(const std::string& source_file, 
		     std::string dest_file, 
		     bool v)
{
   char* buf = nullptr;
   std::string retmsg;
   std::ifstream sf;
   std::ofstream df;
   int block_count = 0;
   try
   {
      // get the length of the input file
      sf.seekg (0, sf.end);
      int length = sf.tellg();
      sf.seekg (0, sf.beg);

      // allocate memory:
      char* buf = new char [length];

      sf.open(source_file, std::ios::in | std::ios::binary);
      if(!sf.is_open())
	throw std::runtime_error("File: " + source_file + " not found");
      
      df.open(dest_file, std::ios::out | std::ios::binary);
      if(!df.is_open())
	throw std::runtime_error("File: " + dest_file + " could not be not opened");

      if(v)
        std::cout << "block size: " << length << std::endl;
      
      sf.read(buf, length);
      if(sf.gcount() > 0)
      {
	if(v)
	  std::cout << "wrote block" << ":" << ++block_count << " size-> "  << sf.gcount() << std::endl;  
	df.write(buf,sf.gcount());
      }
   }
   catch(std::exception& ex)
   {
      retmsg = ex.what();
   } 
 
   if(sf.is_open()) 
      sf.close();

   if(df.is_open())
      df.close();
   
   delete buf; // return memory to the heap
   retmsg = dest_file + " written successfully";
   return retmsg;
}

void usage()
{
  std::cerr << "Usage: cp [-v] source-file  dest-file  block-size" << std::endl;
}


int main(int argc, char* argv[])
{
   std::string source_file;
   std::string dest_file;
   bool verbose = false;
   int block_size;

   // handles "cp source-file dest-file" 
   if(argc == 4)
   {
      source_file = std::string(argv[1]);
      dest_file  =  std::string( *(argv + 2));  // demonstrate using pointer syntax to index array
      block_size = atoi(argv[3]);
      
      if(block_size <= 0)
      {
        usage();
        return 2;
      }
   }
   // handles "cp -v source-file dest-file"
   else if(argc == 5)
   {
      if(std::string(argv[1]) == "-v")
      //if(argv[1] == "-v")
      {	
	verbose = true;
        source_file = std::string(argv[2]);
        dest_file  =  std::string( *(argv + 3));  // demonstrate using pointer syntax to index array
        block_size = atoi(argv[4]);

	if(block_size <= 0)
	{
          usage();
          return 2;
	}
      }
      else
      {
	 usage();
	 return 2;
      }
   }
   else
   {
      usage();
      return 1;
   }
     
   std::string msg = CopyFileByBlock(source_file, dest_file, block_size, verbose);
   //std::string msg = CopyFile(source_file, dest_file, verbose);
   std::cout << msg << std::endl;
   return 0;
}


