
#include <stdio.h>
#include <string.h>
#include "../headers/save_load.h"

int main(void)
{
    HashTable *ht = createHashTable(100);
    Graph *g = createGraph(100);

    if (ht == NULL || g == NULL)
    {
        printf("Failed to create data structures.\n");
        if (ht != NULL) freeHashTable(ht);
        if (g != NULL) freeGraph(g);
        return 1;
    }

    /* Add five people */
    struct Person people[5] = {
        {1, "Rahul", "suspect", 28, "9876543210", "Main suspect"},
        {2, "Aditya", "witness", 25, "9876543211", "Saw the incident"},
        {3, "Priya", "victim", 22, "9876543212", "Victim record"},
        {4, "Rohan", "witness", 30, "9876543213", "Nearby witness"},
        {5, "Sneha", "suspect", 27, "9876543214", "Under investigation"}
    };

    for (int i = 0; i < 5; i++)
        insertPerson(ht, people[i]);

    /* Add a relationship */
    addNode(g, 1);
    addNode(g, 2);
    addEdge(g, 1, 2, "CONTACT", 5);

    /* Save the case */
    if (!saveCase("test_case.txt", ht, g))
    {
        printf("FAIL: Could not save case.\n");
        freeHashTable(ht);
        freeGraph(g);
        return 1;
    }

    printf("Save test: PASS\n");

    /* Create fresh structures to load into */
    HashTable *loadedHT = createHashTable(100);
    Graph *loadedGraph = createGraph(100);

    if (loadedHT == NULL || loadedGraph == NULL)
    {
        printf("Failed to create loading structures.\n");
        freeHashTable(ht);
        freeGraph(g);
        if (loadedHT != NULL) freeHashTable(loadedHT);
        if (loadedGraph != NULL) freeGraph(loadedGraph);
        return 1;
    }

    if (!loadCase("test_case.txt", loadedHT, loadedGraph))
    {
        printf("FAIL: Could not load case.\n");
        freeHashTable(ht);
        freeGraph(g);
        freeHashTable(loadedHT);
        freeGraph(loadedGraph);
        return 1;
    }

    /* Verify all five people */
    int passed = 1;

    for (int i = 0; i < 5; i++)
    {
        struct Person *p = searchPerson(loadedHT, people[i].id);

        if (p == NULL || strcmp(p->name, people[i].name) != 0)
        {
            printf("FAIL: Person %d was not loaded correctly.\n",
                   people[i].id);
            passed = 0;
        }
    }

    if (passed)
        printf("Five-person load test: PASS\n");

    /* Verify the graph edge */
    EdgeNode *edge = getNeighbors(loadedGraph, 1);

    if (edge != NULL &&
        edge->destinationId == 2 &&
        strcmp(edge->type, "CONTACT") == 0 &&
        edge->weight == 5)
    {
        printf("Graph edge load test: PASS\n");
    }
    else
    {
        printf("Graph edge load test: FAIL\n");
        passed = 0;
    }

    freeHashTable(ht);
    freeGraph(g);
    freeHashTable(loadedHT);
    freeGraph(loadedGraph);

    return passed ? 0 : 1;
}
