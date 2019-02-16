#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=5010;
const int maxM=200010;
const int inf=2147483647;

class Queue_Data
{
public:
    int u,di;
};

bool operator < (Queue_Data A,Queue_Data B)
{
    return A.di>B.di;
}

int n,m;
int cnt=0,Head[maxN],Next[maxM*2],V[maxM*2],W[maxM*2];
int Dist[maxN];
bool vis[maxN];
priority_queue<Queue_Data> Q;

void Add_Edge(int u,int v,int w);

int main()
{
    mem(Head,-1);
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++)
    {
	int u,v,w;
	scanf("%d%d%d",&u,&v,&w);
	Add_Edge(u,v,w);Add_Edge(v,u,w);
    }
    for (int i=1;i<=n;i++) Dist[i]=inf;
    Dist[1]=0;Q.push((Queue_Data){1,0});
    int cnt=0;
    ll mst=0;
    do
    {
	int u=Q.top().u;Q.pop();
	if (vis[u]==1) continue;
	vis[u]=1;
	mst+=Dist[u];
	cnt++;
	for (int i=Head[u];i!=-1;i=Next[i])
	{
	    int v=V[i];
	    if ((vis[v]==0)&&(Dist[v]>W[i]))
	    {
		Dist[v]=W[i];
		Q.push((Queue_Data){v,Dist[v]});
	    }
	}
    }
    while (!Q.empty());
    if (cnt==n) printf("%lld\n",mst);
    else printf("orz\n");
    return 0;
}

void Add_Edge(int u,int v,int w)
{
    cnt++;Next[cnt]=Head[u];Head[u]=cnt;
    V[cnt]=v;W[cnt]=w;
    return;
}
