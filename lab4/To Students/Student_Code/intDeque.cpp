#include "intDeque.h"


template class LinkedList<string>;
template class LinkedList<int>;


void intDeque::pop_front()
{
  if (!size) return;
  elements->remove(elements->head->value);
  size--;
}

bool intDeque::isDup(int val)
{
  return elements->isDup(val);
}

void intDeque::pop_back()
{
  if (!size) return;
  elements->remove(elements->tail->value);
  size--;
}

void intDeque::push_front(int val)
{
  if (size == m_size) return;
  elements->insertHead(val);
  size++;
}

void intDeque::push_back(int val)
{
  if (size == m_size) return;
  elements->insertTail(val);
  size++;
}

int intDeque::front()
{
  if (!size) return -1;
  return elements->head->value;
}

int intDeque::back()
{
  if (!size) return -1;
  return elements->tail->value;
}

bool intDeque::full()
{
  return (size == m_size) ? true : false;
}

bool intDeque::empty()
{
  return (!size) ? true : false;
}