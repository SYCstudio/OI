#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=320;
const int maxM=maxN*maxN*4;
const int inf=2147483647;

class Edge
{
public:
    int u,v,flow;
};

int n,m;
int S,T;
int cnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Depth[maxN];
int Q[maxN];
int cur[maxN];

void Add_Edge(int u,int v,int flow);
bool Bfs();
int dfs(int u,int flow);

int main()
{
    mem(Head,-1);
    scanf("%d%d",&n,&m);
    S=0;T=n+1;
    for (int i=1;i<=n;i++)
    {
	int x;scanf("%d",&x);
	if (x==0) Add_Edge(S,i,1);
	else Add_Edge(i,T,1);
    }
    for (int i=1;i<=m;i++)
    {
	int x,y;scanf("%d%d",&x,&y);
	Add_Edge(x,y,1);
	Add_Edge(y,x,1);
    }
    /*
    cout<<"A"<<endl;
    for (int i=S;i<=T;i++)
    {
	cout<<i<<":";
	for (int j=Head[i];j!=-1;j=Next[j])
	    cout<<E[j].u<<" "<<E[j].v<<" "<<E[j].flow<<endl;
	cout<<endl;
    }
    //*/
    int Ans=0;
    while (Bfs())
    {
	//for (int i=S;i<=T;i++) cout<<Depth[i]<<" ";
	//cout<<endl;
	//return 0;
	for (int i=S;i<=T;i++) cur[i]=Head[i];
	while (int di=dfs(S,inf))
	    Ans+=di;
    }
    printf("%d\n",Ans);
    return 0;
}

void Add_Edge(int u,int v,int flow)
{
    cnt++;Next[cnt]=Head[u];Head[u]=cnt;
    E[cnt].u=u;E[cnt].v=v;E[cnt].flow=flow;

    cnt++;Next[cnt]=Head[v];Head[v]=cnt;
    E[cnt].u=v;E[cnt].u=v;E[cnt].flow=0;
    return;
}

bool Bfs()
{
    mem(Depth,0);
    Depth[S]=1,Q[1]=S;
    int h=1,t=0;
    do
    {
	t++;int u=Q[t];
	for (int i=Head[u];i!=-1;i=Next[i])
	{
	    int v=E[i].v;
	    if ((Depth[v]==0)&&(E[i].flow>0))
	    {
		//cout<<"Update:"<<u<<"->"<<v<<endl;
		Depth[v]=Depth[u]+1;
		h++;Q[h]=v;
	    }
	}
    }
    while (t<h);
    if (Depth[T]==0) return 0;
    return 1;
}

int dfs(int u,int flow)
{
    if (u==T) return flow;
    for (int &i=cur[u];i!=-1;i=Next[i])
    {
	int v=E[i].v;
	if ((E[i].flow>0)&&(Depth[v]==Depth[u]+1))
	{
	    int di=dfs(v,min(flow,E[i].flow));
	    if (di>0)
	    {
		E[i].flow-=di;
		E[i^1].flow+=di;
		return di;
	    }
	}
    }
    return 0;
}
