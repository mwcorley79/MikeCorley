///////////////////////////////////////////////////////////////////////
// serialize.cpp - provides example use of serialization             //
// ver 1.0                                                           //
// Language:    g++, ver 7.4                                         //
// Platform:    Dell Precison m7720, Linux Mint 19.1                 //
// Application: Demonstrate serialization, CSE 384                   //
// Author:      Mike Corley, CST 4-232, Syracuse University          //
//              (315) XXX-XXXX , mwcorley@syr.edu                    //
///////////////////////////////////////////////////////////////////////

template <typename T>
std::string convert<T>::ToString(const T& t)
{
   std::ostringstream out;
   out << t;
   return out.str();
}

template <typename T>
T convert<T>::FromString(const std::string &s)
{
  T t;
  std::istringstream in(s);
  in >> t;
  return t;
}





