#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

template <class T>
class LinkedList
{
    public:
        LinkedList();
        void add(T info);
        void deque();
        void remove(Node<T> * before,Node<T> * current);
        T getfirstdata();
        Node<T> * returnhead();
        virtual ~LinkedList();
    protected:
    private:
        Node<T> *head,*tail;
};

#endif // LINKEDLIST_H
