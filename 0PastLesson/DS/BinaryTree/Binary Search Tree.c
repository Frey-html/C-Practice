#include <stdio.h>
#include <stdlib.h>
typedef int *ElementType;

typedef struct BinaryTree *Tree;

struct BinaryTree{
    Tree Left;
    Tree Right;
    ElementType Element;
};

int main(){

}