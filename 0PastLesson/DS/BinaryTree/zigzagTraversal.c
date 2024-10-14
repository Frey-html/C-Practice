#include <stdio.h>
#include <stdlib.h>

#define MaxNodes 100

typedef int ElementType;
typedef struct TreeNode *Tree;
struct TreeNode{
    ElementType Value;
    Tree Left;
    Tree Right;
};

void ZigZagTraversal(Tree root);
Tree BuildTree(ElementType *inorder, ElementType *postorder, int length);//通过中序遍历和后序遍历构建二叉树
Tree NewNode(void);

int main(){
    int n;                   //num of nodes
    ElementType inorder[MaxNodes];
    ElementType postorder[MaxNodes];
    Tree root;

    scanf("%d", &n);
    for(int i = 0;i < n;i++){
        scanf("%d", &inorder[i]);
    }
    for(int i = 0;i < n;i++){
        scanf("%d", &postorder[i]);
    }

    root = BuildTree(inorder, postorder, n);
    ZigZagTraversal(root);
    while(1);
    return 0;
}


Tree NewNode(void){
    Tree Node;
    Node = (Tree)malloc(sizeof(struct TreeNode));
    Node->Left = NULL;
    Node->Right = NULL;
    return Node;
}

Tree BuildTree(ElementType *inorder, ElementType *postorder, int length){
    if(length <= 0) return NULL;
    Tree Node = NewNode();
    int Node_Now = postorder[length - 1];
    Node->Value = Node_Now;
    int inorder_mid = 0, postorder_right = 0;    //caulculate the division of subtree's traversal
    while(inorder[inorder_mid] != Node_Now && inorder_mid < length - 1) inorder_mid++;
    //while(postorder[postorder_right] != inorder[inorder_mid + 1] && inorder_mid < length - 1) postorder_right++;
    postorder_right = inorder_mid;
    Node->Left = BuildTree(inorder, postorder, postorder_right);
    Node->Right = BuildTree(inorder + inorder_mid + 1, postorder + postorder_right, length - inorder_mid - 1);
    return Node; 
}

void ZigZagTraversal(Tree root){
    Tree queue[MaxNodes];    //the queue used to print level traversal of the tree
    int head = 0, tail = 0;  //head and tail of the queue
    int length = 1;          //length of the queue
    int nodenum = 1;         //num of nodes of this level in the tree
    //int cnt = nodenum;       //count the num of nodes already put in the level
    int level[MaxNodes];
    int level_now = -1;      //tail of array level now
    int order = 1;     //order = 1:output the level from left to right, order = -1:viseversa
    queue[0] = root;
    while(length != 0){
        nodenum = length;
        level_now = -1;
        for(int i = 0;i < nodenum;i++){
            if(queue[head]->Left != NULL){
                queue[++tail] = queue[head]->Left;
                length++;
            }
            if(queue[head]->Right != NULL){
                queue[++tail] = queue[head]->Right;
                length++;
            }
            level[++level_now] = queue[head]->Value;
            head++;
            length--;
        }
        if(order == -1){
            for(int i = 0;i <= level_now;i++){
                printf("%d ", level[i]);
            }
        }else{
            for(int i = level_now;i >= 0;i--){
                printf("%d ", level[i]);
            }
        }
        order *= -1;
    }
}