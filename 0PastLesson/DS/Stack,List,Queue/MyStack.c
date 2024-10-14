#include <stdio.h>
#include <stdlib.h>
#include <genlib.h>
#define Max 10

struct StacktCDT{
    int Top;
    void* Array[Max];
};

typedef struct StacktCDT  *Stack;

Stack CreateStack(){
    Stack S;
    S = New(Stack);
    S->Top = -1;
    return S;
}

int IsEmpty(Stack S){
    if(S->Top == -1) return 1;
    return 0;
}

void *Pop(Stack S){
    if(IsEmpty(S))
        Error("Pop from an empty stack");
    else{
        void *ans;
        ans = S->Array[S->Top--];
        return ans;
    }
}

void Push(Stack S, void *obj){
    if(S->Top == Max - 1)
        Error("Push in an full stack");
    else{
        S->Array[++S->Top] = obj;
    }
}



