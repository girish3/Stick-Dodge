#include "Node.h"

template <class T>
Node<T>::Node()
{
    //next=NULL;
}

template <class T>
void Node<T>::setData(T info)
{
    data = info;
}

template <class T>
void Node<T>::setNext(T * next)
{
    this->next = next;
}

template <class T>
void Node<T>::setNextNull()
{
    this->next=NULL;
}

template <class T>
Node<T> * Node<T>::getNext()
{
    return next;
}

template <class T>
T Node<T>::getData()
{
    return data;
}

template <class T>
Node<T>::~Node()
{
    //dtor
}
