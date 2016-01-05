#include "intIRDeque.h"


template class LinkedList<string>;
template class LinkedList<int>;


void intIRDeque::pop_front()
{
  if (!size) return;
  elements->remove(elements->head->value);
  size--;
}

bool intIRDeque::isDup(int val)
{
  return elements->isDup(val);
}

void intIRDeque::pop_back()
{
  if (!size) return;
  elements->remove(elements->tail->value);
  size--;
}

void intIRDeque::push_front(int val)
{
  if (size == m_size) return;
  elements->insertHead(val);
  size++;
}


int intIRDeque::front()
{
  if (!size) return -1;
  return elements->head->value;
}

int intIRDeque::back()
{
  if (!size) return -1;
  return elements->tail->value;
}

bool intIRDeque::full()
{
  return (size == m_size) ? true : false;
}

bool intIRDeque::empty()
{
  return (!size) ? true : false;
}