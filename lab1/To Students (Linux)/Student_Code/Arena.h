#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctype.h>
#include "ArenaInterface.h"
using namespace std;

class Arena: public ArenaInterface
{
  public:
    Arena()
    {
//      cout << "creating new arena" << endl;
    }
    ~Arena();
    bool addFighter(string info);
    bool removeFighter(string name);
    FighterInterface* getFighter(string name);
    int getSize();
    static const char* getToken(const char *p,string& buf);
    static const char* getIntToken(const char *p,int& num);
  protected:
    map <string, FighterInterface*> fighter_map;
    
};