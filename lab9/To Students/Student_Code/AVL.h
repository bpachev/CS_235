#include "AVLInterface.h"
#include "Node.h"

    
enum CHILD_TYPE {RIGHT,LEFT};
typedef struct DEL_INFO 
{
  Node* parent;
  CHILD_TYPE ctype;
} DEL_INFO;


class AVL : public AVLInterface
{
public:
  AVL(): root(0)
  {}

  
  ~AVL();
  NodeInterface* getRootNode();
  bool add(int data);
  bool remove(int data);
  void clear();
  bool recur_remove(int data, Node* curr_node, DEL_INFO &d_info);
  bool recur_find_predecessor(Node* curr_node, Node* pred_parent, DEL_INFO &d_info);
  
  Node* root;
  void rebalance(Node* curr_node, DEL_INFO &d_info);
};