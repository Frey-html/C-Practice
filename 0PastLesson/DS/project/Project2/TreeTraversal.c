/***********************************************
Tree Traversal

Function:input the partial results of a binary tree's traversals in in-order, pre-order, and post-order
output the complete results and the level order traversal sequence of the corresponding tree

Input:
(1)A positive integer N (≤100)
(2)Incomplete in-order traversal sequence
(3)Incomplete pre-order traversal sequence
(4)Incomplete post-order traversal sequence
The tree nodes are numbered from 1 to N and no number is given out of the range.
A - represents a missing number.

Output:
(1)Complete in-order traversal sequence
(2)Complete pre-order traversal sequence
(3)Complete post-order traversal sequence
(4)Complete level-order traversal sequence
***********************************************/
#include <stdio.h>
#include <stdlib.h>
#define MaxN 100
#define ElementType int

typedef struct TreeNode *Node;
struct TreeNode{
    Node left;
    Node right;
    ElementType value;
};

/********************
 *Function declaration
*********************/
Node NewNode(void);
//create a new node

Node BuildTree(ElementType *inorder, ElementType *preorder, ElementType *postorder, int length);
//build a tree through three incomplete traversals and complete the traversal sequence
//return node with value 0 if it is impossible

void LevelOrderTraversal(Node root);
//output the lever-order traversal of a tree

int NotIn(ElementType *Array, int length, int value);
//find if a value is concluded in an array
//return 1 if not found and 0 if found

void CompleteSequence(ElementType *Array, int length);
//complete the sequence:if exist a sequence that only missing one node
//it can be a complete sequence since the value is ranged from 1 to n

int main(){
    ElementType inorder[MaxN], preorder[MaxN], postorder[MaxN];
    Node Tree;
    int N = 0;
    scanf("%d", &N);
    //read in treee's traversals in in-order, pre-order and post-order, set 0 in the position of absent node
    char temp;
    int cnt_in = 0, cnt_pre = 0, cnt_post = 0;//record the number of missing nodes in three sequence
    for(int i = 0;i < N;i++){
        scanf(" %c", &temp);
        if(temp == '-'){
            inorder[i] = 0;
            cnt_in++;
        }
        else inorder[i] = temp - '0';
    }
    for(int i = 0;i < N;i++){
        scanf(" %c", &temp);
        if(temp == '-'){
            preorder[i] = 0;
            cnt_in++;
        }
        else preorder[i] = temp - '0';
    }
    for(int i = 0;i < N;i++){
        scanf(" %c", &temp);
        if(temp == '-'){
            postorder[i] = 0;
            cnt_in++;
        }
        else postorder[i] = temp - '0';
    }
    //complete the sequence:if exist a sequence that only missing one node
    //it can be a complete sequence since the value is ranged from 1 to n
    CompleteSequence(inorder, N);
    CompleteSequence(preorder, N);
    CompleteSequence(postorder, N);

    //Build binary Tree and complete three traversals' sequence
    Tree = BuildTree(inorder, preorder, postorder, N);
    cnt_in = cnt_pre = cnt_post = 0;
    for(int i = 0;i < N;i++){ //re count the number of missing value
        if(inorder[i] == 0){
            cnt_in++;
        }
        if(preorder[i] == 0){
            cnt_pre++;
        }
        if(postorder[i] == 0)
        {
            cnt_post++;
        }
    }
    while(cnt_in == 1 || cnt_pre == 1 || cnt_post == 1){
        //the tree is not built but sequence can be completed and build tree again
        CompleteSequence(inorder, N);
        CompleteSequence(preorder, N);
        CompleteSequence(postorder, N);
        Tree = BuildTree(inorder, preorder, postorder, N);
        cnt_in = cnt_pre = cnt_post = 0;
        for(int i = 0;i < N;i++){ //re count the number of missing value
            if(inorder[i] == 0){
                cnt_in++;
            }
            if(preorder[i] == 0){
                cnt_pre++;
            }
            if(postorder[i] == 0)
            {
                cnt_post++;
            }
        }
    }
    if(Tree->value == 0){
        printf("Impossible\n");
        system("pause");
        return 0;
    }

    //Output three traversals' sequence
    for(int i = 0;i < N;i++){
        printf("%d", inorder[i]);
        if(i != N-1) printf(" ");
    }
    printf("\n");
    for(int i = 0;i < N;i++){
        printf("%d", preorder[i]);
        if(i != N-1) printf(" ");
    }
    printf("\n");
    for(int i = 0;i < N;i++){
        printf("%d", postorder[i]);
        if(i != N-1) printf(" ");
    }
    printf("\n");
    //Output sequence of Lever-order Traversal
    LevelOrderTraversal(Tree);
    system("pause");
}

Node NewNode(void){
    Node root;
    root = (Node)malloc(sizeof(struct TreeNode));
    root->left = NULL;
    root->right = NULL;
    root->value = 0;
    return root;
}

