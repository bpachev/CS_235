#include "fighter.h"
#include "Arena.h"
#include <stdlib.h>
#include <sstream>
#include <math.h>

string Fighter::getName()
{
  return name;
}

int Fighter::getMaximumHP()
{
  return maximumHP;
}

int Fighter::getCurrentHP()
{
  return currentHP;
}

int Fighter::getStrength()
{
  //cout << "getting strength of " << name << strength << endl;
  return strength;
}

int Fighter::getSpeed()
{
  //cout << "getting speed of " << name << endl;
  return speed;
}

int Fighter::getMagic()
{
  //cout << "getting magic of " << name << endl;
  return magic;
}



void Fighter::takeDamage(int damage_given)
{
  //cout << name << " si Taking damage of " << damage_given << endl; 
  int speed_reduction = speed/4;
  if(speed_reduction>=damage_given) currentHP -= 1;
  else currentHP = currentHP - damage_given + speed_reduction;
}


void Fighter::regenerate()
{
  //cout << "regenerating fighter: " << name << endl;
  HP_INC(strength/6);
}

int Fighter::HP_INC(int HPinc)
{
  if(HPinc<1) currentHP += 1;
  else currentHP += HPinc;
  if(currentHP > maximumHP) currentHP = maximumHP;
}


#define DO_TOKEN_MAGIC(var) p = Arena::getIntToken(p, var); if (!p || !*p) return false; if (var<=0) return false;
#define DO_TOKEN_LAST_MAGIC(var) p = Arena::getIntToken(p, var); if (!p || *p) return false; if (var<=0) return false; 


bool Fighter::initFighter(const char* p, const string& fname)
{
  name = fname; 
  DO_TOKEN_MAGIC(maximumHP)
  currentHP = maximumHP;
  DO_TOKEN_MAGIC(strength)
  DO_TOKEN_MAGIC(speed)
  DO_TOKEN_LAST_MAGIC(magic)
  return true;
}

int Cleric::getMana()
{
  return mana;
}

void Cleric::reset()
{
  currentHP = maximumHP;
  mana = max_mana;
}

int Cleric::getDamage()
{
  return magic;
}

void Cleric::regenerate()
{
  HP_INC(strength/6);
  int manaInc = magic/5;
  if(manaInc) mana += manaInc;
  else mana++;
  if(mana>max_mana) mana = max_mana;
}

void Cleric::typeInit()
{
  max_mana = 5*magic;
  mana = max_mana;
}

bool Cleric::useAbility()
{
  if(mana>=CLERIC_ABILITY_COST) 
  {
    HP_INC(magic/3);
    mana -= CLERIC_ABILITY_COST;
    return true;
  }
  else return false;
}

bool Archer::useAbility()
{
  speed += 1;
  return true;
}

void Archer::reset()
{
  currentHP = maximumHP;
  speed = orig_speed;
}

int Archer::getDamage()
{
  return speed;
}

void Archer::typeInit()
{
  orig_speed = speed;
}

int Robot::getDamage()
{
  //cout << "Get robot damage " << name << endl;
  int d = strength + bonus;
  bonus = 0;
  return d;
}

void Robot::reset()
{
  //cout << "resetting robot " << name << endl; 
  currentHP = maximumHP;
  bonus = 0;
  elec = max_elec;
}

void Robot::typeInit()
{
  max_elec = 2*magic;
  elec = max_elec;
}

bool Robot::useAbility()
{
  //cout << "Using Robot " << name << " at " << this << endl;
  if(elec < ROBOT_ABILITY_COST) return false;
  bonus = (int)((float)strength  * (pow((float)(elec)/(float)(max_elec),4)));
  elec-=ROBOT_ABILITY_COST;
  return true;
}