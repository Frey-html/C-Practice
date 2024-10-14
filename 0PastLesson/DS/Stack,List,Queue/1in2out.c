//One way in, Two way out
//The is a special queue that can insert at the end and delete at the head and end
//input a insertion sequence and severals ouput sequence and judge if we can obtain these output sequence
/**********************************************************************************************************
Each input file contains one test case. For each case, the first line gives 2 positive integers N and K (≤10), 
which are the number of insertions and the number of queries, respectively. Then N distinct numbers are given 
in the next line, as the insertion sequence. Finally K lines follow, each contains N inserted numbers as the 
deletion sequence to be checked.
All the numbers in a line are separated by spaces.
***********************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define MaxLength 20

int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    int enqueue[MaxLength];          //the sequence of number that read in the queue
    int output[MaxLength];        //the output sequence to be tested
    int queue[MaxLength];          //the queue that can enqueue at the end and dequeue at head and end
    int cur_e = 0;      //current index of array enqueue[]
    int cur_o = 0;      //current index of array output[]
    int head = 0, rear = -1, length = 0;//head, rear and length of queue output

    //read in the enqueue sequence
    for(int i = 0;i < N;i++){
        scanf("%d", enqueue+i);
    }

    //read in the possible output sequence for K times and then judge if it is legal
    for(int i = 0;i < K;i++){
        for(int j = 0;j < N;j++){
            scanf("%d", output+j);
        }

        head = 0, rear = -1, length = 0;
        cur_e = cur_o = 0;

        while(cur_e < N){
            if(enqueue[cur_e] == output[cur_o]){
                cur_e++;
                cur_o++;
                continue;
            }
            queue[++rear] = enqueue[cur_e++];
            length++;
            while((queue[head] == output[cur_o] || queue[rear] == output[cur_o]) && length > 0){
                if(queue[head] == output[cur_o]){
                    head++;
                    length--;
                    cur_o++;
                }
                else{
                    rear--;
                    length--;
                    cur_o++;
                }
            }
        }
        while((queue[head] == output[cur_o] || queue[rear] == output[cur_o]) && length > 0){
                if(queue[head] == output[cur_o]){
                    head++;
                    length--;
                    cur_o++;
                }
                else{
                    rear--;
                    length--;
                    cur_o++;
                }
        }
        if(length == 0) printf("yes\n");
        else printf("no\n");
    }
    system("pause");
}

