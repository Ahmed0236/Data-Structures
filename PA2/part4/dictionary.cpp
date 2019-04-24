#ifndef __DICTIONARY_CPP
#define __DICTIONARY_CPP
#include "dictionary.h"
#include <time.h>
#include <stdio.h>
#include <iomanip>
#include <chrono>

//compiler command g++ -std=c++0x 
Dictionary::Dictionary() { 
}

Dictionary::~Dictionary(){

}

void Dictionary::initialize(string wordsFile) {
	
	ifstream myfile;
	myfile.open(wordsFile.c_str());
	string data;
	int i = 0;
	if (myfile.is_open()){
		while (!myfile.eof()){
			myfile >> data;
			Dictionary::insertWord(data);
			i++;
			//cout << i << endl;
		}
		myfile.close();
		cout << "closed file" << endl;
	}else{
		cout << "unable to open file" << endl;
	}
	cout << "total words : " << i << endl;
}

bool Dictionary::deleteWord(string word) {
	if (findWord(word)) {
		wordsTree.delete_node(word);
		cout << "sccessful deletion" << endl;
		return true;
	} else{
		cout << "Item does not exists" << endl;
		return false;
	}
}
bool Dictionary::editWord(string oldWord, string newWord) {
	
	node<string> *temp = findWord(oldWord);
	if (temp != NULL) {
		temp->key = newWord;
		cout << "Successfull edit" << endl;
		return true;
	} else{
		cout << "Item not found" << endl;
		return false;
	}
}
bool Dictionary::insertWord(string word) {
	wordsTree.insert(word);
	return false; 
}
node<string>* Dictionary::findWord(string word) {

	auto start = chrono::steady_clock::now();
	node<string> *ptr = wordsTree.search(word);
    auto end = chrono::steady_clock::now();

	if (ptr != NULL) {
		cout << "FOUND" << endl;
		cout << "findWord() took " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns to search for " << word << endl;
		return ptr;
	} else{
		cout << "NOT FOUND" << endl;
		cout << "findWord() took " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " ns to search for " << word << endl;
		return NULL;
	}
}

#endif

int main() {
	cout << "AVL" << endl;
	Dictionary d;

	d.initialize("words.txt");
	d.findWord("asterion");
	d.findWord("bribeless");
	d.findWord("confederates");
	d.findWord("decompensation");
	d.findWord("economists");
	d.findWord("fozier");
	d.findWord("gallinae");
	d.findWord("hepler");
	d.findWord("interred");
	d.findWord("jumbo");
	d.findWord("kalon");
	d.findWord("like-sex");
	d.findWord("mohole");
	d.findWord("naivite");
	d.findWord("overcalled");
	d.findWord("periclase");
	d.findWord("quester");
	d.findWord("razzly");
	d.findWord("scleroxanthin");
	d.findWord("tropary");
	d.findWord("unjealously");
	d.findWord("vernon");
	d.findWord("whetted");
	d.findWord("xenos");
	d.findWord("ylang-ylang");
	d.findWord("zoomechanics");

	d.editWord("quester","questerahmed");
	d.findWord("quester");
	d.findWord("questerahmed");

	d.deleteWord("questerahmed");
	d.findWord("questerahmed");

	return 0;
}
