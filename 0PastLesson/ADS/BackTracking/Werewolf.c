//week6
//back tracking algorithm
#include <stdio.h>
#include <stdlib.h>
#define MaxPlayer 100
#define MaxResult 101

int * result[MaxResult];
int count = 0;

void BackTraking(int *remark, int *lier, int *identity, int n, int liers_remain, int N, int M, int L);

int Check(int *remark, int *lier, int *identity, int n, int liers_remain, int N, int M, int L);

void AddResult(int *remark, int *lier, int *identity, int liers_remain, int N, int M, int L);

void Add(int *identity, int N, int M);

//sort the result
void Sort(int M);

//output the first result
void Output(int M);

int main(){
    int N, M, L;
    char sign;
    scanf("%d %d %d", &N, &M, &L);
    int remark[MaxPlayer+1];            //the remark of all the players
    int lier[MaxPlayer+1] = {0};        //if lies[i] = 1, represent player i lies 
    int identity[MaxPlayer+1] = {0};    //-1 represents werewolf  1 represents human
    
    for(int i = 1;i <= N;i++){
        scanf("%c%d", &sign, remark+i);
        if(sign == '-') remark[i]*=-1;
    }
    BackTraking(remark, lier, identity, 0, L, N, M, L);
    Sort(N);
    Output(M);
    printf("count:%d", count);
    return 0;
}

void BackTraking(int *remark, int *lier, int *identity, int n, int liers_remain, int N, int M, int L){
    //身份补全
    int judge = 0;
    judge = Check(remark, lier, identity, n, liers_remain, N, M, L);
    if(judge == 1 && n != N){
        //int conflict = 0;//remark conflict pruning
        int remark_of = remark[n+1];//the person that remark[n+1] point to
        if(remark[n+1] < 0) remark_of *= -1; 
        int temp;//store the current value of identity[n+1]

        //option 1, remark[n+1] is a lie
        if(liers_remain > 0){//there still liers in the people to be tested
            temp = identity[remark_of];
            //remark[n+1] is a lie and remark conflic not happen
            if(temp == 0 || temp != 0 && remark[n+1] * temp < 0){
                lier[n+1] = 1;
                if(remark[n+1] < 0){
                    identity[remark_of] = 1;
                }else{
                    identity[remark_of] = -1;
                }
                BackTraking(remark, lier, identity, n+1, liers_remain-1, N, M, L);
                //undo
                lier[n+1] = 0;
                identity[remark_of] = temp;
            }  
        }
        //option 2, remark[n+1] is not a lie
        temp = identity[remark_of];
        //remark[n+1] is truth and remark conflic not happen
        if(temp == 0 || temp != 0 && remark[n+1] * temp > 0){
            if(remark[n+1] < 0){
                identity[remark_of] = -1;
            }else{
                identity[remark_of] = 1;
            }
            BackTraking(remark, lier, identity, n+1, liers_remain, N, M, L);
            //undo
            identity[remark_of] = temp;
        }
    }
    //find a result
    //check again?
    if(n == N && judge == 1){
        AddResult(remark, lier, identity, liers_remain, N, M, L);
    }
    return;
}

int Check(int *remark, int *lier, int *identity, int n, int liers_remain, int N, int M, int L){
    if(n == 0) return 1;
    if(n == N) return 0;
    int werewolf = 0, werewolf_liers = 0;
    //count the werewolf and the werewolf liers
    for(int i = 1;i <= N;i++){
        if(identity[i] == -1){
            werewolf++;
            if(lier[i] == 1){
                werewolf_liers++;
            }
        }
    }
    if(werewolf > M) return 0;
    if(werewolf_liers == M) return 0;
    return 1;
}

void Sort(int M){
    if(count <= 1) return;
    int *temp;
    int judge;
    for(int i = 0;i < count;i++){
        for(int j = 0;j < count-i-1;j++){
            judge = 0;
            for(int k = 0;k < M;k++){
                if(result[j][k] < result[j+1][k]){
                    judge = 1;
                    break;
                }
            }
            if(judge){
                temp = result[j];
                result[j] = result[j+1];
                result[j+1] = temp;
            }
        }
    }
}

void Output(int M){
    if(count == 0) printf("No Solution");
    else{
        for(int i = 0;i < M;i++){
        printf("%d ", result[0][i]);
        }
    }
}

void AddResult(int *remark, int *lier, int *identity, int liers_remain, int N, int M, int L){
    if(liers_remain != 0) return;
    
}