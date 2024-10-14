#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**************************
 * 1-Struct defination
 *************************/
#define MaxTime 1000001 //defined as an infinite value for the length of edge

typedef struct EdgeCDT* Edge;

struct EdgeCDT{
    int end;    //the end vertice of the directed edge
    int weight; //the weight of the edge
    int next;   //the next edge who has the same adjacent vertice of this edge
};

typedef struct GraphCDT* Graph;

struct GraphCDT{
    Edge *adjlist;//an array of linked list that record all the edges, edges[i] is all the edges which include the ith vertice
    int **Dist;//the dist array in dijkstra algorithm for each pick-up spots 
    int **Path;//the path array in dijkstra algorithm for each pick-up spots
    int *ambulance;//the arrary that record the number of ambulance at dispatch centers
};

/***************************
*2-Function declaration
***************************/
//Create a new Edge in the graph
Edge NewEdge(void);

//Insert a edge (u, v) with weight in graph
void InsertEdge(Edge edge, int u, int v, int weight, Graph graph);

//N:the sum of Ns and Na, Na:the number of pick-up spots, Ns:the number of dispatch centers
Graph Initialize(int N, int Na, int Ns);

//find the shortest path from start point to the other point 
//and then store the result in graph->dist and graph->path
void Dijkstra(Graph graph, int startpoint);

/***************************
*3-Main Function
***************************/
int main(){
    int Ns, Na, M, K;
    scanf("%d %d", &Ns, &Na);//read in Ns and Na
    //initialize the graph
    Graph graph;
    graph = Initialize(Ns+Na, Na, Ns);

    //read in the number of ambulance
    for(int i = 0;i < Na;i++){
        scanf("%d", &graph->ambulance[i]);
    }

    //read in the edges
    scanf("%d", &M);
    int u, v, weight;
    char string1[10], string2[10];
    Edge temp;
    for(int i =0;i < M;i++){
        //read in the first and second node's number as string to testify whether 
        //a node is a dispatch center
        //dispatch center A-i have the index of i + Ns in the array of adjacent list
        scanf("%s", string1);
        scanf("%s", string2);
        scanf("%d", &weight);
        u = atoi(string1);
        v = atoi(string2);
        if(string1[0] == 'A') u += Ns; //u is a dispatch center
        if(string1[0] == 'A') v += Ns; //v is a dispatch center
        temp = NewEdge();
        InsertEdge(temp, u, v, weight, graph);//insert the edge to the head of adjacent list in the graph structure
    }
   
    return;
}


/***************************
*4-Function Defination
***************************/
Edge NewEdge(void){
    Edge edge;
    edge = (Edge)malloc(sizeof(struct EdgeCDT));
    edge->end = -1;      //initialize the end and the weight of the edge to -1
    edge->weight = -1;   //represent it is a dummy node
    edge->next = NULL;
    return edge;
}

void InsertEdge(Edge edge, int u, int v, int weight, Graph graph){
    edge->end = v;
    edge->weight = weight;
    edge->next = graph->adjlist[u]->next;
    graph->adjlist[u]->next = edge;
}

Graph Initialize(int N, int Na, int Ns){
    Graph graph;
    graph = (Graph)malloc(sizeof(struct GraphCDT)); //distribute space for the graph
    graph->adjlist = (Edge*)malloc(sizeof(Edge)*(Ns+Na));
    graph->ambulance = (int*)malloc(sizeof(Na));
    graph->Dist = (int**)malloc(sizeof(int));
    graph->Path = (int**)malloc(sizeof(int));
    memset(graph->Dist, MaxTime, sizeof(int));//initialize the distance array of each node to infinite
    memset(graph->Path, 0, sizeof(int));      //initialize the path array of each node to 0
    Edge temp;
    for(int i = 0;i < Ns;i++){
        temp = NewEdge();
        graph->adjlist[i] = temp; //initialize:set all the adjacent list with a dummy head node
    }
    return graph;
}