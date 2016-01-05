#include "Arena.h"
#include "fighter.h"

int Arena::getSize()
{
  return fighter_map.size();
}

Arena::~Arena()
{
  map<string, FighterInterface*>::iterator it;
  for (it = fighter_map.begin(); it != fighter_map.end(); ++it)
  {
    delete it->second;
  }
}

bool Arena::addFighter(string info)
{
//  cout << "Addfighter:" << info << endl;
  string name;
  string type_str;
  Fighter* newFighter = 0;
  const char *p = info.c_str();
  p = getToken(p,name);
  
  if (!*p) return false;
  
  p = getToken(p,type_str);
  
  if (!*p || type_str.length() != 1) return false;
  
  char type = type_str[0];
  
  if (type == 'R') newFighter = new Robot();
  else if (type == 'C') newFighter = new Cleric();
  else if (type == 'A') newFighter = new Archer();
  else return false;

  if (newFighter->initFighter(p, name))
  {
    newFighter->typeInit();
    if (fighter_map.find(name) != fighter_map.end())
    {
     // cout << "Not Adding FIghter: " << name << endl;
      delete newFighter;
      return false;
    }
   // cout << "adding FIghter: " << name << " with adr " << newFighter << endl;
    fighter_map[name] = newFighter;
    return true;
  }
  else 
  {
    //cout << "Not Adding FIghter: " << name << " because of failed parse" << endl;
    delete newFighter;
    return false;
  }
}

bool Arena::removeFighter(string name)
{
  //cout << "tried to remove " << name << endl;
  if(fighter_map.find(name) == fighter_map.end()) return false; 
  else 
  {
    delete fighter_map[name];
    fighter_map.erase(name);
  }
  return true; 
}

const char* Arena::getToken(const char* p,string& buf)
{
  while (*p && *p != ' ')
  {
    buf += *p++;
  }
  p++;
  return p;
}

const char* Arena::getIntToken(const char *p,int& num)
{
  num = 0;
  
  while (*p && *p != ' ')
  {
    if (!isdigit(*p)) return 0;
    num = 10*num + (*p - '0');
    p++;
  }
  if(*p) p++;
  return p;
}

FighterInterface* Arena::getFighter(string name)
{
  if (fighter_map.find(name) == fighter_map.end()) return NULL;
  else return fighter_map[name];
}
