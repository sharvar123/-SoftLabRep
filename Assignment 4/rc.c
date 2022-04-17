#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Reference Counting method on a binary tree

struct node {
 	unsigned int rc;
 	int value;
 	struct node *left;
 	struct node *right;
};

typedef struct node Node;

const Node *empty = NULL;
void inc_ref(Node *node);

 
Node *node(int value,Node *left,Node *right) {
	Node *r = malloc(sizeof(Node));
	r->rc = 1;
	r->value = value;
	r->left = left;
	inc_ref(left);
	
	r->right = right;
	inc_ref(right);
	return r;
 }

//increments ref count of a node
void inc_ref(Node *node) {
	if (node != NULL) {
		node->rc += 1;
	}
}

// decrement the reference count of a node
void dec_ref(Node *node) {
	if (node != NULL) {
		if (node->rc > 1) {
			node->rc -= 1;
		} 
		else {
			dec_ref(node->left);
			dec_ref(node->right);
			free(node);
		}
 	}
}

Node *create_btree(int n){
	
	if (n == 0) {
		return 0;
	} 

	else {
		Node *sub = create_btree(n-1);
		Node *result = node(n, sub, sub);
		dec_ref(sub);
		return result;
 	}
}

 void print_preorder(Node * tree) {
 	if (tree) {
 		printf("%d\n",tree->value);
 		print_preorder(tree->left);
 		print_preorder(tree->right);
 }
}


int main(){
	int k;
	printf("Enter The Depth of the Binary tree:\n\t\t");
	scanf("%d",&k);
	Node* n=create_btree(k);
	printf("Binary tree of depth %d created.\n", k);
 	printf("Nodes of tree in preorder sequence:\n");
    print_preorder(n);
    dec_ref(n);//decreases the reference count and frees the node 
	printf("Node free.\n");

	
}

