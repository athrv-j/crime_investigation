#include <stdio.h>
#include <stdlib.h>
#include "../headers/hash_table.h"

int hash (int key, int size){  // it is used to convert person id to table index ex hash(101,10) so table(1)
    return key%size;
}

HashTable* createHashTable(int size){
    HashTable* ht= (HashTable*)malloc(sizeof(HashTable));
    ht->table=(PersonNode**)malloc(size*sizeof(PersonNode*));
    ht->size=size;
    ht->count=0;
    
    for(int i =0;i<size;i++){
        ht->table[i]=NULL;
    }
    return ht;
}
// createHashTable()
//        ↓
// creates table
//        ↓
// returns address
//        ↓
// ht


void insertPerson(HashTable *ht, struct Person person){
    int index = hash(person.id, ht->size);
    PersonNode *newNode = (PersonNode*)malloc(sizeof(PersonNode));
    newNode->personId = person.id;
    newNode->person=person;

    if(ht->table[index]==NULL){
        ht->table[index]=newNode;
        ht->count++;
    }
}
// person
// ┌──────────────────────┐
// │ id = 101             │
// │ name = "Rahul"       │
// │ role = "suspect"     │
// │ age = 25             │
// │ contact = ...        │
// │ notes = ...          │
// └──────────────────────┘
//              │
//              │ copy
//              ↓
// newNode->person


struct Person* searchPerson(HashTable* ht, int personId){
    int index= hash(personId,ht->size);
    if(ht->table[index]!=NULL && ht->table[index]->personId == personId){
        return &(ht->table[index]->person);
    }
    return NULL;
}

void deletePerson(HashTable* ht, int personId){
    int index=hash(personId,ht->size);
    if(ht->table[index]->personId == personId && ht->table[index]!=NULL){
        free(ht->table[index]);
        ht->table[index]=NULL;
        ht->count--;
    }
}

void freeHashTabke(HashTable*ht){
    for(int i=0;i<ht->size;i++){
        if(ht->table[i]!=NULL)
            free(ht->table[i]);
    }
    free(ht->table);
    free(ht);
}
