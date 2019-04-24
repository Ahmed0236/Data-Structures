#ifndef __LIST_CPP
#define __LIST_CPP

#include <cstdlib>
#include "LinkedList.h"

template <class T>
LinkedList<T>::LinkedList()
{
    head = NULL;
    tail = NULL;
}

template <class T>
LinkedList<T>::LinkedList(LinkedList<T>& otherLinkedList)
{
    if (otherLinkedList.head == NULL) {
        head = NULL;
        tail = NULL;
    }

    else
    {
	    head = new ListItem<T>(otherLinkedList.getHead()->value);
        ListItem<T> *current = head;
        ListItem<T> *objhead = otherLinkedList.head;
        ListItem<T> *currentobj = otherLinkedList.head;
        while (currentobj->next != NULL)
        {
            current->next = new ListItem<T>(currentobj->next->value);
            currentobj = currentobj->next;
            current = current->next;
        }
    }
	// else
	// {
	// 	ListItem<T> *p = otherLinkedList.head;
	// 	while (p)
	// 	{
	// 		insertAtTail(p->value);
	// 		p = p->next;
	// 	}
	// }
}

template <class T>
LinkedList<T>::~LinkedList()
{
    ListItem<T> *p = head;
    while(p){
        ListItem<T> *q = p->next;
        delete p;
        p = q;
    }

}

template <class T>
void LinkedList<T>::insertAtHead(T item)
{
    ListItem<T> *temp = new ListItem<T>(item);

    if (head == NULL) {
        head = temp;
        tail = temp;
    }
    else
    {   
		temp->next = head;
		head->prev = temp;
        head = temp;
    }
}

template <class T>
void LinkedList<T>::insertAtTail(T item)
{
    ListItem<T> *temp = new ListItem<T>(item);

    if (tail == NULL ) {
        head = temp;
        tail = temp;
    }

    else
    {     
		tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
}

template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{
    ListItem<T> *temp = new ListItem<T>(toInsert);

    if (head == NULL) {
        insertAtHead(toInsert);
    }

    else
    {
        //for traversal
        ListItem<T> *p = head;
        ListItem<T> *q;

        while (p->value != afterWhat)
        {
            p = p->next;
        }

        if (p->next == NULL)
        {
            insertAtTail(toInsert);
        }

        else
        {
            q = p->next;

            p->next = temp;
            temp->prev = p;

            temp->next = q;
            q->prev = temp;
        }
    }
}


template <class T>
ListItem<T>* LinkedList<T>::getHead()
{
    return head;
}

template <class T>
ListItem<T>* LinkedList<T>::getTail()
{
    return tail;
}

template <class T>
ListItem<T> *LinkedList<T>::searchFor(T item)
{
    ListItem<T> *p = head;
    while(p){
        if (p->value == item) {
            return p;
        }
        else
        {
            p = p->next;
        }
    }

    return NULL;
}

template <class T>
void LinkedList<T>::deleteElement(T item)
{
    ListItem<T> *p = head;

    if(head && head->value == item)
    {
        deleteHead();
        return;
    }

    if(tail && tail->value == item)
    {
        deleteTail();
        return;
    }

    {
        while (p)
        {
            if (p->value == item)
            {
                ListItem<T> *m = p->prev;
                ListItem<T> *n = p->next;
                m->next = n;
                n->prev = m;
                delete p;
                return;
                //p = n;

            }
            p = p->next;
        }
    }


}

template <class T>
void LinkedList<T>::deleteHead()
{
    if(head == NULL){return;}
    ListItem<T> *temp = head;
    head = head->next;
    delete temp;
}

template <class T>
void LinkedList<T>::deleteTail()
{
    ListItem<T> *p = head;

    if(p == NULL) {return;}

    while(p){
        if(p->next && p->next->next == NULL)
        {
            delete p->next;
            p->next = NULL;
            break;
        }
        p = p ->next;
    }


}

template <class T>
int LinkedList<T>::length()
{
    int counter = 0;
    ListItem<T> *p = head;
    while(p){
        counter++;
        p = p->next;
    }
    return counter;
}

template <class T>
void LinkedList<T>::Print()
{
	ListItem<T> *p = head;
	while (p)
	{
		cout << p->value << endl;
		p = p->next;
	}
}

//   int main()
//   {
//       LinkedList<int> A;
//       A.insertAtHead(1);
//       A.insertAtHead(2);
//       A.insertAtHead(3);
//       A.insertAtTail(4);
//       A.insertAtTail(5);
//       A.insertAtTail(6);
//       A.Print();
//       LinkedList<int> B(A);
// 	  B.insertAtHead(69);
//       cout << "printing B" << endl;
//       B.Print();

//  	 //system("Pause");
//   }


#endif
