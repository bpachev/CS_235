#include "BSTInterface.h"
#include "Node.h"

class BST : public BSTInterface
{
public:
  BST(): root(0)
  {}
  enum CHILD_TYPE {RIGHT,LEFT};
  typedef struct DEL_INFO 
  {
    Node* parent;
    CHILD_TYPE ctype;
  } DEL_INFO;

  NodeInterface* getRootNode();
  bool add(int data);
  bool remove(int data);
  void clear();
  bool recur_remove(int data, Node* curr_node, DEL_INFO &d_info);

  
private:
  Node* root;
  
};