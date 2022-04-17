#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Mark and Sweep method

struct node {
	int value;
	struct node *left;
	struct node *right;
	bool mark;
	struct node *next;
};

typedef struct node Node;

struct root {
	Node *start;
	struct root *next;
};

typedef struct root Root;

struct heap {
 Node *nodes;
 Root *roots;
};
 
typedef struct heap Heap;

//Creates a fresh heap with empty set of roots and nodes
Heap *make_heap(void) {
    Heap *a = malloc(sizeof(Heap));
	a->roots = NULL;
 	a->nodes = NULL;
 	printf("Created\n");

 	return a;
 }
 
//Creating a Node 
Node *node(int value,Node *left, Node *right, Heap *a) {
 Node *r = malloc(sizeof(Node));
 r->value = value;
 r->left = left;
 r->right = right;
 //
 r->mark = false;
 r->next = a->nodes;
 a->nodes = r;
 return r;
 }
 
 //Creating a root
 Root *root(Node *node,Heap *a) {
 	Root *g = malloc(sizeof(Root));
 	g->start = node;
 	g->next = a->roots;
 	a->roots = g;
 	return g;
 }


//marks a node if unmarked,and then recursively marks subnodes
void mark_node(Node *node) {
	if (node != NULL && !node->mark) {
		node->mark = true;
		mark_node(node->left);
		mark_node(node->right);
	}
}

// mark() procedure iterates over the roots, marking the nodes reachable from it.
void mark(Heap *a) {
	
	Root *g = a->roots;
 	while (g != NULL) {
 		mark_node(g->start);
 		g = g->next;
 	}
 	printf("Mark Executed\n");
 }

void sweep(Heap *a) {
 	Node *n = a->nodes;
 	Node *live = NULL;
 	while (n != NULL) {
	 	Node *tl = n->next;
	 	if (!(n->mark)) {
	 		free(n);
	 	} 
		else {
	 		n->mark = false;
	 		n->next = live;
	 		live = n;
	 	}
	 	n = tl;
	}
 	a->nodes = live;
 	printf("Sweep Executed\n");

 }

// marks and sweeps! 
 void gc(Heap *a) {
	mark(a);
	sweep(a);
}


int main(){
	Heap * a =make_heap();
	
	gc(a);	
}
