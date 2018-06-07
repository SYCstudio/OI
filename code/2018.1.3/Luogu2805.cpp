#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define Id(x,y) ((x)*C+(y))
#define Getx(id) ((id)/C)
#define Gety(id) ((id)%C)

const int maxN=1000;
const int maxMap=32;
const int maxM=maxN*maxN*10;
const int inf=2147483647;

class Edge
{
public:
    int u,v,w;
};

class Graph
{
public:
    int cnt;
    int Head[maxN],Next[maxM];
    Edge E[maxM];
    Graph()
    {
	cnt=-1;mem(Head,-1);
	return;
    }
    void Add_Edge(int u,int v,int w)
    {
	cnt++;Next[cnt]=Head[u];Head[u]=cnt;E[cnt].u=u;E[cnt].v=v;E[cnt].w=w;
	return;
    }
    void OutpEdge()
    {
	for (int i=0;i<=cnt;i++) cout<<E[i].u<<"->"<<E[i].v<<" "<<E[i].w<<" "<<endl;
	return;
    }
};

int n,S,T;
int R,C;
Graph G1,G2;
int Score[maxMap][maxMap];
int InDegree[maxN],Q[maxN],Depth[maxN],cur[maxN];
bool Circle[maxN];//是否在环上

bool bfs();
int dfs(int u,int flow);

int main()
{
    scanf("%d%d",&R,&C);
    //for (int i=0;i<R;i++) for (int j=0;j<C;j++) cout<<"("<<i<<","<<j<<") "<<Id(i,j)<<" "<<Getx(Id(i,j))<<" "<<Gety(Id(i,j))<<endl;
    n=R*C+1;S=n-1;T=n;
    for (int i=0;i<R;i++)
	for (int j=0;j<C;j++)
	{
	    scanf("%d",&Score[i][j]);
	    int prot;scanf("%d",&prot);
	    for (int k=1;k<=prot;k++)
	    {
		int px,py;scanf("%d%d",&px,&py);
		G1.Add_Edge(Id(i,j),Id(px,py),0);
		InDegree[Id(px,py)]++;
	    }
	    if (j!=0) G1.Add_Edge(Id(i,j),Id(i,j-1),0),InDegree[Id(i,j-1)]++;
	}
    //G1.OutpEdge();
    //Top排序把环和环控制的点找出来
    int h=0,t=0;
    mem(Circle,1);
    for (int i=0;i<R*C;i++) if (InDegree[i]==0) Circle[Q[++h]=i]=0/*,cout<<"Not in Circle:"<<i<<" "<<Getx(i)<<" "<<Gety(i)<<endl*/;
    while (t!=h)
    {
	int u=Q[++t];
	for (int i=G1.Head[u];i!=-1;i=G1.Next[i])
	{
	    int v=G1.E[i].v;InDegree[v]--;
	    if (InDegree[v]==0) Circle[Q[++h]=v]=0;
	}
    }
    //for (int i=0;i<R*C;i++) cout<<Circle[i]<<" ";cout<<endl;
    int sum=0;
    //cout<<"S:"<<S<<" T:"<<T<<endl;
    for (int i=0;i<R;i++)
	for (int j=0;j<C;j++)
	{
	    if (Circle[Id(i,j)]) continue;
	    for (int e=G1.Head[Id(i,j)];e!=-1;e=G1.Next[e])
		if (Circle[G1.E[e].v]==0)
		    G2.Add_Edge(Id(i,j),G1.E[e].v,0),G2.Add_Edge(G1.E[e].v,Id(i,j),inf);
	    if (Score[i][j]>=0) G2.Add_Edge(S,Id(i,j),Score[i][j]),G2.Add_Edge(Id(i,j),S,0),sum+=Score[i][j];
	    else G2.Add_Edge(Id(i,j),T,-Score[i][j]),G2.Add_Edge(T,Id(i,j),0);
	    //if (j==C-1) G2.Add_Edge(S,Id(i,j),inf),G2.Add_Edge(Id(i,j),S,0);
	}
    //G2.OutpEdge();

    int mxflow=0;
    while (bfs())
    {
	for (int i=0;i<=n;i++) cur[i]=G2.Head[i];
	while (int di=dfs(S,inf)) mxflow+=di;
    }
    //cout<<sum<<" "<<mxflow<<endl;
    printf("%d\n",sum-mxflow);
    return 0;
}

bool bfs()
{
    mem(Depth,-1);
    int h=1,t=0;Q[1]=S;Depth[S]=1;
    do
    {
	int u=Q[++t];
	for (int i=G2.Head[u];i!=-1;i=G2.Next[i])
	{
	    int v=G2.E[i].v;
	    if ((G2.E[i].w>0)&&(Depth[v]==-1)) Depth[Q[++h]=v]=Depth[u]+1;
	}
    }
    while (t!=h);
    if (Depth[T]==-1) return 0;
    return 1;
}

int dfs(int u,int flow)
{
    if (u==T) return flow;
    for (int &i=cur[u];i!=-1;i=G2.Next[i])
    {
	int v=G2.E[i].v;
	if ((G2.E[i].w>0)&&(Depth[v]==Depth[u]+1))
	{
	    int di=dfs(v,min(flow,G2.E[i].w));
	    if (di)
	    {
		G2.E[i].w-=di;
		G2.E[i^1].w+=di;
		return di;
	    }
	}
    }
    return 0;
}
