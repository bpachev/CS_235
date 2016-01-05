//Benjamin Pachev CS Fall 235 Midterm
#pragma once
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "DoubleLinkedList.h"
using namespace std;
class RedRover
{
public:
  RedRover(): roster(new DoubleLinkedList()), teamA(new DoubleLinkedList()), teamB(new DoubleLinkedList()) 
  {}
  
  void menu();
  void view_roster();
  bool upload_roster(string filename);
  void shuffle_roster();
  void user_play(int turn);
  void auto_play(int turn);
  void view_teams();
  void create_teams();
private:
  Person* pick_name(DoubleLinkedList* l);
  DoubleLinkedList* roster;
  DoubleLinkedList* teamA;
  DoubleLinkedList* teamB;
  
  
};