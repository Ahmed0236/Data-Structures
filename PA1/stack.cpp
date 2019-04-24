#ifndef __STACK_CPP
#define __STACK_CPP
#include "stack.h"

template <class T>
Stack<T>::Stack()
{
    list;
}

    
template <class T>
Stack<T>::Stack(Stack<T> &otherStack)
{
    if (otherStack.list.getHead() == NULL)
    {
        return;
    }

    // else
    // {
    //     head = new ListItem<T>(otherLinkedList.getHead()->value);
    //     ListItem<T> *current = head;
    //     ListItem<T> *objhead = otherLinkedList.head;
    //     ListItem<T> *currentobj = otherLinkedList.head;
    //     while (currentobj->next != NULL)
    //     {
    //         current->next = new ListItem<T>(currentobj->next->value);
    //         currentobj = currentobj->next;
    //         current = current->next;
    //     }
    // }
    else
    {
        ListItem<T> *p = otherStack.list.getHead();
        LinkedList<T> temp;
        while(p){
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
Stack<T>::~Stack()
{
    list.~LinkedList();
}

template <class T>
void Stack<T>::push(T item)
{
    list.insertAtHead(item);
}

template <class T>
T Stack<T>::top()
{
    return list.getHead()->value;
}

template <class T>
T Stack<T>::pop()
{
    T temp = list.getHead()->value;
    list.deleteHead();
    return temp;
}

template <class T>
int Stack<T>::length()
{
    return list.length();
}

template <class T>
bool Stack<T>::isEmpty()
{
    if (list.getHead() == NULL) {
        return true;
    }
    return false;
    
}

template <class T>
void Stack<T>::print()
{
    list.Print();
}

// int main()
// {
//     Stack<int> A;

//     A.push(1);
//     A.push(2);
//     A.push(3);

//     cout << "Printing A " << endl;
//     A.print();
//     Stack<int> B(A);
//     cout << "Printing B" << endl;
//     B.print();
//     cout << "length :" <<  B.length() << endl;
//     cout << "B top : " << B.top() << endl;
//     cout << "A empty : " << A.isEmpty() << endl;
//     cout << "B empty : " << B.isEmpty() << endl;

 
// }




#endif
