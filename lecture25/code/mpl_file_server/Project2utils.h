#ifndef _PROJ2_UTILS_H
#define _PROJ2_UTILS_H

#include <mutex>
#include <vector>
#include <string>

#include "mpl.h"

namespace CSE384
{

  using FileServerMessageType = enum { CONNECT_REQUEST = 1, FILELIST_REQUEST = 2, SEND_FILE_CREATE = 3,
                                       SEND_FILE_BLOCK = 4, SEND_FILE_CLOSE = 5, FILE_REQUEST=6, ERROR_RESPONSE=7 };

  // setup socket options 
  class ReceiverSocketOptions : public CSE384::SocketConfiguration
  {
   public:
     virtual int SetSocketOptions(int sock_fd)
     {
        int optval = 1;
        return setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
     }
  };

  class SenderSocketOptions : public CSE384::SocketConfiguration
  {
    public:
     virtual int SetSocketOptions(int sock_fd)
     {
        int optval = 1;
        return setsockopt(sock_fd, SOL_SOCKET, SO_KEEPALIVE, (char *)&optval, sizeof(optval));
     }
  };

  extern std::mutex ioLock; // intentionally global for synchronizing cout
  
  extern std::vector<std::string> TokenizeString(const std::string& str, char delim);

  // send multiple (vector of Messages) requests to the server
  extern bool SendServerRequest(const EndPoint& server_ep, const EndPoint& this_client_ep,  
                                const std::vector<Message>& msgList, int connect_attempts = 2);

  // send a single message request to the server
  extern bool SendServerRequest(const EndPoint& server_ep, const EndPoint& this_client_ep, 
                                const Message& msg, int connect_attempts = 2);

  // send single response message to client
  extern bool SendClientResponse(const EndPoint &client_ep, const Message &msg, 
                                 int connect_attempts=2);
  
  // send multiple (vector of Messages) response to the client
  extern bool SendClientResponse(const EndPoint &client_ep, const std::vector<Message> &msgList, 
                                 int connect_attempts=2);

  extern int GetFileSize(const std::string& filename);
                                 
}
#endif 