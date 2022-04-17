#include <stdio.h>
#include <stdlib.h>
#define V 100

//Create a simulator for the heap management schema using linked list as shown in the given figure. 
//The program output should display the adjacency matrix for the above schema 
 

/* Adjacency list node*/
typedef struct adjlist_node
{
    int vertex;                
    struct adjlist_node *next; 
}adjlist_node_t, *adjlist_node_p;

// Adjacency list 
typedef struct adjlist
{
    int num_members;          
    adjlist_node_t *head;      
}adjlist_t, *adjlist_p;


typedef struct graph
{
    int num_vertices;         /*Number of vertices*/
    adjlist_p adjListArr;
	int array [][V];     /*Adjacency Mtrix' array*/
}graph_t, *graph_p;

// Function to create an adjacency list node
adjlist_node_p createNode(int v)
{
    adjlist_node_p newNode = (adjlist_node_p)malloc(sizeof(adjlist_node_t));
    if(!newNode)
        printf("Unable to allocate memory for new node");

    newNode->vertex = v;
    newNode->next = NULL;

    return newNode;
}

// Function to create a graph with n vertices; Creates both directed graphs
graph_p createGraph(int n)
{
    int i;
    graph_p graph = (graph_p)malloc(sizeof(graph_t));
    if(!graph)
        printf("Unable to allocate memory for graph");
    graph->num_vertices = n;

    // Create an array of adjacency lists
    graph->adjListArr = (adjlist_p)malloc(n * sizeof(adjlist_t));
    if(!graph->adjListArr)
        printf("Unable to allocate memory for adjacency list array");

    for(i = 0; i < n; i++)
    {
        graph->adjListArr[i].head = NULL;
        graph->adjListArr[i].num_members = 0;
    }
    // Creates an array of adjacency matrix
    int  j;
 	for (i = 0; i < graph->num_vertices; i++){
    	for (j = 0; j < graph->num_vertices; j++){
    		graph->array[i][j] = 0;
		}
      		
	}

    return graph;
}

// Adds an edge to a graph
void addEdge(graph_t *graph, int src, int dest)
{
    /* Add an edge from src to dst in the adjacency list*/
    adjlist_node_p newNode = createNode(dest);
    newNode->next = graph->adjListArr[src].head;
    graph->adjListArr[src].head = newNode;
    graph->adjListArr[src].num_members++;
    graph->array[src][dest]=1; // Chnages the value of element of adjacency matrix array from 0 to 1

}

// Function to print the adjacency list of graph
void displayGraph(graph_p graph)
{
    int i;
    for (i = 0; i < graph->num_vertices; i++)
    {
        adjlist_node_p adjListPtr = graph->adjListArr[i].head;
        printf("\n%d: ", i);
        while (adjListPtr)
        {
            printf("%d->", adjListPtr->vertex);
            adjListPtr = adjListPtr->next;
        }
        printf("NULL\n");
    }
}

//function to print Adjacency Matrix
void printAdjMatrix(graph_p graph) {
printf("\n\nAdjacency Matrix Of Given Graph:\n\n");
  int i, j;

  for (i = 0; i < graph->num_vertices; i++) {
    printf("%d: ", i);
    for (j = 0; j < graph->num_vertices; j++) {
    	if (graph->array[i][j]!=1){printf("0\t");}
    	else{
    		 printf("%d\t", graph->array[i][j]);

		}
    }
    printf("\n");
  }
}

int main()
{
    graph_p dir_graph = createGraph(8);
    addEdge(dir_graph, 0, 5);
    addEdge(dir_graph, 1, 2);
    addEdge(dir_graph, 1, 9);
    addEdge(dir_graph, 1, 10);
 	  addEdge(dir_graph, 5, 1);
    addEdge(dir_graph, 7, 1);
    addEdge(dir_graph, 7, 8);
    addEdge(dir_graph, 8, 9);
    addEdge(dir_graph, 3, 8);
    addEdge(dir_graph, 3, 10);
   
    displayGraph(dir_graph);
    printf("Adjacency Matrix Of Given Graph:\n\n");
    printAdjMatrix(dir_graph);

    return 0;
}
