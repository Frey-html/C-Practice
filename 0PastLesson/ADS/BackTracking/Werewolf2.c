//week6
//back tracking algorithm
//核心--回溯分支的依据：是否说谎和是否是狼人，后者check更简单，前者会导致身份未完全判断，check中需要增加回溯
//回溯核心：只需要确定哪些是狼人，剩下的就是村民
//且可以从编号大的开始确认，可以极大的减少分支，且第一个结果就是所需结果
#include <stdio.h>
#include <stdlib.h>
#define MaxPlayer 100
#define MaxResult 101

int * result[MaxResult];
int count = 0;

void BackTraking(int *remark, int *identity, int n, int wolf_remain, int N, int M, int L);

int Check(int *remark, int *identity, int n, int wolf_remain, int N, int M, int L);

//sort the result
void Sort(int M);

//output the first result
void Output(int M);

int main(){
    int N, M, L;
    char sign;
    scanf("%d %d %d", &N, &M, &L);
    int remark[MaxPlayer+1];            //the remark of all the players
    //int lier[MaxPlayer+1] = {0};        //if lies[i] = 1, represent player i lies 
    int identity[MaxPlayer+1] = {0};    //-1 represents werewolf  1 represents human
    
    for(int i = 1;i <= N;i++){
        scanf("%c%d", &sign, remark+i);
        if(sign == '-') remark[i]*=-1;
    }
    BackTraking(remark, identity, 0, M, N, M, L);
    Sort(M);
    Output(M);
    return 0;
}

void BackTraking(int *remark, int *identity, int n, int wolf_remain, int N, int M, int L){
    int judge = 0;
    judge = Check(remark, identity, n, wolf_remain, N, M, L);
    if(judge == 1 && n != N){
        //option 1, player n+1 is werewolf
        if(wolf_remain > 0){
                identity[n+1] = -1;
                BackTraking(remark, identity, n+1, wolf_remain-1, N, M, L);
                //undo
                identity[n+1] = 0;
        }
        //option 2, player n+1 is human
        if(wolf_remain == 0){
            for(int i = n+1;i <= N;i++){
                identity[i] = 1;
            }
            BackTraking(remark, identity, N, 0, N, M, L);
            //undo
            for(int i = n+1;i <= N;i++){
                identity[i] = 0;
            }
        }
        else{
            identity[n+1] = 1;
            BackTraking(remark, identity, n+1, wolf_remain, N, M, L);
            //undo
            identity[n+1] = 0;
        }
    }
    //find a result
    if(n == N && judge == 1){
        int temp = 0;
        result[count] = (int*)malloc(M*sizeof(int));
        for(int i = N;i >= 1;i--){
            if(identity[i] < 0){
                result[count][temp++] = i;
            }
        }
        count++;
    }
    return;
}

int Check(int *remark, int *identity, int n, int wolf_remain, int N, int M, int L){
    if(n == 0) return 1;
    if(n == N && wolf_remain != 0) return 0;

    int liers = 0, werewolf_liers = 0;
    int remark_toward;
    //count the werewolf, liers and werewolf liers
    for(int i = 1;i <= n;i++){
        remark_toward = remark[i];
        if(remark_toward < 0) remark_toward *= -1;
        //player i is a lier
        if(identity[remark_toward] * remark[i] < 0){
            liers++;
            //lier is a werewolf
            if(identity[i] < 0){
                werewolf_liers++;
            }
        }
    }
    if(liers > L) return 0;
    if(werewolf_liers == M) return 0;
    if(wolf_remain == 0)
    if(n == N && liers != L) return 0;
    if(n == N && werewolf_liers == 0) return 0;

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
        printf("%d", result[0][i]);
        if(i != M-1) printf(" ");
        }
    }
}
