#include <stdio.h>

#define ElementType int
#define MAXN 100

void merge_pass( ElementType list[], ElementType sorted[], int N, int length );

void output( ElementType list[], int N )
{
    int i;
    for (i=0; i<N; i++) printf("%d ", list[i]);
    printf("\n");
}

void  merge_sort( ElementType list[],  int N )
{
    ElementType extra[MAXN];  /* the extra space required */
    int  length = 1;  /* current length of sublist being merged */
    while( length < N ) { 
        merge_pass( list, extra, N, length ); /* merge list into extra */
        output( extra, N );
        length *= 2;
        merge_pass( extra, list, N, length ); /* merge extra back to list */
        output( list, N );
        length *= 2;
    }
} 


int main()
{
    int N, i;
    ElementType A[MAXN];

    scanf("%d", &N);
    for (i=0; i<N; i++) scanf("%d", &A[i]);
    merge_sort(A, N);
    output(A, N);

    return 0;
}

void merge_pass( ElementType list[], ElementType sorted[], int N, int length ){
    int cur = 0; //current initial position of left sublist
    int pos1 = 0, pos2 = 0;
    if(length < N && 2 * length > N){
        int rightmax = N - length;
        while(pos1 < length && pos2 < rightmax){
            if(list[cur+pos1] <= list[cur+length+pos2]){
                    sorted[cur+pos1+pos2] = list[cur+pos1];
                    pos1++;
            }else{
                    sorted[cur+pos1+pos2] = list[cur+length+pos2];
                    pos2++;
            }
        }
        while(pos1 < length){
                sorted[cur+pos1+pos2] = list[cur+pos1];
                pos1++;
            }
            while(pos2 < rightmax){
                sorted[cur+pos1+pos2] = list[cur+length+pos2];
                pos2++;
            }
    }
    else{
        while(cur + 2 * length <= N){
            pos1 = pos2 = 0;
            while(pos1 < length && pos2 < length){
                if(list[cur+pos1] <= list[cur+length+pos2]){
                    sorted[cur+pos1+pos2] = list[cur+pos1];
                    pos1++;
                }else{
                    sorted[cur+pos1+pos2] = list[cur+length+pos2];
                    pos2++;
                }
            }
            while(pos1 < length){
                sorted[cur+pos1+pos2] = list[cur+pos1];
                pos1++;
            }
            while(pos2 < length){
                sorted[cur+pos1+pos2] = list[cur+length+pos2];
                pos2++;
            }
            cur += 2*length;
        }
        while(cur < N){
            sorted[cur] = list[cur];
            cur++;
        }
    }
}