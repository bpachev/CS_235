#include "NodeInterface.h"

class Node : public NodeInterface
{
public:
  Node (int d): data(d), right(0), left(0)
  {}
    
  int getData();
  NodeInterface * getLeftChild();
  NodeInterface * getRightChild();
  int data;
  Node* right;
  Node* left;

};