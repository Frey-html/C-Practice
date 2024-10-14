#include <stdio.h>
#include <stdlib.h>
#define ElementType int
#define MinData 0x10000000
#define MinPQSize 10000

typedef struct HeapStruct *PriorityQueue;
struct HeapStruct{
    int Capacity;
    int Size;
    ElementType *Elements;
};

PriorityQueue Initialize(int MaxElements);
void PercolateUp(PriorityQueue H, int index, int value);
void PercolateDown(PriorityQueue H, int index, int value);
void Insert(ElementType X, PriorityQueue H);
ElementType DeleteMin(PriorityQueue H);

int main(){
    return 0;
}

PriorityQueue Initialize(int MaxElements){
    PriorityQueue H;
    if(MinPQSize < MaxElements){
        printf("Priority Size is too small\n");
        return NULL;
    }
    H = (PriorityQueue)malloc(sizeof(struct HeapStruct));
    if(H == NULL){
        print("Malloc out of space");
        return NULL;
    }
    H->Elements = (ElementType*)malloc((MaxElements+1)*sizeof(ElementType));
    if(H->Elements == NULL){
        print("Malloc out of space");
        return NULL;
    }
    H->Capacity = MaxElements;
    H->Size = 0;
    H->Elements[0] = MinData; //set the sentinel
}

void PercolateUp(PriorityQueue H, int index, int value){
    int i = index;
    while(H->Elements[i / 2] > value){
        H->Elements[i] = H->Elements[i/2];
        i /= 2;
    }
    H->Elements[i] = value;
}

void PercolateDown(PriorityQueue H, int index, int value){
    int i, child;
    for(i = index;i * 2 <= H->Size;i = child){
        child = i * 2;
        if(child != H->Size && H->Elements[child + 1] < H->Elements[child]){
            child++;
        }
        if(value > H->Elements[child]){
            H->Elements[i] = H->Elements[child];
        }
        else break;
    }
    H->Elements[i] = value;
}

void Insert(ElementType X, PriorityQueue H){
    if(H->Size == H->Capacity){
        printf("Insert in a full heap");
        return;
    }
    PercolateUp(H, ++H->Size, X);
}

ElementType DeleteMin(PriorityQueue H){
    if(H->Size == 0){
        printf("Delete from an empty heap\n");
        return;
    }
    int min = H->Elements[0], max = H->Elements[H->Size--];
    PercolateDown(H, max, 1);
    return min;
}