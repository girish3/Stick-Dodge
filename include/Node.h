#ifndef NODE_H
#define NODE_H
//#define NULL 0

#include "const.h"

class Node
{
    public:
        Node(Bullet info);
        //void setData(Bullet info);
        void setNext(Node * next);
        void setNextNull();
        Node* getNext();
        Bullet getData();
        virtual ~Node();
    protected:
    private:
        Bullet data;
        Node *next;

};

#endif // NODE_H
