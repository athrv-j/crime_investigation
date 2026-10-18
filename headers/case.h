
#ifndef CASE_H
#define CASE_H

#include "hash_table.h"
#include "graph.h"

#define MAX_LOCATIONS 100
#define MAX_EVIDENCE 100
#define MAX_EVENTS 100

typedef struct {
    HashTable *people;
    Graph *graph;

    struct Location locations[MAX_LOCATIONS];
    int locationCount;

    struct Evidence evidence[MAX_EVIDENCE];
    int evidenceCount;

    struct Event events[MAX_EVENTS];
    int eventCount;

} Case;

Case *createCase(int hashSize, int maxNodes);
void freeCase(Case *c);

int addLocation(Case *c, struct Location location);
int addEvidence(Case *c, struct Evidence evidence);
int addEvent(Case *c, struct Event event);

#endif
