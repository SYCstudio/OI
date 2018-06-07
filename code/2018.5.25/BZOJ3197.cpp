#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define ull unsigned long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const ull base1=20020729;
const ull base2=170524;
const int inf=2147483647;

class SortData
{
public:
	int depth,id;
	ull hash;
};

int n;
int Val1[maxN],Val2[maxN];
ull Hash[maxN];
int Depth[maxN],Fa[maxN];
SortData Sorter[maxN];
int F[maxN][maxN];

bool cmp1(SortData A,SortData B);
bool cmp2(int a,int b);
int DP(int u,int v);

namespace Tree
{
	const int maxN=1010;
	const int maxM=maxN*2;
	
	int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
	int Size[maxN],mxSon[maxN];
	int root;
	ull Sorter[maxN];

	void Init();
	void Add_Edge(int u,int v);
	void GetRoot();
	void dfs_root(int u,int fa);
	void GetHash(int u,int fa);
}

namespace Flow
{
	const int maxN=1510;
	const int maxM=maxN*maxN*30;

	class Edge
	{
	public:
		int u,v,flow,w;
	};

	int S,T;
	int edgecnt,Head[maxN],Next[maxM];
	Edge E[maxM];
	int Dist[maxN],Flow[maxN],Path[maxN];
	queue<int> Queue;
	bool inqueue[maxN];

	void Init();
	void Add_Edge(int u,int v,int flow,int w);
	int GetMxFlow();
	bool Spfa();
}

int main()
{
	Tree::Init();
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		Tree::Add_Edge(u,v);Tree::Add_Edge(v,u);
	}
	
	for (int i=1;i<=n;i++) scanf("%d",&Val1[i]);
	for (int i=1;i<=n;i++) scanf("%d",&Val2[i]);

	Tree::GetRoot();
	Tree::GetHash(Tree::root,0);

	//for (int i=1;i<=n;i++) cout<<Hash[i]<<" ";cout<<endl;

	for (int i=1;i<=n;i++) Sorter[i]=((SortData){Depth[i],i,Hash[i]});
	sort(&Sorter[1],&Sorter[n+1],cmp1);
	//for (int i=1;i<=n;i++) cout<<"("<<Sorter[i].depth<<","<<Sorter[i].id<<","<<Sorter[i].hash<<")"<<endl;
	for (int i=1,j;i<=n;i=j)
	{
		j=i+1;
		while ((j<=n)&&(Sorter[i].depth==Sorter[j].depth)&&(Sorter[i].hash==Sorter[j].hash)) j++;
		//cout<<"("<<i<<","<<j<<")"<<endl;
		for (int k=i;k<j;k++)
			for (int l=i;l<j;l++)
			{
				F[Sorter[k].id][Sorter[l].id]=DP(Sorter[k].id,Sorter[l].id);
				//printf("F[%d][%d] %d\n",Sorter[k].id,Sorter[l].id,F[Sorter[k].id][Sorter[l].id]);
			}
	}
	printf("%d\n",F[Tree::root][Tree::root]);
}

bool cmp1(SortData A,SortData B)
{
	if (A.depth!=B.depth) return A.depth>B.depth;
	return A.hash<B.hash;
}

bool cmp2(int a,int b)
{
	return Hash[a]<Hash[b];
}

int DP(int u,int v)
{
	//cout<<"u:"<<u<<" v:"<<v<<endl;
	int st1[maxN],st2[maxN],top1=0,top2=0;
	for (int i=Tree::Head[u];i!=-1;i=Tree::Next[i])
		if (Tree::V[i]!=Fa[u]) st1[++top1]=Tree::V[i];
	for (int i=Tree::Head[v];i!=-1;i=Tree::Next[i])
		if (Tree::V[i]!=Fa[v]) st2[++top2]=Tree::V[i];
	sort(&st1[1],&st1[top1+1],cmp2);
	sort(&st2[1],&st2[top2+1],cmp2);
	//for (int i=1;i<=top1;i++) cout<<st1[i]<<" ";cout<<endl;
	//for (int i=1;i<=top2;i++) cout<<st2[i]<<" ";cout<<endl;
	Flow::Init();
	Flow::S=top1+top2+1;Flow::T=Flow::S+1;
	for (int i=1;i<=top1;i++) Flow::Add_Edge(Flow::S,i,1,0);
	for (int i=1;i<=top2;i++) Flow::Add_Edge(i+top1,Flow::T,1,0);
	for (int i=1,j;i<=top1;i=j)
	{
		j=i+1;
		while ((j<=top1)&&(Hash[st1[i]]==Hash[st1[j]])) j++;
		for (int k=i;k<j;k++)
			for (int l=i;l<j;l++)
				Flow::Add_Edge(k,top1+l,1,F[st1[k]][st2[l]]);
	}
	return Flow::GetMxFlow()+(Val1[u]^Val2[v]);
}

