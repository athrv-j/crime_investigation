
#include <stdio.h>
#include <stdlib.h>

#include "../headers/ranking.h"
#include "../headers/heap.h"

// Calculate a lead's score
int scoreLead(int edgeCount, int evidenceCount)
{
    return edgeCount * 10 + evidenceCount * 20;
}

// Rank all people from highest score to lowest
void rankLeads(Graph *g, int *evidenceCount, int n)
{
    if (g == NULL || evidenceCount == NULL || n <= 0)
        return;

    if (n > g->maxNodes)
        n = g->maxNodes;

    MaxHeap *heap = createHeap(n);

    if (heap == NULL)
    {
        printf("Failed to create ranking heap.\n");
        return;
    }

    // Calculate and insert each person's score
    for (int i = 0; i < n; i++)
    {
        int edgeCount = 0;
        EdgeNode *neighbor = getNeighbors(g, i);

        while (neighbor != NULL)
        {
            edgeCount++;
            neighbor = neighbor->next;
        }

        Lead lead;
        lead.personId = i;
        lead.score = scoreLead(edgeCount, evidenceCount[i]);

        if (!heapInsert(heap, lead))
        {
            printf("Failed to insert lead %d.\n", i);
            freeHeap(heap);
            return;
        }
    }

    // Extract leads in descending score order
    printf("Lead ranking (highest score first):\n");

    while (heap->size > 0)
    {
        Lead lead = heapExtractMax(heap);

        if (lead.personId == -1)
            continue;

        printf("Person %d | Score: %d\n",
               lead.personId, lead.score);
    }

    freeHeap(heap);
}
