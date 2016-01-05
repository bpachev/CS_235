//Benjamin Pachev CS Fall 235 Midterm
#pragma once
#include "Person.h"
#include <string>
#include <stdio.h>
using namespace std;

class DoubleLinkedList
{
public:
  DoubleLinkedList(): head(0), tail(0), size(0)
  {}
  Person* head;
  Person* tail;
  int size;
  Person* at(int i);
  bool add(string n, int sp, int st);
  bool remove(string n);
  bool insert(string n_after,string n, int sp, int st);
  void print_names();
  void clear();
  void print_self();
  Person* random_pick();
  Person* get_by_name(string name);
};