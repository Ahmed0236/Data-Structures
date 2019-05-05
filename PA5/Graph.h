#ifndef GRAPH__H
#define GRAPH__H
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <set>
#include <algorithm>
#include <queue>
#include <stack>
// You may include more libraries.

using namespace std;
class node;

class edge
{
	// You may add more variables and functions in this class
	public:
		node* Origin;
		node* Dest;
		float weight;	

		edge()
		{	
			this->Origin = NULL;
			this->weight = 0;
			this->Dest = NULL;
		}

		edge(node*a, node*b, float w)
		{
			this->Origin = a;
			this->Dest = b;
			this->weight = w;
		}
};
class node
{
	// You may add more variables and functions in this class
	public:
		bool visit; // flag to check if the node has been already visited
		string name;
		float weight;
		string prev;
		vector<edge> edges; // edges connected to node
		node()
		{
			this->visit = false;
			this->name = "";
			this->weight = 99;
			this->prev = "";
		}
		node(string name)
		{
			this->visit = false;
			this->name = name;
			this->weight = 99;
			this->prev = "";
		}
};

struct greatersNode
{
	bool operator()(node *a, node*b)
	{
		if(a->weight > b->weight){
			return true;
		}
		return false;
	}
};

struct greatersEdge
{
	bool operator()(edge &a, edge &b)
	{
		if(a.weight > b.weight){
			return true;
		}
		return false;
	}
};

class priorityQueue
{	
	public:
		vector<node*> v;
		void push(node* key)
		{
			v.push_back(key);
			make_heap(v.begin(),v.end(),greatersNode());
			return;
		}
		node*pop()
		{	
			make_heap(v.begin(),v.end(),greatersNode());
			node* temp = new node;
			for(int i = 0; i < v.size()-1; i++)
			{	
				temp = v[i];
				v[i] = v[i+1];
				v[i+1] = temp; 
			}
			temp = v.back();
			v.pop_back();
			return temp;
		}
		void update(string p,float d, string parent)
		{	
			//now look for the node
			for(int i = 0; i < v.size(); i++)
			{
				if(v[i]->name == p)
				{
					v[i]->weight = d;
					v[i]->prev = parent;
					make_heap(v.begin(),v.end(),greatersNode());
					return;
				}
			}

		}
		void print()
		{
			for(int i = 0; i < v.size(); i++)
			{
				cout << v[i]->name << " " << v[i]->weight << endl;
			}
		}
		bool isEmpty()
		{
			if(v.size() <= 0){
				return true;
			}
			return false;
		}
		void insertEdge(node* n, edge e)
		{
			
		}
};

class Minheap
{	
	public:
		vector<edge> v;
		void push(edge key)
		{
			v.push_back(key);
			make_heap(v.begin(),v.end(),greatersEdge());
			return;
		}
		edge pop()
		{	
			make_heap(v.begin(),v.end(),greatersEdge());
			edge temp ;
			for(int i = 0; i < v.size()-1; i++)
			{	
				temp = v[i];
				v[i] = v[i+1];
				v[i+1] = temp; 
			}
			temp = v.back();
			v.pop_back();
			return temp;
		}

		void print()
		{
			for(int i = 0; i < v.size(); i++)
			{
				cout << v[i].Origin->name << " to " << v[i].Dest->name<< " " << v[i].weight << endl;
			}
		}
		bool isEmpty()
		{
			if(v.size() <= 0){
				return true;
			}
			return false;
		}
};



class Graph
{
	public:

		priorityQueue q;
		Minheap h;

		vector<node*> Mst; // minimum spanning tree
		vector<node*> PERSONS;
		vector<edge> EDGES;
		Graph(char* filename, bool isUnitLenght);
		void display(node* temp);// displays the graph
		
		void insertEdge(vector<node*>&,edge);
		void addEdge(string,string,float);
		node* getPerson(string);
		void printEdges();
		void printNodes();
		void printFriends(node*);
		void printEdge(edge);
		node* search(vector<node*>&, string);

		
		int printCost(vector<node*>v);
		bool isVisited(vector<node*>&,node*);
		bool Reachable(string start, string dest);
		vector<node*> Prims();
		vector<node*> Kruskal(); //runs kruskal algorithm and returns the Minimum spanning tree
		vector<string> Dijkstra(string start, string dest, float &d);
};

#endif

