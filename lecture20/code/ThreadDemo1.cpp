///////////////////////////////////////////////////////////////////////////////////
// Name        : ThreadDemo1.cpp
// Author      : Jim Fawcett
// Version     : 1.0
// Description : Simple demo of threads and locks
//============================================================================
// Compiler command: g++ -o DemoThreadDemo1 ThreadDemo1.cpp  -lpthread
// Run Command:  ./DemoThreadDemo1 
///////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <unistd.h>
#include <pthread.h>
using namespace std;

// mutex is needed to keep parent and child output stream
// from mingling

pthread_mutex_t mutex;  // todo: make global lock with static mutex

//----< show process and thread ids with message >---------------------

void showIds(const char* s)
{
  pid_t pid = getpid();
  pthread_t tid = pthread_self();
  cout << "\n  " << s << " pid " << (unsigned int)pid
       << ", tid "  << (unsigned int)tid;
}
//----< function defining child thread operation >---------------------

void* thrd_funct(void* arg)
{
  pthread_mutex_lock(&mutex);
  showIds("child thread: ");
  cout << "\n  child exit";
  pthread_mutex_unlock(&mutex);
  return ((void*)0);
}
//----< thread demo entry >--------------------------------------------

int main()
{
  pthread_mutex_init(&mutex, NULL);

  cout << "\n  Thread Demo";
  cout << "\n =============\n";

  pthread_t ntid;
  int err = pthread_create(&ntid, NULL, thrd_funct, NULL);
  if(err != 0)
  {
    cout << "\n  can't create child thread\n\n";
    return 0;
  }
  pthread_mutex_lock(&mutex);
  showIds("main thread: ");
  pthread_mutex_unlock(&mutex);
  pthread_join(ntid, NULL);

  pthread_mutex_destroy(&mutex);
  cout << "\n  parent exit\n\n";
  return 0;
}
