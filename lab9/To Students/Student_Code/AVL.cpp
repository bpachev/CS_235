#include "AVL.h"
#include <cstdlib>
#include <iostream>
using namespace std;

bool recur_add(int data, Node* curr_node, DEL_INFO &d_info, AVL* self);
void recur_clear(Node* curr_node);

AVL::~AVL()
{
  clear();
  root = 0;
}


NodeInterface * AVL::getRootNode()
{
  return root;
}

bool AVL::add(int data) 
{
  if (!root) 
  {
    root = new Node(data);
    return true;
  }
  DEL_INFO d_info = {NULL, RIGHT};
  bool tmp = recur_add(data, root, d_info, this);
  int lh = (root->left) ? root->left->height + 1 : 0;
  int rh = (root->right) ? root->right->height + 1 : 0;
  if (abs(lh-rh) > 1) rebalance(root, d_info);  
  return tmp;  
}

bool recur_add(int data,Node * curr_node, DEL_INFO &d_info, AVL* self)
{
  bool tmp;
  int curr_data = curr_node->data;
  int rh;
  int lh;
  if (data == curr_data) return false;
  else if (data > curr_data)
  {
    if(!curr_node->right) 
    {
      curr_node->right = new Node(data);
      lh = (curr_node->left) ? curr_node->left->height + 1 : 0;
      rh = (curr_node->right) ? curr_node->right->height + 1 : 0;
      curr_node->height = (rh > lh) ? rh : lh;
      
      return true;
    }
    else 
    {
      DEL_INFO info = {curr_node, RIGHT}; 
      tmp = recur_add(data, curr_node->right,info,self);
      lh = (curr_node->left) ? curr_node->left->height + 1 : 0;
      rh = (curr_node->right) ? curr_node->right->height + 1 : 0;
      curr_node->height = (rh > lh) ? rh : lh;
      if (abs(lh-rh) > 1) self->rebalance(curr_node, d_info);
      return tmp;      
    }
  }
  else if (data < curr_data)
  {
    if(!curr_node->left)
    {
      curr_node->left = new Node(data);
      lh = (curr_node->left) ? curr_node->left->height + 1 : 0;
      rh = (curr_node->right) ? curr_node->right->height + 1 : 0;
      curr_node->height = (rh > lh) ? rh : lh;
      
      return true;
    }
    else 
    {
      DEL_INFO info = {curr_node, LEFT};
      tmp = recur_add(data, curr_node->left,info,self);
      lh = (curr_node->left) ? curr_node->left->height + 1 : 0;
      rh = (curr_node->right) ? curr_node->right->height + 1 : 0;
      curr_node->height = (rh > lh) ? rh : lh;
      if (abs(lh-rh) > 1) self->rebalance(curr_node, d_info);      
      return tmp;
    }
  }
 
}

bool AVL::remove(int data) 
{
//  if (data == 200) return false;
  if (!root) return false;
  else 
  {
    DEL_INFO info = {NULL, RIGHT};
    return recur_remove(data,root,info);
  }
}

#define UPDATE_HEIGHT(node,rh,lh) rh = (node->right) ? node->right->height + 1 : 0; lh = (node->left) ? node->left->height + 1 : 0; node->height = (rh > lh) ? rh : lh;

void AVL::rebalance(Node* curr_node,DEL_INFO &d_info)
{
  int r,l;  
  Node * r_node = curr_node->right;
  Node * l_node = curr_node->left;
  int rh = (r_node) ? r_node->height : -1;
  int lh = (l_node) ? l_node->height : -1;
  
  if (rh > lh)
  {
    Node * rr_node = curr_node->right->right;
    Node * rl_node = curr_node->right->left;
    int rrh = (rr_node) ? rr_node->height : -1;
    int rlh = (rl_node) ? rl_node->height : -1;
    
    //right-right
    if (rrh >= rlh)
    {
      curr_node->right = r_node->left;
      r_node->left = curr_node;
      UPDATE_HEIGHT(curr_node,rh,lh);
      UPDATE_HEIGHT(r_node,rh,lh);
      if (!d_info.parent)
      {
        root = r_node;
        return;
      }
      
      
      if (d_info.ctype == RIGHT) d_info.parent->right = r_node;
      if (d_info.ctype == LEFT) d_info.parent->left = r_node;
      
      return; 
    }
    
    //right-left
    else
    {
//      cout << "Right-left rebalance" << endl;      
      // first rebalance
      curr_node->right = rl_node;
      r_node->left = rl_node->right;
      rl_node->right = r_node;
      UPDATE_HEIGHT(r_node,r,l);
      UPDATE_HEIGHT(rl_node,r,l);
      // rename nodes
      r_node = curr_node->right;
      rr_node = curr_node->right->right;      
      //second rebalance
      curr_node->right = r_node->left;
      r_node->left = curr_node;
      UPDATE_HEIGHT(curr_node,r,l);
      UPDATE_HEIGHT(r_node,rh,lh);
      
      if (!d_info.parent)
      {
        root = r_node;
        return;
      }
      
      if (d_info.ctype == RIGHT) d_info.parent->right = r_node;
      if (d_info.ctype == LEFT) d_info.parent->left = r_node;
      
      return;
    }
    
  }
  
  else
  {
    Node * lr_node = curr_node->left->right;
    Node * ll_node = curr_node->left->left;
    int lrh = (lr_node) ? lr_node->height : -1;
    int llh = (ll_node) ? ll_node->height : -1;
    
    //left-left
    if (llh >= lrh)
    {
      curr_node->left = l_node->right;
      l_node->right = curr_node;
      UPDATE_HEIGHT(curr_node,r,l);
      UPDATE_HEIGHT(l_node,r,l);      
      if (!d_info.parent)
      {
        root = l_node;
        return;
      }

      
      if (d_info.ctype == RIGHT) d_info.parent->right = l_node;
      if (d_info.ctype == LEFT) d_info.parent->left = l_node;
      
      return;
    }
    
    //left-right
    else
    {
      //first rebalance
      curr_node->left = lr_node;
      l_node->right = lr_node->left;
      lr_node->left = l_node;
      UPDATE_HEIGHT(l_node,r,l);
      UPDATE_HEIGHT(lr_node,r,l);
      
      //rename nodes
      l_node = curr_node->left;
      lr_node = curr_node->left->right;
      
      //second rebalance
      curr_node->left = l_node->right;
      l_node->right = curr_node;
      UPDATE_HEIGHT(curr_node,r,l);
      UPDATE_HEIGHT(l_node,r,l);      
      if (!d_info.parent)
      {
        root = l_node;
        return;
      }
      
      if (d_info.ctype == RIGHT) d_info.parent->right = l_node;
      if (d_info.ctype == LEFT) d_info.parent->left = l_node;      
      
      return;
    }
    
  }
  
}


