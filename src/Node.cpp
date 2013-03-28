#include "Node.h"

Node::Node(Bullet info)
{
    next=NULL;
    data=info;
}

/*
void Node::setData(Bullet info)
{
    data = info;
}
*/

void Node::setNext(Node * next)
{
    this->next = next;
}

void Node::setNextNull()
{
    this->next=NULL;
}

Node * Node::getNext()
{
    return next;
}

Bullet Node::getData()
{
    return data;
}

Node::~Node()
{
    //dtor
}
