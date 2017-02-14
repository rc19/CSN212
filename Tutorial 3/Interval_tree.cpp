#include<bits/stdc++.h>
using namespace std;

struct TreeNode{
	TreeNode *left, *right, *parent;
	int low,high,maxi;
	char color;
};
TreeNode* root, *nil;

void InsertFixUp(TreeNode *z);


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
	y  = nil;
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
			else if(z == z->parent->right){
				z = z->parent;
				LeftRotate(z);
			}
			
			z->parent->color = 'b';
			z->parent->parent->color = 'r';
			RightRotate(z->parent->parent);
		}
		else{
			y = z->parent->parent->left;
			
			if(y->color == 'r'){
				z->parent->color = 'b';
				y->color = 'b';
				z->parent->parent->color = 'r';
				z = z->parent->parent;
			}
			else if(z == z->parent->left){
				z = z->parent;
				RightRotate(z);
			}
			
			z->parent->color = 'b';
			z->parent->parent->color = 'r';
			LeftRotate(z->parent->parent);
		}
	}
	root->color = 'b';
}

/*void Transplant(TreeNode *u, *v){
	
	if(u->parent == nil) root = v;
	else if(u == u->parent->left) u->parent->left = v;
	else u->parent->right = v;
	
	v->parent = u->parent;
}
*/
int main(){
	
}
