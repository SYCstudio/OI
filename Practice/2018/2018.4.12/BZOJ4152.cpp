#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=200100;
const int maxM=maxN*4;
const int inf=2147483647;

class Pos
{
public:
	int x,y,id;
};

class Edge
{
public:
	int v;
	ll w;
};

class HeapData
{
public:
	int u;
	ll dist;
};

int n;
int edgecnt=0,Head[maxN],Next[maxM];
Pos P[maxN];
Edge E[maxM];
ll Dist[maxN];
priority_queue<HeapData> H;
bool vis[maxN];

bool cmp1(Pos A,Pos B);
bool cmp2(Pos A,Pos B);
bool operator < (HeapData A,HeapData B);
void Add_Edge(int u,int v,ll w);

int main()
{
	mem(Head,-1);
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		cin>>P[i].x>>P[i].y;
		P[i].id=i;
	}
	sort(&P[1],&P[n+1],cmp1);
	for (int i=2;i<=n;i++) Add_Edge(P[i-1].id,P[i].id,P[i].x-P[i-1].x);
	sort(&P[1],&P[n+1],cmp2);
	for (int i=2;i<=n;i++) Add_Edge(P[i-1].id,P[i].id,P[i].y-P[i-1].y);

	mem(Dist,-1);
	Dist[1]=0;H.push((HeapData){1,0});
	do
	{
		int u=H.top().u;H.pop();
		if (vis[u]==1) continue;
		vis[u]=1;
		for (int i=Head[u];i!=-1;i=Next[i])
			if ((vis[E[i].v]==0)&&((Dist[E[i].v]==-1)||(Dist[E[i].v]>Dist[u]+E[i].w)))
			{
				Dist[E[i].v]=Dist[u]+E[i].w;
				H.push((HeapData){E[i].v,Dist[E[i].v]});
			}
	}
	while (!H.empty());
	cout<<Dist[n]<<endl;
	return 0;
}

bool cmp1(Pos A,Pos B)
{
	return A.x<B.x;
}

bool cmp2(Pos A,Pos B)
{
	return A.y<B.y;
}

bool operator < (HeapData A,HeapData B)
{
	return A.dist>B.dist;
}

void Add_Edge(int u,int v,ll w)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt].v=v;E[edgecnt].w=w;
	edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt].v=u;E[edgecnt].w=w;
	return;
}
