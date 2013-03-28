#include "LinkedList.h"

template <class T>
LinkedList<T>::LinkedList()
{
    head=NULL;
    tail=NULL;
}

template <class T>
void LinkedList<T>::add(T info)
{
    if(head==NULL)
    {
        head = new Node<T>;
        head->setData(info);
        tail=head;
    }
    else
    {
        Node<T> *temp = new Node<T>;
        temp->setData(info);
        tail->setNext(temp);
        tail = temp;
    }
}

template <class T>
void LinkedList<T>::remove(Node<T> * before,Node<T> * current)
{
    if(before==NULL)                                    //head is to be removed
    {
        head = current->getNext();
    }
    else
    {
        before->setNext(current->getNext());
    }
    delete current;
}

template <class T>
T LinkedList<T>::getfirstdata()
{
    return head->getData();
}

template <class T>
void LinkedList<T>::deque()
{
    remove(NULL,head);
}

template <class T>
Node<T> * LinkedList<T>::returnhead()
{
    return head;
}

template <class T>
LinkedList<T>::~LinkedList()
{
    //dtor
}
