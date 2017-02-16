/*
Assumptions: 1. Since 'low(or start)' value of the interval is being used as a key,
			therefore it is assumed that all the intervals have distinct starting
			points in time in order to have distinct set of keys.
			
			2. Deletion is to be carried out if the interval to be deleted exists in the tree.
*/



#include<bits/stdc++.h>
using namespace std;

struct TreeNode{
	TreeNode *left, *right, *parent;
	int low,high,maxi;
	char color;
};
TreeNode* root, *nil;

void LeftRotate(TreeNode *x);
void RightRotate(TreeNode *y);
void InsertFixUp(TreeNode *z);
void Insert(TreeNode *z);
void Transplant(TreeNode *u, TreeNode *v);
void Delete(TreeNode *z);
void DeleteFixUp(TreeNode *z);
TreeNode* TreeMin(TreeNode *z);
TreeNode* IntervalSearch(int start, int end);
TreeNode* TreeSearch(TreeNode *x, int start);

void LeftRotate(TreeNode *x){
	TreeNode *y;
	y = x->right;
	x->right = y->left;
	
	if(y->left != nil)  y->left->parent = x;
	
	y->parent = x->parent;
	
	if(x->parent == nil) root = y;
	else if(x == x->parent->left)  x->parent->left = y;
	else x->parent->right = y;
	
	y->left = x;
	x->parent = y;
	
	x->maxi = max(x->left->maxi, max(x->right->maxi, x->high));
    y->maxi = max(x->maxi, max(y->right->maxi, y->high));
}

void RightRotate(TreeNode *y){
	TreeNode *x;
	x = y->left;
	y->left = x->right;

    if (x->right != nil)  x->right->parent=y;
	 
    x->parent = y->parent;
    
    if(y->parent == nil) root = x;
	else if(y == y->parent->left)	y->parent->left = x;
	else y->parent->right = x;
	
    x->right = y;
    y->parent = x;

    y->maxi = max(y->left->maxi, max(y->right->maxi, y->high));
    x->maxi = max(x->left->maxi, max(y->maxi, x->high));
}

void Insert(TreeNode *z){
	TreeNode *x, *y;
	y = nil;
	x = root;
	while(x != nil){
		y = x;
		
		if(z->low < x->low) x = x->left;
		else x = x->right;
		
	}
	z->parent = y;
	
	if(y == nil) root = z;
	else if(z->low < y->low) y->left = z;
	else y->right = z;
	
	z->left = z->right = nil;
	z->color = 'r';
	
	while(z != nil){
		z->maxi = max(z->high, max(z->left->maxi, z->right->maxi));
		z = z->parent;
	}
	InsertFixUp(z);
}

void InsertFixUp(TreeNode *z){
	TreeNode *y;
	while(z->parent->color == 'r'){
		
		if(z->parent == z->parent->parent->left){
			y = z->parent->parent->right;
			
			if(y->color == 'r'){
				z->parent->color = 'b';
				y->color = 'b';
				z->parent->parent->color = 'r';
				z = z->parent->parent;
			}
			else{
				if(z == z->parent->right){
					z = z->parent;
					LeftRotate(z);
			    }
			
				z->parent->color = 'b';
				z->parent->parent->color = 'r';
				RightRotate(z->parent->parent);
			}
		}
		else{
			y = z->parent->parent->left;
			
			if(y->color == 'r'){
				z->parent->color = 'b';
				y->color = 'b';
				z->parent->parent->color = 'r';
				z = z->parent->parent;
			}
			else{
				if(z == z->parent->left){
					z = z->parent;
					RightRotate(z);
				}
			
				z->parent->color = 'b';
				z->parent->parent->color = 'r';
				LeftRotate(z->parent->parent);
			}
		}
	}
	root->color = 'b';
}

void Transplant(TreeNode *u, TreeNode *v){
	
	if(u->parent == nil) root = v;
	else if(u == u->parent->left) u->parent->left = v;
	else u->parent->right = v;
	
	v->parent = u->parent;
}

