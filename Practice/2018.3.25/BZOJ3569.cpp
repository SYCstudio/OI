#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
//#define ull unsigned long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=500100*2;
const int maxM=500100*2;
const int inf=2147483647;

class Edge
{
public:
	int val;
	int u,v;
	bool path;
};

int n,m;
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM];
Edge E[maxM];
int Val[maxN];
bool vis[maxN];
int Base[31];

void Add_Edge(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int fa);

int main()
{
	//ios::sync_with_stdio(false);
	srand(141404^170524);mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=0;i<m;i++)
	{
		scanf("%d%d",&E[i].u,&E[i].v);
		Add_Edge(E[i].u,E[i].v);Add_Edge(E[i].v,E[i].u);
	}
	
	dfs1(1,1);
	for (int i=0;i<m;i++)
		if (E[i].path==0)
		{
			E[i].val=rand()%(1<<30);
			Val[E[i].u]^=E[i].val;
			Val[E[i].v]^=E[i].val;
		}
	mem(vis,0);
	dfs2(1,1);

	int Q;scanf("%d",&Q);
	int Ans=0;
	while (Q--)
	{
		int K;scanf("%d",&K);
		mem(Base,0);
		bool flag=1;
		while (K--)
		{
			int e;scanf("%d",&e);e^=Ans;e=E[e-1].val;
			for (int i=30;i>=0;i--)
				if ((e&(1<<i))!=0)
				{
					if (Base[i]==0){
						Base[i]=e;break;
					}
					else e^=Base[i];
				}
			if (e==0) flag=0;
		}
		if (flag==1) printf("Connected\n"),Ans++;
		else printf("Disconnected\n");
	}
	return 0;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs1(int u,int fa)
{
	vis[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0)
		{
			E[i>>1].path=1;
			dfs1(V[i],u);
		}
	return;
}

void dfs2(int u,int fa)
{
	vis[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0)
		{
			dfs2(V[i],u);
			E[i>>1].val^=Val[V[i]];
			Val[u]^=Val[V[i]];
		}
	return;
}
