
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "mpl.h"

using FileTransferMessageType = enum { FILE_OPEN_REQUEST=0x0A ,
                                       FILE_WRITE_BLOCK_REQUEST=0x0B,
                                       FILE_CLOSE_RQUEST=0x0C 
                                     };

std::string ExtractFilename(const std::string fullpath)
{
   std::size_t found = fullpath.find_last_of("//");
   return fullpath.substr(found+1);
}

void sendFileBlock(const std::string& filename, 
                   int block_size, 
                   bool v, 
                   CSE384::Sender& sender)
{
   int block_count = 0;
   char* buf = nullptr;
   std::string retmsg;
   std::ifstream sf;

   try
   {
      // allocate buffer of block_size bytes
      buf = new char[block_size];

      // open the file
      sf.open(filename, std::ios::in | std::ios::binary);
      if(!sf.is_open())
	      throw std::runtime_error("File: " + filename + " not found");
      
       CSE384::Message fileCreateMsg(ExtractFilename(filename), FileTransferMessageType::FILE_OPEN_REQUEST);
       sender.PostMessage(fileCreateMsg);

       std::cout << "Sent file request to create file: " << filename << std::endl;
       CSE384::Message replyMsg =  sender.GetMessage();
       
       // get server acknowledgement
       std::cout << replyMsg << std::endl;
     
       // attempt to read block size bytes
       sf.read(buf, block_size);
       while(sf.gcount() > 0)
       {
          CSE384::Message blockMessage(buf, sf.gcount(), FILE_WRITE_BLOCK_REQUEST);
          // write what was actually read
          sender.PostMessage(blockMessage);
          CSE384::Message reply = sender.GetMessage();  
          
          if(v)
          {
	          std::cout << "Sent" << ":" << ++block_count << " size-> "  << sf.gcount() << std::endl;
             std::cout << reply << std::endl;
          }       
         
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

   sender.PostMessage(CSE384::Message(nullptr, 0, FileTransferMessageType::FILE_CLOSE_RQUEST));
   std::cout << sender.GetMessage() << std::endl;

   delete buf; // return memory to the heap
}


int main(int argc, char* argv[])
{
   if(argc != 5)
   {
      std::cerr << "Usage: filename   block_size   ip-address  port" << std::endl;
      return 0;
   }

   std::string filename(argv[1]);
   int block_size = std::stoi(argv[2]);
   CSE384::EndPoint serverEp(argv[3], std::stoi(argv[4]));

   // instantiate a sender 
   CSE384::Sender sender;

   int wait_secs = 1; // wait time between connection attempts
   int verbose_level = 1;  // verbose (display connect attempts)
   int connect_attempts = 10; // make 10 connection attempts
   if(sender.ConnectPersist(serverEp, connect_attempts, wait_secs, verbose_level) < 10)
   {
      sendFileBlock(filename, block_size, true, sender);
      sender.Close();
   }
   else
      perror("Connect:"); // for now, using c-style error printing
}