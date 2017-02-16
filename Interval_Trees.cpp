#include <bits/stdc++.h>
using namespace std;
 
struct Interval
{
    int low;
	int high;
};
 
struct Node_Tree
{
    Interval invl; 
    int max; //Additional information for augmented Data Structure
    Node_Tree *left, *right;
};
 
Node_Tree *new_node(Interval invl1)
{
    Node_Tree *temp= new Node_Tree;
    temp->invl.low = invl1.low;
    temp->invl.high = invl1.high;
    temp->max= invl1.high; //Storing the high value of interval in max of new node
    temp->left= NULL;
	temp->right= NULL;
}; 
 
Node_Tree *insert(Node_Tree *root, Interval i)
{
    if(root==NULL)
        return new_node(i);
 
    int l_value = root->invl.low;
    if(i.low<l_value)
        root->left = insert(root->left,i);
    else
        root->right = insert(root->right,i);
        
    if(root->max<i.high)
        root->max= i.high;
 
    return root;
}

Node_Tree* minm(Node_Tree* root)  // node with minimum key in the subtree rooted at root
{
  	while((root->left)!=NULL) 
  		root = root->left;
  	
	  return root;
}

Node_Tree *Delete(Node_Tree* root, Interval invl1)
{
  	if(root == NULL) 
  		return root;
  	else if(invl1.low< root->invl.low) 
		root->left = Delete(root->left,invl1);
  	else if(invl1.low>root->invl.low) 
		root->right = Delete(root->right, invl1);
  	else 
  	{
    	if(((root->left)==NULL) && (&(root->right)==NULL))
		{
      		delete root;
      		root = NULL;
    	}	 
		else if((root->left)==NULL)
		{
      		Node_Tree* temp = root;
      		root = root->right;
      		delete temp;
    	} 
		else if((root->right)==NULL)
		{
      		Node_Tree* temp = root;
      		root = root->left;
      		delete temp;
    	}	 
		else
		{
      		Node_Tree *temp = minm(root->right);
      		root->invl = temp->invl;
      		root->max= max(max(root->right->max,root->left->max),root->invl.high); //Taking the maximum of both
      		root->right = Delete(root->right, temp->invl);
    	}
  	}
  	
	return root;
}

void print_tree(Node_Tree *root)
{
    if(root==NULL) 
		return;
    print_tree(root->left);

    cout<<"Low - "<<root->invl.low<<", High - "<<root->invl.high<<", Maximum = "<<root->max<<endl;
 
    print_tree(root->right);
}
 
bool Overlap_Check(Interval invl1, Interval invl2)
{
    if(invl1.low<=invl2.high&&invl2.low<=invl1.high)
        return true;
        
    return false;
}

Interval k = {0,0}; //Just a dummy Interval which returns [0,0]
 
Interval search(Node_Tree *root, Interval invl1)
{
    if(root==NULL) 
		return k;
 
    if(Overlap_Check((root->invl),invl1)) //Checking if interval is overlapping with root
        return root->invl;
 
    if((root->left!=NULL) && (root->left->max>=invl1.low))
        return search(root->left,invl1);
 
    return search(root->right,invl1);
}
 
int main()
{
    Node_Tree* root = NULL;
    //Inserting the sample data set with 6 intervals
    root = insert(root,{15,20});
    root = insert(root,{10,30});
    root = insert(root,{17,19});
    root = insert(root,{5,20});
    root = insert(root,{12,15});
    root = insert(root,{30,40});
 
    cout << "The Interval Tree for sample dataset is :\n"<<endl;
    print_tree(root);
    
    root = insert(root,{32,38});
    
    cout<<"\nOne more interval has been added to the tree."<<endl;
    cout<<"\nDeleting the interval added in the end - [32,38]"<<endl;
    
    root=Delete(root,{32,38});
    
    //Checking is for data set given in the example
    
    cout<<"\nSearching for interval 1 - [14,16]"<<endl;
    
    Interval invl1 = search(root,{14,16});
    
    if((invl1.low==0) && (invl1.high==0))
        cout<<"Interval not found"<<endl;
    else
        cout<<"Interval found and overlaps with ["<<invl1.low<<", "<<invl1.high<<"]"<<endl;
        
    cout<<"\nSearching for interval 2 - [21,23]"<<endl;
    
    Interval invl2 = search(root,{21,23});
    if(invl2.low==0 && invl2.high==0)
        cout<<"Interval not found"<<endl;
    else
        cout<<"Interval found and overlaps with ["<<invl2.low<<", "<<invl2.high<<"]"<<endl;
        
        
    return 0;
}
