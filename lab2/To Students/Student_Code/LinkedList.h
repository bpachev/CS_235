
#include "LinkedListInterface.h"
#include "Node.h"
#include <string>
#include <exception>

using namespace std;

template<class T>
class LinkedList: public LinkedListInterface<T>
{
  public:
    LinkedList(): head(0), tail(0), m_size(0)
    {}
    Node<T>* head;
    Node<T>* tail;
    ~LinkedList(void);
    void insertHead(T value);
    void insertTail(T value);
    void insertAfter(T value, T insertionNode);
    void remove(T value);
    void clear();
    T at(int index);
    int size();
    bool isDup(T value);
    
    
    static int foo() {return 0;}
  protected:
    int m_size;
  
  
};