#ifndef CHAINING_CPP
#define CHAINING_CPP
#include "Chaining.h"
#include "hashfunctions.cpp"

HashC::HashC(int size){

    this->tableSize = size;
    this->hashTable = new LinkedList<string>[tableSize];

}

HashC::~HashC(){

}

unsigned long HashC::hash(string input){

    return polyHash(input);
}

void HashC::insert(string word){

    unsigned long index = divCompression(hash(word),tableSize);
    hashTable[index].insertAtTail(word);
    return;
} 
 
ListItem<string>* HashC::lookup(string word){

    unsigned long index = divCompression(hash(word),tableSize);
    return hashTable[index].searchFor(word);

}

void HashC::deleteWord(string word){
    unsigned long index = divCompression(hash(word),tableSize); 
    hashTable[index].deleteElement(word);
    return;
}

void HashC::Print(){

    ListItem<string> *ptr;

    for(int i = 0 ; i < tableSize; i++){
        ptr = hashTable[i].getHead();
        while(ptr){
            cout << ptr->value ;
            ptr = ptr->next;
        }
        cout << endl;
    }   
}



#endif