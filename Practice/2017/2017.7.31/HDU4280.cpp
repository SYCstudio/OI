#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

#define min(x,y) x>y? y : x
#define RG register

const int maxN=200031;
const int maxM=500031;
const int inf=2147483647;

struct Edge
{
	int v,flow;
};

int n,m;
int S,T;
int cnt=-1;
int Head[maxN];
int Next[maxM];
Edge E[maxM];
int cur[maxN];
int depth[maxN];
int Queue[maxN];

inline void Add_Edge(int u,int v,int flow);
int dfs(int u,int flow);
inline int read();

int main()
{
	int Case;
	Case=read();
	while (Case--)
	{
		memset(Head,-1,sizeof(Head));
		cnt=-1;
		n=read();
		m=read();
		int minx=inf,maxx=-inf;
		for (int i=1;i<=n;i++)
		{
			int x=read(),y=read();
			if (x<minx)
			{
				minx=x;
				S=i;
			}
			if (x>maxx)
			{
				maxx=x;
				T=i;
			}
		}
		for (int i=1;i<=m;i++)
		{
			int u=read(),v=read(),flow=read();
			Add_Edge(u,v,flow);
		}
		int Ans=0;
		while (1)
		{
			memset(depth,-1,sizeof(depth));
			int Top=1,Tail=0;
			depth[S]=1;
			Queue[1]=S;
			do
			{
				Tail++;
				int u=Queue[Tail];
				if (u==T)
					break;
				for (int i=Head[u];i!=-1;i=Next[i])
				{
					int v=E[i].v;
					if ((E[i].flow>0)&&(depth[v]==-1))
					{
						depth[v]=depth[u]+1;
						Top++;
						Queue[Top]=v;
					}
				}
			}
			while (Top!=Tail);
			if (depth[T]==-1)
				break;
			for (int i=1;i<=n;i++)
				cur[i]=Head[i];
			
			while (int di=dfs(S,inf))
				Ans+=di;
		}
		printf("%d\n",Ans);
	}
	return 0;
}

inline int read()
{
	int x=0;
	scanf("%d",&x);
	return x;
	int k=1;
	char ch=getchar();
	while (((ch>'9')||(ch<'0'))&&(ch!='-'))
		ch=getchar();
	if (ch=='-')
	{
		ch=getchar();
		k=-1;
	}
	while ((ch>='0')&&(ch<='9'))
	{
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*k;
}

inline void Add_Edge(int u,int v,int flow)
{
	cnt++;
	Next[cnt]=Head[u];
	Head[u]=cnt;
	E[cnt].v=v;
	E[cnt].flow=flow;

	cnt++;
	Next[cnt]=Head[v];
	Head[v]=cnt;
	E[cnt].v=u;
	E[cnt].flow=flow;
	return;
}

int dfs(int u,int flow)
{
	if (u==T)
		return flow;
	for (int &i=cur[u];i!=-1;i=Next[i])
	{
		int v=E[i].v;
		if ((depth[v]==depth[u]+1)&&(E[i].flow>0))
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
