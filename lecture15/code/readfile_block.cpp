// HW # 8  -- complete function CopyFileByBlock below
// Compilation Command: g++ -o block_cp readfile_block.cpp
// Run Command        : ./block_cp  source-file  dest-file  block-size
//                      ./block_cp  ./foo.txt  ./foo2.txt  4096
//                      ./block_cp  -v ./foo.txt  ./foo2.txt  4096

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
     // allocate a buffer to hold block size bytes 
     
     //1.  open the input file stream (sf)
     //2.  if the file could not be opened successfully, throw a runtime exception  
     //3.  open the dest (output) file from writing
     //4. if the file could not be opened successfully, throw a runtime exception 
      
     //5  read and write the newnew file (block at a time) 
  
     /* 
        attempt to read "block_size" bytes of data from sf into the allocated buffer     
        while( bytes read greater than zero)
        {
          if(v)
	        std::cout << "wrote block" << ":" << ++block_count << " size-> "  << sf.gcount() << std::endl;  
          
          write the number of bytes read from sf to df 	

          attempt to read "block_size" bytes of data from sf into the allocated buffer
        }
     */
   }
   catch(std::exception& ex)
   {
      retmsg = ex.what();
   } 
 
   // 6. close source file (sf)
   // 7. close dest file (df)
   
   // 8. return buffer memory to the heap (delete)
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

      // allocate memory using c++ new (not malloc)
      char* buf = new char [length];

      sf.open(source_file, std::ios::in | std::ios::binary);
      if(!sf.is_open())
	throw std::runtime_error("File: " + source_file + " not found");
      
      df.open(dest_file, std::ios::out | std::ios::binary);
      if(!df.is_open())
	throw std::runtime_error("File: " + dest_file + " could not be not opened");

      if(v)
        std::cout << "block size: " << length << std::endl;
      
      //read the entire file into the buffer
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
   
   //uncomment to test   
   //std::string msg = CopyFileByBlock(source_file, dest_file, block_size, verbose);
   std::string msg = CopyFile(source_file, dest_file, verbose);
   std::cout << msg << std::endl;
   return 0;
}
