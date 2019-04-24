#include "list.cpp"
#include <time.h>
#include <algorithm>
using namespace std;


void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}



int Partition(int arr[], int start, int end)
{
    //int pivot = median(arr[start],arr[(start-end)/2],arr[end]);
    int a = arr[start];
    int b = arr[end];
    int c = arr[(start+end)/2];

    //a is median
    if (a > b && a < c || a > c && a < b)
    {   
        swap(&arr[start],&arr[end]);
    }
    //c is median
    else if (c > a && c < b || c > b && c < a)
    {
        swap(&arr[end],&arr[(start+end)/2]);
    }

    int pivot = arr[end];

    int pIndex = start-1;
    for(int i = start ; i < end; i++)
    {
        if(arr[i] <= pivot)
        {
            pIndex++;
            swap(&arr[i],&arr[pIndex]);    
        }
    }
    swap(&arr[pIndex+1],&arr[end]);
    return pIndex+1;
}

void QuickSort(int arr[], int start, int end)
{
    if(start < end)
    {
        int pIndex = Partition(arr,start,end);
        QuickSort(arr,start,pIndex-1);
        QuickSort(arr,pIndex+1,end);
    }
}


//======================================================================
//==========================Quick Sort on Linked list===================

ListItem<long> *partition(ListItem<long> *l, ListItem<long> *h)
{
    int x = h->value;
    ListItem<long> *i = l->prev;
   
    for (ListItem<long> *j = l; j != h; j = j->next)
    {
        if (j->value <= x)
        {          
            i = (i == NULL) ? l : i->next;
            swap((i->value), (j->value));
        }
    }
    i = (i == NULL) ? l : i->next; 
    swap((i->value), (h->value));
    return i;
}

ListItem<long> *partition_random(ListItem<long> *l, ListItem<long> *h)
{
    srand(time(NULL));
    int random = l->value + rand() % (h->value - l->value);
    
    ListItem<long> *ptr = l;
    for(int i = 0; i < random; i++)
    {
        ptr = ptr->next;
    }

    swap(ptr->value,h->value);
    return partition(l,h);
}



void _quickSort(ListItem<long> *l, ListItem<long> *h)
{
    if (h != NULL && l != h && l != h->next)
    {
        ListItem<long> *p = partition(l, h);
        _quickSort(l, p->prev);
        _quickSort(p->next, h);
    }
}

ListItem<long> *lastNode(ListItem<long> *root)
{
    while (root && root->next){
        root = root->next;
    }
    return root;
}

void quickSortList(ListItem<long> *head)
{
    ListItem<long> *h = lastNode(head);
    _quickSort(head, h);
}


// int main()
// {

//     List<long> a;
//     a.insertAtHead(4);
//     a.insertAtHead(7);
//     a.insertAtHead(8);
//     a.insertAtHead(2);
//     a.insertAtHead(9);
//     a.insertAtHead(13);
//     a.insertAtHead(5);

//     quickSortList(a.getHead());
//     a.display_list();

// }
