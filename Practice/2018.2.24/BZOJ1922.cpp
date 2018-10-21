#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=3010;
const int maxM=70010;
const int inf=2147483647;

class Edge
{
public:
	int v;
	ll w;
};

class Queue_Data
{
public:
	int u;ll w;
};

bool operator < (Queue_Data A,Queue_Data B)
{
	return A.w>B.w;
}

int n,m;
int edgecnt=0,Head[maxN],Next[maxM];
Edge E[maxM];
ll Dist[maxN];
int Degree[maxN],edgecnt2=0,Head2[maxN],Next2[maxM*10],V2[maxM*10];
bool vis[maxN];
priority_queue<Queue_Data> Q;

int main()
{
	mem(Head,-1);mem(Head2,-1);
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=1;i<=m;i++)
	{
		int u,v,w;cin>>u>>v>>w;
		edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt].v=v;E[edgecnt].w=w;
	}
	for (int i=1;i<=n;i++)
	{
		cin>>Degree[i];//cout<<i<<" "<<Degree[i]<<endl;
		for (int j=1;j<=Degree[i];j++)
		{
			int u;cin>>u;
			edgecnt2++;Next2[edgecnt2]=Head2[u];Head2[u]=edgecnt2;V2[edgecnt2]=i;
		}
	}
	mem(Dist,-1);Dist[1]=0;Q.push((Queue_Data){1,0});
	do
	{
		Queue_Data u=Q.top();Q.pop();
		if (vis[u.u]) continue;
		vis[u.u]=1;
		//cout<<"u:"<<u.u<<endl;
		for (int i=Head2[u.u];i!=-1;i=Next2[i])
		{
			Degree[V2[i]]--;
			//cout<<"Muns:"<<u.u<<"->"<<V2[i]<<endl;
			if (Degree[V2[i]]==0)
				if (Dist[V2[i]]!=-1)
				{
					Dist[V2[i]]=max(Dist[V2[i]],Dist[u.u]);
					Q.push((Queue_Data){V2[i],Dist[V2[i]]});
				}
		}
		for (int i=Head[u.u];i!=-1;i=Next[i])
			if ((vis[E[i].v]==0)&&((Dist[E[i].v]==-1)||(Dist[E[i].v]>Dist[u.u]+E[i].w)))
			{
				Dist[E[i].v]=Dist[u.u]+E[i].w;
				//cout<<u.u<<"->"<<E[i].v<<" "<<Degree[E[i].v]<<endl;
				if (Degree[E[i].v]==0) Q.push((Queue_Data){E[i].v,Dist[E[i].v]});
			}
	}
	while (!Q.empty());
	//for (int i=1;i<=n;i++) cout<<Dist[i]<<" ";cout<<endl;
	printf("%lld\n",Dist[n]);
	return 0;
}
