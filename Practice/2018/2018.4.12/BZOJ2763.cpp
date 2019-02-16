#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=20010;
const int maxM=50100*2;
const int maxK=12;
const int inf=2147483647;

class Edge
{
public:
	int v,w;
};

class HeapData
{
public:
	int u,k,dist;
};

int n,m,K,S,T;
int edgecnt=0,Head[maxN],Next[maxM];
Edge E[maxM];
int Dist[maxN][maxK];
bool vis[maxN][maxK];
priority_queue<HeapData> H;

void Add_Edge(int u,int v,int w);
bool operator < (HeapData A,HeapData B);

int main()
{
	mem(Head,-1);
	ios::sync_with_stdio(false);
	cin>>n>>m>>K;cin>>S>>T;S++;T++;
	for (int i=1;i<=m;i++)
	{
		int u,v,w;cin>>u>>v>>w;u++;v++;
		Add_Edge(u,v,w);Add_Edge(v,u,w);
	}
	mem(Dist,-1);
	for (int i=0;i<=K;i++)
	{
		Dist[S][i]=0;
		H.push((HeapData){S,i,0});
	}
	do
	{
		HeapData u=H.top();H.pop();
		if (vis[u.u][u.k]==1) continue;
		vis[u.u][u.k]=1;
		for (int i=Head[u.u];i!=-1;i=Next[i])
		{
			if ((vis[E[i].v][u.k]==0)&&((Dist[E[i].v][u.k]==-1)||(Dist[E[i].v][u.k]>u.dist+E[i].w)))
			{
				//cout<<"("<<u.u<<","<<u.k<<")->("<<E[i].v<<","<<u.k<<") "<<u.dist<<" "<<E[i].w<<endl;
				Dist[E[i].v][u.k]=u.dist+E[i].w;
				H.push((HeapData){E[i].v,u.k,Dist[E[i].v][u.k]});
			}
			if ((u.k<K)&&(vis[E[i].v][u.k+1]==0)&&((Dist[E[i].v][u.k+1]==-1)||(Dist[E[i].v][u.k+1]>u.dist)))
			{
				Dist[E[i].v][u.k+1]=u.dist;
				H.push((HeapData){E[i].v,u.k+1,u.dist});
			}
		}
	}
	while (!H.empty());
	int Ans=inf;
	//for (int i=0;i<=K;i++) cout<<Dist[T][i]<<endl;
	for (int i=0;i<=K;i++) Ans=min(Ans,Dist[T][i]);
	cout<<Ans<<endl;
	return 0;
}

void Add_Edge(int u,int v,int w)
{
	//cout<<u<<"-"<<v<<" "<<w<<endl;
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt].v=v;E[edgecnt].w=w;
	return;
}

bool operator < (HeapData A,HeapData B)
{
	return A.dist>B.dist;
}
