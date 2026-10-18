
#include <stdlib.h>
#include <string.h>
#include "../headers/graph.h"

Graph* createGraph(int maxNodes)
{
    if (maxNodes <= 0)
        return NULL;

    Graph *g = malloc(sizeof(Graph));

    if (g == NULL)
        return NULL;

    g->adjacencyList = calloc((size_t)maxNodes, sizeof(EdgeNode*));
    g->inDegree = calloc((size_t)maxNodes, sizeof(int));
    g->nodeExists = calloc((size_t)maxNodes, sizeof(int));

if (g->adjacencyList == NULL ||
    g->inDegree == NULL ||
    g->nodeExists == NULL)
{
    free(g->adjacencyList);
    free(g->inDegree);
    free(g->nodeExists);
    free(g);
    return NULL;
}
    g->maxNodes = maxNodes;
    g->nodeCount = 0;

    return g;
}


void addNode(Graph *g, int nodeId)
{
    if (g == NULL || nodeId < 0 || nodeId >= g->maxNodes)
        return;

    if (g->nodeExists[nodeId] == 0)
    {
        g->nodeExists[nodeId] = 1;
        g->nodeCount++;
    }
}


void addEdge(Graph *g, int sourceId, int destId,
             char *type, int weight)
{
    
    if (g == NULL ||
        sourceId < 0 || sourceId >= g->maxNodes ||
        destId < 0 || destId >= g->maxNodes ||
        type == NULL)
    {
        return;
    }

    addNode(g, sourceId);
    addNode(g, destId);
    
    EdgeNode *newEdge = malloc(sizeof(EdgeNode));
    
    newEdge->timespan = 0;

    if (newEdge == NULL)
        return;

    newEdge->destinationId = destId;

    // Safely copy the relationship type into the fixed-size field.
    strncpy(newEdge->type, type, sizeof(newEdge->type) - 1);
    newEdge->type[sizeof(newEdge->type) - 1] = '\0';

    newEdge->weight = weight;
    newEdge->next = NULL;

    // Append the edge to the source node's adjacency list.
    if (g->adjacencyList[sourceId] == NULL)
    {
        g->adjacencyList[sourceId] = newEdge;
    }
    else
    {
        EdgeNode *current = g->adjacencyList[sourceId];

        while (current->next != NULL)
        {
            current = current->next;
        }

        current->next = newEdge;
    }

    g->inDegree[destId]++;
}

EdgeNode* getNeighbors(Graph *g, int nodeId)
{
    if (g == NULL || nodeId < 0 || nodeId >= g->maxNodes)
        return NULL;

    return g->adjacencyList[nodeId];
}

int getInDegree(Graph *g, int nodeId)
{
    if (g == NULL || nodeId < 0 || nodeId >= g->maxNodes)
        return 0;

    return g->inDegree[nodeId];
}

void freeGraph(Graph *g)
{
    if (g == NULL)
        return;

    for (int i = 0; i < g->maxNodes; i++)
    {
        EdgeNode *current = g->adjacencyList[i];

        while (current != NULL)
        {
            EdgeNode *temp = current;
            current = current->next;
            free(temp);
        }
        free(g->nodeExists);
    }

    free(g->adjacencyList);
    free(g->inDegree);
    free(g);
}
