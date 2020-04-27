/* 
 * File:   SyncOut.h
 * Author: Mike C.
 * /////////////////////////////////////////////////////////////////////
   // port of Dr. Fawcett's syncOut class to use CPP 11 std::mutex locks
 * Created on April 5, 2015, 10:10 PM
 */

#ifndef SYNCOUT_H
#define	SYNCOUT_H

#include <iostream>
#include <mutex>

namespace MPL {

class syncOut
{
  public:
    syncOut(std::ostream& out);
    
    template <typename T>
    syncOut& operator << (const T& t);
    
    syncOut& operator << (syncOut& (*op) (syncOut&));
    
    template <typename T>
    void operator()(const T& t);
    
    void flush();
    
    friend syncOut& locked(syncOut& so);
    friend syncOut& unlocked(syncOut& so);
    
  private:
     static std::mutex _l;
     std::ostream& _out;
};

//----< constructor >------------------------------------------------
inline syncOut::syncOut(std::ostream& out) : _out(out) 
{}


//----< insertion >--------------------------------------------------
template <typename T>
syncOut& syncOut::operator << (const T& t)
{
  _out << t;
  _out.flush();
  return *this;
}

//----< insertion >--------------------------------------------------
inline syncOut& syncOut::operator << (syncOut& (*op)(syncOut&))
{
  return (*op)(*this);
}

//----< functor >----------------------------------------------------
template <typename T>
void syncOut::operator()(const T& t)
{
  _l.lock();
  _out << t;
  _out.flush();
  _l.unlock();
}

//----< flush output stream >----------------------------------------
inline void syncOut::flush() { _out.flush(); }


//----< lock manipulator >-------------------------------------------
inline syncOut& locked(syncOut& so)
{
  so._l.lock();
  return so;
}

//----< unlock manipulator >-----------------------------------------
inline syncOut& unlocked(syncOut& so)
{
  so._l.unlock();
  return so;
}

//----< unlock manipulator >-----------------------------------------
inline syncOut& endl(syncOut& so)
{
  so << "\n";
  return so;
}

extern syncOut sout;
}
#endif	/* SYNCOUT_H */

