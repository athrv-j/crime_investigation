#ifndef GRAPH_H
#define GRAPH_H

#include "struct.h"

typedef struct EdgeNode {
    int destinationId;
    char type[100];
    int weight;
    struct EdgeNode *next;
} EdgeNode;

typedef struct {
    EdgeNode **adjacencyList;
    int *inDegree;
    int maxNodes;
    int nodeCount;
} Graph;

// Functions
Graph* createGraph(int maxNodes);
void addNode(Graph *g, int nodeId);
void addEdge(Graph *g, int sourceId, int destId, char *type, int weight);
EdgeNode* getNeighbors(Graph *g, int nodeId);
int getInDegree(Graph *g, int nodeId);
void freeGraph(Graph *g);

#endif