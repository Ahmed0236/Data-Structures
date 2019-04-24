#ifndef DOUBLEHASH_CPP
#define DOUBLEHASH_CPP
#include "doubleHash.h"
#include "hashfunctions.cpp"

HashD::HashD(){
    tableSize = 10000; // you cant change this
    count = 0;

    hashTable = new block *[tableSize];
    for (int i = 0; i < tableSize; i++)
    {
        hashTable[i] = NULL;
    }
}

HashD::~HashD(){
    for (int i = 0; i < tableSize; i++)
    {
        delete hashTable[i];
    }
    delete[] hashTable;
}


unsigned long HashD::hash1(string value){
    //return polyHash(value);
    return polyHash(value);
}

unsigned long HashD::hash2(string value){
    return bitHash(value);
}


void HashD::resizeTable(){
    //find the load factor
    double lf = (double)count/(double)tableSize;
    long oldTableSize = tableSize;
    bool resize = false;

    if (lf >= 0.55)    //0.7//0.55
    {
        tableSize = tableSize * 2; //double the table
        resize = true;
    }
    else if (lf <= 0.25) //0.25
    {   
        tableSize = tableSize / 2; //half the table
        resize = true;
    }

    if (resize == true)
    {   
        block **temp = hashTable;
        for (int i = 0; i < oldTableSize; i++)
        {
            temp[i] = hashTable[i];
        }

        hashTable = new block *[tableSize];
        for (int i = 0; i < tableSize; i++)
        {
            hashTable[i] = NULL;
        }

        for (int i = 0; i < oldTableSize; i++)
        {
            if (temp[i] != NULL && temp[i]->value != "")
            {
                insert(temp[i]->value);
            }
        }
        delete[] temp;
        resize = false;
    }
    resize = false;
}

void HashD::insert(string value){
    
    unsigned long h1 = divCompression(hash1(value),tableSize);
    //unsigned long h2 = divCompression(hash2(value),tableSize);
    unsigned long h2 = 7 - divCompression(hash1(value),tableSize)%7;

   
    int i = 0;
    unsigned long index = ((h1 + i * h2))%tableSize;
    
    if(hashTable[index] == NULL)
    {
        hashTable[index] = new block(index,value);
    }
      
    else
    {     //cout << "collision..." << endl;
          while (hashTable[index] != NULL && hashTable[index]->value != "" )
          {   
              index = ((h1 + i*h2)) % tableSize;
              i++;
          }
          hashTable[index] = new block(index, value);
          //cout << "insertion after collision" << endl;
      }
      
    
    count++;
    resizeTable();
}

void HashD::deleteWord(string value){
    
    block *ptr = lookup(value);
    ptr->key = 0;
    ptr->value = "";
    count--;
    resizeTable();
}

block* HashD::lookup(string value){

    unsigned long h1 = divCompression(hash1(value), tableSize);
    unsigned long h2 = 7 - divCompression(hash1(value),tableSize)%7 ;

    int i = 0;
    unsigned long index = ((h1 + i*h2))%tableSize;
    block *ptr = hashTable[index];

    if (ptr != NULL)
    {
        if (ptr->value == value)
        {
            return ptr;
        }
        else
        {
            while (ptr)
            {   
                //cout << "probing..." << endl;
                if (ptr->value == value)
                {
                    return ptr;
                }
                i++;
                index = (h1 + i*h2) % tableSize;
                ptr = hashTable[index];
            }
        }
    }
    else
    {
        return NULL;
    }

    return NULL;
}


#endif