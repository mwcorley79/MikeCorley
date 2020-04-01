///////////////////////////////////////////////////////////////////////////////////
// Name        : ThreadDemo2.cpp
// Author      : Mike Corley
// Version     : 1.0
// Description : three threads share (read/write) data
//============================================================================
// Compiler command: g++ -o DemoThreadDemo2 ThreadDemo2.cpp  -lpthread
// Run Command:  ./DemoThreadDemo2 
///////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <string>
#include <cstdlib>
using namespace std;

class Mutex
{
   public:
     Mutex();
     void lock();
     void unlock();
     ~Mutex();
    
     // explicitly prevent copy and assignment 
     Mutex(const Mutex&) = delete;
     Mutex& operator=(Mutex&) = delete;

   private:
      pthread_mutex_t mutex;
};

inline Mutex::Mutex()
{
  pthread_mutex_init(&mutex, NULL);
}

inline void Mutex::lock()
{
  pthread_mutex_lock(&mutex);
}

inline void Mutex::unlock()
{
  pthread_mutex_unlock(&mutex);
}

inline Mutex::~Mutex()
{
  pthread_mutex_destroy(&mutex);
}


typedef enum {odd, even} Type;
struct ARGS
{
  int val; 
  string* msg;
};  


// mutex is needed to keep parent and child output stream
// from mingling
Mutex m;

//----< function defining child thread operation >---------------------
void* thrd_funct(void* arg)
{
  ARGS* args = (ARGS*) arg;
  int val = args->val;
  
  for(int i = 0; i < 50; ++i)
  {
    int n = (rand() % 10) + 1;
     sleep(n);
     //critical section 
     m.lock();
     *(args->msg) += to_string(args->val);
     std::cout << "Thread " 
               << args->val << ":-> " << *(args->msg) 
               << std::endl;
     m.unlock();
     
     //pthread_yield();
  }
  return ((void*)0);
}


//----< thread demo entry >--------------------------------------------
int main()
{
  cout << "\n  Thread Demo";
  cout << "\n =============\n";
  string msg;
  pthread_t thread_handles[3];
  
  ARGS args;
  args.msg = &msg;
  args.val = 1;
  
  int err = pthread_create(&thread_handles[0], NULL, thrd_funct, &args);
  if(err != 0)
  {
    cout << "\n  can't create child thread\n\n";
    return 0;
  }

  
  ARGS args2;
  args2.msg = &msg;
  args2.val = 2;

  pthread_t ntid2;
  int err2 = pthread_create(&thread_handles[1], NULL, thrd_funct, &args2);
  if(err2 != 0)
  {
    cout << "\n  can't create child thread\n\n";
    return 0;
  }

    for(int i = 0; i < 5; ++i)
    {
       m.unlock();
       std::cout <<"Thread M:-> " << msg << std::endl;
       sleep(5);
       m.unlock();
    }
    std::cout << "okay thread M says bye " << std::endl; 
  
  pthread_join(thread_handles[0], NULL);
  pthread_join(thread_handles[1], NULL);

  //std::cout << msg << std::endl;
  cout << "\n  parent exit\n\n";
  return 0;
}
