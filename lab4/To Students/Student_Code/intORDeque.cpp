#include "intORDeque.h"


template class LinkedList<string>;
template class LinkedList<int>;


void intORDeque::pop_front()
{
  if (!size) return;
  elements->remove(elements->head->value);
  size--;
}


void intORDeque::push_front(int val)
{
  if (size == m_size) return;
  elements->insertHead(val);
  size++;
}

void intORDeque::push_back(int val)
{
  if (size == m_size) return;
  elements->insertTail(val);
  size++;
}

int intORDeque::front()
{
  if (!size) return -1;
  return elements->head->value;
}

int intORDeque::back()
{
  if (!size) return -1;
  return elements->tail->value;
}

bool intORDeque::full()
{
  return (size == m_size) ? true : false;
}

bool intORDeque::empty()
{
  return (!size) ? true : false;
}

bool intORDeque::isDup(int val)
{
  return elements->isDup(val);
}
