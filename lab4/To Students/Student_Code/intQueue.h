#pragma once
#include "LinkedList.h"
using namespace std;

class intQueue
{
public:
  intQueue(int capacity) : m_size(capacity), size(0), elements(new LinkedList<int>())
  {}
  
  void add(int val);
  void remove();
  int first();
  bool full();
  bool empty();
  int size;
  bool isDup(int val);
  
private:
  int m_size;
  LinkedList<int>* elements;
  
};