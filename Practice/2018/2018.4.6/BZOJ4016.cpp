#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=30010;
const int maxM=60010*2;
const int inf=2147483647;

class Edge
{
public:
	int v,w;
};

class Queue_Data
{
public:
	int u,dist;
};

int n,m,K;
int Ans=0,Cnt;
int Dist[maxN];
bool vis[maxN];
vector<Edge> G[maxN];
priority_queue<Queue_Data> Heap;
priority_queue<int,vector<int>,greater<int> > Qp;
int Fa[maxN],FaW[maxN];
int edgecnt=0,Head[maxN],Next[maxM];
Edge E[maxM];
int root,mxSon[maxN],Size[maxN],nowsum;
int Max[maxN],Tot[maxN],histcnt,Hist[maxN];
int head;
Edge Queue[maxN];
//int depth,mxdepth;

bool operator < (Edge A,Edge B);
bool operator < (Queue_Data A,Queue_Data B);
void Add_Edge(int u,int v,int w);
void GetFa(int u);
void GetRoot(int u,int fa);
void Solve(int u);
void Calc(int u,int fa,int sum,int cnt);

int main()
{
	//freopen("in.in","r",stdin);freopen("err.out","w",stderr);
	mem(Head,-1);
	scanf("%d%d%d",&n,&m,&K);
	for (int i=1;i<=m;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		G[u].push_back((Edge){v,w});G[v].push_back((Edge){u,w});
	}

	mem(Dist,-1);Dist[1]=0;
	Heap.push((Queue_Data){1,0});
	do
	{
		int u=Heap.top().u;Heap.pop();
		if (vis[u]) continue;
		vis[u]=1;
		for (int i=0;i<G[u].size();i++)
			if ((vis[G[u][i].v]==0)&&((Dist[G[u][i].v]==-1)||(Dist[G[u][i].v]>Dist[u]+G[u][i].w)))
			{
				Dist[G[u][i].v]=Dist[u]+G[u][i].w;
				Heap.push((Queue_Data){G[u][i].v,Dist[G[u][i].v]});
			}
	}
	while (!Heap.empty());
	//for (int i=1;i<=n;i++) cerr<<Dist[i]<<endl;
	/*
	Qp.push(1);mem(vis,0);vis[1]=1;
	do
	{
		int u=Qp.top();Qp.pop();
		for (int i=0;i<G[u].size();i++)
			if ((Dist[G[u][i].v]==Dist[u]+G[u][i].w)&&(vis[G[u][i].v]==0))
			{
				Fa[G[u][i].v]=u;FaW[G[u][i].v]=G[u][i].w;vis[G[u][i].v]=1;
				Qp.push(G[u][i].v);
			}
	}
	while (!Qp.empty());
	//*/
	mem(vis,0);
	GetFa(1);
	
	//for (int i=1;i<=n;i++) cout<<Fa[i]<<" ";cout<<endl;

	for (int i=2;i<=n;i++) Add_Edge(i,Fa[i],FaW[i]);

	root=0;mxSon[0]=inf;nowsum=n;mem(vis,0);
	GetRoot(1,1);
	Solve(root);

	cout<<Ans<<" "<<Cnt<<endl;

	//cout<<"mxdepth:"<<mxdepth<<endl;
	return 0;
}

bool operator < (Edge A,Edge B){
	return A.v<B.v;
}

bool operator < (Queue_Data A,Queue_Data B){
	return A.dist>B.dist;
}

void Add_Edge(int u,int v,int w)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt].v=v;E[edgecnt].w=w;
	edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt].v=u;E[edgecnt].w=w;
	return;
}

void GetFa(int u)
{
	vis[u]=1;
	sort(G[u].begin(),G[u].end());
	for (int i=0;i<G[u].size();i++)
		if ((Dist[G[u][i].v]==Dist[u]+G[u][i].w)&&(vis[G[u][i].v]==0))
		{
			Fa[G[u][i].v]=u;FaW[G[u][i].v]=G[u][i].w;
			GetFa(G[u][i].v);
		}
	return;
}

void GetRoot(int u,int fa)
{
	mxSon[u]=0;Size[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((E[i].v!=fa)&&(vis[E[i].v]==0))
		{
			GetRoot(E[i].v,u);
			Size[u]+=Size[E[i].v];mxSon[u]=max(mxSon[u],Size[E[i].v]);
		}
	mxSon[u]=max(mxSon[u],nowsum-Size[u]);
	if (mxSon[u]<mxSon[root]) root=u;
	return;
}

void Solve(int u)
{
	//cout<<"Solve:"<<u<<endl;
	//depth++;mxdepth=max(mxdepth,depth);
	vis[u]=1;
	histcnt++;Hist[1]=histcnt;Max[1]=0;Tot[1]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[E[i].v]==0)
		{
			head=0;
			Calc(E[i].v,u,E[i].w,1);
			for (int j=1;j<=head;j++)
			{
				if (Queue[j].v>K) continue;
				//cout<<Queue[j].v<<" "<<Queue[j].w<<endl;
				if (Hist[K-Queue[j].v]==histcnt)
				{
					if (Ans==Max[K-Queue[j].v]+Queue[j].w) Cnt+=Tot[K-Queue[j].v];
					else if (Ans<Max[K-Queue[j].v]+Queue[j].w) Ans=Max[K-Queue[j].v]+Queue[j].w,Cnt=Tot[K-Queue[j].v];
				}
			}
			for (int j=1;j<=head;j++)
			{
				if (Queue[j].v>=K) continue;
				if (Hist[Queue[j].v+1]!=histcnt)
				{
					Hist[Queue[j].v+1]=histcnt;
					Max[Queue[j].v+1]=Queue[j].w;Tot[Queue[j].v+1]=1;
				}
				else if (Max[Queue[j].v+1]==Queue[j].w) Tot[Queue[j].v+1]++;
				else if (Max[Queue[j].v+1]<Queue[j].w) Max[Queue[j].v+1]=Queue[j].w,Tot[Queue[j].v+1]=1;
			}
			//cout<<endl;
		}
	//cout<<endl;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[E[i].v]==0)
		{
			root=0;nowsum=Size[E[i].v];
			GetRoot(E[i].v,E[i].v);
			Solve(root);
		}
	//depth--;
	return;
}

void Calc(int u,int fa,int sum,int cnt)
{
	Queue[++head]=((Edge){cnt,sum});
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((E[i].v!=fa)&&(vis[E[i].v]==0)) Calc(E[i].v,u,sum+E[i].w,cnt+1);
	return;
}
