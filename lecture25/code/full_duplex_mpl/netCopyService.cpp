#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sys/stat.h>

#include "mpl.h"

bool ParseCommandLine(int argc, char *argv[],
                      std::string &RootPath,
                      std::string &server_ip,
                      int& server_port)
{
    if (argc != 4)
    {
        std::cerr << "Usage: Root-Filpath  ip-address  port" << std::endl;
        return false;
    }

    // get the user specified file storage path for use by the server
    RootPath = argv[1];
    
    struct stat info;
    // check that the storage path exists
    if( stat(RootPath.c_str(), &info ) == 0)
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
        return false;
    }

    // get the user specified server IP address and service port
    server_ip = std::string(argv[2]);
    server_port = std::stoi(argv[3]);

    return true;
}


using FileTransferMessageType = enum { FILE_OPEN_REQUEST=0x0A ,
                                       FILE_WRITE_BLOCK_REQUEST=0x0B,
                                       FILE_CLOSE_REQUEST=0x0C 
                                     };

// this is an example of custom server processing class
class FileTransferHandler : public CSE384::ClientHandler
{
  public:
  
     FileTransferHandler(const std::string& root_path): filename(""),
                                                        rootpath(root_path),
                                                        created(false),
                                                        block_count(0)
     {}

    // this is a creational function: you must implement it
    // the Receiver creates an instance of this class (it's how the server polymorphism works)
    virtual ClientHandler *Clone()
    {
       return new FileTransferHandler(rootpath);
    }

    void DoProcessFileReceiveRequest(CSE384::Message &msg)
    {
      switch (msg.GetType())
      {
        case FileTransferMessageType::FILE_OPEN_REQUEST:
        {
          filename = msg.ToString();
          df.open(rootpath + filename, std::ios::out | std::ios::binary);
          created = df.is_open();
          if (created)
          {
             std::string outPutMsg = "Uploading file: " + msg.ToString();
             std::cout << "Uploading file: " + msg.ToString() << std::endl;
             PostMessage(CSE384::Message(std::string(" Reply from server: received request to upload file: " + filename)));
          }
          else
          {
             PostMessage(CSE384::Message(std::string(" Reply from server: error on request to upload file: " + filename)));
             std::cout << "Error creating file: " << filename << std::endl;
          }
        }
        break;

        case FileTransferMessageType::FILE_WRITE_BLOCK_REQUEST:
        {
          if (created)
          {
             block_count++;
             df.write(msg.GetData(), msg.Length());
             std::cout << "wrote file block #: " << block_count << " of size " << msg.Length() << std::endl;
             CSE384::Message replyMsg(std::string("Reply from server: wrote file block " + 
                                                  std::to_string(block_count) + " of size: " + 
                                                  std::to_string(msg.Length())));
             PostMessage(replyMsg);
          }
        }
        break;

        case FileTransferMessageType::FILE_CLOSE_REQUEST:
        {
          if (created)
          {
            std::cout << "Succesfully Uplaoded file from client: " << filename << std::endl;
            PostMessage(CSE384::Message(std::string("Server Acknowledgement: " + filename + " created successfully")));
            df.close();
          }
       }
       break;
    };
  }

  // this is where you define the custom server processing: you must implement it
  virtual void AppProc()
  {
      CSE384::Message msg;
      while ((msg = GetMessage()).GetType() != CSE384::MessageType::DISCONNECT)
      {
         DoProcessFileReceiveRequest(msg);
      }
  }

  private:
    std::string filename;
    std::string rootpath;
    std::ofstream df;
    bool created;
    int block_count;
};

int main(int argc, char *argv[])
{
   std::string rooted_path;
   std::string ip_address;
   int port;

   if (ParseCommandLine(argc, argv, rooted_path, ip_address, port))
   {
      // define server endpoint ip address and port for listening
      CSE384::EndPoint serverEP(ip_address, port);

      // define instance of custom server processing (ccustom client handler)
      FileTransferHandler th(rooted_path);

      // define instance of the receiver (server host)
      CSE384::Receiver receiver(serverEP);

      // register the custom client handler with receiver instance
      receiver.RegisterClientHandler(&th);

      // start the server listening thread
      receiver.Start();
      std::cout << "Server listening on: " << serverEP << std::endl;
      std::cout << "Press any key to quit" << std::endl;
      std::cin.get();

      //shut it listener and quit
      receiver.Stop();
   }

   return 0;
}