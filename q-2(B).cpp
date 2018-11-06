/*
	Submitted by : Akash kulshreshtha 
	Roll no		 : 03
	Subject		 : Design and Analysis of Algorithm
	Assignment   : 3, Section A
	Question no. : 2(B) - from a given vertex in a weighted connected graph,find shortest path to other vertices using bellman's ford algorith
*/

#include<iostream>
using namespace std;

class Graph {
    
    struct Edge {
        
        int source;
        int destination;
        int weight;
    };
    
    int V;
    int E;
    
public:
    
    Edge *edge;
    
    static int index;
    
    Graph(int V, int E) {
        
        this->V = V;
        this->E = E;
        edge = new Edge[E];
    }
    
    void addEdge(int source, int destination, int weight)
    { if(index < E)
    {   edge[++index].source = source;
        edge[index].destination = destination;
        edge[index].weight = weight; }
    }
    
    int getV()
    { return V; }
    
    int getE()
    { return E; }
    
};

int Graph::index = -1;


void printMinDist(int source_distance[], int size) {
    
    for(int i = 0; i < size; i++)
    { cout << source_distance[i] << endl; }
    
    cout << endl;
}


void BellmanFord(Graph *graph, int src = 0) {
    
    int V = graph->getV();
    int E = graph->getE();
    
    int source_distance[V];
    
    for(int i = 0; i < V; i++)
    { source_distance[i] = INT_MAX; }
    
    source_distance[src] = 0;
    
    // Iterates through all the edges and Relaxes them. This process is done |V| - 1 times
    for(int i = 0; i < V - 1; i++)
    {
        for(int j = 0; j < E; j++)
        {
            int source = graph->edge[j].source;
            int dest = graph->edge[j].destination;
            int weight = graph->edge[j].weight;
            
            //Calculates and compares (<) Relaxation value. Ignores if the source value is Infinity/INT_MAX
            if(source_distance[source] != INT_MAX && source_distance[source] + weight < source_distance[dest])
            { source_distance[dest] = source_distance[source] + weight; }
        }
    }
    
    printMinDist(source_distance, V);
    
}



int main() {
    
    int V = 7, E = 10;
    Graph *graph = new Graph(V, E);
    
    // addEdge(source, destination, weight)
    
    graph->addEdge(0, 1, 6);
    graph->addEdge(0, 2, 5);
    graph->addEdge(0, 3, 5);
    
    graph->addEdge(1, 4, -1);
    
    graph->addEdge(2, 1, -2);
    graph->addEdge(2, 4, 1);
    
    graph->addEdge(3, 2, -2);
    graph->addEdge(3, 5, -1);
    
    graph->addEdge(4, 6, 3);
    
    graph->addEdge(5, 6, 3);
    
    BellmanFord(graph);
    
    return 0;
}


/** Since the Edges are E are getting relaxed V-1 times, its time complexity is given by Big-oh O(E * V).
 In the case of V = E, the time complexity would be O(n^2).
 
 Also, if it were a complete graph where each node is connected to every other node, then the value of E would be:-
    E = V * (V-1) / 2
 
 This multiplied by V - 1 would be:-
 
 V * (V-1) * (V - 1) / 2
 
 would give us a time complexity of O(n^3).
 
 Therefore, in the case of a complete graph; Bellman-Ford would take cubic amount of time as compared to quadratic time.
 
**/
