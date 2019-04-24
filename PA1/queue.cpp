#ifndef __QUEUE_CPP
#define __QUEUE_CPP
#include "queue.h"

template <class T>
Queue<T>::Queue()
{
    list;
}
    
template <class T>
Queue<T>::Queue(Queue<T>& otherQueue)
{   
    if(otherQueue.list.getHead() == NULL)
    {
        return;
    }

    else
    {
        ListItem<T> *p = otherQueue.list.getHead();
        LinkedList<T> temp;
        while (p)
        {
            temp.insertAtHead(p->value);
            p = p->next;
        }

        ListItem<T> *q = temp.getHead();
        while (q)
        {
            list.insertAtHead(q->value);
            q = q->next;
        }
    }
}

template <class T>
Queue<T>::~Queue()
{
    list.~LinkedList();
}

template <class T>
void Queue<T>::enqueue(T item)
{
    list.insertAtTail(item);
}

template <class T>
T Queue<T>::front()
{
    return list.getHead()->value;
}

template <class T>
T Queue<T>::dequeue()
{
    T temp = list.getHead()->value;
    list.deleteHead();
    return temp;
}

template <class T>
int Queue<T>::length()
{
	return list.length();
}

template <class T>
bool Queue<T>::isEmpty()
{
    if (list.getHead() == NULL) {
        return true;
    }
    return false;
}

template <class T>
void Queue<T>::print()
{
    list.Print();
}

// int main()
// {
//     Queue<int> A;
//     A.enqueue(1);
//     A.enqueue(2);
//     A.enqueue(3);
//     A.print();
//     cout << "length : " << A.length() << endl;
//     A.dequeue();
//     A.print() ;

// }
#endif
