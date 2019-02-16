#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=51000*10;
const int maxM=maxN*10;
const int inf=2147483647;

class EDGE
{
public:
	int a,b,c,d;
};

int n,m,K;
int edgecnt,HeadIn[maxN],HeadOut[maxN],Next[maxN],V[maxN];
EDGE E[maxN];
int PreIn[maxN],PreOut[maxN],SufIn[maxN],SufOut[maxN],Queue[maxN];

void Add(int &head,int v);
void Doing(int id);
bool cmp(int a,int b);

namespace TRIE
{
	const int maxBit=15;
	
	map<int,int> Son[maxN];
	int dfncnt,Dfn[maxN],Fa[maxBit][maxN],Depth[maxN];

	void Add(int u,int v,int w);
	void Do();
	void dfs_dfn(int u);
	int GetLCA(int u,int v);
}

namespace GRAPH
{
	class HeapData
	{
	public:
		int u,dist;
	};
	
	int NodeW[maxN];
	int nodecnt;
	int edgecnt=0,Head[maxN],Next[maxM],V[maxM],W[maxM],Dist[maxN];
	bool vis[maxN];
	priority_queue<HeapData> H;

	void Add_Edge(int u,int v,int w);
	bool operator < (HeapData A,HeapData B);
	void Dij();
}

int main()
{
	//freopen("20.in","r",stdin);freopen("out.out","w",stdout);
	mem(HeadIn,-1);mem(HeadOut,-1);edgecnt=0;TRIE::dfncnt=0;GRAPH::nodecnt=0;GRAPH::edgecnt=0;mem(GRAPH::Head,-1);
	int TTT;scanf("%d",&TTT);
	while (TTT--)
	{
		scanf("%d%d%d",&n,&m,&K);
		GRAPH::nodecnt=m;
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d%d%d",&E[i].a,&E[i].b,&E[i].c,&E[i].d);
			Add(HeadIn[E[i].b],i);Add(HeadOut[E[i].a],i);
			GRAPH::NodeW[i]=E[i].c;
		}
		for (int i=1;i<K;i++)
		{
			int u,v,w;scanf("%d%d%d",&u,&v,&w);
			TRIE::Add(u,v,w);
		}
		//cout<<"Nodecnt:"<<GRAPH::nodecnt<<endl;

		//cout<<"Input over"<<endl;
		
		TRIE::Do();
		
		for (int i=1;i<=n;i++) Doing(i);

		GRAPH::Dij();

		for (int i=2;i<=n;i++)
		{
			int ans=inf;
			for (int j=HeadIn[i];j!=-1;j=Next[j])
				ans=min(ans,GRAPH::Dist[V[j]]);
			printf("%d\n",ans);
		}

		mem(HeadIn,-1);mem(HeadOut,-1);edgecnt=0;TRIE::dfncnt=0;GRAPH::nodecnt=0;GRAPH::edgecnt=0;mem(GRAPH::Head,-1);mem(TRIE::Fa,0);mem(TRIE::Depth,0);mem(GRAPH::NodeW,0);
		for (int i=1;i<=K;i++) TRIE::Son[i].clear();
	}
	return 0;
}

void Add(int &head,int v)
{
	edgecnt++;Next[edgecnt]=head;head=edgecnt;V[edgecnt]=v;
	return;
}

