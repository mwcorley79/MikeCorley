#include "StringConversion.h"
#include "Nav.h"
#include "Fileinfo.h"

using namespace std;
using namespace Win32Tools;

void main(int argc, char *argv[]) {

  cout << "\n  Testing Directory Navigator "
       << "\n =============================\n";

  if(argc == 1) {
    cout << "\n  please enter starting path\n";
    return;
  }

  try {
// create default processing object and start navigation

  cout << "\n  testing default dir/file processing: "
       << "\n --------------------------------------\n";

  stdOut << TEXT("\n  starting path = ") << fileInfo::getPath() << TEXT("\n");

  defProc dp;
  navig nav(dp);
  nav.walk(Convert::ToStdStr(argv[argc-1]),TEXT("*.*"));

  stdOut << TEXT("\n  ending path = ") << fileInfo::getPath() << TEXT("\n\n");

// User defined processing definded here.  Note that
// local classes can be defined as long as all members
// are inline.  Otherwise, just declare and define above
// main.
//
// These do nothing but prepend each output with some
// "-" characters to show that user defined processing
// is actually being used.  In a real application user 
// defined processing will certainly be quite different
// from the default
//
  class userProc : public defProc {

  public:
    virtual void fileProc(const fileInfo &fi) {
      fileInfo newfi = fi;
      newfi.showDate(false);
      newfi.showData(stdOut); 
    }
    virtual void dirsProc(const stdStr &dir) {
      stdOut << TEXT("\n  ") << dir.c_str() << endl;
    }
  };

// restart with user defined processing

  cout << "\n  testing modified dir/file processing: "
       << "\n ---------------------------------------\n";

  stdOut << TEXT("\n  starting path = ") << fileInfo::getPath() << TEXT("\n");

  userProc udp;
  navig newNav(udp);
  newNav.walk(Convert::ToStdStr(argv[argc-1]),Convert::ToStdStr("*.*"));  // change
  cout << "\n  ending path = " << Convert::ToString(newNav.getPath());    // change
  cout << "\n\n";
  }
  catch(std::exception& ex)
  {
    cout << ex.what();
  }
}
