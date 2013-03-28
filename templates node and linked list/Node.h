#ifndef NODE_H
#define NODE_H
#define NULL 0
template <class T>
class Node
{
    public:
        Node();
        void setData(T info);
        void setNext(T * next);
        void setNextNull();
        Node<T>* getNext();
        T getData();
        virtual ~Node();
    protected:
    private:
        T data;
        Node *next;

};

#endif // NODE_H
