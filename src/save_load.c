
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/save_load.h"

int saveCase(const char *filename, HashTable *ht, Graph *g)
{
    if (filename == NULL || ht == NULL || g == NULL)
        return 0;

    FILE *fp = fopen(filename, "w");

    if (fp == NULL)
        return 0;

    /* Save all people */
    for (int i = 0; i < ht->size; i++)
    {
        PersonNode *current = ht->table[i];

        while (current != NULL)
        {
            struct Person p = current->person;

            if (fprintf(fp, "PERSONS: %d|%s|%s|%d|%s|%s\n",
                        p.id, p.name, p.role, p.age,
                        p.contact, p.notes) < 0)
            {
                fclose(fp);
                return 0;
            }

            current = current->next;
        }
    }

    /* Save every directed graph edge */
    for (int i = 0; i < g->maxNodes; i++)
    {
        EdgeNode *edge = getNeighbors(g, i);

        while (edge != NULL)
        {
            if (fprintf(fp, "EDGES: %d|%d|%s|%d\n",
                        i, edge->destinationId,
                        edge->type, edge->weight) < 0)
            {
                fclose(fp);
                return 0;
            }

            edge = edge->next;
        }
    }

    if (fclose(fp) != 0)
        return 0;

    return 1;
}

int loadCase(const char *filename, HashTable *ht, Graph *g)
{
    if (filename == NULL || ht == NULL || g == NULL)
        return 0;

    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
        return 0;

    char line[1500];

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        /* Remove newline characters */
        line[strcspn(line, "\r\n")] = '\0';

        if (strncmp(line, "PERSONS: ", 9) == 0)
        {
            struct Person p = {0};

            char *field = strtok(line + 9, "|");
            if (field == NULL) goto invalid_record;
            p.id = atoi(field);

            field = strtok(NULL, "|");
            if (field == NULL) goto invalid_record;
            snprintf(p.name, sizeof(p.name), "%s", field);

            field = strtok(NULL, "|");
            if (field == NULL) goto invalid_record;
            snprintf(p.role, sizeof(p.role), "%s", field);

            field = strtok(NULL, "|");
            if (field == NULL) goto invalid_record;
            p.age = atoi(field);

            field = strtok(NULL, "|");
            if (field == NULL) goto invalid_record;
            snprintf(p.contact, sizeof(p.contact), "%s", field);

            field = strtok(NULL, "|");
            if (field == NULL) goto invalid_record;
            snprintf(p.notes, sizeof(p.notes), "%s", field);

            /* Avoid duplicate person IDs */
            if (searchPerson(ht, p.id) == NULL)
                insertPerson(ht, p);
        }
        else if (strncmp(line, "EDGES: ", 7) == 0)
        {
            int source, destination, weight;
            char type[100];

            char *field = strtok(line + 7, "|");
            if (field == NULL) goto invalid_record;
            source = atoi(field);

            field = strtok(NULL, "|");
            if (field == NULL) goto invalid_record;
            destination = atoi(field);

            field = strtok(NULL, "|");
            if (field == NULL) goto invalid_record;
            snprintf(type, sizeof(type), "%s", field);

            field = strtok(NULL, "|");
            if (field == NULL) goto invalid_record;
            weight = atoi(field);

            if (source < 0 || destination < 0 ||
                source >= g->maxNodes || destination >= g->maxNodes)
            {
                goto invalid_record;
            }

            addNode(g, source);
            addNode(g, destination);
            addEdge(g, source, destination, type, weight);
        }

        continue;

invalid_record:
        fclose(fp);
        return 0;
    }

    if (ferror(fp))
    {
        fclose(fp);
        return 0;
    }

    if (fclose(fp) != 0)
        return 0;

    return 1;
}
