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
	node *p1 = getPerson(start);
	for (int i = 0; i < p1->edges.size(); i++)
	{
		if (p1->edges[i].Dest->name == dest)
		{
			return true;
		}
	}
	return false;
}

vector<node*> Graph::Prims()
{

}

vector<node*> Graph::Kruskal()
{

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
		//cout << ptr->name << " " << ptr->weight << endl;
		//now visit his unvisited friends
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
	Graph g("t.txt");
	float d;
	vector<string> p = g.Dijkstra("egg","ant",d);

	cout << "cost : " <<  d << endl;
}

#endif
