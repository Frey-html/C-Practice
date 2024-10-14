#include<stdio.h>
#include<string.h>
#include<time.h>
#define MAXN 1010
#define MAX 100000
int G[MAXN][MAXN];//如果点i，j有连线，则G[i][j]=1,如果无连线，则G[i][j]=0
int n,answer,cnt[MAXN],group[MAXN],vis[MAXN],price[MAXN],mincost,a[MAXN]; 
//n为水果总数 
//answer为第一行ouput的安全水果最大值 
//cnt[i]表示从i到n这些点中的最大团所含点数 
//vis[i]存储当前搜索到的团的各点值 
//group[i]存储ouput的最大团的各点值
void dfs(int u,int now,int cost)
{
	int i, j;
	for(i = u+1; i <= n; i++)
	{
		if(cnt[i]+now < answer || (cnt[i]+now == answer && cost >= mincost))
		return;//如果含当前点u的最大团所含点数比目前找到的最大团点数少，或者两者相等但cost相等或更高，那么直接返回 
		//如果点数相同价格也相同？？
		if( G[u][i] ) //如果当前点u与新点i相连
		{
			for(j = 0; j < now; j++ )
			{
				if( !G[i][vis[j]] )
				break;//如果新点i与已在团内的点（除了u以外的）已经相连，那么不用加入i到团中
			}
			if( j == now )//新点i不在团中
			{
				vis[now] = i;
				dfs(i,now+1,cost+price[i]);
			} 
		}
	}
	if( now > answer || (now == answer && cost < mincost) )
	//如果得到的新最大团的点数更大或者相同但是cost更低，那么更新group[] ,answer,mincost
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
void sort(int a[],int num)//对原序号升序排序 ，原序号即数组a[]中存的值 
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
	int now = -1;//now表示现在正在搜索团内的第now个点，现在团内只有now-1个点 
	int m;//m表示忌口tips条数 
	int x,price0;
	int first[MAX],second[MAX];
	int list[MAXN];
    int no[MAXN]; 
    int i,j;
	clock_t start, end;
	scanf("%d %d", &m, &n);
	memset(G, -1, sizeof(G));//为图G申请空间
	for(i = 0; i < m; i++) 
	{
		scanf("%d %d", &first[i], &second[i]);
		for(j = 1; j <= n; j++) 
    	G[i+1][j]=1;
    	//连接各点，相当于对于任意i、j，G[i][j]=1 
	}
	for(i = 0; i < n; i++)
	{
		scanf("%d %d",&x,&price0); 
		no[x] = i+1;//x的新序号为i 
		price[i+1] = price0;// 新序号为i的水果价格为price0 
		list[i+1] = x;//新水果清单中第i个为x 
    } 
    for(i = 0; i < m; i++)
    {
    	G[ no[first[i]] ][ no[second[i]] ] = G[ no[second[i]] ][ no[first[i]] ] = 0;
		//更新图 G,把开始输入的不能一起吃的水果的新编号no[first[i]],no[second[i]]对应的G[][]的值赋为0 
    }
	start = clock();
    maxclique();
	printf("%d\n",answer);
	for(i=0;i<=answer-1;i++) 
	{
		a[i]=list[group[i]];//把最终结果复制到a[]中，方便对原序号升序打印 
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
