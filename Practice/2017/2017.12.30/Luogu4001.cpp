#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll int
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define Id(x,y,opt) ((((x)-1)*(m-1)+(y))*2-(int)(opt==1))

const int maxN=1001;
const int maxNode=maxN*maxN*2;
const int maxM=maxNode*3*2;
const int inf=2147483647;

class Queue_Data
{
public:
    ll u,dist;
};

bool operator < (Queue_Data A,Queue_Data B)
{
    return A.dist>B.dist;
}

int n,m;
int S,T;
int cnt=0,Head[maxNode],Next[maxM],V[maxM];
ll W[maxM];
ll Dist[maxNode];
int Q[maxNode/2];
bool vis[maxNode];

void Add_Edge(int u,int v,int w);

int main()
{
    //freopen("bjrabbit.in","r",stdin);
    //freopen("bjrabbit.out","w",stdout);
    mem(Head,-1);
    scanf("%d%d",&n,&m);S=(n-1)*(m-1)*2+1;T=(n-1)*(m-1)*2+2;
    if ((n==1)||(m==1))
    {
	if (m>n) swap(n,m);
	int Ans=inf;
	for (int i=1;i<=n;i++)
	{
	    int x;scanf("%d",&x);
	    Ans=min(Ans,x);
	}
	printf("%d\n",Ans);
	return 0;
    }
    for (int i=1;i<=n;i++)//横向道路
	for (int j=1;j<m;j++)
	{
	    int w;scanf("%d",&w);
	    if (i==1) Add_Edge(Id(i,j,2),T,w);
	    else if (i==n) Add_Edge(S,Id(i-1,j,1),w);
	    else Add_Edge(Id(i,j,2),Id(i-1,j,1),w);
	}
    for (int i=1;i<n;i++)//纵向道路
	for (int j=1;j<=m;j++)
	{
	    int w;scanf("%d",&w);
	    if (j==1) Add_Edge(S,Id(i,j,1),w);
	    else if (j==m) Add_Edge(Id(i,j-1,2),T,w);
	    else Add_Edge(Id(i,j-1,2),Id(i,j,1),w);
	}
    for (int i=1;i<n;i++)//斜向道路
	for (int j=1;j<m;j++)
	{
	    int w;scanf("%d",&w);
	    Add_Edge(Id(i,j,1),Id(i,j,2),w);
	}
    /*
    for (int i=1;i<=T;i++)
    {
	for (int j=Head[i];j!=-1;j=Next[j])
	    cout<<i<<"->"<<V[j]<<" "<<W[j]<<endl;
	cout<<endl;
    }
    //*/
    mem(Dist,127);
    Dist[S]=0;
    int h=1,t=0;
    Q[1]=S;
    vis[S]=1;
    do
    {
	t++;if (t>=maxNode/2) t=0;int u=Q[t];
	for (int i=Head[u];i!=-1;i=Next[i])
	{
	    int v=V[i];
	    if (Dist[v]>Dist[u]+W[i])
	    {
		Dist[v]=Dist[u]+W[i];
		if (vis[v]==0)
		{
		    h++;if (h>=maxNode/2) h=0;
		    Q[h]=v;
		    vis[v]=1;
		}
	    }
	}
	vis[u]=0;
    }
    while (t!=h);
    /*
    Q.push((Queue_Data){S,0});
    do
    {
	Queue_Data u=Q.top();Q.pop();
	if (vis[u.u]) continue;
	vis[u.u]=1;
	for (int i=Head[u.u];i!=-1;i=Next[i])
	{
	    int v=V[i];
	    if ((vis[v]==0)&&(Dist[v]>Dist[u.u]+W[i]))
	    {
		Dist[v]=Dist[u.u]+W[i];
		Q.push((Queue_Data){v,Dist[v]});
	    }
	}
    }
    while (!Q.empty());
    //*/
    printf("%d\n",Dist[T]);
    return 0;
}

void Add_Edge(int u,int v,int w)
{
    cnt++;Next[cnt]=Head[u];Head[u]=cnt;V[cnt]=v;W[cnt]=w;
    cnt++;Next[cnt]=Head[v];Head[v]=cnt;V[cnt]=u;W[cnt]=w;
    return;
}
