#ifndef GRAPH__CPP
#define GRAPH__CPP
#include "Graph.h"



Graph::Graph(char* file, bool isUnitLength=false)
{
	ifstream myfile;
	myfile.open(file);

	string line;

	bool isnode = false;
	bool isEdge = false;

	while (getline(myfile, line))
	{
		if (line == "PEOPLE")
		{
			isnode = true;
			isEdge = false;
			continue;
		}

		if (line == "CONNECTIONS")
		{
			isnode = false;
			isEdge = true;
			continue;
		}

		//reading nodes of persons
		if (isnode)
		{
			for (int i = 0; i < line.length(); i++)
			{
				if (line[i] == ' ')
				{
					line = line.substr(0, i);
				}
			}
			node *temp = new node(line);
			PERSONS.push_back(temp);
		}

		//reading edges
		if (isEdge)
		{
			string Person1, Person2;
			float edge_weight;
			int i;

			for (i = 0; i < line.length(); i++)
			{
				if (line[i] == ' ')
				{
					Person1 = line.substr(0, i);
					line = line.substr(i + 1);
					break;
				}
			}

			for (i = 0; i < line.length(); i++)
			{
				if (line[i] == ' ')
				{
					Person2 = line.substr(0, i);
					edge_weight = atof(line.substr(i + 1).c_str());
					break;
				}
			}
			if(isUnitLength){
				edge_weight = 1;
			}
			addEdge(Person1, Person2, edge_weight);
		}
	}
}

void Graph::display(node* temp)
{
	if(temp->visit)
		return;
	
	cout << "Person: " << temp->name;
	temp->visit = 1;
	for(int i=0; i< temp->edges.size(); i++)
	{
		if(!temp->edges[i].Origin->visit || !temp->edges[i].Dest->visit)
		cout << "->" << temp->edges[i].weight << endl;
		display(temp->edges[i].Origin);
		display(temp->edges[i].Dest);
	}
}

void Graph::addEdge(string a, string b, float c)
{
	node *p1 = getPerson(a);
	node *p2 = getPerson(b);

	//builds an edge p1 pointing to person 1 and p2 to person 2
	edge temp1(p1, p2, c);
	edge temp2(p2, p1, c);
	//1. insert in obverall edges vector
	EDGES.push_back(temp1);

	//2. insert in adjacancy list of both nodes
	p1->edges.push_back(temp1);
	p2->edges.push_back(temp2);
}


node *Graph::getPerson(string line)
{
	node *ptr;
	for (int i = 0; i < PERSONS.size(); i++)
	{
		ptr = PERSONS[i];
		if (PERSONS[i]->name == line)
		{
			return ptr;
		}
	}
	return NULL;
}


bool Graph::Reachable(string start, string dest)
{	
	int hops = 0;
	queue<node*> q;
	vector<node*> visitedList;

	node* v;
	node* ptr;
	node *p;

	p = getPerson(start);
	visitedList.push_back(p);
	q.push(p);

	while(!q.empty())
	{
		v = q.front();
		q.pop();

		if(v->name == dest)
		{
			return true;
		}
		for(int i = 0; i < v->edges.size(); i++)
		{	
			ptr = v->edges[i].Dest;
			if(!isVisited(visitedList,ptr))
			{	
				visitedList.push_back(ptr);
				q.push(ptr);
			}
		}
	}
	return false;
}

vector<node*> Graph::Prims()
{	
	vector<node*> visited;

	//create mstSet
	node *ptr = PERSONS[0];
	ptr->weight = 0;
	ptr->visit = true;
	q.push(ptr);

	float distance = 0;
//BUILD MINHEAP OF NODES	
	node *p = new node();
	for(int i = 1; i < PERSONS.size(); i++)
	{
		p = PERSONS[i];
		p->weight = 99;
		p->visit = true;
		q.push(p);
	}

	
	node* m = new node();
	while(!q.isEmpty())
	{	
		m = q.pop();
		//explore his neighbours
		node *Friend = new node();
		vector<edge> E = m->edges;
		m->edges.clear();
		for(int i = 0; i < E.size(); i++)
		{	
			Friend = E[i].Dest;

			if (!isVisited(visited, Friend))
			{
				//tempDistance = node_weight + edge_weight
				distance = ptr->weight + ptr->edges[i].weight;
				if (distance < Friend->weight)
				{	
					//update weight
					m->edges.clear();
					q.update(Friend->name, distance, ptr->name);
					//insert edge in final list
					m->edges.push_back(E[i]);
				}
			}
		}
		visited.push_back(m);
	}


	cout << "PRIM COST : " << printCost(visited) << endl;

	return visited;
}

void Graph::insertEdge(vector<node*>&v,edge e)
{
	//chech if both sides are visited or not
	node*p1 = search(v,e.Origin->name);
	node*p2 = search(v,e.Dest->name);
	float c = e.weight;
	
	//if both are visited then return
	if(p1->visit == true && p2->visit == true)
	{	
		return;
	}
	else{
		//mark both as visited
		//printEdge(e);
		p1->visit = true;
		p2->visit = true;

		//build edges
		edge e1(p1, p2, c);
		edge e2(p2, p1, c);

		p1->edges.push_back(e1);
		p2->edges.push_back(e2);

		return;
	}

}

