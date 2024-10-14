#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MaxLevel 10
typedef int keyType;
typedef double valueType;

//structure of node
typedef struct NodeCDT{
    keyType key;     //key of node
    valueType value; //value of node
    struct NodeCDT *next[]; //flexible array
} Node;

//structure of skiplist
typedef struct SkipListCDT{
    int level;   //level
    Node *head;  //pointer to head node
} SkipList;

//create a new node 
//level:level of the node
Node *createNode(int level, keyType key, valueType val);

//create a skiplist
SkipList *createList(void);

//return a random level of a node when create a new node
int randomLevel(void);

//return a pointer to the needed node
Node *search(SkipList *list, keyType key);

//insert a value into a skiplist
//return True if success to insert else return False
int insertKey(SkipList *list, keyType key, valueType value);

//delete a node from skiplist
//return True if success to delete else return False
int deleteKey(SkipList *list, keyType key);

//print skiplist
void printList(SkipList *list);

//free skiplist
void freeList(SkipList *list);

#endif