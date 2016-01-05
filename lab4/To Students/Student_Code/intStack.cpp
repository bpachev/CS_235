#include "intStack.h"
#include "LinkedList.h"
using namespace std;

bool intStack::isDup(int val)
{
  return elements->isDup(val);
}

int intStack::top()
{
  if (size) return this->elements->tail->value;
  else return -1;
}

bool intStack::empty()
{
  if (size == 0) return true;
  else return false;
}

void intStack::pop()
{
  if (size==0) return;
  this->elements->remove(elements->tail->value);
  size--;
}

bool intStack::full()
{
  if (size >= max_size) return true;
  else return false;
}

bool intStack::push(int val)
{
  if (full()) return false;
  elements->insertTail(val);
  size++;
  return true;
}