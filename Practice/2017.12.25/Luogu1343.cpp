#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=201;
const int maxM=2001*2;
const int inf=2147483647;

class Edge
{
public:
    int v,w;
};

int n,m,x;
//Graph
int cnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
//Dinic
int Depth[maxN],cur[maxN];
queue<int> Q;

void Add_Edge(int u,int v,int w);
bool bfs();
int dfs(int u,int flow);

int main()
{
    mem(Head,-1);
    scanf("%d%d%d",&n,&m,&x);
    for (int i=1;i<=m;i++)
    {
	int u,v,w;
	scanf("%d%d%d",&u,&v,&w);
	Add_Edge(u,v,w);Add_Edge(v,u,0);
    }
    int Ans=0;
    while (bfs())
    {
	for (int i=1;i<=n;i++) cur[i]=Head[i];
	while (int di=dfs(1,inf)) Ans+=di;
    }
    if (Ans==0)
    {
	printf("Orz Ni Jinan Saint Cow!\n");
	return 0;
    }
    printf("%d %d\n",Ans,x/Ans+(int)(x%Ans!=0));
    return 0;
}

void Add_Edge(int u,int v,int w)
{
    cnt++;Next[cnt]=Head[u];Head[u]=cnt;
    E[cnt].v=v;E[cnt].w=w;
    return;
}

bool bfs()
{
    while (!Q.empty()) Q.pop();
    Q.push(1);
    mem(Depth,-1);
    Depth[1]=1;
    do
    {
	int u=Q.front();Q.pop();
	for (int i=Head[u];i!=-1;i=Next[i])
	{
	    int v=E[i].v;
	    if ((E[i].w>0)&&(Depth[v]==-1))
	    {
		Depth[v]=Depth[u]+1;
		Q.push(v);
	    }
	}
    }
    while (!Q.empty());
    if (Depth[n]==-1) return 0;
    return 1;
}

int dfs(int u,int flow)
{
    if (u==n) return flow;
    for (int &i=cur[u];i!=-1;i=Next[i])
    {
	int v=E[i].v;
	if ((E[i].w>0)&&(Depth[v]==Depth[u]+1))
	{
	    int di=dfs(v,min(flow,E[i].w));
	    if (di!=0)
	    {
		E[i].w-=di;
		E[i^1].w+=di;
		return di;
	    }
	}
    }
    return 0;
}
