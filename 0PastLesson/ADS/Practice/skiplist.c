#include "skiplist.h"

//create a new node 
//level:level of the node
Node *createNode(int level, keyType key, valueType val){
    Node *newNode;
    //allocate space for a new node
    newNode = (Node *)malloc(sizeof(Node) + level * sizeof(Node*));
    if(newNode == NULL){
        return NULL;
    }
    newNode->key = key;
    newNode->value = val;
    return newNode;
}

//create a skiplist
SkipList *createList(void){
    //allocate space for a new skiplist
    SkipList *newList = (SkipList *)malloc(sizeof(SkipList));
    if(newList == NULL){
        return NULL;
    }
    //level of skiplist is 0 initially
    newList->level = 0;
    //create an empty headnode
    Node *head = createNode(MaxLevel, -1, 0);
    if(head == NULL) return NULL;
    //set the end of every level of skip list(NULL)
    for(int i = 0;i < MaxLevel;i++){
        head->next[i] = NULL;
    }
    //generate seed for random algorithm
    srand(time(0));
    newList->head = head;
    return newList;
}

//return a random level of a node when create a new node
int randomLevel(void){
    int level = 1;
    while(rand() % 2 == 0){
        level += 1;
    }
    if(level < MaxLevel) return level;
    return MaxLevel;
}

//return a pointer to the needed node
Node *search(SkipList *list, keyType key){
    //current node and next node
    Node *cur = list->head, *next = NULL;
    //current level
    int level = list->level - 1;
    while(level >= 0){
        //search in this level
        //find the first node whose key is greater or equal to search key
        //or go down to lower level
        while((next = cur->next[level]) && next->key < key){
            cur = next;
        }
        if(next != NULL && next->key == key){
            return next;
        }
        level--;
    }
    //if there is still no result after searching in the lowest level
    //return NULL
    return NULL;
}

//insert a value into a skiplist
//return True if success to insert else return False
int insertKey(SkipList *list, keyType key, valueType value){
    Node *update[MaxLevel];//array of the insert position of each level
    Node *cur = list->head, *next = NULL;
    int level = list->level - 1;
    //find insert position of every level
    while(level >= 0){
        while((next = cur->next[level]) && next->key < key){
            cur = next;
        }
        update[level] = cur;
        level--;
    }
    //if search key already exist in the skiplist
    if(next != NULL && next->key == key){
        next->value = value;
        return 1;
    }
    //generate new node
    int newLevel;
    newLevel = randomLevel();
    Node * node = createNode(newLevel, key, value);
    if(node == NULL) return 0;
    //update the max level of skiplist
    if(newLevel > list->level){
        for(int i = list->level;i < newLevel;i++){
            update[i] = list->head;
        }
        list->level = newLevel;
    }
    //insert level by level
    for(int i = 0;i < newLevel;i++){
        node->next[i] = update[i]->next[i];
        update[i]->next[i] = node;
    }
    return 1;
}

//delete a node from skiplist
//return True if success to delete else return False
int deleteKey(SkipList *list, keyType key){
    Node *update[MaxLevel];//array of the insert position of each level
    Node *cur = list->head, *next = NULL;
    int level = list->level - 1;
    //find delete position of every level
    while(level >= 0){
        while((next = cur->next[level]) && next->key < key){
            cur = next;
        }
        update[level] = cur;
        level--;
    }
    //now next is node to be deleted
    //can't find the key to be deleted
    if(next == NULL || next->key != key){
        return 0;
    }
    //delete by level
    for(int i = list->level - 1;i >= 0;i--){
        if(update[i]->next[i] == next){
            update[i]->next[i] = next->next[i];
        }
        //the highest level become empty after deletion
        //reduce the level of skiplist
        if(list->head->next[i] == NULL){
            list->level--;
        }
    }
    free(next);
    return 1;
}

//print skiplist
void printList(SkipList *list){
    //print the skiplist from highest level
    if(list->level == 0 && list->head->next[0] == NULL) printf("skiplist is empty now\n");
    Node *cur;
    for(int i = list->level - 1;i >= 0;i--){
        printf("level %d:\n", i);
        cur = list->head;
        while((cur = cur->next[i]) != NULL){
            printf("key:%d val:%.3lf\t", cur->key, cur->value);
        }
        printf("\n");
    }
}

//free skiplist
void freeList(SkipList *list){
    if(list == NULL) return;
    Node *cur, *next;
    cur = list->head->next[0];
    while((next = cur->next[0]) != NULL){
        free(cur);
        cur = next;
    }
    free(list->head);
    free(list);
    return;
}