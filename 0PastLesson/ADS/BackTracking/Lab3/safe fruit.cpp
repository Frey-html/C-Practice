#include<stdio.h>
#include<string.h>
#include<time.h>
#define MAXN 1010
#define MAX 100000
int G[MAXN][MAXN];//�����i��j�����ߣ���G[i][j]=1,��������ߣ���G[i][j]=0
int n,answer,cnt[MAXN],group[MAXN],vis[MAXN],price[MAXN],mincost,a[MAXN]; 
//nΪˮ������ 
//answerΪ��һ��ouput�İ�ȫˮ�����ֵ 
//cnt[i]��ʾ��i��n��Щ���е�������������� 
//vis[i]�洢��ǰ���������ŵĸ���ֵ 
//group[i]�洢ouput������ŵĸ���ֵ
void dfs(int u,int now,int cost)
{
	int i, j;
	for(i = u+1; i <= n; i++)
	{
		if(cnt[i]+now < answer || (cnt[i]+now == answer && cost >= mincost))
		return;//�������ǰ��u�����������������Ŀǰ�ҵ�������ŵ����٣�����������ȵ�cost��Ȼ���ߣ���ôֱ�ӷ��� 
		//���������ͬ�۸�Ҳ��ͬ����
		if( G[u][i] ) //�����ǰ��u���µ�i����
		{
			for(j = 0; j < now; j++ )
			{
				if( !G[i][vis[j]] )
				break;//����µ�i���������ڵĵ㣨����u����ģ��Ѿ���������ô���ü���i������
			}
			if( j == now )//�µ�i��������
			{
				vis[now] = i;
				dfs(i,now+1,cost+price[i]);
			} 
		}
	}
	if( now > answer || (now == answer && cost < mincost) )
	//����õ���������ŵĵ������������ͬ����cost���ͣ���ô����group[] ,answer,mincost
	{
		for( i = 0; i < now; i++)
			group[i] = vis[i];
			answer = now;
			mincost = cost;
	}
}
void maxclique() 
{
	answer = -1;
	for(int i = n; i > 0; i--)
	{
		vis[0] = i;
		dfs( i, 1, price[i] );
		cnt[i] = answer;
	}
}
void sort(int a[],int num)//��ԭ����������� ��ԭ��ż�����a[]�д��ֵ 
{
	int i,j,m;
	for(i = 1; i < num; i++)
	{
		for(j = i; j > 0; j--)
		{
			if(a[j] < a[j-1])
			{
				m = a[j-1];
				a[j-1] = a[j];
				a[j] = m;
			}
		}
	}
}
int main()
{
	int now = -1;//now��ʾ���������������ڵĵ�now���㣬��������ֻ��now-1���� 
	int m;//m��ʾ�ɿ�tips���� 
	int x,price0;
	int first[MAX],second[MAX];
	int list[MAXN];
    int no[MAXN]; 
    int i,j;
	clock_t start, end;
	scanf("%d %d", &m, &n);
	memset(G, -1, sizeof(G));//ΪͼG����ռ�
	for(i = 0; i < m; i++) 
	{
		scanf("%d %d", &first[i], &second[i]);
		for(j = 1; j <= n; j++) 
    	G[i+1][j]=1;
    	//���Ӹ��㣬�൱�ڶ�������i��j��G[i][j]=1 
	}
	for(i = 0; i < n; i++)
	{
		scanf("%d %d",&x,&price0); 
		no[x] = i+1;//x�������Ϊi 
		price[i+1] = price0;// �����Ϊi��ˮ���۸�Ϊprice0 
		list[i+1] = x;//��ˮ���嵥�е�i��Ϊx 
    } 
    for(i = 0; i < m; i++)
    {
    	G[ no[first[i]] ][ no[second[i]] ] = G[ no[second[i]] ][ no[first[i]] ] = 0;
		//����ͼ G,�ѿ�ʼ����Ĳ���һ��Ե�ˮ�����±��no[first[i]],no[second[i]]��Ӧ��G[][]��ֵ��Ϊ0 
    }
	start = clock();
    maxclique();
	printf("%d\n",answer);
	for(i=0;i<=answer-1;i++) 
	{
		a[i]=list[group[i]];//�����ս�����Ƶ�a[]�У������ԭ��������ӡ 
	}
	sort(a,answer);
	printf("%03d",a[0]);
	for(i=1;i<=answer-1;i++)
	printf(" %03d",a[i]);
	printf("\n%d",mincost);
	end = clock();
	printf("\nElapsed time for finding maxclique: %ldms", end - start);
	return 0; 
}
