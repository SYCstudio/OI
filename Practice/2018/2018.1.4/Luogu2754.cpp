#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxPos=20;
const int maxTime=1010;
const int maxSpaceship=21;
const int maxN=maxPos*maxTime;
const int maxM=maxSpaceship*maxTime*maxPos*4+maxN*2;
const int inf=2147483647;

class Edge
{
public:
    int v,flow;
};

int n,m,K,S,T;
int edgecnt,Head[maxN],Next[maxM];
Edge E[maxM];
int SpaceShip[maxSpaceship];
int Pathcnt[maxSpaceship],Path[maxSpaceship][maxPos];
int Queue[maxN],Depth[maxN],cur[maxN];

bool Check(int mid);
int Id(int x,int y);
void Add_Edge(int u,int v,int flow);
void _Add(int u,int v,int flow);
bool Bfs();
int dfs(int u,int flow);

int main()
{
    scanf("%d%d%d",&n,&m,&K);
    for (int i=1;i<=m;i++)
    {
	scanf("%d%d",&SpaceShip[i],&Pathcnt[i]);
	for (int j=1;j<=Pathcnt[i];j++) scanf("%d",&Path[i][j]);
    }
    int l=0,r=maxTime;
    int Ans;
    do
    {
	int mid=(l+r)/2;
	//cout<<l<<" "<<r<<endl;
	if (Check(mid))
	{
	    Ans=mid;
	    r=mid-1;
	}
	else l=mid+1;
    }
    while (l<=r);
    printf("%d\n",Ans);
    return 0;
}

int Id(int x,int y)
{
    if (y==0) return S;
    if (y==-1) return T;
    return x*n+y;
}

bool Check(int mid)
{
    edgecnt=-1;mem(Head,-1);S=n*(mid+1)+1;T=n*(mid+1)+2;
    //cout<<"S:"<<S<<" T:"<<T<<endl;
    for (int i=0;i<mid;i++)
	for (int j=1;j<=m;j++)
	{
	    int nowpos=Path[j][i%Pathcnt[j]+1];
	    if (nowpos==-1) continue;
	    int nexpos=Path[j][(i+1)%Pathcnt[j]+1];
	    if (nexpos==0) continue;
	    Add_Edge(Id(i,nowpos),Id(i+1,nexpos),SpaceShip[j]);
	}
    for (int i=0;i<mid;i++)
	for (int j=1;j<=n;j++)
	    Add_Edge(Id(i,j),Id(i+1,j),inf);
    /*
    for (int i=1;i<=T;i++)
    {
	for (int j=Head[i];j!=-1;j=Next[j])
	    cout<<i<<"->"<<E[j].v<<" "<<E[j].flow<<endl;
	cout<<endl;
    }
    //*/
    int ret=0;
    while ((Bfs())&&(ret<K))
    {
	int di;
	for (int i=1;i<=T;i++) cur[i]=Head[i];
	while ((ret<K)&&(di=dfs(S,inf))) ret+=di;
	//cout<<di<<endl;
    }
    if (ret>=K) return 1;
    return 0;
}

void Add_Edge(int u,int v,int flow)
{
    //cout<<u<<" "<<v<<endl;
    _Add(u,v,flow);_Add(v,u,0);
    return;
}

void _Add(int u,int v,int flow)
{
    edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;
    E[edgecnt].v=v;E[edgecnt].flow=flow;
    return;
}

bool Bfs()
{
    mem(Depth,-1);
    int h=1,t=0;
    Queue[1]=S;Depth[S]=1;
    do
    {
	int u=Queue[++t];
	for (int i=Head[u];i!=-1;i=Next[i])
	{
	    int v=E[i].v;
	    if ((E[i].flow>0)&&(Depth[v]==-1)) Depth[Queue[++h]=v]=Depth[u]+1;
	}
    }
    while (t!=h);
    if (Depth[T]==-1) return 0;
    return 1;
}

int dfs(int u,int flow)
{
    if (u==T||!flow) return flow;
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
