#include "BST.h"

bool recur_add(int data, Node* curr_node);
void recur_clear(Node* curr_node);

NodeInterface * BST::getRootNode()
{
  return root;
}

bool BST::add(int data) 
{
  if (!root) 
  {
    root = new Node(data);
    return true;
  }
  return recur_add(data, root);  
}

bool recur_add(int data,Node * curr_node)
{
  int curr_data = curr_node->data;
  if (data == curr_data) return false;
  else if (data > curr_data)
  {
    if(!curr_node->right) 
    {
      curr_node->right = new Node(data);
      return true;
    }
    else return recur_add(data, curr_node->right);
  }
  else if (data < curr_data)
  {
    if(!curr_node->left)
    {
      curr_node->left = new Node(data);
      return true;
    }
    else return recur_add(data, curr_node->left);
  }
 
}

bool BST::remove(int data) 
{
  if (!root) return false;
  else 
  {
    DEL_INFO info = {NULL, RIGHT};
    return recur_remove(data,root,info);
  }
}

bool BST::recur_remove(int data, Node* curr_node, DEL_INFO &d_info)
{
  if (data < curr_node->data)
  {
    if (!curr_node->left) return false;
    DEL_INFO info = {curr_node, LEFT}; 
    return recur_remove(data, curr_node->left,info);
  }
  
  else if (data > curr_node->data)
  {
    if (!curr_node->right) return false;
    DEL_INFO info  = {curr_node, RIGHT};
    return recur_remove(data, curr_node->right, info);
  }
  
  else
  {
    if(!curr_node->left && !curr_node->right)
    {
      delete curr_node;
      if (curr_node == root) 
      {
        root = 0;
        return true;
      }
      if (d_info.ctype == RIGHT) d_info.parent->right = 0;
      else if (d_info.ctype == LEFT) d_info.parent->left = 0;
      return true;      
    }
    
    else if(!curr_node->left)
    {
      curr_node->data = curr_node->right->data;
      curr_node->left = curr_node->right->left;
      Node * temp = curr_node->right->right;
      delete curr_node->right;
      curr_node->right = temp;
      return true;
    }
    
    else 
    {
      Node * pred_parent;
      Node * predecessor = curr_node->left;
      if (!predecessor->right)
      {
        curr_node->data = predecessor->data;
        Node * temp = predecessor->left;
        delete predecessor;
        curr_node->left = temp;
        return true;
      }
      
      while (predecessor->right)
      {
        pred_parent = predecessor;
        predecessor = predecessor->right;
      }
      
      curr_node->data = predecessor->data;
      if (!predecessor->left)
      {
        delete predecessor;
        pred_parent->right = 0;
        return true;
      }
      
      else
      {
        pred_parent->right = predecessor->left;
        delete predecessor;
        return true;
      }
    }
    
  }
}

void BST::clear() 
{
 if(!root) return;
 recur_clear(root);
 root = 0; 
}

void recur_clear(Node* curr_node)
{
  if (curr_node->right) recur_clear(curr_node->right);
  if (curr_node->left) recur_clear(curr_node->left);
  delete curr_node;
}
