#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <chrono>
#include <time.h>
using namespace std;

int COUNTER = 0;


struct node
{   
public:
    int counter;
    int key;
    string value;
public:
    node()
    {
        key = 0;
        value = "";
        counter = 0;
    }

    node(int a, string b)
    {
        key = a;
        value = b;
        counter = 0;
    }

};


class Cache
{

private:
    int size;
    node* table;
    int counter;

public:
    Cache();
    void sort();
    void insert(node);
    node getFromDictionary(int);
    node search(int key);
    bool isFull();

};


Cache::Cache()
{
    size = 0;
    table = new node[500];
    
}

bool Cache::isFull()
{
    if(size == 500)
    {
        return true;
    }
    return false;
}

node Cache::search(int key)
{
    //find in cache
    for(int i = 0; i < size; i++)
    {
        if(table[i].key == key)
        {   
            table[i].counter++;
            return table[i];
        }
    }

    //find in dictionary
    return getFromDictionary(key);
        
}



void Cache::insert(node item)
{
    //if table is not full then insert in table
    if(!isFull())
    {
        table[size] = item;
        size++;
    }

    //if table is full then LFU
    else
    {
        table[499] = item;   //size will now be fixe to 1000 
    }
    
    sort(); //sort regardless of num elements in table
}

node Cache::getFromDictionary(int key)
{
    ifstream file("dictionary.txt");

    string word;
    string line;
    int num;

    while (!file.eof())
    {
        getline(file, line);

        for (int i = 0; i < line.length(); i++)
        {
            if (line.at(i) == ' ')
            {
                num = stoi(line.substr(0, i)); //get number
                word = line.substr(i + 1);     //get word

                if (num == key)
                {   
                    node temp(num, word);
                    Cache::insert(temp);
                    file.close();
                    COUNTER++;
                    return temp;
                }
            }
        }
    }
    file.close();
    cout << "not found " << endl;
    node t(-1,"");
    return t;
}



void Cache::sort()
{   
    node temp;
    for (int i = 0; i < (size - 1); i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (table[j].counter < table[j+1].counter)
            {
                temp = table[j];
                table[j] = table[j + 1];
                table[j + 1] = temp;
            }
        }
    }
}


vector<node> message;

void Decode()
{
    Cache m;
    string word;
    int key;
    ifstream f3("testsecret.txt");
    while (f3 >> word)
    {
        key = stoi(word);
        message.push_back(m.search(key));
    }
    f3.close();
}


void DecodeWithCache()
{
    std::chrono::high_resolution_clock::time_point timeStart = std::chrono::high_resolution_clock::now();
    
    Decode();
    
    std::chrono::high_resolution_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> totalTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeEnd - timeStart);
    cout << "Time Taken with Cache : " << totalTime.count() << " SECONDS." << endl;
    cout << "Elements : " << message.size() << endl;
}