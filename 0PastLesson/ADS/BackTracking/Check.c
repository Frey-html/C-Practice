int Check(int *remark, int *lier, int *identity, int n, int liers_remain, int N, int M, int L){
    if(n == 0) return 1;
    if(n == N && liers_remain != 0){
        return 0;
    }
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
    if(n == N){
        if(werewolf != M) return 0;
        if(werewolf_liers == M) return 0;
        if(werewolf_liers == 0) return 0;
    }
    return 1;
}

if(judge == 1 && n == N){
        int temp = 0;
        result[count] = (int*)malloc(MaxPlayer*sizeof(int));
        for(int i = N;i >= 1;i--){
            if(identity[i] == -1){
                result[count][temp++] = i;
            }
        }
        count++;
    }