//Benjamin Pachev CS Fall 235 Midterm
#pragma once
#include <string>
#include <stdio.h>
using namespace std;

class Person
{
public:
  Person(string n, int sp, int st): name(n), speed(sp), strength(st), next(0), prev(0)
  {}
  Person* prev;
  Person* next;
  string name;
  int speed;
  int strength;
};