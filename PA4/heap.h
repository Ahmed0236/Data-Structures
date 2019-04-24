#ifndef __HEAP_H
#define __HEAP_H

#include <iostream>
#include <climits>
#include <cmath>

using namespace std;
 
class MinHeap
{
public:
    int *harr; // pointer to array of elements in heap
    int capacity; // maximum possible size of min heap
    int heap_size; // Current number of elements in min heap
public:
    // Constructor
    MinHeap(int cap);
 
    // to heapify a subtree with root at given index
    void MinHeapify(int i);
 
    // return index of the parent of a node at index i
    int parent(int i)
    {
        return floor((i-1)/2);
    }
 
    // get index of left child of node at index i
    int left(int i)
    {
        return (2*i)+1;
    }
 
    // get index of right child of node at index i
    int right(int i)
    {
        return (2*i)+2;
    }
 
    // remove minimum element (or root) from min heap
    int extractMin();
 
    // Decreases key value of key at index i to new_val 
    // (assume new_val will always be smaller than harr[i])
    void decreaseKey(int i, int new_val);
 
    // Returns the minimum key (key at root) from min heap
    int getMin()
    {
        return harr[0];
    }
 
    // Deletes a key stored at index i
    void deleteKey(int i);
 
    // Inserts a new key 'k'
    void insertKey(int k);

    int* getHeap()
    {
        return harr;
    }


    void swap(int *a, int *b)
    {
        int temp = *a;
        *a = *b;
        *b = temp;
    }


    void print()
    {
        for(int i = 0; i < heap_size; i++)
        {
            cout << harr[i] << " ";
        }
        cout << endl;
    }

};

#endif