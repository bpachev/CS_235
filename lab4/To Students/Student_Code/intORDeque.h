#pragma once
#include "LinkedList.h"
using namespace std;

class intORDeque
{
public:
  intORDeque(int capacity): size(0), m_size(capacity), elements(new LinkedList<int>())
  {}
  
  void pop_front();
  void push_back(int val);
  void push_front(int val);
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