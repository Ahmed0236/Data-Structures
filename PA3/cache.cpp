#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>

#include <chrono>
#include <thread>
#include <future>
#include <time.h>
#include <ctime>
using namespace std;

vector<string> Decode;
int counter = 0;








    ///////////////////////////
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
                        Decode.push_back(word); //found the right word
                        //cout << word << endl;
                        counter++;
                        found = true;
                    }
                    break;
                }
            }

            if (found == true)
            {
                break;
            }
        }
        file.close();
    }

    void withoutCache()
    {
        string word;
        int key;
        //to read secret
        ifstream f3("testsecret.txt");
        while (f3 >> word)
        {
            key = stoi(word);
            //cout << key << endl;
            getWord(key);
        }
        f3.close();
    }

    int main()
    {
        std::chrono::high_resolution_clock::time_point timeStart = std::chrono::high_resolution_clock::now();

        withCache();

        std::chrono::high_resolution_clock::time_point timeEnd = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> totalTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeEnd - timeStart);
        cout << "Time Taken : " << totalTime.count() << " SECONDS." << endl;

        cout << "words : " << counter << endl;
    }
