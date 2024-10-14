//input a sequence 
//construct a complete binary search tree
//output the level-order traversal of the tree
#include <stdio.h>
#include <stdlib.h>
#define ElementType int
#define MaxLength 1001

typedef struct CompleteBST *CBST;
struct CompleteBST{
    int Size;
    ElementType *Elements;
};

CBST NewTree(void){
    CBST tree;
    tree = (CBST)malloc(sizeof(struct CompleteBST));
    return tree;
}

void Initialize(CBST tree, int size){
    tree->Size = size;
    tree->Elements = (ElementType*)malloc((size+1)*sizeof(ElementType));
    //the node start from index 1 
    //it is convenient to obtain the index of the node's child because it's a complete binary tree
}

void MergeSort(ElementType *array, int length);

void BuildTree(ElementType* cbt, ElementType* sorted_sequence, int length, int index);

int main(){
    int length;
    int sequence[MaxLength];
    CBST tree = NewTree();
    scanf("%d", &length);
    for(int i = 0;i < length;i++){
        scanf("%d", &sequence[i]);
    }
    Initialize(tree, length);
    MergeSort(sequence, length);

    BuildTree(tree->Elements, sequence, tree->Size, 1);
    for(int i = 1;i <= length;i++){
        printf("%d", tree->Elements[i]);
        if(i != length) printf(" ");
    }
    system("pause");
}

void MergeSort(ElementType *array, int length){
    if(length == 1) return;

    int l_left = length/2, l_right = length - l_left;
    int i_left = 0, i_right = 0;
    int *temp = (ElementType*)malloc(length*sizeof(ElementType));
    
    MergeSort(array, l_left);
    MergeSort(array + l_left, l_right);
    //merge the result
    while(i_left < l_left && i_right < l_right){
        if(*(array+i_left) < *(array + l_left + i_right)){
            temp[i_left + i_right] = *(array+i_left);
            i_left++;
        }else{
            temp[i_left + i_right] = *(array+l_left+i_right);
            i_right++;
        }
    }
    if(i_left < l_left && i_right >= l_right){
        while(i_left < l_left){
            temp[i_left + l_right] = array[i_left];
            i_left++;
        }
    }
    if(i_left >= l_left && i_right < l_right){
        while(i_right < l_right){
            temp[l_left + i_right] = array[l_left + i_right];
            i_right++;
        }
    }
    for(int i = 0;i < length;i++){
        array[i] = temp[i];
    }
    free(temp);
}

void BuildTree(ElementType* cbt, ElementType* sorted_sequence, int length, int index){
    if(length == 0) return;
    if(length == 1){
        cbt[index] = sorted_sequence[0];
        return;
    }

    int length_l = 0, length_r = 0;
    int length_prelevel = 1;
    int length_lastlevel;
    int lastlevel_left = 0;
    int lastlevel_right = 0;
   
    while((length_prelevel + 1) * 2 - 1 < length){
        length_prelevel = (length_prelevel + 1) * 2 - 1;
    }
    length_lastlevel = length - length_prelevel;
    if(length_lastlevel <= (length_prelevel+1)/2){
        lastlevel_left = length_lastlevel;
        lastlevel_right = 0;
    }else{
        lastlevel_left = (length_prelevel+1)/2;
        lastlevel_right = length_lastlevel - lastlevel_left;
    }
    length_l = (length_prelevel - 1)/2 + lastlevel_left;
    length_r = (length_prelevel - 1)/2 + lastlevel_right;

    cbt[index] = sorted_sequence[length_l];
    BuildTree(cbt, sorted_sequence, length_l, 2*index);
    BuildTree(cbt, sorted_sequence + length_l + 1, length_r, 2*index+1);
}