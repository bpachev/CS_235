template<class T>
class Node
{
  public:
    Node(T ndata): value(ndata), next(0)
    {}
    T value;
    Node<T>* next;
};