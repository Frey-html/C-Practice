//there is n people put their hat as a stack, the heavier one person is, the bigger is his hat
//read in the stack of hat size and the weight of the people, output the order of person's index for leaving
//and pick up their own hats
//Sample Input:
//10
//12 19 13 11 15 18 17 14 16 20
//67 90 180 98 87 105 76 88 150 124
//Sample Output:
//3 4 8 6 10 2 1 5 9 7

//the first hat is the biggest, so the heaviest guy leave first, who has index 3

#include <stdio.h>
#include <stdlib.h>
#define Max 10001
typedef struct bindCDT *bind;

struct bindCDT{
    int hatsize;
    int weight;
    int order;
};

void Sort(int *array, int length);

int main(){
    int n;
    scanf("%d", &n);
    int hatstack[Max];
    int hat_sorted[Max];
    int weight[Max];
    int weight_sorted[Max];
    bind *relationship;
    relationship = (bind*)malloc(sizeof(bind)*n);
    for(int i = 0;i < n;i++){
        relationship[i] = (bind)malloc(sizeof(struct bindCDT));
    }
    for(int i = 0;i < n;i++){
        scanf("%d", hatstack+i);
        hat_sorted[i] = hatstack[i];
    }
    for(int i = 0;i < n;i++){
        scanf("%d", weight+i);
        weight_sorted[i] = weight[i];
    }
    Sort(hat_sorted, n);
    Sort(weight_sorted, n);

    for(int i = 0;i < n;i++){
        relationship[i]->hatsize = hat_sorted[i];
        relationship[i]->weight = weight_sorted[i];
    }
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            if(relationship[j]->weight == weight[i]){
                relationship[j]->order = i+1;
                break;
            }
        }
    }
    for(int i = 1;i <= n;i++){
        for(int j = 0;j < n;j++){
            if(relationship[j]->hatsize == hatstack[n-i]){
                printf("%d", relationship[j]->order);
                if(i != n) printf(" ");
            }
        }
    }
    
    system("pause");
}
    

void Sort(int *array, int length){
    if(length == 1 || length == 0) return;
    int length_left;
    int length_right;
    length_left = length/2;
    length_right = length - length_left;

    Sort(array, length_left);
    Sort(array+length_left, length_right);
    int *temp;
    temp = (int*)malloc(length*sizeof(int));
    int cur_left = 0, cur_right = 0;
    while(cur_left < length_left && cur_right < length_right){
        if(array[cur_left] < array[cur_right + length_left]){
            temp[cur_left + cur_right] = array[cur_left];
            cur_left++;
        }
        else{
            temp[cur_left + cur_right] = array[length_left+cur_right];
            cur_right++;
        }
    }
    if(cur_left == length_left){
        while(cur_right < length_right){
            temp[length_left + cur_right] = array[length_left + cur_right];
            cur_right++;
        }
    }
    if(cur_right == length_right){
        while(cur_left < length_left){
            temp[cur_left + length_right] = array[cur_left];
            cur_left++;
        }
    }
    for(int i = 0;i < length;i++){
        array[i] = temp[i];
    }
    free(temp);
}