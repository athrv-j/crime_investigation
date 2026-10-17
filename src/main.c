
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/hash_table.h"
#include "../headers/graph.h"
#include "../headers/save_load.h"
#include "../headers/ranking.h"
#include "../headers/cycle.h"

#define MAX_NODES 100
#define HASH_SIZE 100

void addPersonMenu(HashTable *ht, Graph *g)
{
    struct Person p = {0};

    printf("\nEnter Person ID: ");
    if (scanf("%d", &p.id) != 1)
    {
        printf("Invalid ID.\n");
        while (getchar() != '\n');
        return;
    }

    if (p.id < 0 || p.id >= MAX_NODES)
    {
        printf("ID must be between 0 and %d.\n", MAX_NODES - 1);
        while (getchar() != '\n');
        return;
    }

    if (searchPerson(ht, p.id) != NULL)
    {
        printf("Person ID already exists.\n");
        while (getchar() != '\n');
        return;
    }

    getchar(); /* Consume newline */

    printf("Enter name: ");
    if (fgets(p.name, sizeof(p.name), stdin) == NULL)
        return;
    p.name[strcspn(p.name, "\n")] = '\0';

    printf("Enter role: ");
    if (fgets(p.role, sizeof(p.role), stdin) == NULL)
        return;
    p.role[strcspn(p.role, "\n")] = '\0';

    printf("Enter age: ");
    if (scanf("%d", &p.age) != 1)
    {
        printf("Invalid age.\n");
        while (getchar() != '\n');
        return;
    }

    getchar();

    printf("Enter contact: ");
    if (fgets(p.contact, sizeof(p.contact), stdin) == NULL)
        return;
    p.contact[strcspn(p.contact, "\n")] = '\0';

    printf("Enter notes: ");
    if (fgets(p.notes, sizeof(p.notes), stdin) == NULL)
        return;
    p.notes[strcspn(p.notes, "\n")] = '\0';

    insertPerson(ht, p);
    addNode(g, p.id);

    printf("Person added successfully.\n");
}

void searchPersonMenu(HashTable *ht)
{
    int id;

    printf("\nEnter Person ID to search: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Invalid ID.\n");
        while (getchar() != '\n');
        return;
    }

    struct Person *p = searchPerson(ht, id);

    if (p == NULL)
    {
        printf("Person not found.\n");
        return;
    }

    printf("\nID: %d\nName: %s\nRole: %s\nAge: %d\n"
           "Contact: %s\nNotes: %s\n",
           p->id, p->name, p->role, p->age,
           p->contact, p->notes);
}

int main(void)
{
    HashTable *ht = createHashTable(HASH_SIZE);
    Graph *g = createGraph(MAX_NODES);

    if (ht == NULL || g == NULL)
    {
        printf("Failed to initialize the system.\n");
        freeHashTable(ht);
        freeGraph(g);
        return 1;
    }

    int choice;

    do
    {
        printf("\n========== CRIME INVESTIGATION SYSTEM ==========\n");
        printf("1. Add Person\n");
        printf("2. Search Person by ID\n");
        printf("3. Autocomplete Name (not connected yet)\n");
        printf("4. Find Connection (BFS - not connected yet)\n");
        printf("5. Show Connected People (DFS - not connected yet)\n");
        printf("6. Shortest Route (Dijkstra - not connected yet)\n");
        printf("7. Rank Leads\n");
        printf("8. Check for Cycles\n");
        printf("9. Save Case\n");
        printf("10. Load Case\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
                addPersonMenu(ht, g);
                break;

            case 2:
                searchPersonMenu(ht);
                break;

            case 3:
            case 4:
            case 5:
            case 6:
                printf("This feature is not connected yet.\n");
                break;

            case 7:
            {
                int evidenceCount[MAX_NODES] = {0};
                rankLeads(g, evidenceCount, MAX_NODES);
                break;
            }

            case 8:
                printf("Cycle detected: %s\n",
                       hasCycle(g) ? "YES" : "NO");
                break;

            case 9:
                if (saveCase("case.txt", ht, g))
                    printf("Case saved successfully to case.txt.\n");
                else
                    printf("Failed to save case.\n");
                break;

            case 10:
                if (loadCase("case.txt", ht, g))
                    printf("Case loaded successfully from case.txt.\n");
                else
                    printf("Failed to load case. Check the file and IDs.\n");
                break;

            case 0:
                printf("Exiting system. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 0);

    freeHashTable(ht);
    freeGraph(g);

    return 0;
}
