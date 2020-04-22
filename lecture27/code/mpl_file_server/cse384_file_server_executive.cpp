//////////////////////////////////////////////////////////////////////////////
// File:        cse384_file_server_executive.cpp
// Description: this file implements a basic a fule server prototype 
//              which is the basis for Project 2
// Compiler Command: g++ -o server cse384_file_server_executive.cpp Sender.cpp Receiver.cpp ClientHandler.cpp Message.cpp MPUtils.cpp Cpp11-BlockingQueue.cpp FileSystem.cpp Project2utils.cpp -lpthread
// Run Command     : ./server ./serverFiles 127.0.0.1 6060
/////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

#include "mpl.h"
#include "FileSystem.h"
#include "Project2utils.h"

using namespace CSE384;
using namespace FileSystem;
using namespace std;

bool ParseCommandLine(int argc, char *argv[],
                      string &RootPath,
                      string &server_ip,
                      int &server_port)
{
    if (argc != 4)
    {
        std::cerr << "Usage: Root-Filpath  ip-address  port" << std::endl;
        return false;
    }

    // get the user specified file storage path for use by the server
    RootPath = argv[1];

    // check that the storage path exists
    if (Directory::exists(RootPath))
    {
        // check the storage path has the trailing '/', else put in there
        if (RootPath[RootPath.length() - 1] != '/')
            RootPath += '/';
    }
    else
    {
        std::cerr << "Specified Server File Store Path: "
                  << RootPath << " doesn't exist, or is not accessible"
                  << std::endl;
        return 1;
    }

    // get the user specified server IP address and service port
    server_ip = std::string(argv[2]);
    server_port = std::stoi(argv[3]);

    return true;
}

// ***********************************************************************
// *****  Project 2: Complete this function DoProcesSendFileRequest ******
// ***********************************************************************   

// Once complete, this function will use message passing to transfer files
// to a remote clients: follow the instructions number below: You may
// wish to use you HW8 solution as reference becuase the logic is 
// similar

bool DoProcessSendFileRequest(const std::string &rooted_path, 
                              const std::string &filename, 
                              int block_size, 
                              const EndPoint &clientEP)
{
   std::ifstream sf;

   // #1 allocate buffer of block_size bytes
   char *buf = new char[block_size];

   // open the source file for binary reading
   string absolute_path = rooted_path + filename;
   sf.open(absolute_path, std::ios::in | std::ios::binary);
   if (!sf.is_open())
      return false;
   
   // define an instance of a sender
   Sender sender;

   // connect to the client's listener 
   if (sender.Connect(clientEP))
   {
      // start the send thread
      sender.Start();
      
      // check to see if start() was successful and send thread is active
      if (sender.IsSending())
      {
         // first send the filename to the client as Message of type SEND_FILE_CREATE
         sender.PostMessage(Message(filename, FileServerMessageType::SEND_FILE_CREATE));

         // send over the file in chucks of size block_size  
         // attempt to read one block at a time
         sf.read(buf, block_size);
         while (sf.gcount() > 0)
         {
            // write whatever was read into the sender as new message of type SEND_FILE_BLOCK
            sender.PostMessage(Message(buf, sf.gcount(), FileServerMessageType::SEND_FILE_BLOCK));
            std::cout << "Transmitting file block of size " << sf.gcount() << std::endl;
          
            // read another block
            sf.read(buf, block_size);
         }

         // send the message to close the file
         sender.PostMessage(Message(nullptr, 0, FileServerMessageType::SEND_FILE_CLOSE));

         sender.Stop();
         return true;
      }
   }

   return false;
}

// get the list of the files on the server, and send back as a single message
bool DoServiceFileListRequest(const EndPoint& clientEp, const std::string& rootedpath)
{
   std::vector<std::string> files = Directory::getFiles(rootedpath);

   std::ostringstream temp;
   for (int i = 0; i < files.size() - 1; ++i)
   { 
      int fsize = GetFileSize(rootedpath + files[i]);
      temp << files[i] + "- " + std::to_string(fsize) + " bytes"  ":";
   }
   int fsize = GetFileSize(rootedpath + files[files.size()-1]);
   temp << files[files.size()-1] + " - " + std::to_string(fsize) + " bytes";
   Message responseMessage(temp.str(), FileServerMessageType::FILELIST_REQUEST);

   // send the list of files a single message back to the client
   return SendClientResponse(clientEp, responseMessage);
}


