#include "Node.h"

int Node::getData()
{
  return data;  
}

int Node::getHeight()
{
  return height;
}

NodeInterface * Node::getLeftChild()
{
  return left;
}

NodeInterface * Node::getRightChild()
{
  return right;
}
