/****************
In this project, you are supposed to implement a B+ tree of order 3, with the following operations:
initialize, insert (with splitting) and search. The B+ tree should be able to print out itself.
****************/ 
#include <stdio.h>
#include <stdlib.h>

#define Order 3
#define LeastKey 2

typedef struct Node* BPlusTree;
typedef int ElementType;

struct Node{
    struct Node* father;
    //pointer that point to the node's father
    ElementType numsOfKeys;
    //the number of keys stored in leaves or index stored in the non-leaf node
    ElementType keys[Order+1];
    //array that stores the keys
    struct Node *child[Order+1];
    //array that stores the pointers to the node's children
    int isleaf;
    //wether the node is a leaf
    int isroot;
    //wether the node is root
};

BPlusTree NewNode(void);
//Create a new node

BPlusTree NewTree(void);
//Create a new root

void Insert(BPlusTree root, ElementType element);
//Insert a root into a BplusTree

int AddKey(BPlusTree node, ElementType element);
//add a key into the node and return it's position in the ascending keylist in the node

void AddChild(BPlusTree node, int position, BPlusTree child);
//add a pointer to a new child in node

int CheckAndAdjust(BPlusTree node);
//split the node if it is needed, return if the node is legal

BPlusTree Split(BPlusTree node);
//split the origin node into left part and return right part

BPlusTree Find(BPlusTree root, ElementType element);
//Find the proper leaf for elelment to insert in

void Print(BPlusTree root);
//Print the BPlusTree in level order





int main(){

}

BPlusTree NewNode(void){
    BPlusTree node;
    node = (BPlusTree)malloc(sizeof(struct Node));
    node->father = NULL;
    node->numsOfKeys = 0;
    for(int i = 0;i < Order + 1;i++){
        node->child[i] = NULL;
    }
    node->isleaf = 0;
    node->isroot = 0;
    return node;
}


BPlusTree NewTree(void){
    BPlusTree node = NewNode();
    node->isroot = 1;
    node->isleaf = 1;
    return node;
}

void Insert(BPlusTree root, ElementType element){
    BPlusTree leaf = Find(root, element); //the proper leaf to insert in
    int done = 0;
    AddKey(leaf, element);
    while(CheckAndAdjust(root) != 1){
        root = root->father;
    }
}

int AddKey(BPlusTree node, ElementType element){
    int position = 0;
    while(element > node->keys[position]){
        position++;
    }
    
    for(int i = node->numsOfKeys;i > position;i--){
        node->keys[i] = node->keys[i-1];
    }
    node->keys[position] = element;
    return position;
}

void AddChild(BPlusTree node, int position, BPlusTree child){
    for(int i = node->numsOfKeys;i > position + 1;i--){
        node->child[i] = node->child[i-1];
    }
    node->child[position+1] = child;
}

int CheckAndAdjust(BPlusTree node){
    if(node->isleaf == 1){
        if(node->numsOfKeys <= Order) return 1;
        //no nead to split
        else{
            BPlusTree rightpart = Split(node);
            //spilt is done, then add an index to their father
            rightpart->isleaf = 1;
            if(node->isroot){
                BPlusTree newroot = NewTree();
                node->father = newroot;
                rightpart->father = newroot;
                node->isroot = 0;
                newroot->numsOfKeys = 1;
                AddKey(newroot, rightpart->keys[0]);
                newroot->child[0] = node;
                newroot->child[1] = rightpart;
            }else{
                int position = AddKey(node->father, rightpart->keys[0]);
                AddChild(node->father, position, rightpart);
            }
            return 0;
        }
    }else{
        if(node->numsOfKeys < Order) return 1;
        else{
            BPlusTree rightpart = Split(node);
        }
    }
}


//存疑
BPlusTree Split(BPlusTree node){
    BPlusTree rightpart = NewNode();
    rightpart->father = node->father;
    rightpart->numsOfKeys = LeastKey;
    for(int i = 0;i < LeastKey;i++){
        rightpart->keys[i] = node->keys[Order-LeastKey+i];
    }
    node->numsOfKeys -= LeastKey;
    return rightpart;
}

BPlusTree Find(BPlusTree root, ElementType element){
    if(root->isleaf){
        // for(int i = 0;i < root->numsOfKeys;i++){
        //     if(element == root->keys[i]){
        //         return root;
        //     }
        //     return NULL;
        // }
        return root;
    }
    //if this node is a leaf, return the node 

    for(int i = 0;i < root->numsOfKeys;i++){
        if(element < root->keys[i]){
            return Find(root->child[i], element);
        }
    }
    return Find(root->child[root->numsOfKeys], element);
    //if this node is not a leaf, find the element in its child
}

void Print(BPlusTree root){
    BPlusTree queue[1000];
    queue[0] = root;
    int head = 0;
    int rear = 1;
    int childOfThisLevel = 1;
    int childOfNextLevel = 0;
    while(head < rear){
        childOfNextLevel = 0;
        for(int i = 0;i < childOfThisLevel;i++){
            printf("[");
            for(int k = 0;k < queue[head]->numsOfKeys;k++){
                printf("%d", queue[head]->keys[k]);
                if(k != queue[head]->numsOfKeys - 1){
                    printf(",");
                }
            }
            printf("]");

            if(!queue[head]->isleaf){
                for(int k = 0;k < queue[head]->numsOfKeys + 1;k++){
                    queue[++rear] = queue[head]->child[i];
                }
                childOfNextLevel += queue[head]->numsOfKeys + 1;
            }
            head++;
        }
        printf("\n");
        childOfThisLevel = childOfNextLevel;
    }
}




