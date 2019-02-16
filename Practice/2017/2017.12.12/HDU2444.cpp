#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=210;
const int maxM=maxN*maxN*2;
const int inf=2147483647;

int n,m;
int cnt,Head[maxN],Next[maxM],V[maxM];
int Color[maxN],Match[maxN];
int Q[maxN];
bool vis[maxN];

void Add_Edge(int u,int v);
bool Check();
bool Hungary(int u);

int main()
{
    while (scanf("%d%d",&n,&m)!=EOF)
    {
	cnt=0;
	mem(Head,-1);
	for (int i=1;i<=m;i++)
	{
	    int u,v;scanf("%d%d",&u,&v);
	    Add_Edge(u,v);Add_Edge(v,u);
	}
	if (Check()==0) printf("No\n");
	else
	{
	    int Ans=0;
	    mem(Match,-1);
	    for (int i=1;i<=n;i++)
	    {
		mem(vis,0);
		if (Hungary(i)) Ans++;
	    }
	    printf("%d\n",Ans/2);
	}
    }
    return 0;
}

void Add_Edge(int u,int v)
{
    cnt++;Next[cnt]=Head[u];V[cnt]=v;
    Head[u]=cnt;
    return;
}

bool Check()
{
    mem(Color,-1);
    int h=1,t=0;
    Q[1]=1;
    Color[1]=1;
    while (t<h)
    {
	t++;int u=Q[t];
	for (int i=Head[u];i!=-1;i=Next[i])
	{
	    int v=V[i];
	    if (Color[v]==-1)
	    {
		Color[v]=Color[u]^1;
		h++;Q[h]=v;
	    }
	    else if (Color[v]==Color[u]) return 0;
	}
    }
    return 1;
}

bool Hungary(int u)
{
    for (int i=Head[u];i!=-1;i=Next[i])
    {
	int v=V[i];
	if (vis[v]==0)
	{
	    vis[v]=1;
	    if ((Match[v]==-1)||(Hungary(Match[v])))
	    {
		Match[v]=u;
		return 1;
	    }
	}
    }
    return 0;
}
