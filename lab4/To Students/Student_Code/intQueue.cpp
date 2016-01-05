#include "intQueue.h"

void intQueue::add(int val)
{
  if (size == m_size) return;
  this->elements->insertTail(val);
  size++;
}

bool intQueue::isDup(int val)
{
  return elements->isDup(val);
}

void intQueue::remove()
{
  if (!size) return;
  this->elements->remove(elements->head->value);
  size--;
}

int intQueue::first()
{
  if (!size) return -1;
  return elements->head->value;
}

bool intQueue::full()
{
  if (size == m_size) return true;
  else return false;
}

bool intQueue::empty()
{
  if (size == 0) return true;
  else return false;
}