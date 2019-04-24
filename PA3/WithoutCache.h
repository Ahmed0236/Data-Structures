#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <chrono>

using namespace std;

vector<string> Message;
int counter = 0;



void getWord(int key)
{
    ifstream file;
    file.open("dictionary.txt");

        string word;
        string line;
        int num;
        bool found = false;

        while (!file.eof())
        {
            getline(file, line);
            for (int i = 0; i < line.length(); i++)
            {
                if (line.at(i) == ' ')
                {

                    num = stoi(line.substr(0, i));
                    word = line.substr(i + 1);

                    if (num == key)
                    {
                        Message.push_back(word); 
                        counter++;
                        file.close();
                        return;
                    }
                 
                }
            }
        }
        file.close();
        return;
}


void readKeys()
{
        string word;
        int key;
    
        ifstream f3("testsecret.txt");
        while (f3 >> word)
        {
            key = stoi(word);
            getWord(key);
        }
        f3.close();
}

void DecodeWithoutHash()
    {
        std::chrono::high_resolution_clock::time_point timeStart = std::chrono::high_resolution_clock::now();
        
        readKeys();

        std::chrono::high_resolution_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> totalTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeEnd - timeStart);
        cout << "Time Taken : " << totalTime.count() << " SECONDS." << endl;

        cout << "words : " << counter << endl;
    }
