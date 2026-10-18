
#include <stdlib.h>
#include "../headers/case.h"

Case *createCase(int hashSize, int maxNodes)
{
    if (hashSize <= 0 || maxNodes <= 0)
        return NULL;

    Case *c = calloc(1, sizeof(Case));

    if (c == NULL)
        return NULL;

    c->people = createHashTable(hashSize);
    c->graph = createGraph(maxNodes);

    if (c->people == NULL || c->graph == NULL)
    {
        freeCase(c);
        return NULL;
    }

    return c;
}

void freeCase(Case *c)
{
    if (c == NULL)
        return;

    freeHashTable(c->people);
    freeGraph(c->graph);
    free(c);
}

int addLocation(Case *c, struct Location location)
{
    if (c == NULL || c->locationCount >= MAX_LOCATIONS)
        return 0;

    for (int i = 0; i < c->locationCount; i++)
    {
        if (c->locations[i].id == location.id)
            return 0;
    }

    c->locations[c->locationCount++] = location;
    return 1;
}

int addEvidence(Case *c, struct Evidence evidence)
{
    if (c == NULL || c->evidenceCount >= MAX_EVIDENCE)
        return 0;

    for (int i = 0; i < c->evidenceCount; i++)
    {
        if (c->evidence[i].id == evidence.id)
            return 0;
    }

    c->evidence[c->evidenceCount++] = evidence;
    return 1;
}

int addEvent(Case *c, struct Event event)
{
    if (c == NULL || c->eventCount >= MAX_EVENTS)
        return 0;

    for (int i = 0; i < c->eventCount; i++)
    {
        if (c->events[i].id == event.id)
            return 0;
    }

    c->events[c->eventCount++] = event;
    return 1;
}
