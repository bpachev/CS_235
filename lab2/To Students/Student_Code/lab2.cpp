#include "LinkedList.h"
#include <iostream>
#include <stdio.h>


#ifdef MAIN
int main(void)
{
  LinkedList<string>* myList;
  myList = new LinkedList<string>();
  myList->insertHead("FOO");
  delete myList;
}
#endif