namespace Tree
{
	void Init()
	{
		edgecnt=0;mem(Head,-1);
		return;
	}

	void Add_Edge(int u,int v)
	{
		edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
		return;
	}

	void GetRoot()
	{
		root=0;mxSon[0]=inf;
		dfs_root(1,0);

		if ((mxSon[root]<<1)==n)
		{
			int node1=root;
			root=0;dfs_root(node1,0);
			for (int i=Head[node1],last=-1;i!=-1;last=i,i=Next[i])
				if ((Size[V[i]]<<1)==n)
				{
					++n;
					if (i==Head[node1]) Head[node1]=Next[i];
					else Next[last]=Next[i];
					for (int j=Head[V[i]],last2=-1;j!=-1;last2=j,j=Next[j])
						if (V[j]==node1)
						{
							if (j==Head[V[i]]) Head[V[i]]=Next[j];
							else Next[last2]=Next[j];
							break;
						}
					
					Add_Edge(node1,n);Add_Edge(n,node1);Add_Edge(V[i],n);Add_Edge(n,V[i]);
					root=n;
					break;
				}
		}

		//cout<<"root:"<<root<<endl;
		//for (int i=1;i<=n;i++) for (int j=Head[i];j!=-1;j=Next[j]) cout<<i<<"->"<<V[j]<<endl;
		return;
	}

	void dfs_root(int u,int fa)
	{
		Size[u]=1;mxSon[u]=0;
		for (int i=Head[u];i!=-1;i=Next[i])
			if (V[i]!=fa)
			{
				dfs_root(V[i],u);
				Size[u]+=Size[V[i]];
				mxSon[u]=max(mxSon[u],Size[V[i]]);
			}
		mxSon[u]=max(mxSon[u],n-Size[u]);
		if (mxSon[u]<mxSon[root]) root=u;
		return;
	}

	void GetHash(int u,int fa)
	{
		Depth[u]=Depth[fa]+1;Fa[u]=fa;
		for (int i=Head[u];i!=-1;i=Next[i])
			if (V[i]!=fa) GetHash(V[i],u);
		int cnt=0;
		for (int i=Head[u];i!=-1;i=Next[i])
			if (V[i]!=fa) Sorter[++cnt]=Hash[V[i]];
		sort(&Sorter[1],&Sorter[cnt+1]);
		Hash[u]=base2;
		for (int i=1;i<=cnt;i++) Hash[u]=((Hash[u]*base1)^Sorter[i])+Sorter[i];
		//Order[++ordcnt]=u;
		return;
	}
}

namespace Flow
{
	void Init()
	{
		edgecnt=-1;mem(Head,-1);
		return;
	}

	void Add_Edge(int u,int v,int flow,int w)
	{
		edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt].u=u;E[edgecnt].v=v;E[edgecnt].flow=flow;E[edgecnt].w=w;
		edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt].u=v;E[edgecnt].v=u;E[edgecnt].flow=0;E[edgecnt].w=-w;
		return;
	}

	int GetMxFlow()
	{
		/*
		for (int i=1;i<=T;i++)
			for (int j=Head[i];j!=-1;j=Next[j])
				if (E[j].flow) cout<<i<<"->"<<E[j].v<<" "<<E[j].w<<endl;
		//*/
		int Ans=0;
		int flowsum=0;
		while (Spfa())
		{
			Ans=Ans+Flow[T]*Dist[T];flowsum+=Flow[T];
			//cout<<Flow[T]<<" "<<Dist[T]<<endl;
			int now=T;
			while (now!=S)
			{
				//cout<<now<<" ";
				E[Path[now]].flow-=Flow[T];
				E[Path[now]^1].flow+=Flow[T];
				now=E[Path[now]].u;
			}
			//cout<<endl;
		}
		//cout<<"flow:"<<flowsum<<endl;
		return Ans;
	}

	bool Spfa()
	{
		for (int i=1;i<=T;i++) Dist[i]=inf;
		while (!Queue.empty()) Queue.pop();
		mem(inqueue,0);
		Dist[S]=0;Queue.push(S);Flow[S]=inf;inqueue[S]=1;
		do
		{
			int u=Queue.front();Queue.pop();
			for (int i=Head[u];i!=-1;i=Next[i])
				if ((E[i].flow>0)&&(Dist[E[i].v]>Dist[u]+E[i].w))
				{
					Dist[E[i].v]=Dist[u]+E[i].w;Flow[E[i].v]=min(Flow[u],E[i].flow);Path[E[i].v]=i;
					if (inqueue[E[i].v]==0)
					{
						Queue.push(E[i].v);
						inqueue[E[i].v]=1;
					}
				}
			inqueue[u]=0;
		}
		while (!Queue.empty());
		if (Dist[T]==inf) return 0;
		return 1;
	}
}
