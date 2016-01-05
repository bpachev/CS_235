#pragma once
#include "LinkedList.h"
using namespace std;

class intDeque
{
public:
  intDeque(int capacity): size(0), m_size(capacity), elements(new LinkedList<int>())
  {}
  
  void pop_front();
  void pop_back();
  void push_front(int val);
  void push_back(int val);
  int front();
  int back();
  bool full();
  bool empty();
  int size;
  bool isDup(int val);
  
private:
  int m_size;
  LinkedList<int>* elements;
};