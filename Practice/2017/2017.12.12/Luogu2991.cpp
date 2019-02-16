#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50011;
const int maxM=150100;
const int maxK=11;
const int inf=2147483647;

int n,m,K;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
ll Hap[maxM];
ll F[maxK][maxN];//F[k][u]表示从u出发随机走k次的最大高兴值

ll dfs(int k,int now);

int main()
{
    mem(Head,-1);mem(F,-1);
    scanf("%d%d%d",&n,&m,&K);
    for (int i=1;i<=m;i++)
    {
	int u,v,hap;scanf("%d%d%d",&u,&v,&hap);
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;Hap[edgecnt]=hap;
    }
    dfs(K,1);
    printf("%lld\n",F[K][1]);
    return 0;
}

ll dfs(int k,int now)
{
    if (F[k][now]!=-1) return F[k][now];
    F[k][now]=0;
    for (int i=Head[now];i!=-1;i=Next[i])
    {
	int v=V[i];ll w=Hap[i];
	F[k][now]=max(F[k][now],dfs(k,v)+w);
    }
    if (k==0) return F[k][now];
    for (int i=Head[now];i!=-1;i=Next[i])
    {
	int v=V[i];ll w=Hap[i];
	F[k][now]=min(F[k][now],dfs(k-1,v)+w);
    }
    return F[k][now];
}
