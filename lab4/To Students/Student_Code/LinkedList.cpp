#include "LinkedList.h"
#include <stdio.h>
#include <iostream>
#include <string>



template<class T>LinkedList<T>::~LinkedList(void)
{
  Node<T>* thead = 0; 
  while(head!=tail)
  {
    thead = head->next;
    delete head;
    head = thead;
  }
  
  delete tail;
}

template<class T>
void LinkedList<T>::insertHead(T value)
{ 
  if (isDup(value)) return;
  
  Node<T>* new_head = new Node<T>(value);
 
  if (!head)
  {
    head = tail = new_head;
    m_size++;
    return;
  }
  
  new_head->next = head;
  head = new_head;
  m_size++;
}

template<class T>
void LinkedList<T>::insertTail(T value)
{
  if (isDup(value)) return;
  
  Node<T>* new_tail = new Node<T>(value);
  
  if (!head)
  {
    head = tail = new_tail;
    m_size++;
    return;
  }
  
  tail->next = new_tail;
  tail = new_tail;
  m_size++;
}

template<class T>
void LinkedList<T>::insertAfter(T value, T insertionNode)
{
  if (!head) return;
  
  if (isDup(value)) return;
  
  Node<T>* curr = head;

  while (insertionNode != curr->value)
  {
    if (curr == tail) return; //reached end of list and value not found
    curr = curr->next;
  }

  Node<T>* new_node = new Node<T>(value);
  
  if (curr == tail)
  {
    tail->next = new_node;
    tail = new_node;
    m_size++;
    return;
  }
   
  new_node->next = curr->next;
  curr->next = new_node;
  m_size++;
}

template<class T>
void LinkedList<T>::remove(T value)
{
  if (!head) return;
  
  if (value == head->value)
  {
    Node<T>* temp_next = head->next;
    delete head;
    head = temp_next;
    if (!head) tail = 0;
    m_size--;
    return;
  }
  
  Node<T>* curr = head;
  Node<T>* prev = 0;
  
  while (value != curr->value)
  {
    if (curr == tail) return; //reached end of list and value not found
    prev = curr;
    curr = curr->next;
  }
  
  if (curr == tail) 
  {
    delete tail;
    prev->next = 0;
    tail = prev;
    m_size--;
    return;
  }
  
  prev->next = curr->next;
  delete curr;
  m_size--;
  return;
}

template<class T>
bool LinkedList<T>::isDup(T value)
{
  Node<T>* curr = head;
  
  while(curr)
  {
    if (curr->value == value) return true;
    curr = curr->next;
  }
  
  return false;
}

template<class T>
void LinkedList<T>::clear()
{
  Node<T>* thead = 0; 
  
  while (head!=tail)
  {
    thead = head->next;
    delete head;
    head = thead;
  }
  
  
  if (tail) delete tail;
  
  m_size = 0;
  head = 0;
  tail = 0;
}

template<class T>
T LinkedList<T>::at(int index)
{
  
  int cnt = 0;
  Node<T>* curr = head;
  if (index>=m_size || index<0)
  {
    return 0;;
  }
    
  for (cnt = 0;cnt<index; cnt++)
  {
    curr = curr->next;
  }
  
  return curr->value;
}

template<class T>
int LinkedList<T>::size()
{
  return m_size;
}

template class LinkedList<string>;
template class LinkedList<int>;
