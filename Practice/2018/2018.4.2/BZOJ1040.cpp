#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1001000;
const int maxM=maxN*2;
const int inf=2147483647;

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
ll W[maxN];
ll F[2][maxN];
int vis[maxN];
int node1,node2;
ll Ans=0;

void Add_Edge(int u,int v);
void Do(int u);
void dfs_find(int u,int fa);
void dfs(int u,int fa);

int main()
{
	ios::sync_with_stdio(false);mem(Head,-1);
	
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		int v;cin>>W[i]>>v;
		Add_Edge(i,v);Add_Edge(v,i);
	}
	for (int i=1;i<=n;i++)
		if (vis[i]==0) Do(i);
	cout<<Ans<<endl;
	return 0;
}

void Add_Edge(int u,int v)
{
	for (int i=Head[u];i!=-1;i=Next[i]) if (V[i]==v) return;
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void Do(int u)
{
	node1=node2=0;
	dfs_find(u,u);
	//cout<<node1<<" "<<node2<<endl;
	if (node1==0)
	{
		dfs(u,u);
		Ans+=max(F[0][u],F[1][u]);
		return;
	}
	dfs(node1,node1);
	ll mx=max(F[0][node1],F[1][node1]);
	swap(node1,node2);
	dfs(node1,node1);
	mx=max(mx,max(F[0][node1],F[1][node1]));
	Ans+=mx;
	return;
}

void dfs_find(int u,int fa)
{
	vis[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			//cout<<u<<"->"<<V[i]<<endl;
			if (vis[V[i]]==1) node1=u,node2=V[i];
			else dfs_find(V[i],u);
		}
	return;
}

void dfs(int u,int fa)
{
	F[0][u]=0;F[1][u]=W[u];
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			if ((u==node1)&&(V[i]==node2)) continue;
			if ((u==node2)&&(V[i]==node1)) continue;
			dfs(V[i],u);
			F[0][u]+=max(F[0][V[i]],F[1][V[i]]);
			F[1][u]+=F[0][V[i]];
		}
	if (u==node2) F[1][u]=0;
	return;
}
