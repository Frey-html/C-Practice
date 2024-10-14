#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/* 
    HuffmanTree node, at first all the nodes are treated as HuffmanTree
    consists of the weight(frequency) and left,right son pointer.
*/
typedef struct Node* HTree;
struct Node{
    int weight;
    HTree Left,Right;
};
/* 
    MinHeap structure, used to store nodes and execute DeleteMin to get min-weight-node
    size is number of Elements in the Heap
    Elements is used to store Nodes
*/
typedef struct Heap* MinHeap;
struct Heap{
    int size;
    int capcity;
    HTree Elements;
};

/* 
    There are two basic requirements about HuffmanTree
    1. Huffman Tree has minimum WPL, The WPL is the sum of the weighted path lengths of all leaf nodes of the tree
    WPL = w1*l1+ w2*l2 + w3*l3 ...wi is the weight(frequency) of leaf node
    2. None of the code of a character in Huffman Code is the prefix code of another charactor
*/
MinHeap Initialize(int n); //function used to initialize a heap
MinHeap BuildHeap(int *weight, int n); //used to build a min-heap
void Insert(MinHeap H, HTree T); //used to insert a single node into the min-heap
HTree DeleteMin(MinHeap H); //used to delete the minimum node and return it
HTree BuildHuffmanTree(MinHeap H); //used to build a HuffmanTree on the base of the min-heap
void PrintHeap(MinHeap H); //useless test function

int WPL(HTree T, int L); //function used to calculate the WPL of a HuffmanTree
int JudgePrefix(char *a, char *b); //Judge whether a string is the prefix code of another string


MinHeap Initialize(int n){
    // initialize a heap
    MinHeap H = (MinHeap)malloc(sizeof(struct Heap));
    H->size = 0;
    H->capcity = n;
    // allocate one more space to set the guard node
    H->Elements = (HTree)malloc(sizeof(struct Node)*(n+1));
    H->Elements[0].weight = -1;
    return H;
}
void Insert(MinHeap H, HTree T){
    // insert a HuffmanTree node into the min-heap
    int i = ++H->size;
    /* classic algorithm, Element[0].weight is the smallest one
        Faster than Swap()
    */
    for(i; H->Elements[i/2].weight>T->weight; i/=2){
        // find the correct place by comparing
        H->Elements[i] = H->Elements[i/2];
        H->Elements[i/2] = *T;
    }
    //insert the node *T into correct place 
    H->Elements[i] = *T;
}
MinHeap BuildHeap(int *weight, int n){
    // this function is used to build a min-heap
    MinHeap H = Initialize(n);
    HTree HNode = (HTree)malloc(sizeof(struct Node));
    for(int i=0; i<n; i++){
        // use a simple iteration to insert a HuffmanTree node into the min-heap
        HNode->weight = weight[i];
        HNode->Left = HNode->Right = NULL;
        Insert(H, HNode);
    }
    free(HNode);
    return H;
}
HTree DeleteMin(MinHeap H){
    // DeleteMin and return the node
    int i, child;
    // classic O(logN) algorithm
    HTree MinElement,LastElement;
    MinElement = (HTree)malloc(sizeof(struct Node));
    LastElement = (HTree)malloc(sizeof(struct Node));
    // save the min element
    *MinElement = H->Elements[1];
    // take the last element and reset size
    *LastElement = H->Elements[H->size--];  
    //find smaller child
    for(i=1; i*2<=H->size; i=child){
        child = i*2;
        if(child != H->size && H->Elements[child+1].weight<H->Elements[child].weight){
            child++;
        }
        // Perlocate one level
        if(LastElement->weight > H->Elements[child].weight){
            H->Elements[i] = H->Elements[child];
        }
        else break; // find the proper position
    }
    // insert lastelement into the proper position
    H->Elements[i] = *LastElement;
    return MinElement;     
}    
HTree BuildHuffmanTree(MinHeap H){
    // this function is used to build a Huffman Tree
    int i;
    HTree T;
    //we need to record the size because H->size will change soon
    int NowSize = H->size;
    for(i=1; i<NowSize; i++){
        T = (HTree)malloc(sizeof(struct Node));
        /* 
            According to the operation of Huffman, each time execute DeleteMin twice,
            and attach them to the left and right of the new node T
        */
        T->Left = DeleteMin(H);
        T->Right = DeleteMin(H);
        // fresh the weight of the new node:sum of weights of its children
        T->weight = T->Left->weight + T->Right->weight;
        //insert T into min-heap
        Insert(H,T);
    }
    /*
        The last one element after the iteration is the root of the Huffman Tree,
        DeleteMin again to get the node and return
    */
    T = DeleteMin(H); 
    return T;
}
int WPL(HTree T, int L){
    // function used to calculate the WPL of a Huffman Tree
    // The base case of the recursion: find the leaf node and return weight*length
    if(T->Left == NULL && T->Right == NULL){
        return T->weight * L;
    }
    // not leaf node: continue recursion downwards and get sum of results
    else return WPL(T->Left,L+1) + WPL(T->Right,L+1);
}
int JudgePrefix(char *a, char *b){
    // Judge the second requirement
    int index = 0;
    // get the length of string
    int lena = strlen(a);
    int lenb = strlen(b);
    // choose the smaller one
    int len = (lena < lenb) ? lena:lenb;
    // find the index of the first different character in two strings
    while(a[index] == b[index] && index < len) index++;
    // if index is equal to len, then the smaller string must be the prefix of the other string
    if(index == len) return 1;
    else return 0;
}
void PrintHeap(MinHeap H){
    for(int i=0;i<H->size;i++){
        printf("%d ",H->Elements[i+1].weight);
    }
}
int main(){
    int N;
    int weight[256] = {0};
    scanf("%d",&N);
    char c[N];
    memset(c,0,N);
    // read the data
    for(int i=0; i<N; i++){
        scanf(" %c %d",&c[i],&weight[i]);
    }
    // build min-heap on the base of weight
    MinHeap H = BuildHeap(weight,N);
    // build Huffman Tree on the base of min-heap
    HTree T = BuildHuffmanTree(H);
    // calculate the WPL of the Huffman Tree as standard WPL to compare with students'
    int HuffmanWPL = WPL(T, 0);
    int M;
    scanf("%d",&M);
    char stu[N][64];
    for(int i=0;i<M;i++){
        memset(stu,0,N*64);
        int StuWPL = 0; // WPL of students' code
        int flag = 1; // Yes or No
        for(int j=0;j<N;j++){
            getchar(); // pass the extra '\n'
            scanf("%c %s",&c[j],&stu[j]);
            StuWPL += strlen(stu[j]) * weight[j]; //calculate the students' WPL 
            // Judge whether the second requirement is met
            for(int k=0; k<j; k++){
                if(JudgePrefix(stu[j],stu[k])){
                    flag = 0;
                    break;
                }
            }
        }
        // if the students' WPL is different with WPL of the Huffman Tree, print No
        if(StuWPL != HuffmanWPL){
            flag = 0;
        }
        if(flag ==1) printf("Yes\n");
        else printf("No\n");
    }
}