// this is where we define the server processing functionality
class ServerCommandHandler : public ClientHandler
  {
    public:
      
       ServerCommandHandler(EndPoint& ep, const std::string& rootPath): myEP(ep), rooted_path(rootPath)
       {}

       // this is a creational function: you must implement it
       // the Receiver creates an instance of this class (it's how the server polymorphism works) 
       virtual ClientHandler* Clone()
       {
          return new ServerCommandHandler(myEP,rooted_path);
       }
        
       // this is the custom server processing entry point
       virtual void AppProc()
       {
          // while there are messages in the blocking queue, and you have seen the disconnect
          // message, pull messages out and display them.
          bool done = false;
          do 
          {
             Message msg = GetMessage(); 
             switch(msg.GetType())
             {
                 // client closed the socket, so shutdown on the server end
                 case MessageType::DISCONNECT:
                    done = true;    
                 break;

                  // received a connect message from the client containing client's return endpoint
                 case FileServerMessageType::CONNECT_REQUEST:
                 {
                    clientEp.Parse(msg.ToString());
                    std::cout << " Hello! New Connection From: " << clientEp << std::endl;
                    
                    if(!SendClientResponse(clientEp, Message(myEP.ToString(), CONNECT_REQUEST)))
                      std::cout << "Problem communicating with " << clientEp << "! Is it running?" << std::endl;
                 }
                 break;

                 // received a request from a client for server's current file list
                 case FileServerMessageType::FILELIST_REQUEST:
                     // get the list of files currently on the server, and send to the client
                    if(DoServiceFileListRequest(clientEp, rooted_path))
                       std::cout << "FILE LIST request recieved! Okay! Sent to: " << clientEp << std::endl;
                    else
                       std::cout << "Problem communicating with " << clientEp << "! Is it running?" << std::endl;
                 break;

                 //  received a request from a client for specific file to download
                 case  FileServerMessageType::FILE_REQUEST:
                 {
                    std::vector<std::string> tokens = TokenizeString(msg.ToString(), ':');
                    string requested_file = tokens[0];   int block_size = std::stoi(tokens[1]);
                    
                    if(DoProcessSendFileRequest(rooted_path, requested_file, block_size, clientEp))
                       std::cout << "FILE REQUEST received. " << requested_file << " transmitted to " << clientEp << std::endl; 
                    else
                    {
                       std::string message = "Requested file: " + requested_file + " not found";
                       SendClientResponse(clientEp, Message(message,FileServerMessageType::ERROR_RESPONSE));
                    }
                 }
                 break;
             }
          }
          while(!done);
          std::cout << clientEp << " has disconnected! Bye! " << std::endl;
       }
       private:
         EndPoint clientEp;
         EndPoint myEP;
         std::string rooted_path;
   };

   
   int main(int argc, char* argv[])
   {
       try
       {
           string RootPath;
           string server_ip_address;
           int server_port;

           if (ParseCommandLine(argc, argv, RootPath, server_ip_address, server_port))
           {
               // define server endpoint ip address and port for listening
               EndPoint FileServerEP(server_ip_address, server_port);

               // define instance of the receiver (server host)
               ReceiverSocketOptions socket_options;
               Receiver receiver(FileServerEP, &socket_options);

               // define an instance of (custom) server processing lient handler)
               ServerCommandHandler server_cmd_handler(FileServerEP, RootPath);

               // register the custom client handler with receiver instance
               receiver.RegisterClientHandler(&server_cmd_handler);

               // start the server listening thread
               receiver.Start();

               std::cout << "CSE 384 File Service listening on: " << FileServerEP << std::endl;
               //std::cout << "Using File Storage Path: " << Path::getFullFileSpec(RootPath) << std::endl;
               std::cout << "Press <ENTER> to shutdown" << std::endl;
               std::cin.get();

               //shut done the listener and quit
               receiver.Stop();
           }
       }
       catch (std::exception &ex)
       {
           std::cerr << "Error starting the service: " << ex.what() << std::endl;
       }

       return 0;
   }