#pragma once
#include "LinkedList.h"
using namespace std;


class intStack
{
public:
  intStack(int mSize)
  {
    max_size = mSize;
    size = 0;
    elements = new LinkedList<int>();
    elements->insertHead(5);
  }
  
  bool isDup(int val);
  int top();
  bool empty();
  void pop();
  bool push(int val);
  bool full();
  int size;
  int max_size;
  LinkedList<int>* elements;
};