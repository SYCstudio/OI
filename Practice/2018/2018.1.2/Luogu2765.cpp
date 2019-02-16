#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=6000;
const int maxM=60010;
const int inf=2147483647;

class Edge
{
public:
    int u,v,flow;
};

int Ballcnt;

class Graph
{
public:
    int cnt;
    int Head[maxN],Next[maxM];
    Edge E[maxM];
    int cur[maxN],Depth[maxN],Q[maxN];
    bool vis[maxN];
    Graph()
	{
	    cnt=-1;mem(Head,-1);
	    return;
	}
    void Add_Edge(int u,int v,int flow)
	{
	    _Add(u,v,flow);_Add(v,u,0);
	    return;
	}
    void _Add(int u,int v,int flow)
	{
	    cnt++;Next[cnt]=Head[u];Head[u]=cnt;E[cnt].u=u;E[cnt].v=v;E[cnt].flow=flow;
	    return;
	}
    int Dinic()
	{
	    int mxflow=0;
	    while (bfs())
	    {
		for (int i=0;i<=Ballcnt*2+1;i++) cur[i]=Head[i];
		while (int di=dfs(0,inf)) mxflow+=di;
	    }
	    return mxflow;
	}
    bool bfs()
	{
	    mem(Depth,-1);Depth[0]=1;
	    int h=1,t=0;Q[1]=0;
	    do
	    {
		int u=Q[++t];
		for (int i=Head[u];i!=-1;i=Next[i])
		{
		    int v=E[i].v;
		    if ((E[i].flow>0)&&(Depth[v]==-1))
		    {
			Depth[v]=Depth[u]+1;
			Q[++h]=v;
		    }
		}
	    }
	    while (t!=h);
	    //for (int i=0;i<=Ballcnt*2+1;i++) cout<<Depth[i]<<" ";
	    //cout<<endl;
	    if (Depth[1]==-1) return 0;
	    return 1;
	}
    int dfs(int u,int flow)
	{
	    if (u==1) return flow;
	    for (int &i=cur[u];i!=-1;i=Next[i])
	    {
		int v=E[i].v;
		if ((E[i].flow>0)&&(Depth[v]==Depth[u]+1))
		{
		    int di=dfs(v,min(flow,E[i].flow));
		    if (di)
		    {
			E[i].flow-=di;
			E[i^1].flow+=di;
			return di;
		    }
		}
	    }
	    return 0;
	}
    void Outp()
	{
	    mem(vis,0);
	    for (int i=1;i<=Ballcnt;i++)
	    {
		if (vis[i]) continue;
		int now=i*2;bool flag;
		do
		{
		    vis[now/2]=1;
		    flag=0;printf("%d ",now/2);
		    for (int j=Head[now];j!=-1;j=Next[j])
			if ((E[j].v%2==1)&&(E[j].v/2-1<=Ballcnt)&&(E[j].flow==0))
			{
			    now=E[j].v-1;flag=1;
			    break;
			}
		}
		while (flag);
		printf("\n");
	    }
	    return;
	}
};

int n,Flowsum;
Graph G;

int main()
{
    scanf("%d",&n);
    Flowsum=Ballcnt=0;
    do
    {
	Ballcnt++;G.Add_Edge(0,Ballcnt*2,1);G.Add_Edge(Ballcnt*2+1,1,1);
	for (int i=1;i<Ballcnt;i++) if ((int)(sqrt(Ballcnt+i))*(int)(sqrt(Ballcnt+i))==Ballcnt+i) G.Add_Edge(i*2,Ballcnt*2+1,1);
	Flowsum+=G.Dinic();
	if (Ballcnt-Flowsum>n)
	{
	    Ballcnt--;break;
	}
    }
    while (1);
    printf("%d\n",Ballcnt);
    G.Outp();
    return 0;
}
