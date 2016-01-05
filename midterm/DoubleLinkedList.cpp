//Benjamin Pachev CS Fall 235 Midterm
#include "DoubleLinkedList.h"
#include <ctype.h>
#include <stdlib.h>

bool DoubleLinkedList::add(string n, int sp, int st)
{
  Person* temp = new Person(n,sp,st);

  if(!head)
  {
    head = temp;
    tail = temp;
    size++;
    return true;
  }
  
  tail->next = temp;
  temp->prev = tail;
  tail = temp;
  size++;
  return true;
}

Person* DoubleLinkedList::random_pick()
{
  return at(rand() % size);
}

Person* DoubleLinkedList::at(int i)
{
  if (i>=size) return NULL;
  int j;
  Person* temp = head;
  for (j = 0; j < i; j++)
  {
    temp = temp->next;
  }
  return temp;
}

bool DoubleLinkedList::insert(string n_after,string n, int sp, int st)
{
  if(n_after == tail->name) 
  {
    return add(n, sp, st);
  }
  Person* temp = head;
  while(temp)
  {
    if (n_after == temp->name)
    {
      Person* new_person = new Person(n, sp, st);
      new_person->prev = temp;
      new_person->next = temp->next;
      temp->next->prev = new_person;
      temp->next = new_person;
      size++;
      return true;
    }
    temp = temp->next;
  }
  return false;
}


Person* DoubleLinkedList::get_by_name(string n)
{
  if (!head) return 0;
  Person* temp = head;
  
  while(temp)
  {
    if (temp->name == n) return temp;
    temp = temp->next;
  }
  return 0;
}

void DoubleLinkedList::print_names()
{
  if(!head) return;
  Person* temp = head;
  while (temp)
  {
    printf("%s",temp->name.c_str());
    temp = temp->next;
    if (temp) printf(",");
  }
  printf("\n");
  
}

bool DoubleLinkedList::remove(string n)
{
  if (!head) return false;
  
  Person* temp;
  
  if(n == head->name) 
  {
    temp = head->next;
    delete head;
    head = temp;
    if(head == 0) tail = 0;
    size--;
    return true;
  }
  
  else if(n == tail->name)
  {
    temp = tail->prev;
    delete tail;
    temp->next = 0;    
    tail = temp;
    size--;
    return true;
  }
  
  temp = head;
  
  while (temp->name!=n)
  {
    if (temp == tail)
    {
      return false;
    }
    temp = temp->next;
  }
  
  temp->prev->next = temp->next;
  temp->next->prev = temp->prev;
  delete temp;
  size--;
  return true;  
}

void DoubleLinkedList::clear()
{
  if (!head) return;
  Person* temp = head;
  
  while(temp)
  {
    temp = head->next;
    delete head;
    head = temp;
  }
  head = 0;
  tail = 0;
  size = 0;
}

void DoubleLinkedList::print_self()
{
  if(!head) return;
  Person* temp = head;
  while (temp)
  {
    printf("%s",temp->name.c_str());
    printf(" %d",temp->strength);
    printf(" %d\n", temp->speed);
    temp = temp->next;
  }
}