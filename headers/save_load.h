#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include "hash_table.h"
#include "graph.h"

/* Save people and graph edges to a file */
int saveCase(const char *filename, HashTable *ht, Graph *g);

/* Load people and graph edges from a file */
int loadCase(const char *filename, HashTable *ht, Graph *g);

#endif
