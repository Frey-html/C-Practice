//week6
//back tracking algorithm
//核心--回溯分支的依据：是否说谎和是否是狼人，后者check更简单，前者会导致身份未完全判断，check中需要增加回溯
//回溯核心：只需要确定哪些是狼人，剩下的就是村民
//且可以从编号大的开始确认，可以极大的减少分支，且第一个结果就是所需结果
#include <stdio.h>
#include <stdlib.h>
#define MaxPlayer 101
#define MaxResult 101

int * result[MaxResult];
int count = 0;

void BackTraking(int *remark, int *identity, int n, int wolf_remain, int N, int M, int L);

int Check(int *remark, int *identity, int wolf_remain, int N, int M, int L);

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
    Output(M);
    return 0;
}

void BackTraking(int *remark, int *identity, int n, int wolf_remain, int N, int M, int L){
    //只需要找到最大的一个结果
    if(count == 1) return;
    if(n != N){
        //option 1, player n+1 is werewolf
        if(wolf_remain > 0){
                identity[N-n] = -1;
                BackTraking(remark, identity, n+1, wolf_remain-1, N, M, L);
                //undo
                identity[N-n] = 0;
        }
        //option 2, player n+1 is human
        if(wolf_remain == 0){
            for(int i = N-n;i >= 1;i--){
                identity[i] = 1;
            }
            BackTraking(remark, identity, N, 0, N, M, L);
            //undo
            for(int i = N-n;i >= 1;i--){
                identity[i] = 0;
            }
        }
        else{
            identity[N-n] = 1;
            BackTraking(remark, identity, n+1, wolf_remain, N, M, L);
            //undo
            identity[N-n] = 0;
        }
    }
    //find a result
    int judge = 0;
    if(n == N) judge = Check(remark, identity, wolf_remain, N, M, L);
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

int Check(int *remark, int *identity, int wolf_remain, int N, int M, int L){
    if(wolf_remain != 0) return 0;
    int liers = 0, werewolf_liers = 0;
    int remark_toward;
    //count the werewolf, liers and werewolf liers
    for(int i = N;i >=1;i--){
        if(identity[i] != -1) identity[i] = 1;
    }
    for(int i = N;i >= 1;i--){
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
    if(werewolf_liers == M) return 0;
    if(liers != L) return 0;
    if(werewolf_liers == 0) return 0;

    return 1;
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
