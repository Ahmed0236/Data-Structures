#ifndef __SORTS_CPP
#define __SORTS_CPP
#include "sorts.h"
#include "heap.cpp"
#include "Queen.cpp"


//=====================================================================================
vector<long> InsertionSort(vector<long> nums)
{

    const int size = nums.size();
    long *arr = new long[size];

    for(int i = 0; i < size; i++){
        arr[i] = nums[i];
    }

    for (int i = 1; i < size; i++)
    {
        int temp = arr[i];
        int k = i - 1;
        while (k >= 0 && arr[k] > temp)
        {
            arr[k + 1] = arr[k];
            k--;
        }
        arr[k + 1] = temp;
    }

    nums.clear();
    //copy back to vector
    for(int i = 0; i < size; i++)
    {
        nums.push_back(arr[i]);
    }

    return nums;
}
//=====================================================================================
vector<long> MergeSort(vector<long> nums)
{
    //copy from vector to a linked list
    List<long> temp;
    for(int i = 0; i < nums.size(); i++)
    {
        temp.insertAtHead(nums[i]);
    }
    temp.head = mergeSort(temp.getHead());
    nums.clear();

    //insert sorted to vector
    ListItem<long> *node = temp.getHead();
    for(int i = 0; i < temp.length(); i++)
    {
        nums.push_back(node->value);
        node = node->next;
    }

    return nums;
}

//=====================================================================================
vector<long> QuickSortArray(vector<long> nums)
{
    //copy to array
    int start = 0;
    int end = nums.size();
    int *arr = new int[nums.size()];
    for(int i = 0; i < nums.size(); i++)
    {
        arr[i] = nums[i];
    }
    nums.clear();

    QuickSort(arr,start,end);

    //copy to vector
    for(int i = 0; i < end; i++)
    {
        nums.push_back(arr[i]);
    }

    return nums;
}

//=====================================================================================
vector<long> QuickSortList(vector<long> nums)
{
    //copy to linked list
    List<long> list;
    int end = nums.size();
    for(int i = 0; i < end ;i++)
    {
        list.insertAtHead(nums[i]);
    }
    nums.clear();
    quickSortList(list.getHead());

    //copy to vector
    ListItem<long> *node = list.getHead();
    for(int i = 0; i < end ; i++)
    {
        nums.push_back(node->value);
        node = node->next;
    }
    return nums;
}

//=====================================================================================
vector<long> HeapSort(vector<long> nums)
{
    //copy vector to heap
    int size = nums.size();
    MinHeap *heap = new MinHeap(size);
    for(int i = 0; i < size; i++)
    {
        heap->insertKey(nums[i]);
    }
    nums.clear();

    //copy back to vector
    for(int i = 0; i < size; i++)
    {
        nums.push_back(heap->extractMin());
    }

    return nums;
}

//=====================================================================================

vector<long> QueenOfAllSorts(vector<long> nums)
{
    vector<long> t = BS(nums);
    return t;
}  


#endif