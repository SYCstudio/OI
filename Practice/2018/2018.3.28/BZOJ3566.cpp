#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=501000;
const int maxM=maxN*2;
const int inf=2147483647;

int n;
ld Node[maxN];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
ld W[maxM];
ld F[maxN];

void Add_Edge(int u,int v,int w);
void dfs1(int u,int fa);
void dfs2(int u,int fa,ld gl);

int main()
{
	ios::sync_with_stdio(false);mem(Head,-1);

	cin>>n;
	for (int i=1;i<n;i++)
	{
		int u,v,w;cin>>u>>v>>w;
		Add_Edge(u,v,w);Add_Edge(v,u,w);
	}
	for (int i=1;i<=n;i++)
	{
		int w;cin>>w;
		Node[i]=(ld)w/(ld)(100);
	}
	dfs1(1,1);
	//for (int i=1;i<=n;i++) cout<<F[i]<<" ";cout<<endl;
	dfs2(1,1,1);
	//for (int i=1;i<=n;i++) cout<<F[i]<<" ";cout<<endl;
	ld Ans=0;
	for (int i=1;i<=n;i++) Ans=Ans+(1-F[i]);
	printf("%.6LF\n",Ans);
	return 0;
}

void Add_Edge(int u,int v,int w)
{
	ld ww=(ld)w/(ld)100;
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=ww;
	return;
}

void dfs1(int u,int fa)
{
	F[u]=1-Node[u];
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			dfs1(V[i],u);
			F[u]=F[u]*((1-W[i])+W[i]*F[V[i]]);
		}
	return;
}

void dfs2(int u,int fa,ld gl)
{
	F[u]=F[u]*gl;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			ld t=(1-W[i])+W[i]*F[V[i]];
			t=F[u]/t;
			dfs2(V[i],u,t+((ld)1-t)*((ld)1-W[i]));
		}
	return;
}