int Graph::printCost(vector<node*> v)
{
	float x = 0;
	for (int i = 0; i < v.size(); i++)
	{
		for (int j = 0; j < v[i]->edges.size(); j++)
		{
			x = x + v[i]->edges[j].weight;
		}
	}
	return x;
}

vector<node*> Graph::Kruskal()
{
	//populate the minheap
	for(int i = 0; i < EDGES.size(); i++)
	{
		h.push(EDGES[i]);
	}

	//create vector of nodes
	vector<node*> temp;
	node* p;
	for(int i = 0; i < PERSONS.size(); i++)
	{	
		p = PERSONS[i];
		p->edges.clear();
		temp.push_back(p);
	}

	int vertices = PERSONS.size();
	int i = 0;
	edge e;
	while(i < vertices)
	{	
		e = h.pop();
		insertEdge(temp,e);
		i++;
	}

	float d;
	for(int i = 0; i < temp.size(); i++)
	{
		for(int j = 0; j < temp[i]->edges.size(); j++)
		{
			d = d + temp[i]->edges[j].weight ;
		}
	}
	Mst = temp;
	cout << "MST COST : " << d/2 << endl;
	return temp;
}

vector<string> Graph::Dijkstra(string start, string dest, float &d)
{
	getPerson(start)->weight = 0;

	for(int i = 0; i < PERSONS.size(); i++)
	{	
		q.push(PERSONS[i]);
	}

	vector<node*> v;
	float tempDistance;

	node* ptr = new node;
	while (!q.isEmpty())
	{
		ptr = q.pop();
		ptr->visit = true;
		node* Friend = new node;
		for(int i = 0; i < ptr->edges.size(); i++)
		{	
			Friend = ptr->edges[i].Dest;
			if(!isVisited(v,Friend))
			{	
				//tempDistance = node_weight + edge_weight
				tempDistance = ptr->weight + ptr->edges[i].weight;
				if(tempDistance < Friend->weight)
				{	
					q.update(Friend->name,tempDistance,ptr->name);
				}
			}
		}
		v.push_back(ptr);
	}
	
	//now trace back the path along with the cost
	vector<string> path;
	stack<node*> s;
	float cost;
	
	node* to = search(v,start);
	node* from = search(v,dest);
	d = from->weight;

	do
	{
		s.push(from);
		from = search(v, from->prev);

	} while (from->name != to->name);
	s.push(from);
	
	while (!s.empty())
	{	
		path.push_back(s.top()->name);
		s.pop();
	}
	
	return path;
}

void Graph::printEdges()
{
	cout << "size : " << EDGES.size() << endl;
	for (int i = 0; i < EDGES.size(); i++)
	{
		cout << EDGES[i].Origin->name << " " << EDGES[i].Dest->name << " " << EDGES[i].weight << endl;
	}
}

void Graph::printNodes()
{
	cout << "size : " << PERSONS.size() << endl;
	for (int i = 0; i < PERSONS.size(); i++)
	{
		cout << PERSONS[i]->name << " " << PERSONS[i]->name.length() << endl;
	}
}

void Graph::printEdge(edge e)
{
	cout << e.Origin->name << " " << e.Dest->name << " " << e.weight << endl;
}

void Graph::printFriends(node *person)
{
	
	for (int i = 0; i < person->edges.size(); i++)
	{
		printEdge(person->edges[i]);
	}
}

bool Graph::isVisited(vector<node*>&a,node*p)
{
	for(int i = 0; i < a.size(); i++)
	{
		if(a[i]->name == p->name)
		{
			return true;
		}
	}
	return false;
}

node* Graph::search(vector<node*>&v,string name)
{
	for(int i = 0; i < v.size(); i++)
	{
		if(v[i]->name == name)
		{
			return v[i];
		}
	}
	return NULL;
}

int main()
{
	cout<<"Initialize your graph in main!"<<endl;
	Graph g("friends.txt");

	//cout << g.Reachable("Ali", "Trump") << endl;

	vector<node*> a = g.Prims();


}

#endif

/*
1) Check reachability for following nodes and deduce nature of the dataset.
   	Mannan, Ali      (true)
	Mannan, Trump	 (true)    
	Ali, Trump		 (true)

	This is a connected undirected graph where there is a path leading from 
	every vertex to any other vertex in the graph

2) 2 hops away

3) 3 hops away

4)	Ali->Trump (11)
	Mannan->Trump (8)

5) 	cost (Weighted) = 30
	cost (unitLength) = 12

	unit length graph will have multiple mst as the sum of vertex weight is same in all	
	efficient utilization of resources in communicating between differnt people on the network
	designiing an efficeint transportation system
*/