#include "LinkedList.h"

LinkedList::LinkedList()
{
    head=NULL;
    tail=NULL;
}

void LinkedList::add(Bullet info)
{
    if(head==NULL)
    {
        head = new Node(info);
        tail=head;
    }
    else
    {
        Node *temp =new  Node(info);
        tail->setNext(temp);
        tail = temp;
    }
}

void LinkedList::remove(Node * before,Node * current)
{
    if(before==NULL)                                    //head is to be removed
    {
        head = current->getNext();
    }
    else if(current->getNext()==NULL)               //remove tail
    {
        tail=before;
        before->setNext(NULL);
    }
    else
    {
        before->setNext(current->getNext());
    }
    delete current;
    //current=NULL;
}

Bullet LinkedList::getfirstdata()
{
    return head->getData();
}

void LinkedList::deque()
{
    remove(NULL,head);
}

Node * LinkedList::returnhead()
{
    return head;
}

void  LinkedList::set_null()
{
    head=NULL;
    tail=NULL;
}

LinkedList::~LinkedList()
{
    //dtor
}
