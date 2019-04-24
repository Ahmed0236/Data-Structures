#ifndef HASHFUNCTIONS_CPP
#define HASHFUNCTIONS_CPP
#include <string>
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;
// this takes in a string and returns a 64bit hash. // 31
unsigned long polyHash(string value,int a = 31){

    int i;
    unsigned long r = 0;
    char c;

    for (i = 0; i < value.length(); i++)
    {
        c = value.at(i); // process next character
        r = (int)c + a * r; // Cascaded evaluation of the polynoimal (classic trick)
    }
    return r;
}	

//does some bitwise operation and generates a 64bit hash.
unsigned long bitHash(string value){

    unsigned long h = 0;
    for (int i = 0; i < value.length(); i++)
    {
        h = (h << 5) | (h >> 27); // 5-bit cyclic shift of the running sum
        h = h + (unsigned long)value.at(i);     // add in next character
    }
    return h;
}


// Size is the size of array maintained by the hashtable.
unsigned long divCompression(unsigned long hash,long size){
    
    //return (labs(hash) % size);
    return hash%size;
}
// multiplication addition and division compression. 
unsigned long madCompression(unsigned long hash,long size,int m = 1993,int a = 1637){

    return (labs(hash*a + m) % size);

}

#endif
// you may write your own program to test these functions.


