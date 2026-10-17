#include <stdlib.h>
#include <string.h>
#include "../headers/graph.h"

Graph* createGraph(int maxNodes) {
    Graph *g = (Graph*)malloc(sizeof(Graph));
    g->adjacencyList = (EdgeNode**)malloc(maxNodes * sizeof(EdgeNode*));
    g->inDegree = (int*)malloc(maxNodes * sizeof(int));
    g->maxNodes = maxNodes;
    g->nodeCount = 0;
    
    for (int i = 0; i < maxNodes; i++) {
        g->adjacencyList[i] = NULL;
        g->inDegree[i] = 0;
    }
    return g;
}

void addNode(Graph *g, int nodeId) {
    if (nodeId < g->maxNodes) {
        g->nodeCount++;
    }
}

void addEdge(Graph *g, int sourceId, int destId, char *type, int weight) {
    if (sourceId >= g->maxNodes || destId >= g->maxNodes) return;
    
    // Create new edge node
    EdgeNode *newEdge = (EdgeNode*)malloc(sizeof(EdgeNode));
    newEdge->destinationId = destId;
    strcpy(newEdge->type, type);
    newEdge->weight = weight;
    newEdge->next = NULL;
    
    // Add to source's adjacency list
    if (g->adjacencyList[sourceId] == NULL) {
        g->adjacencyList[sourceId] = newEdge;
    } else {
        EdgeNode *current = g->adjacencyList[sourceId];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newEdge;
    }
    
    // Update in-degree of destination
    g->inDegree[destId]++;
}

EdgeNode* getNeighbors(Graph *g, int nodeId) {
    if (nodeId >= g->maxNodes) return NULL;
    return g->adjacencyList[nodeId];
}

int getInDegree(Graph *g, int nodeId) {
    if (nodeId >= g->maxNodes) return 0;
    return g->inDegree[nodeId];
}

void freeGraph(Graph *g) {
    for (int i = 0; i < g->maxNodes; i++) {
        EdgeNode *current = g->adjacencyList[i];
        while (current != NULL) {
            EdgeNode *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(g->adjacencyList);
    free(g->inDegree);
    free(g);
}