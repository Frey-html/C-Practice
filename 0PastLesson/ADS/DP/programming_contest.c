//6-1 Programming Contest (14 point(s))
#include <stdio.h>

#define MAXN 10
#define MAXS 1000

int need_time(const int time[], const int score[], int happy_score, int n);

int main() {
  int n, i, happy_score;
  int time[MAXN], score[MAXN];
  scanf("%d %d", &n, &happy_score);
  for (i = 0; i < n; ++i)
      scanf("%d", &time[i]);
  for (i = 0; i < n; ++i)
      scanf("%d", &score[i]);
  printf("%d\n", need_time(time, score, happy_score, n));
  return 0;
}

int need_time(const int time[], const int score[], int happy_score, int n){
    int min_time[101][MAXS+1];
    int temp;
    int infinit = 10100;
    for(int j = 0;j <= happy_score;j++){
        if(score[0] >= j) min_time[0][j] = time[0];
        else min_time[0][j] = infinit;
    }
    for(int i = 1;i < n;i++){
        for(int j = 0;j <= happy_score;j++){
            min_time[i][j] = min_time[i-1][j];
            if(score[i] < j && min_time[i-1][j-score[i]]){
                temp = min_time[i-1][j-score[i]] + time[i];
                if(temp < min_time[i][j])
                   min_time[i][j] = temp;
            }
            if(score[i] >= j && time[i] < min_time[i][j]){
                min_time[i][j] = time[i];
            }
        }
    }
    if(min_time[n-1][happy_score] == infinit) return -1;
    return min_time[n-1][happy_score];
}