void Doing(int id)
{
	//cout<<"Doing:"<<id<<endl;
	int cnt=0;
	for (int i=HeadIn[id];i!=-1;i=Next[i]) Queue[++cnt]=V[i];
	for (int i=HeadOut[id];i!=-1;i=Next[i]) Queue[++cnt]=-V[i];
	sort(&Queue[1],&Queue[cnt+1],cmp);

	//cout<<cnt<<endl;
	//for (int i=1;i<=cnt;i++) cout<<Queue[i]<<" ";cout<<endl;

	for (int i=1;i<=cnt;i++)
	{
		PreIn[i]=++GRAPH::nodecnt;PreOut[i]=++GRAPH::nodecnt;SufIn[i]=++GRAPH::nodecnt;SufOut[i]=++GRAPH::nodecnt;
		if (i>1)
		{
			GRAPH::Add_Edge(PreIn[i-1],PreIn[i],0);
			GRAPH::Add_Edge(PreOut[i-1],PreOut[i],0);
			GRAPH::Add_Edge(SufIn[i],SufIn[i-1],0);
			GRAPH::Add_Edge(SufOut[i],SufOut[i-1],0);
		}
		if (Queue[i]>0) GRAPH::Add_Edge(Queue[i],PreIn[i],0),GRAPH::Add_Edge(Queue[i],SufIn[i],0);
		if (Queue[i]<0) Queue[i]*=-1,GRAPH::Add_Edge(PreOut[i],Queue[i],0),GRAPH::Add_Edge(SufOut[i],Queue[i],0);
	}

	//for (int i=1;i<=cnt;i++) cout<<PreIn[i]<<" ";cout<<endl;
	//for (int i=1;i<=cnt;i++) cout<<SufIn[i]<<" ";cout<<endl;
	//for (int i=1;i<=cnt;i++) cout<<PreOut[i]<<" ";cout<<endl;
	//for (int i=1;i<=cnt;i++) cout<<SufOut[i]<<" ";cout<<endl;

	for (int i=1;i<cnt;i++)
	{
		int lca=TRIE::GetLCA(E[Queue[i]].d,E[Queue[i+1]].d);
		//cout<<"LCA:"<<E[Queue[i]].d<<" "<<E[Queue[i+1]].d<<" "<<lca<<endl;
		int d=TRIE::Depth[lca]-1;
		GRAPH::Add_Edge(PreIn[i],PreOut[i+1],d);
		GRAPH::Add_Edge(SufIn[i+1],SufOut[i],d);
	}
	return;
}

bool cmp(int u,int v){
	return TRIE::Dfn[E[abs(u)].d]<TRIE::Dfn[E[abs(v)].d];
}

namespace TRIE
{
	void Add(int u,int v,int w){
		Son[u][w]=v;return;
	}

	void Do()
	{
		Depth[1]=1;
		dfs_dfn(1);
		for (int i=1;i<maxBit;i++)
			for (int j=1;j<=K;j++)
				if ((Fa[i-1][j])&&(Fa[i-1][Fa[i-1][j]]))
					Fa[i][j]=Fa[i-1][Fa[i-1][j]];
		return;
	}

	void dfs_dfn(int u)
	{
		Dfn[u]=++dfncnt;
		for (map<int,int>::iterator i=Son[u].begin();i!=Son[u].end();i++) Depth[(*i).second]=Depth[u]+1,Fa[0][(*i).second]=u,dfs_dfn((*i).second);
		return;
	}

	int GetLCA(int u,int v)
	{
		if (Depth[u]<Depth[v]) swap(u,v);
		for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u])&&(Depth[Fa[i][u]]>=Depth[v])) u=Fa[i][u];
		if (u==v) return u;
		for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u])&&(Fa[i][v])&&(Fa[i][u]!=Fa[i][v])) u=Fa[i][u],v=Fa[i][v];
		return Fa[0][u];
	}
}

namespace GRAPH
{
	void Add_Edge(int u,int v,int w){
		edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
		//cout<<"Add:"<<u<<"->"<<v<<" "<<w<<endl;
		return;
	}

	bool operator < (HeapData A,HeapData B){
		return A.dist>B.dist;
	}

	void Dij()
	{
		mem(Dist,127);mem(vis,0);while (!H.empty()) H.pop();
		for (int i=1;i<=m;i++) if (E[i].a==1) if (Dist[i]>NodeW[i]) Dist[i]=NodeW[i],H.push((HeapData){i,Dist[i]});
		do
		{
			int u=H.top().u;H.pop();
			if (vis[u]) continue;
			vis[u]=1;
			for (int i=Head[u];i!=-1;i=Next[i])
				if ((vis[V[i]]==0)&&(Dist[V[i]]>Dist[u]+NodeW[V[i]]+W[i]))
					Dist[V[i]]=Dist[u]+NodeW[V[i]]+W[i],H.push((HeapData){V[i],Dist[V[i]]});
		}
		while (!H.empty());
		//for (int i=1;i<=nodecnt;i++) cout<<Dist[i]<<" ";cout<<endl;
		return;
	}
}