bool AVL::recur_remove(int data, Node* curr_node, DEL_INFO &d_info)
{
  int rh, lh;
  if (data < curr_node->data)
  {
    if (!curr_node->left) return false;
    DEL_INFO info = {curr_node, LEFT}; 
    bool tmp =  recur_remove(data, curr_node->left,info);
    rh = (curr_node->right) ? curr_node->right->height + 1 : 0;
    lh = (curr_node->left) ? curr_node->left->height + 1 : 0;
    curr_node->height = (rh > lh) ? rh : lh;
    if (abs(rh-lh) > 1) rebalance(curr_node, d_info);    
    return tmp;
  }
  
  else if (data > curr_node->data)
  {
    if (!curr_node->right) return false;
    DEL_INFO info  = {curr_node, RIGHT};
    bool tmp = recur_remove(data, curr_node->right, info);
    rh = (curr_node->right) ? curr_node->right->height + 1 : 0;
    lh = (curr_node->left) ? curr_node->left->height + 1 : 0;
    curr_node->height = (rh > lh) ? rh : lh;
    if (abs(rh-lh) > 1) rebalance(curr_node, d_info);
    return tmp;
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
      // missing predecessor
      curr_node->data = curr_node->right->data;
      curr_node->left = curr_node->right->left;
      curr_node->height = curr_node->right->height;
      Node * temp = curr_node->right->right;
      delete curr_node->right;
      curr_node->right = temp;
      return true;
    }
    
    else 
    {
      Node * predecessor = curr_node->left;
      if (!predecessor->right)
      {
        //the predecessor is the left child
        curr_node->data = predecessor->data;
        curr_node->height = predecessor->height;
        Node * temp = predecessor->left;
        delete predecessor;
        curr_node->left = temp;
        UPDATE_HEIGHT(curr_node,rh,lh);
        if (abs(rh-lh) > 1) rebalance(curr_node, d_info);         
        return true;
      }
      
      DEL_INFO info = {curr_node,LEFT};
      bool tmp = recur_find_predecessor(curr_node,predecessor,info);
      rh = (curr_node->right) ? curr_node->right->height + 1 : 0;
      lh = (curr_node->left) ? curr_node->left->height + 1 : 0;
      curr_node->height = (rh > lh) ? rh : lh;
      if (abs(rh-lh) > 1) rebalance(curr_node, d_info);
      
      return tmp;
/*      while (predecessor->right)
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
      } */
    }
    
  }
}

bool AVL::recur_find_predecessor(Node* curr_node, Node* pred_parent, DEL_INFO &d_info)
{
  Node* predecessor = pred_parent->right;
  if (predecessor->right)
  {
    DEL_INFO info = {pred_parent, RIGHT};
    bool tmp = recur_find_predecessor(curr_node, predecessor, info);
    int rh = (pred_parent->right) ? pred_parent->right->height + 1 : 0;
    int lh = (pred_parent->left) ? pred_parent->left->height + 1 : 0;
    pred_parent->height = (rh > lh) ? rh : lh;
    if (abs(rh-lh) > 1) rebalance(pred_parent, d_info);
    return tmp;
  }
  else
  {
    curr_node->data = predecessor->data;
    if (!predecessor->left)
    {
      delete predecessor;
      pred_parent->right = 0;
      int rh = (pred_parent->right) ? pred_parent->right->height + 1 : 0;
      int lh = (pred_parent->left) ? pred_parent->left->height + 1 : 0;
      pred_parent->height = (rh > lh) ? rh : lh;
      if (abs(rh-lh) > 1) rebalance(pred_parent, d_info);
      
      return true;
    }
    
    else
    {
      pred_parent->right = predecessor->left;
      delete predecessor;
      int rh = (pred_parent->right) ? pred_parent->right->height + 1 : 0;
      int lh = (pred_parent->left) ? pred_parent->left->height + 1 : 0;
      pred_parent->height = (rh > lh) ? rh : lh;
      if (abs(rh-lh) > 1) rebalance(pred_parent, d_info);
      
      return true;
    }
  }
}

void AVL::clear() 
{
 cout << "clearing AVL tree" << endl;
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
