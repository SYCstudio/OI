#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=301000*2;
const int maxBit=18;
const int inf=2147483647;
const ll INF=1e17;

class EDGE
{
public:
	int u,v;
	ll w;
	bool chs;
};

class Edge
{
public:
	int v;
	ll w;
};

int n,m;
int UFS[maxN];
EDGE EE[maxM];
int edgecnt=0,Head[maxN],Next[maxM];
Edge E[maxM];
int Fa[maxBit][maxN],Depth[maxN];
ll FaW[maxBit][maxN],FaWW[maxBit][maxN];

bool operator < (EDGE A,EDGE B);
int Find(int x);
void Add_Edge(int u,int v,int w);
void dfs(int u);

int main()
{
	mem(Head,-1);
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=1;i<=n;i++) UFS[i]=i;
	for (int i=1;i<=m;i++) cin>>EE[i].u>>EE[i].v>>EE[i].w;
	sort(&EE[1],&EE[m+1]);
	ll mst=0;
	for (int i=1;i<=m;i++)
		if (Find(EE[i].u)!=Find(EE[i].v))
		{
			mst+=EE[i].w;
			UFS[Find(EE[i].u)]=Find(EE[i].v);
			EE[i].chs=1;
			Add_Edge(EE[i].u,EE[i].v,EE[i].w);Add_Edge(EE[i].v,EE[i].u,EE[i].w);
		}
	//cout<<mst<<endl;
	Depth[1]=1;dfs(1);
	for (int i=1;i<maxBit;i++)
		for (int j=1;j<=n;j++)
			if ((Fa[i-1][j]!=0)&&(Fa[i-1][Fa[i-1][j]]!=0))
			{
				Fa[i][j]=Fa[i-1][Fa[i-1][j]];
				FaW[i][j]=max(FaW[i-1][j],FaW[i-1][Fa[i-1][j]]);
				FaWW[i][j]=max(FaWW[i-1][j],FaWW[i-1][Fa[i-1][j]]);
				if (FaW[i][j]!=FaW[i-1][j]) FaWW[i][j]=max(FaWW[i][j],FaW[i-1][j]);
				if (FaW[i][j]!=FaW[i-1][Fa[i-1][j]]) FaWW[i][j]=max(FaWW[i][j],FaW[i-1][Fa[i-1][j]]);
			}
	ll mmst=INF;
	for (int e=1;e<=m;e++)
		if (EE[e].chs==0)
		{
			int u=EE[e].u,v=EE[e].v;
			//cout<<u<<" "<<v<<" "<<EE[e].w<<endl;
			ll mx=-1,mx2=-1;
			if (Depth[u]<Depth[v]) swap(u,v);
			for (int i=maxBit-1;i>=0;i--)
				if ((Fa[i][u]!=0)&&(Depth[Fa[i][u]]>=Depth[v]))
				{
					mx=max(mx,FaW[i][u]);
					mx2=max(mx2,FaWW[i][u]);
					//cout<<"u:"<<u<<" i:"<<i<<" w1:"<<FaW[i][u]<<" w2:"<<FaWW[i][u]<<endl;
					if (mx!=FaW[i][u]) mx2=max(mx2,FaW[i][u]);
					u=Fa[i][u];
				}
			if (u==v)
			{
				//cout<<"Case1:"<<mx<<" "<<mx2<<endl;
				if (mx==EE[e].w) mx=mx2;
				mmst=min(mmst,mst-mx+EE[e].w);
				continue;
			}
			//cout<<"now:"<<u<<" "<<v<<endl;
			for (int i=maxBit-1;i>=0;i--)
				if ((Fa[i][u]!=0)&&(Fa[i][v]!=0)&&(Fa[i][u]!=Fa[i][v]))
				{
					mx=max(mx,FaW[i][u]);mx=max(mx,FaW[i][v]);
					mx2=max(mx2,FaWW[i][u]);mx2=max(mx2,FaWW[i][v]);
					if (mx!=FaW[i][u]) mx2=max(mx2,FaW[i][u]);
					if (mx!=FaW[i][v]) mx2=max(mx2,FaW[i][v]);
					u=Fa[i][u];v=Fa[i][v];
				}
			//cout<<"u:"<<FaW[0][u]<<" "<<FaWW[0][u]<<endl;
			//cout<<"v:"<<FaW[0][v]<<" "<<FaWW[0][v]<<endl;
			mx=max(mx,FaW[0][u]);mx=max(mx,FaW[0][v]);
			mx2=max(mx2,FaWW[0][u]);mx2=max(mx2,FaWW[0][v]);
			if (mx!=FaW[0][u]) mx2=max(mx2,FaW[0][u]);
			if (mx!=FaW[0][v]) mx2=max(mx2,FaW[0][v]);
			//cout<<"Case2:"<<mx<<" "<<mx2<<endl;
			if (mx==EE[e].w) mx=mx2;
			mmst=min(mmst,mst-mx+EE[e].w);
		}
	cout<<mmst<<endl;
	return 0;
}

bool operator < (EDGE A,EDGE B)
{
	return A.w<B.w;
}

int Find(int x)
{
	if (UFS[x]!=x) UFS[x]=Find(UFS[x]);
	return UFS[x];
}

void Add_Edge(int u,int v,int w)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;
	E[edgecnt].v=v;E[edgecnt].w=w;
	return;
}

void dfs(int u)
{
	for (int i=Head[u];i!=-1;i=Next[i])
		if (E[i].v!=Fa[0][u])
		{
			Fa[0][E[i].v]=u;FaW[0][E[i].v]=E[i].w;FaWW[0][E[i].v]=-inf;Depth[E[i].v]=Depth[u]+1;
			dfs(E[i].v);
		}
	return;
}
