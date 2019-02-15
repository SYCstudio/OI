#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10100*2;
const int maxM=maxN*20;
const int maxBit=15;
const int inf=2147483647;

class Edge
{
public:
	int v,w;
};

int n,m,Q,nodecnt;
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM],W[maxM];
int dfncnt,dfn[maxN],low[maxN],Fa[maxN],depth[maxN],dist[maxN];
vector<Edge> T[maxN];
int Seq[maxN],Dis[maxN];
int Pa[maxBit][maxN],Depth[maxN],Dist[maxN];
int Bt[maxN],Tp[maxN],Tpw[maxN];

void Add_Edge(int u,int v,int w);
void tarjan(int u,int fa);
void GetRing(int tp,int bt);
void dfs(int u,int fa);
int LCA(int u,int v);

int main()
{
	mem(Head,-1);
	scanf("%d%d%d",&n,&m,&Q);
	for (int i=1;i<=m;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		Add_Edge(u,v,w);
	}

	nodecnt=n;depth[1]=0;
	tarjan(1,0);

	/*
	for (int i=1;i<=nodecnt;i++)
		for (int j=0;j<T[i].size();j++)
			cout<<i<<"->"<<T[i][j].v<<" "<<T[i][j].w<<endl;
	//*/

	Depth[1]=1;
	dfs(1,0);

	for (int i=1;i<maxBit;i++)
		for (int j=1;j<=nodecnt;j++)
			Pa[i][j]=Pa[i-1][Pa[i-1][j]];

	while (Q--)
	{
		int u,v;scanf("%d%d",&u,&v);
		int lca=LCA(u,v);
		//cout<<u<<" "<<v<<":"<<lca<<endl;
		if (lca<=n){
			printf("%d\n",Dist[u]+Dist[v]-2*Dist[lca]);
			continue;
		}
		int uu=u,vv=v;
		for (int i=maxBit-1;i>=0;i--){
			if ((Pa[i][uu])&&(Depth[Pa[i][uu]]>Depth[lca])) uu=Pa[i][uu];
			if ((Pa[i][vv])&&(Depth[Pa[i][vv]]>Depth[lca])) vv=Pa[i][vv];
		}

		int Ans=Dist[u]-Dist[uu]+Dist[v]-Dist[vv];
		if (depth[uu]<depth[vv]) swap(uu,vv);
		Ans=Ans+min(dist[uu]-dist[vv],dist[Bt[lca]]-dist[uu]+dist[vv]-dist[Tp[lca]]+Tpw[lca]);
		printf("%d\n",Ans);
	}
	return 0;
}

void Add_Edge(int u,int v,int w){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;W[edgecnt]=w;
	return;
}

void tarjan(int u,int fa)
{
	dfn[u]=low[u]=++dfncnt;Fa[u]=fa;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			int v=V[i];
			if (dfn[v]==0){
				depth[v]=depth[u]+1;dist[v]=dist[u]+W[i];
				tarjan(v,u);
				low[u]=min(low[u],low[v]);
				if (dfn[u]<low[v]) T[u].push_back((Edge){v,W[i]}),T[v].push_back((Edge){u,W[i]});
			}
			else low[u]=min(low[u],dfn[v]);
		}
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(dfn[V[i]]>dfn[u])&&(Fa[V[i]]!=u))
			GetRing(u,V[i]);
	return;
}

void GetRing(int tp,int bt)
{
	int ncnt=0;nodecnt++;Tp[nodecnt]=tp;Bt[nodecnt]=bt;
	for (int now=bt;now!=tp;now=Fa[now]){
		Seq[++ncnt]=now;
		for (int i=Head[now];i!=-1;i=Next[i])
			if (V[i]==Fa[now]){
				Dis[ncnt]=W[i];break;
			}
	}
	Seq[++ncnt]=tp;
	for (int i=Head[tp];i!=-1;i=Next[i])
		if (V[i]==bt){
			Dis[ncnt]=W[i];Tpw[nodecnt]=W[i];break;
		}

	//cout<<"GetRing:"<<tp<<" "<<bt<<endl;
	//for (int i=1;i<=ncnt;i++) cout<<Seq[i]<<" ";cout<<endl;
	//for (int i=1;i<=ncnt;i++) cout<<Dis[i]<<" ";cout<<endl;
	
	for (int i=1;i<=ncnt;i++) Dis[i]+=Dis[i-1];

	T[tp].push_back((Edge){nodecnt,0});T[nodecnt].push_back((Edge){tp,0});
	for (int i=1;i<ncnt;i++)
	{
		int d=min(Dis[i-1]+Dis[ncnt]-Dis[ncnt-1],Dis[ncnt-1]-Dis[i-1]);
		T[Seq[i]].push_back((Edge){nodecnt,d});T[nodecnt].push_back((Edge){Seq[i],d});
	}
	return;
}

void dfs(int u,int fa)
{
	int sz=T[u].size();
	for (int i=0;i<sz;i++)
		if (T[u][i].v!=fa){
			Pa[0][T[u][i].v]=u;
			Depth[T[u][i].v]=Depth[u]+1;Dist[T[u][i].v]=Dist[u]+T[u][i].w;
			dfs(T[u][i].v,u);
		}
	return;
}

int LCA(int u,int v)
{
	if (Depth[u]<Depth[v]) swap(u,v);
	//cout<<"LCA:"<<u<<" "<<v<<":"<<Depth[u]<<" "<<Depth[v]<<endl;
	for (int i=maxBit-1;i>=0;i--) if ((Pa[i][u])&&(Depth[Pa[i][u]]>=Depth[v])) u=Pa[i][u];
	if (u==v) return u;
	for (int i=maxBit-1;i>=0;i--) if ((Pa[i][u])&&(Pa[i][v])&&(Pa[i][u]!=Pa[i][v])) u=Pa[i][u],v=Pa[i][v];
	return Pa[0][u];
}
/*
9 10 5
1 2 1
1 4 1
3 4 1
2 3 1
3 7 1
7 8 2
7 9 2
1 5 3
1 6 4
5 6 1
8 9
3 8
4 8
3 6
4 6
//*/
