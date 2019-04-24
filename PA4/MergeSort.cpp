#include "list.cpp"
using namespace std;

ListItem<long> *split(ListItem<long> *head);

ListItem<long> *merge(ListItem<long> *first, ListItem<long> *second)
{
    if (!first){
        return second;
    }

    if (!second){
        return first;
    }

    if (first->value < second->value)
    {
        first->next = merge(first->next, second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else
    {
        second->next = merge(first, second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}

ListItem<long> *mergeSort(ListItem<long> *head)
{
    if (head==NULL  || head->next==NULL){
        return head;
    }
    ListItem<long> *second = split(head);

    head = mergeSort(head);
    second = mergeSort(second);

    return merge(head, second);
}


ListItem<long> *split(ListItem<long> *head)
{
    ListItem<long> *fast = head, *slow = head;
    while (fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    ListItem<long> *temp = slow->next;
    slow->next = NULL;
    return temp;
}

// int main()
// {

//     List<long> l;
//     l.insertAtHead(4);
//     l.insertAtHead(5);
//     l.insertAtHead(2);
//     l.insertAtHead(1);
//     l.insertAtHead(9);
//     l.insertAtHead(7);


//     l.head = mergeSort(l.getHead());
//     l.display_list();
// }
