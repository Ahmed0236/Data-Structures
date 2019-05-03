#ifndef GRAPH__CPP
#define GRAPH__CPP
#include "Graph.h"



Graph::Graph(char* file, bool isUnitLength=false)
{
	
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

bool Graph::Reachable(string start, string dest)
{

}

vector<node*> Graph::Prims()
{

}

vector<node*> Graph::Kruskal()
{

}

vector<string> Graph::Dijkstra(string start, string dest, float &d)
{

}

int main()
{
	cout<<"Initialize your graph in main!"<<endl;
	// write code for part 6 here
}

#endif
