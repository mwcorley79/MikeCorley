/*
 * File:   readTextFile.cpp
 * Author: Mike
 * Description: Read/write text file line by line and parse
 *
 * Compiler build command: g++ -o readTextFileCPPprog ./readTextFile.cpp 
 * Run command           : ./readTextFileCPPprog
*/
 
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <cstdlib>
#include <time.h>

using namespace std;

void WriteTextFile(const std::string& filename)
{
   ofstream outs(filename); 
   string names[] = { "Mike", "Joe", "Jim", "Wayne", "Joy", "Carla" };
   
   if(outs.is_open())
   {
     for(int i = 0; i < 10; ++i)
     {
        outs << names[(rand() % 6)] << "," << i+1 << "," << (rand() % 100) << std::endl;     
     }
   }

   outs.close();
}

vector<string> ParseEntry(const std::string& str, char delim)
{
    vector<string> toks;
    std::stringstream ss(str);
    std::string token;

    while(getline(ss, token, delim)) 
    {
        toks.push_back(token);
    }

    return toks;
}

int main() 
{
  string filename = "test.txt";
  string str;
  ifstream myfile(filename);
  if (!myfile.is_open())
  {
     cerr << "Could not open file: "<< filename << "\n";
     return 1;
  }
  
  // generate pseudo-random number
  srand(time(NULL));   // seed srand
  
  /* write a Text file with the following format:  Name,Id,age */
  WriteTextFile(filename);

  //read file line by line
  while(getline (myfile, str))
  {
     cout << "File entry:-> " << str << '\n';
    
     // parse file entry
     vector<string> toks = ParseEntry(str, ','); 
     cout << toks[0] << "\t" << stoi(toks[1]) << "\t" << stoi(toks[2]) << "\n"; 
  } 
    
  myfile.close();
  return 0;
}
