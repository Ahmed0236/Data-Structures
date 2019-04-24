#ifndef __BST_CPP
#define __BST_CPP
#include "avl.h"
#include <iostream>
#include <queue>
// HELPER FUNCTIONS HERE...
template <class T>
BST<T>::BST(){
	root = NULL;
}

template <class T>
BST<T>:: ~BST(){
    // your destructor code goes here
	clearTree(root);
}

template <class T>
void BST<T>::clearTree(node<T> *p){
	if(p!= NULL){
		clearTree(p->left);
		clearTree(p->right);
		delete p;
	}
}

template <class T>
int BST<T> :: height (node<T>* p){
   // your find height code goes here
	if (p == NULL)
	{
		return 0;
	}
	else
	{
		return p->height;
		//return (max(height(p->left), height(p->right)) + 1);
	}
  
}


template <class T>
int BST<T> :: balanceFactor(node<T>* p){
   // you can use this to find balance factor.
	if (p == NULL)
	{
		return 0;
	}
	else
	{	
		return (height(p->left) - height(p->right));
	}
   
}
//
template <class T>
void BST<T> :: fixHeight(node<T>* p){
   // use this function to fix height of a node after insertion or deletion.
   int hl = height(p->left);
   int hr = height(p->right);

   int update;
   if(hl > hr){
	   update = hl +1;
   }else{
	   update = hr +1;
   }

   p->height = update;
   return;
}

// ROTATING HELPERS 
template <class T>
node<T>* BST<T> :: rotateleft(node<T>* p){
   // Rotate left code goes here.
	node<T> *right = p->right;
 	p->right = right->left;
 	right->left = p;

   // Update heights
   fixHeight(p);
   fixHeight(right);
 
   return right;
}

template <class T>							//Noh  *noh
node<T>* BST<T> :: rotateright(node<T>* p){
   // Rotate right code goes here
   node<T> *left = p->left;
   p->left = left->right;
   left->right = p;
   
   // Update heights
   fixHeight(p);
   fixHeight(left);

   return left;
}

template <class T>
node<T>* BST<T> :: balance(node<T>* p){    
	// Balancing code goes here. You might need to find balance factor and call appropriate rotations.
   
   fixHeight(p);
   
  
   int heightDifference = balanceFactor(p);
   

   //Left subtree is heavier
   
   if (heightDifference > 1) {


		if(balanceFactor(p->left) > 0){
	   		return rotateright(p);
		} 
		else if(balanceFactor(p->left) < 0){
	   		p->left = rotateleft(p->left);
	   		return rotateright(p);
	   	}
			
  	}


   // Right subtree is heavier
   
   if (heightDifference < -1 ) {

   	   //right right case
   	   if(balanceFactor(p->right) < 0){
	   	return rotateleft(p);
   	   } 
   	    //right left case
   	    else if(balanceFactor(p->right) > 0){
	   		p->right = rotateright(p->right);
	   		return rotateleft(p);
   	   }
   }


   //cout << "new root is " << p->key << endl << endl;
   return p;
}
// CLASS FUNCTIONS HERE

template <class T>
void BST<T> :: insert(string value,T k){
	root = insertHelper(value,k,root);
}

// insertion helper
template <class T>
node<T>* BST<T> :: insertHelper(string value,T k, node<T> *p) { // note we need a helper because we need recursive calls
    // Insertion code goes here.
	if (p == NULL)
	{
		p = new node<T>(k, value);
	}

	else if (p->key > k)
	{
		p->left = insertHelper(value, k, p->left);
	}
	else if (p->key < k)
	{
		p->right = insertHelper(value, k, p->right);
	}

    return balance(p);
}
template<class T>
node<T>* BST<T> :: search(T key){
    // Search code goes here.
	node<T> * ptr = getRoot();
	
	while (ptr!= NULL)
	{	

		if (ptr->key == key)
		{
			return ptr;
		}

		else
		{
			if (key > ptr->key)
			{	
				if (ptr->right == NULL)
				{
					return NULL;
				}
				else if (ptr->right != NULL)
				{
					ptr = ptr->right;
				}
				
			}
			if (key < ptr->key)
			{	
				if (ptr->left == NULL)
				{
					return NULL;
				}
				else
				{
					ptr = ptr->left;
				}
			}
		
		}	
	}return NULL;
}



// DELETE HELPER FUNCTIONS
template<class T> //private
node<T>* BST<T> :: findmin(node<T> *p){
    // This function finds the min node of the tree.
	if (p == NULL)
	{
		return NULL;
	}

	else
	{
		while (p->left != NULL)
		{
			p = p->left;
		}
		return p;
	}
}

template<class T> //private
node<T>* BST<T>::removemin(node<T>* p) {
	// This function recursively finds the min node and deletes it.
	if (p == NULL)
	{
		return NULL;
	}

	if (p->left != NULL)
	{
		p->left = removemin(p->left);
	}

	else
	{
		node<T> *q = p;
		p = p->right;
		delete q;
	}

	return balance(p);
   
}

template<class T> //public
void BST<T>::delete_node(T k){
    root = remove(root, k);
}

template<class T> //private
node<T>*  BST<T>::remove(node<T>* p, T k) // k key deletion from p tree
{	
	// This function uses findmin and deletemin to delete arbitrary node in the tree.
	if (p == NULL)
	{	
		//cout << "empty tree " << endl;
		return p;
	}
	
	else if (k < p->key)
	{
		p->left = remove(p->left, k);
	}
	else if (k > p->key)
	{
		p->right = remove(p->right, k);
	}


	else
	{
		//case 1: no children
		if (p->left == NULL && p->right == NULL)
		{	
			//cout << "no children" << endl;
			delete p;
			p = NULL;
			return p;
		}
		//case 2: 1 child
		else if (p->left == NULL)
		{	
			//cout << "no left child " << endl;
			node<T> *temp = p;
			p = p->right;
			delete temp;
		}
		else if (p->right == NULL)
		{	
			//cout << "no right child " << endl;
			node<T> *temp = p;
			p = p->left;
			delete temp;
		}

		//case 3: 2 children
		else if (p->left != NULL && p->right != NULL)
		{	
			//cout << "TWO children " << endl;
			node<T> *temp = findmin(p->right);
			p->key = temp->key;
			p->value = temp->value;
			p->right = remove(p->right, temp->key);
		}

	}
	return balance(p);
}

template<class T>
node<T>* BST<T>::getRoot(){
	return root;
}



// int main()
// {
// 	BST<int> cs;
// 	cs.insert("A",10);
// 	cs.insert("B",20);
// 	cs.insert("C",30);
// 	cs.insert("D",40);
// 	cs.insert("E",50);
// 	cs.insert("F",25);


// 	node<int> *ptr = cs.getRoot();
// 	//cout << cs.height(ptr) << endl << endl; 
// 	//cs.insert("B", 1);
// 	//cout << cs.height(ptr) << endl << endl;
// 	//cs.delete_node(1);
// 	//cout << cs.height(ptr) << endl << endl;
// 	//cs.removemin(ptr);
// 	cs.delete_node(20);
// 	cs.print();
// 	//cout << cs.balanceFactor(ptr) << endl;

// 	cout << "new root is " << ptr->key << endl;
// 	system("pause");
// }
#endif
