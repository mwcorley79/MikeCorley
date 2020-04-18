//////////////////////////////////////////////////////////////////////////////
// File:        cse384_client_executive.cpp                                 //
// Description: this file implements a basic a file server prototype        //
//              which is the basis for Project 2                            //
// Compiler Command: ./buildClient                                          //
// Run Command     : ./client ./clientFiles/ 127.0.0.1 6060 127.0.0.1 5050  //
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <vector>
#include "mpl.h"
#include "FileSystem.h"
#include "Project2utils.h"

using namespace CSE384;
using namespace FileSystem;
using namespace std;


bool ParseCommandLine(int argc, char *argv[],
                      string &RootPath,
                      string &server_ip,
                      int &server_port,
                      string &client_ip,
                      int &client_port)
{
    if (argc != 6)
    {
        std::cerr << "Usage: Root-Filpath  fileserver-ip-address  file-server-port   my-ip   my-port" << std::endl;
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

    // get the user specified IP address and service port pf the client
    client_ip = std::string(argv[4]);
    client_port = std::stoi(argv[5]);

    return true;
}

void DisplayMenu()
{
    // synchronize the console printing 
    // std::lock_guard<std::mutex> l(ioLock);
  
    cout << std::endl;
    cout << "**********************************************" << std::endl;
    cout << "*** CSE 384 File Server Client Menu ver .9 ***" << std::endl;
    cout << "**********************************************" << std::endl;
    cout << " R - List remote files on the server         *" << std::endl;
    cout << " L - List local files on client              *" << std::endl;        
    cout << " D - Download a file from the server         *" << std::endl;
    cout << " Q - Quit                                    *" << std::endl;
    cout <<"***********************************************" << std::endl;
    cout <<"choice:" << std::endl;
}

// this is handler for the client to process server responses  
class FileClientListener : public ClientHandler
{
   public:  
    FileClientListener(const std::string& root_path): root_path_(root_path), 
                                                      filename(""), 
                                                      created(false)
    {}

    // this is a creational function: you must implement it
    // the Receiver creates an instance of this class (it's how the server polymorphism works)
    virtual ClientHandler *Clone()
    {
        return new FileClientListener(root_path_);
    }

    // receieve and tokenize filelist response from the server 
    void DoProcessFileListResponse(Message& msg)
    {
        // synchronize the console printing 
        // std::lock_guard<std::mutex> l(ioLock);      
        std::vector<std::string> files = TokenizeString(msg.ToString(), ':');
        for(int i = 0; i < files.size(); ++i)
        {
            std::cout <<  files[i] << std::endl;
        }
    }

    // receive file from the server
    void DoProcessFileReceiveRequest(Message& msg)
    {
       switch(msg.GetType())
       {
          // message to create the file
          case FileServerMessageType::SEND_FILE_CREATE:
          {
             filename = root_path_ + msg.ToString();
             df.open(filename, std::ios::out | std::ios::binary);
             created = df.is_open();
             if(created)
               std::cout << "Downloading local file: " << filename << std::endl;
             else
             {
                std::cout << "Error creating file: " << filename << std::endl;  
             }
          }
          break;

          // message to write a single block to file strean
          case FileServerMessageType::SEND_FILE_BLOCK:
          {
            if(created)
            {
              df.write(msg.GetData(), msg.Length());
              std::cout << "wrote file block of size " << msg.Length() << std::endl;
            }
          }  
          break;
        
          // message to close the file streeam 
          case FileServerMessageType::SEND_FILE_CLOSE:
          {
            if(created)
            {
             std::cout << "Successfully Downloaded file from server: " << filename << std::endl;
             df.close();
            }
          }
          break;
       };
    }

    void AppProc()
    {
        // while there are messages in the blocking queue, and you have seen the disconnect
        // message, pull messages out and display them.
        bool done = false;
        do
        {
            Message msg = GetMessage();
            switch (msg.GetType())
            {
               case MessageType::DISCONNECT:
                 done = true;
               break;

               case FileServerMessageType::CONNECT_REQUEST:
                 //std::cout << "Connect acknowledgement from server: " << EndPoint(msg.ToString()) << std::endl;
               break;

               case FileServerMessageType::FILELIST_REQUEST: 
                 std::cout << "Files on Server:" << std::endl;
                 DoProcessFileListResponse(msg);
                 DisplayMenu();    
               break; 

               case FileServerMessageType::SEND_FILE_CREATE:
               case FileServerMessageType::SEND_FILE_BLOCK:
               case FileServerMessageType::SEND_FILE_CLOSE:
                  DoProcessFileReceiveRequest(msg); 
                  if(msg.GetType() == (int) FileServerMessageType::SEND_FILE_CLOSE)
                     DisplayMenu(); 
               break;
               
               case FileServerMessageType::ERROR_RESPONSE:
                  std::cout << msg.ToString() << std::endl;
                  DisplayMenu();
               break;
            };  
        } 
        while (!done);
    }
    private:
       string root_path_;
       std::ofstream df;
       string filename;
       bool created;
};


int main(int argc, char *argv[])
{
    try
    {
        string RootPath;
        string server_ip_address;
        int server_port;
        string client_ip_address;
        int client_port;

        if (!ParseCommandLine(argc, argv, RootPath, server_ip_address, server_port,
                              client_ip_address, client_port))
        {
            return 1;
        }

        // **** setup the client listener  ***    
        // server endpoint ip address and port to connect
        EndPoint serverEP(server_ip_address, server_port);

        //client endpoint for getting server response
        EndPoint clientEP(client_ip_address, client_port);

        // define an instance of (custom) server processing lient handler)
        FileClientListener listenerHandler(RootPath);   
        ReceiverSocketOptions options;
        Receiver recv(clientEP, &options);

        // register the custom client handler with receiver instance
        recv.RegisterClientHandler(&listenerHandler);

        // start the server listening thread
        recv.Start();
      
        DisplayMenu();
        char ch;
        std::cin >> ch;
        ch = std::tolower(ch);
    
        do
        {  
            if(ch == 'q')
              break; // exit the menu and shutdown

            switch (ch)
            {
              case 'r':
              {
                  Message msg(nullptr, 0, FileServerMessageType::FILELIST_REQUEST);
                  if(!SendServerRequest(serverEP, clientEP, msg))
                     std::cerr << " Problem Connecting to server " << serverEP << std::endl;   
              }
              break;

              case 'l':
              {
                 std:cout << "Local files:" << std::endl;
                 std::vector<std::string> files = Directory::getFiles(RootPath);
                 for(int i = 0; i < files.size(); ++i)
                 {
                     int fsize = GetFileSize(RootPath + files[i]);
                     std::cout << files[i] + " - " + std::to_string(fsize) + " bytes" << std::endl;
                 }
                 DisplayMenu();
              }
              break;

              case 'd':
              {
                  std::cout << "Enter Filename: " << std::endl;
                  string filename;
                  cin >> filename; 
                  
                  int block_size;
                  std::cout << "Enter Block size: " <<  std::endl;
                  std::cin >> block_size;
                  if(std::cin.fail())
                  {
                    std::cin.clear();
                    block_size = 4096;
                    std::cout << "Bad block size! using size: " << block_size << std::endl;
                  }

                  std::string msgContent = filename + ":" + std::to_string(block_size);
                  Message msg(msgContent, FileServerMessageType::FILE_REQUEST);
                  if(!SendServerRequest(serverEP, clientEP, msg))
                     std::cerr << " Problem Connecting to server " << serverEP << std::endl;
              }
              break;
            };
            std::cin >> ch;
            ch = std::tolower(ch);
        } while (true);
    
        recv.Stop();
    }
    catch (std::exception &ex)      
    {
        std::cerr << ex.what() << std::endl;   
    }

    return 0;
}