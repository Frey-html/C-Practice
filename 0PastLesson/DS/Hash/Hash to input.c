/***********************
7-1 Hashing - Hard Version (18 分)
Given a hash table of size N, we can define a hash function H(x)=x%N. Suppose that the linear probing is used to solve collisions, we can easily obtain the status of the hash table with a given sequence of input numbers.

However, now you are asked to solve the reversed problem: reconstruct the input sequence from the given status of the hash table. Whenever there are multiple choices, the smallest number is always taken.

Input Specification:
Each input file contains one test case. For each test case, the first line contains a positive integer N (≤1000), which is the size of the hash table. The next line contains N integers, separated by a space. A negative integer represents an empty cell in the hash table. It is guaranteed that all the non-negative integers are distinct in the table.

Output Specification:
For each test case, print a line that contains the input sequence, with the numbers separated by a space. Notice that there must be no extra space at the end of each line.

Sample Input:
11
33 1 13 12 34 38 27 22 32 -1 21
结尾无空行
Sample Output:
1 13 12 21 33 34 38 27 22 32
结尾无空行
******************************/


#include <stdio.h>
#define MaxN 1001


int main(){
    int HashTable[MaxN];
    int N;
    int load = 0;       //the number of load of hashtable
    int max = 0;
    scanf("%d", &N);
    for(int i = 0;i < N;i++){
        scanf("%d", HashTable+i);
        if(HashTable[i] >= 0) load++;
        if(HashTable[i] > max) max = HashTable[i];
    }
    max+=1;

    int count[MaxN] = {0}; //count[i] = 1 represent HashTable[i] has been taken in the sequence already get
    int num = 0;         //count the number of already got in the sequence
    int min = 0;
    int found = 0;       //whether a eligible number have been found
    int index = -1;
    int fullfilled = 0;
    int lowerbound = -1;
    while(num < load){
        found = 0;
        index = -1;
        lowerbound = -1;
        while(found != 1){
            min = max;
            for(int i = 0;i < N;i++){
                if(HashTable[i] < 0) continue;
                if(!count[i] && HashTable[i] < min && HashTable[i] > lowerbound){
                    min = HashTable[i];
                    index = i;
                }
            }
            if(min % N == index){
                found = 1;          //该元素填入时不存在linear probing
            }else{
                fullfilled = 1;
                if(min % N < index){ //原位在linear probing结果前
                    for(int i = min % N;i < index;i++){
                        if(count[i] != 1){
                            fullfilled = 0; //该元素存在linear probing且前面有空位，则不该在序列此位置进行hash
                            break;
                        }
                    }
                }else{//原位在linear probing结果后
                    for(int i = min % N;i < N;i++){
                        if(count[i] != 1){
                            fullfilled = 0; 
                            break;
                        }
                    }
                    for(int i = 0;i < index;i++){
                        if(count[i] != 1){
                            fullfilled = 0; 
                            break;
                        }
                    }
                }
                if(fullfilled == 1) found = 1; //该元素存在linear probing且前面无空位，可以在输入序列此位置hash
                else lowerbound = HashTable[index]; //下一次找寻只需找比此时大的，因为更小的已经检验过
            }
        }
        count[index] = 1; //标记为已添入
        num++;
        printf("%d ", HashTable[index]);
    }
    return 0;
}