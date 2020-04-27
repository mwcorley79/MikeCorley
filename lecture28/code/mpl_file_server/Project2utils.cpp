#include "Project2utils.h"
#include <fstream>

namespace CSE384
{
  // intentionally global for synchronizing cout
  std::mutex ioLock;

  int GetFileSize(const std::string& filename)
  {
      std::ifstream sf;
      try
      {
        sf.open(filename, std::ios::in | std::ios::binary);
        if(!sf.is_open())
           return -1;
	
        // get the length of the input file
        sf.seekg (0, sf.end);
        int length = sf.tellg();
        sf.close();
        return length;
      }
      catch(...)
      {}

      return -1;
  }

  std::vector<std::string> TokenizeString(const std::string& str, char delim)
  {
    std::vector<std::string> toks;
    std::stringstream ss(str);
    std::string token;

    while(std::getline(ss, token, delim))
    {
        toks.push_back(token);
    }

    return toks;
  }

  // send multiple (vector of Messages) requests to the server
  bool SendServerRequest(const EndPoint& server_ep, const EndPoint& this_client_ep,  
                       const std::vector<Message>& msgList, int connect_attempts)
  {
    try
    {
        if (server_ep.IsValid())
        {
            // instantiate a sender
            SenderSocketOptions options;
            Sender sender(&options);
        
            // connect to the client peer
            if (sender.ConnectPersist(server_ep, connect_attempts, 1, 0) < connect_attempts)
            {
                // start the send thread
                sender.Start();
                
                if(sender.IsSending())
                { 
                   // need to send server the CONNECT message, so server can reply to us
                   sender.PostMessage(Message(this_client_ep.ToString(), FileServerMessageType::CONNECT_REQUEST));
                  
                   // post all of the message into the blocking queue
                   for (int i = 0; i < msgList.size(); ++i)
                   {
                      sender.PostMessage(msgList[i]);
                   }
    
                   // all done sending, so shutdown the send thread
                   sender.Stop();
                   sender.Close();
                   return true;
                }
            }
        }
    }
    catch (std::exception &ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    return false;
  }

  // send single request message to client
  bool SendServerRequest(const EndPoint& server_ep, const EndPoint& this_client_ep, 
                        const Message& msg, int connect_attempts)
  {
     return SendServerRequest(server_ep, this_client_ep, std::vector<Message> { msg }, connect_attempts);  
  }

  // send single response message to client
  bool SendClientResponse(const EndPoint &client_ep, const Message &msg, int connect_attempts)
  {
      return SendClientResponse(client_ep, std::vector<Message>{msg}, connect_attempts);
  }

  // send multiple (vector of Messages) response to the client
  bool SendClientResponse(const EndPoint &client_ep, const std::vector<Message> &msgList, int connect_attempts)
  {
      try
      {
          if (client_ep.IsValid())
          {
              // instantiate a sender
              SenderSocketOptions sock_opts;
              Sender sender(&sock_opts);

              // connect to the client peer
              if (sender.ConnectPersist(client_ep, connect_attempts, 1, 0) < connect_attempts)
              {
                  // start the send thread
                  sender.Start();
                  if (sender.IsSending())
                  {
                      // post all of the message into the blocking queue
                      for (int i = 0; i < msgList.size(); ++i)
                          sender.PostMessage(msgList[i]);

                      // all done sending, so shutdown the send thread
                      sender.Stop();
                      sender.Close();
                      return true;
                  }
              }
          }
          else
          {
              std::cerr << "client return endpoint unknown??" << std::endl;
          }
      }
      catch (std::exception &ex)
      {
          std::cerr << ex.what() << std::endl;
      }
      return false;
  }
}