/////////////////////////////////////////////////////////////////////////////
// Sender.h -   multithreaded (concurrent) TCP client                      //
//                framework protoype                                       //
// ver 1.0                                                                 //
// Language:    Standard C++ (gcc/g++ 7.4)                                 //
// Platform:    Dell Precision M7720, Linux Mint 19.3 (64-bit)             //
// Application: CSE 384, MPL, Prohect 2 helpers                            //
// Author:      Mike Corley, Syracuse University                           //
//              mwcorley@syr.edu                                           //
/////////////////////////////////////////////////////////////////////////////
/*
 * Package Operations:
 * ===================
 *  This package serves as the basis for efficient light-weight customizable TCP
 *  message passing client server framework.
 *  The intent is to provide the basic facilities enabling the executive (client)
 *  to build custom/resuable TCP message passing clients 
 *  This package assumes the target operating system is POSIX standard compliant 
 *  i.e. standard I/O, sockets (IPv4 - old interface) I/O, and Threading model.   
 
 * Required Files:
 * ==============
 * Sender.h, MPUtils.h,  Sender.cpp, MPUtils.cpp
 *
 * USAGE: See Sender Test stub
 * 
 * Build Process: (for test stub)
 * =============
 * Linux:  g++ -DTEST_SENDER -o  SenderTest Sender.cpp  Message.cpp  MPUtils.cpp -lpthread 
 *
 * Maintenance:
 * ===========
 * ver 1.0 : 29 March 2019
 * -- first release 
*/

#ifndef _Sender_h_
#define _Sender_h_

#include "Cpp11-BlockingQueue.h"
#include "MPUtils.h"
#include "Message.h"

#include <cstring>
#include <thread>
#include <atomic>

namespace CSE384
{
  class Sender
  {
    public: 
     Sender(SocketConfiguration* sc = nullptr);
     virtual ~Sender();
     void Start();
     void Stop();
     bool Close();
     bool IsConnected() const;
     bool IsSending() const;
     void PostMessage(const Message& m);
     bool Connect(const EndPoint& ep);
     int  ConnectPersist(const EndPoint& ep,  unsigned retries, 
                         unsigned wtime_secs, unsigned vlevel);   

     // prevent users from making copies of Sender objects  
     Sender(const Sender&) = delete;
     Sender& operator=(Sender&) = delete;

    private:
        int sockfd;
        SocketConfiguration*  sc_;
        struct sockaddr_in dest;
        std::atomic<bool> isSending_;
        BlockingQueue<Message> send_bq_;
        std::thread  send_thread_;

        // can redefine socket level processing (if you wish)
        virtual void SendSocketMessage(const Message& msg);
        virtual void sendProc();  

        void IsSending(bool issending);
        void Disconnect();        
  };

  inline void Sender::IsSending(bool issending)
  {
     isSending_.store(issending);
  }

  inline bool Sender::IsSending() const
  {
    return isSending_.load(); 
  }

  inline bool Sender::IsConnected() const
  {
     return (sockfd != -1);
  }
}; 

#endif 
