/*
	Submitted by : akash kulshreshtha 
	Roll no		 : 03
	Subject		 : Design and Analysis of Algorithm
	Assignment   : 3, Section A
	Question no. : 2 - From a given vertex in weighted graph ,find shortest path to other vertices using DIJKSTRA'S ALGORITHM
*/

#include<iostream>
using namespace std;

#define VERTEX 6


//Function to find the index of the vertex with the minimum distance value from source which has not yet been visited
int getMinIndex(bool visited[], int source_distance[]) {
    
    int min = INT_MAX;
    int index = -1;
    
    for(int i = 1; i < VERTEX; i++)
    {
        if(visited[i] == false)
        {
            if(source_distance[i] < min)
            { min = source_distance[i];
                index = i; }
        }
    }
    
    return index;
}



int main() {
    
    int adjacency_matrix[VERTEX][VERTEX] = {
        
        { 0, 5, 0, 9, 2, 0 },
        { 5, 0, 2, 0, 0, 0 },
        { 0, 2, 0, 3, 0, 0 },
        { 9, 0, 3, 0, 0, 2 },
        { 2, 0, 0, 0, 0, 3 },
        { 0, 0, 0, 2, 3, 0 }
        
    };
    
    int source_distance[VERTEX];
    bool visited[VERTEX];
    
    //Initialize each vertex's distance from source as Infinity or Max permissible value of Integer
    for(int i = 0; i < VERTEX; i++)
    { source_distance[i] = INT_MAX;
        visited[i] = false; }
    
    
    //Initialize source vertex distance as 0 and mark it as visited
    source_distance[0] = 0;
    visited[0] = true;
    
    
    //Initialize those vertices' distance from source where there is an edge from source to that vertex
    for(int i = 1; i < VERTEX; i++)
    { if(adjacency_matrix[0][i] != 0)
    { source_distance[i] = adjacency_matrix[0][i]; }
    }
    
    
    //The main logic loop which will do the Relaxation process for the given vertices. This will run for |Vertex| - 1 times
    for(int i = 0; i < VERTEX - 1; i++)
    {
        int index = getMinIndex(visited, source_distance);
        
        if(index == -1)
        { break; }
        
        visited[index] = true;
        
        for(int j = 0; j < VERTEX; j++)
        {
            if(adjacency_matrix[index][j] != 0)
            {
                if(source_distance[index] + adjacency_matrix[index][j] < source_distance[j])
                { source_distance[j] = source_distance[index] + adjacency_matrix[index][j]; }
                
            }
        }
        
    }
    
    cout << "Minimum Distance from Source Vertex 1 to every other Vertex:-" << endl << endl;
    
    for(int i = 0; i < VERTEX; i++)
    { cout << i+1 << " --> " << source_distance[i] << " units " << endl; }
    
    cout << endl;
    
    return 0;
}


/*
 
 Time Complexity:-
 
 Dijkstra Algorithm is used to find the shortest distance to |V| no. of vertices in a graph.
 Since we cannot determine exactly how many vertices it will Relax as it totally depends on the graph,
 but it is clearly evident that at most it would Relax |V| no. of vertices.
 
 This is proposed from the hypothesis that a given vertex may be connected to every other vertex in a given graph.
 Such type of graph will be called a Complete graph where each vertex is connected to every other vertex.
 
 Therefore, |V| no. vertices are relaxed against each vertex in a complete graph.
 Hence, |V| * |V| which will be Big-Oh O(|V|^2). Let n = |V| then, the time complexity is O(n^2).
 
 */


/* Test cases
 
 Set VERTEX = 6
 
 {0, 50, 45, 10, 0, 0,},
 {0, 0, 10, 15, 0, 0},
 {0, 0, 0, 0, 30, 0},
 {10, 0, 0, 0, 15, 0},
 {0, 20, 35, 0, 0, 0},
 {0, 0, 0, 0, 3, 0}
 
 
 Set VERTEX = 9
 {0, 4, 0, 0, 0, 0, 0, 8, 0},
 {4, 0, 8, 0, 0, 0, 0, 11, 0},
 {0, 8, 0, 7, 0, 4, 0, 0, 2},
 {0, 0, 7, 0, 9, 14, 0, 0, 0},
 {0, 0, 0, 9, 0, 10, 0, 0, 0},
 {0, 0, 4, 14, 10, 0, 2, 0, 0},
 {0, 0, 0, 0, 0, 2, 0, 1, 6},
 {8, 11, 0, 0, 0, 0, 1, 0, 7},
 {0, 0, 2, 0, 0, 0, 6, 7, 0}
 
 */
