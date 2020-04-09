#include "SyncOut.h"
//----< globally available output stream >---------------------------

namespace MPL
{
  std::mutex syncOut::_l;
  syncOut sout(std::cout);  // globally available sout object
};                         // mimics cout



#ifdef TEST_SYNCOUT
#include <thread>

void ThreadPrintFuncNotSynced(const std::string& name)
{
    for(int i = 0; i < 100; ++i)
    {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::cout << "Hello, this is message " << name <<  i+1 << std::endl;
    }
}


void ThreadPrintSynced()
{
    for(int i = 0; i < 100; ++i)
    {
      MPL::sout << "Hello, this is message: " << i+1 << MPL::endl;
    }
}



int main()
{
   std::thread thrd1(ThreadPrintFuncNotSynced,"Mike");
   std::thread thrd2(ThreadPrintFuncNotSynced,"Jim");
   std::thread thrd3(ThreadPrintFuncNotSynced,"Cully");

   for(int i = 0; i < 15; i++)
      std::cout << "This is message from unsynched main: " << i+1 << std::endl;
   
   thrd1.join();
   thrd2.join();
   thrd3.join();
    
   /* ::getchar();


  std::cout << "This is a console out (but is unsyncronized )" 
            << std::endl;

  MPL::sout << "This is syncronized out (but isstill unsynchronized...hint use \"locked\" "
            << MPL::endl;

  MPL::sout << MPL::locked << "This is syncronized out (and synchronized...but notice the use of \"lock\" and \"unlock\"" 
            << MPL::endl << MPL::unlocked;

  MPL::sout.operator << (MPL::locked).operator << ("Final sync out test").operator << (MPL::endl).operator << (MPL::unlocked); 
 */

  return 0;
}
#endif 