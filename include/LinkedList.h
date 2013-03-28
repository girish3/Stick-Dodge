#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

class LinkedList
{
    public:
        LinkedList();
        void add(Bullet info);
        void set_null();
        void deque();
        void remove(Node * before,Node * current);
        Bullet getfirstdata();
        Node * returnhead();
        virtual ~LinkedList();
    protected:
    private:
        Node *head,*tail;
};

#endif // LINKEDLIST_H
