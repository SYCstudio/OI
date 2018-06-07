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

int n,m,S;
int cnt=0,Head[maxN],Next[maxM],V[maxM],W[maxM];
int Dist[maxN];
bool inqueue[maxN];
queue<int> Q;

void Add_Edge(int u,int v,int w);

int main()
{
    mem(Head,-1);
    scanf("%d%d%d",&n,&m,&S);
    for (int i=1;i<=m;i++)
    {
	int u,v,w;
	scanf("%d%d%d",&u,&v,&w);
	Add_Edge(u,v,w);
    }
    for (int i=1;i<=n;i++) Dist[i]=inf;
    Dist[S]=0;
    Q.push(S);inqueue[S]=1;
    do
    {
	int u=Q.front();Q.pop();
	for (int i=Head[u];i!=-1;i=Next[i])
	{
	    int v=V[i];
	    if (Dist[v]>Dist[u]+W[i])
	    {
		Dist[v]=Dist[u]+W[i];
		if (inqueue[v]==0)
		{
		    Q.push(v);inqueue[v]=1;
		}
	    }
	}
	inqueue[u]=0;
    }
    while (!Q.empty());
    for (int i=1;i<=n;i++) printf("%d ",Dist[i]);
    printf("\n");
    return 0;
}

void Add_Edge(int u,int v,int w)
{
    cnt++;Next[cnt]=Head[u];Head[u]=cnt;
    V[cnt]=v;W[cnt]=w;
    return;
}
