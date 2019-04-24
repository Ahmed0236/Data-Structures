#ifndef VCS_CPP
#define VCS_CPP
#include "VCS.h"
#include <string>

//base constructor, init
VCS::VCS(string file)
{
	curr_size=0;
	filename = file;	
}

//destructor
VCS::~VCS()
{

}


//time to commit
void VCS::commit(string msg)
{	
	ifstream myfile;
	string data;
	string file = filename+".txt";
	myfile.open(file);
	
	while (!myfile.eof())
	{
		getline(myfile,data);
	}
	myfile.close();

	VCS_node temp;
	temp.message = msg;
	temp.time_stamp = container1.length();
	container1.push(temp);

	int t = temp.time_stamp;
	std::string str = std::to_string(t);
	string name = filename+str+".txt";
	ofstream myfile2;
	myfile2.open(name);
	myfile2 << data;
	myfile2.close();
}

//print status of every version
void VCS::status()
{	
	VCS_node temp;
	for(int i = 0; i < container1.length(); i++){
		temp = container1.pop();
		cout << temp.time_stamp << " " << temp.message << endl;
		container1.push(temp);
	}
}

//goes one step back
string VCS::undo()
{	
	if(!container1.isEmpty()){
		container2.push(container1.pop());
	} 
}

//one step ahead
string VCS::redo()
{	
	if(!container2.isEmpty()){
		container1.push(container2.pop());
	} 
}

//goes t_stamp step back or ahead
string VCS::revert(int t_stamp)
{	
	VCS_node temp;
	for(int i = 0; i < t_stamp; i++){
		temp = container1.pop();
		container1.push(temp);
		if(temp.time_stamp == t_stamp){
			return temp.message;
		}
	}
}

#endif