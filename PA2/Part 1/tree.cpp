#ifndef __TREE_CPP
#define __TREE_CPP
#include "tree.h"

// try to make get_node() and get_file() after tree initialization


Tree::Tree(string data)
{
	TreeItem* new_node= new TreeItem();
	new_node->id = 1;
	new_node->latest_data = data;
	root = new_node;
	// write the rest of the code here
}

Tree::~Tree()
{
}


void Tree::branch(int id)
{	
	TreeItem *parent = get_node(id);
	int parentID = parent->id;

	TreeItem *Child = new TreeItem();
	Child->id = parentID*10 + parent->child.size()+1 ;
	Child->latest_data = parent->latest_data;

	//push node in vcs container
	VCS_node temp(parent->latest_data,0);
	Child->container.push_back(temp);

	//push child in child container
	parent->child.push_back(Child);

}

void Tree::merge(int src_id,int dst_id)
{	
	TreeItem *source = get_node(src_id);
	TreeItem *dest =   get_node(dst_id);

	if (source == NULL || dest == NULL) {
		return;
	}
	
	if(source != NULL && dest != NULL)
	{	
		dest->latest_data = dest->latest_data + source->latest_data;

		VCS_node p;
		p.data = dest->container.back().data;
		p.time_stamp = dest->container.back().time_stamp;
		p.data = dest->latest_data;

		dest->container.pop_back();
		dest->container.push_back(p);


		merge_state temp;
		temp.src_id = src_id;
		temp.dst_id = dst_id;

		history.push_back(temp);
	}
}

void Tree::commit(int src_id,string new_data)
{
	TreeItem *ptr = get_node(src_id);

	if (ptr != NULL)
	{
		ptr->latest_data = ptr->latest_data + new_data;
		
		VCS_node temp;
		temp.data = ptr->latest_data;
		//cout << ptr->container.size() << endl;
		temp.time_stamp = ptr->container.size();

		ptr->container.push_back(temp);
		
	}
}

string Tree::get_file(int id, int t_stamp)
{	
	TreeItem *p = get_node(id);
	
	if(p){
		VCS_node temp;
		temp = p->container[t_stamp];
		return temp.data;
	}

	else{
		return "";
	}
} 

TreeItem* Tree::get_node(int id)
{
	TreeItem *ptr = root;

	//found at root
	if (ptr->id == id)
	{	
		// << "found at root node" << endl;
		return ptr;
	}

	if (ptr == NULL)
	{
		return NULL;
	}

	else
	{
		//separate digits
		stack<int> q;
		int number = id;
		while (number > 0) {
			q.push(number % 10);
			number = number / 10;
		}

		if (q.top() != 1) {
			return NULL;
		}
		

		int i = 0;
		int index;
		while (!q.empty()){
			if (i != 0)
			{	
				index = q.top();
				if (ptr->child.size() < index)
				{
					return NULL;
				}
			
				ptr = ptr->child[index - 1];	
				if (ptr->id == id)
				{
					//cout << "FOUND " << endl;
					return ptr;
				}
			}
			q.pop();
			i++;
		}
	}
	return NULL;
} 

vector<merge_state> Tree::merge_history()
{
	return history;
}

void Tree::level_traversal() 
{ 
	Queue<TreeItem*> Q;
	Q.enqueue(root);

	while (!Q.isEmpty())
	{
		TreeItem *ptr = Q.front();
		cout << ptr->id << endl;
		if (ptr->child.empty() == false)
		{
			for (int i = 0; i < ptr->child.size(); i++)
			{
				Q.enqueue(ptr->child[i]);
			}
		}
		Q.dequeue();
	}
} 





#endif
