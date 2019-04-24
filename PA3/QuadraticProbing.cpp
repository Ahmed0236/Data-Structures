#ifndef QUADRATICPROBING_CPP
#define QUADRATICPROBING_CPP

#include "QuadraticProbing.h"
#include "hashfunctions.cpp"


HashL::HashL(){
    tableSize = 1000; // you cant change this
    count = 0;
    
    hashTable = new block*[tableSize];
    for(int i = 0; i < tableSize; i++)
    {
        hashTable[i] = NULL;
    }
}

HashL::~HashL(){
        for (int i  = 0; i < tableSize ; i++)
        {
            delete hashTable[i];
        }
        delete[] hashTable;
    
}

unsigned long HashL::hash(string value){
    return polyHash(value);
}

void HashL::resizeTable(){
    
    double lf = (double)count/(double)tableSize;
    long oldTableSize = tableSize;
    bool resize = false;
    
    if(lf >= 0.70) 
    {
        tableSize = tableSize*2;
        resize = true;
    }
    else if(lf <= 0.25) 
    {
        tableSize = tableSize/2;
        resize = true;
    }

    if(resize == true)
    {
       //create a temp for storing old old hashtable
        block** temp = hashTable;
        for(int i = 0; i < oldTableSize; i++)
        {
            temp[i] = hashTable[i];
        }

        //build a new hashtable
        hashTable = new block*[tableSize];
        for(int i = 0; i < tableSize; i++)
        {
            hashTable[i] = NULL;
        }

        //copy from previous table
        for(int i = 0; i < oldTableSize; i++)
        {
            if(temp[i] == NULL){
                continue;
            }else{
                insert(temp[i]->value); //call insert to insert in the new table
            }
        }
        delete[] temp;
        resize = false;
    }
    resize = false;
}

void HashL::insert(string value){
    
    int i = 0;
    unsigned long hash = divCompression(polyHash(value),tableSize);

    unsigned long index = (hash + (i*i))%tableSize;
    

    if(hashTable[index] == NULL) 
    {
        hashTable[index] = new block(index,value);
    }
    
    else   
    {   
        while(hashTable[index] != NULL && hashTable[index]->value != "") 
        {
            index = (index+(i*i))%tableSize;
            i++;
        }
        hashTable[index] = new block(index,value);
    }
    count++;
    resizeTable();
}

void HashL::deleteWord(string value){

    block* ptr = lookup(value);
    ptr->key = 0;
    ptr->value = "";

    count--;  
    resizeTable();
}


block* HashL::lookup(string value){
    
    int i = 0;
    unsigned long hash = divCompression(polyHash(value),tableSize);

    unsigned long index = (hash+(i*i))%tableSize;

    block *ptr = hashTable[index];

    if(ptr != NULL){
        if(ptr->value == value)
        {
            return ptr;
        }
        else
        {   
            while(ptr)
            {
                if(ptr->value == value)
                {
                    return ptr;
                }
                i++;
                index = (index + (i * i)) % tableSize;
                ptr = hashTable[index];
            }
        }
    }
    else{
        return NULL;
    }
  
    return NULL;
}

#endif