void Delete(TreeNode *z){
	TreeNode *y, *x;
	y = z;
	char y_org_color = y->color;
	
	if(z->left == nil){
		x = z->right;
		Transplant(z,z->right);
	}
	else if(z->right == nil){
		x = z->left;
		Transplant(z,z->left);
	}
	else{
		y = TreeMin(z->right);
		y_org_color = y->color;
		x = y->right;
		
		if(y->parent == z) x->parent == y;
		else{
			Transplant(y,y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		
		Transplant(z,y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	
	z = x->parent;
	while(z != nil){
		z->maxi = max(z->high, max(z->left->maxi, z->right->maxi));
		z = z->parent;
	}
	if(y_org_color == 'b')  DeleteFixUp(x);
}

void DeleteFixUp(TreeNode *x){
	TreeNode *w;
	while(x != root && x->color == 'b'){
		
		if(x == x->parent->left){
			w = x->parent->right;
			
			if(w->color == 'r'){
				w->color = 'b';
				x->parent->color = 'r';
				LeftRotate(x->parent);
				w = x->parent->right;
			}
			
			if(w->left->color == 'b' && w->right->color == 'b'){
				w->color = 'r';
				x = x->parent;
			}
			else{
				
				if(w->right->color = 'b'){
				w->left->color = 'b';
				w->color = 'r';
				RightRotate(w);
				w = x->parent->right;
			   }
			   
			   w->color = x->parent->color;
			   x->parent->color = 'b';
			   w->right->color = 'b';
			   LeftRotate(x->parent);
			   x = root;
		    }
		}
		else{
			w = x->parent->left;
			
			if(w->color == 'r'){
				w->color = 'b';
				x->parent->color = 'r';
				RightRotate(x->parent);
				w = x->parent->left;
			}
			
			if(w->right->color == 'b' && w->left->color == 'b'){
				w->color = 'r';
				x = x->parent;
			}
			else{
				
				if(w->left->color = 'b'){
				w->right->color = 'b';
				w->color = 'r';
				LeftRotate(w);
				w = x->parent->left;
			   }
			   
			   w->color = x->parent->color;
			   x->parent->color = 'b';
			   w->left->color = 'b';
			   RightRotate(x->parent);
			   x = root;
		    }
		}
	}
	x->color = 'b';
}

TreeNode* TreeMin(TreeNode *z){
	while(z->left != nil) z->left;
	return z;
}

TreeNode* TreeSearch(TreeNode *x, int start){
	if(x->low == start) return x;
	if(start < x->low) return TreeSearch(x->left, start);
	else return TreeSearch(x->right, start);
}

TreeNode* IntervalSearch(int start, int end){
	TreeNode *x = root;
	while(x != nil && (end < x->low || start > x->high)){
		
		if(x->left != nil && x->left->maxi >= start)  x = x->left;
		else x = x->right;
	}
	return x;
}

int main(){
	nil->parent = nil->right = nil->left = nil;
	nil->color = 'b';
	nil->low = nil->high = nil->maxi = INT_MIN;
	
	root = nil;
	int choice, start, end;
	TreeNode *newnode;
	do{
		cout<<"Press 0 to Exit, 1 to Insert, 2 to Delete and 3 to Search for an overlapping Interval: ";
		cin>>choice;
		switch(choice){
			
			case 1: 
				cout<<"Enter the interval to insert separated by space: ";
				cin>>start>>end;
				newnode->low = start;
				newnode->high = newnode->maxi = end;
				newnode->color = 'r';
				newnode->parent = newnode->left = newnode->right = nil;
				Insert(newnode);
				break;
			
			case 2:
				cout<<"Enter the interval to delete separated by space: ";
				cin>>start>>end;
				newnode = TreeSearch(root, start);
				Delete(newnode);
				break;
			
			case 3:
				cout<<"Enter the interval to search for overlaps separated by space: ";
				cin>>start>>end;
				newnode = IntervalSearch(start, end);
				
				if(newnode == nil)
					cout<<"No stored interval overlaps with the given interval."<<endl;
				else
					cout<<"The given interval overlaps with ["<<newnode->low<<", "<<newnode->high<<"].";
 
				break;
			
			default:
				cout<<"Exiting from the program."<<endl;
				break;
		}
		
	}while(choice != 0);
}
