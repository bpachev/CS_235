#pragma once
#include "LinkedList.h"
using namespace std;

class intIRDeque
{
public:
  intIRDeque(int capacity): size(0), m_size(capacity), elements(new LinkedList<int>())
  {}
  
  void pop_front();
  void pop_back();
  void push_front(int val);
  int front();
  int back();
  bool full();
  bool empty();
  bool isDup(int val);
  int size;
  
private:
  int m_size;
  LinkedList<int>* elements;
};