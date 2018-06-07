#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define NAME "network"

const int maxN=101;
const int maxM=410*2;
const ld eps=1e-6;
const int inf=2147483647;

class EDGE
{
public:
	int u,v,w;
};

class Edge
{
public:
	int v;
	ld flow;
};

int n,m;
EDGE EE[maxM];
int S,T;
int edgecnt=0,Head[maxN],Next[maxM];
Edge E[maxM];
int Q[maxN],Depth[maxN],cur[maxN],Id[maxM];
bool vis[maxN];

ld Calc(ld K);
void Add_Edge(int u,int v,ld flow,int id);
bool Bfs();
ld dfs(int u,ld flow);
void dfs(int u);

int main()
{
	freopen(NAME".in","r",stdin);freopen(NAME".out","w",stdout);
	bool first=0;
	while (scanf("%d%d",&n,&m)!=EOF)
	{
		ld L=inf,R=0,Ans=0;
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&EE[i].u,&EE[i].v,&EE[i].w);
			//R+=EE[i].w;
			L=min(L,(ld)EE[i].w);R=max(R,(ld)EE[i].w);
		}
		L-=eps;R+=eps;
		//cout<<Calc(2.0)<<endl;
		//cout<<"("<<L<<","<<R<<")"<<endl;
		do
		{
			//cout<<"("<<L<<","<<R<<")"<<endl;
			ld mid=(L+R)/2.0;
			if (Calc(mid)>=-eps) Ans=mid,L=mid+eps;
			else R=mid-eps;
		}
		while(L+eps<=R);

		Calc(Ans);

		//cout<<"Ans:"<<Ans<<endl;

		mem(vis,0);
		dfs(S);
		int cnt=0;
		for (int i=1;i<=m;i++)
			if (EE[i].w<=Ans) cnt++;
			else if (vis[EE[i].u]!=vis[EE[i].v]) cnt++;
		if (first) printf("\n");
		first=1;
		printf("%d\n",cnt);
		bool ot=0;
		for (int i=1;i<=m;i++)
			if (EE[i].w<=Ans)
			{
				if (ot) printf(" ");
				ot=1;
				printf("%d",i);
			}
			else if (vis[EE[i].u]!=vis[EE[i].v])
			{
				if (ot) printf(" ");
				ot=1;
				printf("%d",i);
			}
		printf("\n");
	}
	return 0;
}

ld Calc(ld K)
{
	//cout<<"Check:"<<K<<endl;
	edgecnt=-1;mem(Head,-1);
	ld Ret=0;
	S=1;T=n;
	for (int i=1;i<=m;i++)
	{
		if (EE[i].w>K) Add_Edge(EE[i].u,EE[i].v,EE[i].w-K,i);
		else Ret+=EE[i].w-K;
	}
	while (Bfs())
	{
		for (int i=1;i<=n;i++) cur[i]=Head[i];
		while (ld di=dfs(S,inf)) Ret+=di;
	}
	//cout<<"Check:"<<K<<" "<<Ret<<endl;
	return Ret;
}

void Add_Edge(int u,int v,ld flow,int id)
{
	Id[id]=edgecnt+1;
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,flow});
	edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){u,flow});
	return;
}

bool Bfs()
{
	int h=1,t=0;mem(Depth,-1);
	Q[1]=S;Depth[S]=1;
	do
	{
		int u=Q[++t];
		for (int i=Head[u];i!=-1;i=Next[i])
			if ((E[i].flow>eps)&&(Depth[E[i].v]==-1))
				Depth[Q[++h]=E[i].v]=Depth[u]+1;
	}
	while (t!=h);
	return Depth[T]!=-1;
}

ld dfs(int u,ld flow)
{
	if (u==T) return flow;
	for (int &i=cur[u];i!=-1;i=Next[i])
		if ((E[i].flow>eps)&&(Depth[E[i].v]==Depth[u]+1))
		{
			ld di=dfs(E[i].v,min(flow,E[i].flow));
			if (di)
			{
				E[i].flow-=di;
				E[i^1].flow+=di;
				return di;
			}
		}
	return 0.0;
}

void dfs(int u)
{
	vis[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((E[i].flow>eps)&&(vis[E[i].v]==0))
			dfs(E[i].v);
	return;
}
/*
6 8
1 2 3
1 3 3
2 4 2
2 5 2
3 4 2
3 5 2
5 6 3
4 6 3
4 5
1 2 2
1 3 2
2 3 1
2 4 2
3 4 2
*/
