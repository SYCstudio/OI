#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100100;
const int maxM=1000100*2;
const int inf=2147483647;

class Queue_Data
{
public:
	int u;
	ll dis;
};

ll Height[maxN];

bool operator < (Queue_Data A,Queue_Data B){
	if (Height[A.u]!=Height[B.u]) return Height[A.u]<Height[B.u];
	else return A.dis>B.dis;
}

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
ll W[maxM];
ll Dis[maxN];
bool vis[maxN];
priority_queue<Queue_Data> Q;

void Add_Edge(int u,int v,int w);

int main()
{
	mem(Head,-1);
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=1;i<=n;i++) cin>>Height[i];
	for (int i=1;i<=m;i++)
	{
		int u,v,w;cin>>u>>v>>w;
		if (Height[u]>=Height[v]) Add_Edge(u,v,w);
		if (Height[v]>=Height[u]) Add_Edge(v,u,w);
	}
	mem(Dis,-1);Dis[1]=0;
	Q.push((Queue_Data){1,0});
	ll Ans=0,Sum=0;
	do
	{
		Queue_Data u=Q.top();Q.pop();
		if (vis[u.u]) continue;
		vis[u.u]=1;
		Ans++;Sum=Sum+(ll)Dis[u.u];
		for (int i=Head[u.u];i!=-1;i=Next[i])
			if ((vis[V[i]]==0)&&((Dis[V[i]]==-1)||(Dis[V[i]]>W[i]))){
				Dis[V[i]]=W[i];Q.push((Queue_Data){V[i],Dis[V[i]]});
			}
	}
	while (!Q.empty());
	printf("%lld %lld\n",Ans,Sum);
	return 0;
}

void Add_Edge(int u,int v,int w)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}
