#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Board_Size 8

int count = 0;

void Backtraking(int *board, int n);

int Check(int *board, int n);


int main(){
    int *board;
    board = (int *)malloc((Board_Size+1)*sizeof(int));
    memset(board, 0, (Board_Size+1)*sizeof(int));
    Backtraking(board, 0);
    printf("there is %d solutions", count);
}

void Backtraking(int *board, int n){
    int judge = 0;
    judge = Check(board, n);
    if(judge == 1){
        if(n == Board_Size){//find a result
            for(int i = 1;i <= n;i++){
                printf("%d", board[i]);
            }
            count++;
            printf("%c", '\n');
        }else{
            for(int i = 1;i <= Board_Size;i++){
                board[n+1] = i;
                Backtraking(board, n+1);
            }
        }
    }
    board[n] = 0;//undo
    return;
}

int Check(int *board, int n){
    if(n == 0) return 1;
    int judge = 1;
    for(int i = 1;i < n;i++){
        double slop = (double)(board[n] - board[i])/(n-i);
        if(board[i] == board[n] || slop == 1 || slop == -1){
            judge = 0;
            break;
        }
    }
    return judge;
}