Node BuildTree(ElementType *inorder, ElementType *preorder, ElementType *postorder, int length){
    Node root; 
    if(length == 0) return NULL;
    root = NewNode();
    int length_left = 0, length_right = 0; //the length of sequence of left subtree and right subtree
    int value_of_root = 0;
    int complete = 0;                      //if the traversals can build a tree
    int count_in = 0;                      //count the number of 0(that is nodes which don't have a value) in in-order sequence
    int count_pre = 0;                     //count the number of 0 in pre-order sequence
    int count_post = 0;                    //count the number of 0 in pre-order sequence
    for(int i = 0;i < length;i++){
        if(inorder[i] == 0){
            count_in++;
        }
        if(preorder[i] == 0){
            count_pre++;
        }
        if(postorder[i] == 0)
        {
            count_post++;
        }
    }

    //find the value of current node, if not found, set complete = 0
    if(preorder[0] != 0) value_of_root = preorder[0];
    else if(postorder[length-1] != 0 ) value_of_root = postorder[length - 1];
    
    if(value_of_root != 0){                 //found the value of current node directly
        complete = 0;
        for(length_left;length_left < length;length_left++){
            if(inorder[length_left] == value_of_root){
                complete = 1;
                break;
            }
        }
        if(complete == 1)length_right = length - length_left - 1; 
        //already found the position of current node in in-order sequence
        //so the length of left and right sub trees' length of sequence can be caulculated
        else if(count_in == 1){
            //only one value in in-order sequence is 0 and current node is not found
            //then the only 0's position is current node's position in in-order sequence
            for(length_left = 0;length_left < length;length_left++){
                if(inorder[length_left] == 0){
                    complete = 1;
                    break;
                }
            }
            length_right = length - length_left - 1;
        }
    }else{                                  //testify if value of current node can be found undirectly
        if((count_pre == 1 || count_post == 1) && count_in == 0){
            //pre-order or post-order sequence only omit the value of current node
            //and sequence of in-order traversal is complete
            //then the value and position of current node in in-order sequence can be found
            //by excluding all the value in present in pre-order or in-order sequence
            if(count_pre == 1){
                for(int i = 0;i < length;i++){
                    if(NotIn(preorder, length, inorder[i])){
                        length_left = i;
                        break;
                    }
                }
            }
            else if(count_post == 1){
                for(int i = 0;i < length;i++){
                    if(NotIn(postorder, length, inorder[i])){
                        length_left = i;
                        break;
                    }
                }
            }
            length_right = length - length_left - 1;
        }
        if(length == 1 && (count_pre == 0 || count_in == 0 || count_post == 0)){ 
            //sepecial situation when length == 1
            //the value of root can be found only need one sequence that is not empty
            //and the left sub-tree and right sub-tree must be empty
            if(count_in == 0){
                value_of_root = inorder[0];
            }
            if(count_pre == 0){
                value_of_root = preorder[0];
            }
            if(count_post == 0){
                value_of_root = postorder[0];
            }
            complete = 1;
            length_left = length_right = 0;
        }
    }

    if(complete == 0){                      //can't build a tree        
        return root;                        //return a node with value 0
    }
    else{
        inorder[length_left] = value_of_root;
        preorder[0] = value_of_root;
        postorder[length-1] = value_of_root;
        //complete the key value of current node in three traversals' sequence

        root->value = value_of_root;
        root->left = BuildTree(inorder, preorder + 1, postorder, length_left);
        root->right = BuildTree(inorder + length_left + 1, preorder + length_left + 1, postorder + length_left, length_right);
    }
    if(root->left != NULL && root->left->value == 0 || root->right != NULL && root->right->value == 0){ //has an sub tree that can't be constructed
        root->value = 0;
    }
    return root;
}

void LevelOrderTraversal(Node root){
    Node queue[MaxN];
    int front = 0, rear = 0;
    queue[0] = root;
    while(rear - front >= 0){
        printf("%d", queue[front]->value);
        if(queue[front]->left != NULL){
            queue[++rear] = queue[front]->left;
        }
        if(queue[front]->right != NULL){
            queue[++rear] = queue[front]->right;
        }
        front++;
        if(rear-front >= 0) printf(" "); //print a blank after value if it is not the end of the line
    }
}

int NotIn(ElementType *Array, int length, int value){
    for(int i = 0;i < length;i++){
        if(Array[i] == value) return 1;
    }
    return 0;
}

void CompleteSequence(ElementType *Array, int length){
    int count = 0;
    int index_zero = 0;
    int *sequence;
    sequence = (int*)malloc((length+1) * sizeof(int)); //sequence[i] represent whether i is present in the array
    for(int i = 1;i <= length;i++){ //initialize
        sequence[i] = 0;
    }
    for(int i = 0;i < length;i++){ //find how many nodes are missing
        if(Array[i] == 0){
            count++;
            index_zero = i;
        }
        else{
            sequence[Array[i]] = 1;
        }
    }
    if(count == 1){     //only one node is missing, then the sequence can be completed
        for(int i = 1;i <= length;i++){
            if(sequence[i] == 0){
                Array[index_zero] = i;  //make up the missing number
                break;
            }
        }
    }
}