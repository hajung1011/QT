#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <queue>

#define MAX_VERTEX 30
#define INF 1000

using namespace std;
class Dialog;

typedef struct Vertex
{
    int nVertex;			// Vertex Index
    int nEdgeCount;			// EdgeCount per Vertex
    struct Vertex* Next;	// Next Vertex
    struct Edge* EdgeHead;	// Edge Head Pointer
}Vertex;

typedef struct Edge
{
    int weight;				// Weight
    struct Edge* Next;		// Next Edge
    Vertex* FromVertex;		// From Vertex
    Vertex* TargetVertex;	// Target Vertex

}Edge;

class Graph
{
public:
    Graph();
    ~Graph();

    int **Matrix;			// 2 Dimensional array

    void AddVertex(int data);
    void DeleteVertex(int vertex);

    void AddEdge(int from, int target, int weight);
    void DeleteEdge(int from, int target);

    void DeleteVertexList();
    void DeleteEdgeList(Vertex* vertex);

    void SetVertex(int data);
    void SetEdge();

    int GetVertexCount();
    int GetEdgeCount(Vertex *vertex);

    void PrintGraph();
    void SetMatrix();
    void PrintMatrix();
    bool D_EmptyEdge(int n)
    {
        bool empty = false;
        Vertex* cursor = FindVertex(n);
        empty = EmptyEdge(cursor);
        return empty;
    }
private:
    bool EmptyVertex();
    bool EmptyEdge(Vertex* vertex);

    bool FullVertex();
    bool FullEdge(Vertex* vertex);

    void InitGraph();
    void InitVertex(Vertex* vertex);
    void InitEdge(Edge* edge);

    Vertex* CreateVertex(int data);
    Edge* CreateEdge(int from, int target, int weight);

    Vertex* FindVertex(int data);
    Edge* FindEdge(int from, int target);

    int ExistEdge(int from, int target, int weight);

private:
    int VertexCount;		// Vertex Count
    int MaxEdgeCount;		// Max EdgeCount per Vertex
    Vertex* VertexHead;		// Vertex Head Pointer
};

#endif // GRAPH_H
