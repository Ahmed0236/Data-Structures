#include <iostream>
#include "list.cpp"
#include <vector>
#include "sorts.h"
#include <cmath>
using namespace std;



vector <long> BS(vector<long> nums)
{
    long max = nums[0];
    long min = nums[0];

    int size = nums.size();

    for(int i = 0; i < size; i++)
    {
        if(nums[i] > max){
            max = nums[i];
        }
        if(nums[i] < min){
            min = nums[i];
        }
    }
    //cout << "found max and min" << endl;

    //create array of buckets of size
    List<long> *buckets = new List<long>[max-min+1];


    for(int i = 0; i < size; i++)
    {
        buckets[nums[i]-min].insertAtTail(nums[i]);
    }

    nums.clear();
  
    int n = max-min+1;
    //cout << "now concatenating " << endl;
    for(int i = 0; i < n; i++)
    {
        if(buckets[i].head != NULL)
        {
            ListItem<long> *p = buckets[i].head;
            while(p)
            {
                nums.push_back(p->value);
                p = p->next;
            }
        }
    }
    return nums;

}



// int main()
// {
//     vector<long> p;
//     p.push_back(1);
//     p.push_back(4);
//     p.push_back(7);
//     p.push_back(3);
//     p.push_back(22);

//     vector<long>t = BS(p);

//     for(int i = 0; i < p.size();i++)
//     {
//         cout << t[i] << endl;
//     }
    



// }