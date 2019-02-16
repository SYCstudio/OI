#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10010;
const int maxM=500010;
const int inf=2147483647;

class Queue_Data
{
public:
    int u,dist;
};

bool operator < (Queue_Data A,Queue_Data B)
{
    return A.dist>B.dist;
}

int n,m,S;
int cnt=0,Head[maxN],Next[maxM],V[maxM],W[maxM];
int Dist[maxN];
bool vis[maxN];
priority_queue<Queue_Data> Q;

int main()
{
    mem(Head,-1);
    scanf("%d%d%d",&n,&m,&S);
    for (int i=1;i<=m;i++)
    {
	int u,v,w;
	scanf("%d%d%d",&u,&v,&w);
	cnt++;Next[cnt]=Head[u];Head[u]=cnt;
	V[cnt]=v;W[cnt]=w;
    }
    Queue_Data init;
    for (int i=1;i<=n;i++) Dist[i]=inf;
    Dist[S]=0;
    init.u=S;init.dist=0;
    Q.push(init);
    do
    {
	int u=Q.top().u;
	Q.pop();
	if (vis[u]) continue;
        vis[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
	{
	    int v=V[i];
	    if ((Dist[u]+W[i]<Dist[v])&&(vis[v]==0))
	    {
		Dist[v]=Dist[u]+W[i];
		Q.push((Queue_Data){v,Dist[v]});
	    }
	}
    }
    while (!Q.empty());
    for (int i=1;i<=n;i++) printf("%d ",Dist[i]);
    printf("\n");
    return 0;
}
