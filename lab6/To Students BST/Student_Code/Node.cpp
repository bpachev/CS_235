#include "Node.h"

int Node::getData()
{
  return data;  
}

NodeInterface * Node::getLeftChild()
{
  return left;
}

NodeInterface * Node::getRightChild()
{
  return right;
}
