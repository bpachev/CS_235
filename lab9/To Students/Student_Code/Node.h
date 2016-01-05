#include "NodeInterface.h"

class Node : public NodeInterface
{
public:
  Node (int d): data(d), right(0), left(0), height(0)
  {}
    
  int getData();
  int getHeight();
  NodeInterface * getLeftChild();
  NodeInterface * getRightChild();
  int data;
  int height;
  Node* right;
  Node* left;

};