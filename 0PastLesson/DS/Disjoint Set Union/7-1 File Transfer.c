#include<stdio.h>
#include<stdlib.h>

#define ElementType int

typedef struct DisjointSet_CDT *DisjSet;
struct DisjointSet_CDT{
    ElementType *Elements;
    int Size;
};

DisjSet Initialize(int size);
ElementType Find(ElementType x, DisjSet S);
void Union(ElementType a, ElementType b, DisjSet S);

int main(){
    int size;
    int a, b;
    char order;
    int connected = 0;
    int ConnectedComponents = 0;
    scanf("%d", &size);
    DisjSet set;
    set = Initialize(size);
    
    scanf("%c", &order);
    while(order != 'S'){
        scanf("%d %d", &a, &b);
        if(order == 'I'){
            Union(a, b, set);
        }
        if(order == 'C'){
            if(Find(a, set) == Find(b, set)) printf("yes\n");
            else printf("no\n");
        }
        scanf("%c", &order);
    }
    for(int i = 1;i < size+1;i++){
        if(set->Elements[i] < connected){
            connected = set->Elements[i];
        }
        if(set->Elements[i] < 0){
            ConnectedComponents++;
        }
    }
    connected *= -1;
    if(connected < size){
        printf("There are %d components.\n", ConnectedComponents);
    }
    else printf("The network is connected.");
    system("pause");
}

DisjSet Initialize(int size){
    DisjSet set;
    set = (DisjSet)malloc(sizeof(struct DisjointSet_CDT));
    set->Elements = (ElementType*)malloc((size+1)*sizeof(ElementType));
    for(int i = 0; i < size+1;i++){
        set->Elements[i] = -1;
    }
    return set;
}

ElementType Find(ElementType x, DisjSet S){
    if(S->Elements[x] < 0) return x;
    else return S->Elements[x] = Find(S->Elements[x], S);
}

void Union(ElementType a, ElementType b, DisjSet S){
    int root1, root2, size2;
    root1 = Find(a, S);
    root2 = Find(b, S);
    if(root1 != root2){
        size2 = S->Elements[root2];
        S->Elements[b] = root1;
        S->Elements[root1] += size2;
    }
    return;
}


