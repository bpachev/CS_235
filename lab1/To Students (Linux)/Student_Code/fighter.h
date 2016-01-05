#pragma once
#include "FighterInterface.h"

class Fighter: public FighterInterface
{
  public:
    Fighter()
    {
    }
    string getName();
    int getMaximumHP();
    int getCurrentHP();
    int getStrength();
    int getSpeed();
    int getMagic();
    int HP_INC(int HPinc);
    void takeDamage(int damage_given);
    void regenerate();
    bool initFighter(const char* p, const string& fname);
    virtual void typeInit() = 0;
  protected:
    string name;
    int maximumHP;
    int currentHP;
    int strength;
    int speed;
    int magic;

};

class Cleric: public Fighter
{
  public:
    Cleric()
    {
    }
    void reset();
    bool useAbility();
    void regenerate();
    int getMana();
    int getDamage();
    void typeInit();
    
  protected:
    int mana;
    int max_mana;
};

class Archer: public Fighter
{
  public:
    Archer()
    {
    }
    void reset();
    bool useAbility();
    int getDamage();
    void typeInit();
  protected:
    int orig_speed;
};

class Robot: public Fighter
{
  public:
    Robot(): bonus(0)
    {}
    void reset();
    int getDamage();
    bool useAbility();
    void typeInit();
  protected:
    int bonus;
    int max_elec;
    int elec;
};