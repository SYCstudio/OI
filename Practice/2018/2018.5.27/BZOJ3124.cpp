#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=201000;
const int maxM=maxN*2;
const int inf=2147483647;

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
ll W[maxM];
ll Dist[maxM],Sum1[maxN],Sum2[maxN];
int Queue[maxN],Fa[maxN],St[maxN];
bool vis[maxN];

void Add_Edge(int u,int v,int w);
int Bfs(int S);

int main()
{
	mem(Head,-1);
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		Add_Edge(u,v,w);
	}

	mem(vis,0);
	Bfs(1);
	int id=1;
	for (int i=2;i<=n;i++) if (Dist[i]>Dist[id]) id=i;
	
	mem(vis,0);
	Bfs(id);
	id=1;
	for (int i=2;i<=n;i++) if (Dist[i]>Dist[id]) id=i;
	ll Ans=Dist[id];

	int now=id,cnt=0;
	while (now) St[++cnt]=now,now=Fa[now];
	//cout<<cnt<<endl;
	//for (int i=1;i<=cnt;i++) cout<<St[i]<<" ";cout<<endl;

	Sum1[1]=0;
	for (int i=2;i<=cnt;i++)
		for (int j=Head[St[i]];j!=-1;j=Next[j])
			if (V[j]==St[i-1]){
				Sum1[i]=Sum1[i-1]+W[j];break;
			}

	Sum2[cnt]=0;
	for (int i=cnt-1;i>=1;i--)
		for (int j=Head[St[i]];j!=-1;j=Next[j])
			if (V[j]==St[i+1]){
				Sum2[i]=Sum2[i+1]+W[j];break;
			}

	//for (int i=1;i<=cnt;i++) cout<<Sum1[i]<<" ";cout<<endl;
	//for (int i=1;i<=cnt;i++) cout<<Sum2[i]<<" ";cout<<endl;

	mem(vis,0);
	for (int i=1;i<=cnt;i++) vis[St[i]]=1;
	int L,R;
	for (R=1;R<=cnt;R++)
	{
		int sz=Bfs(St[R]);
		ll mx=-1;
		for (int i=2;i<=sz;i++) mx=max(mx,Dist[Queue[i]]);
		//cout<<"R:"<<R<<" mx:"<<mx<<endl;
		if (mx==Sum2[R]) break;
	}

	mem(vis,0);
	for (int i=1;i<=cnt;i++) vis[St[i]]=1;
	for (L=cnt;L>=1;L--)
	{
		int sz=Bfs(St[L]);
		ll mx=-1;
		for (int i=2;i<=sz;i++) mx=max(mx,Dist[Queue[i]]);
		//cout<<"L:"<<L<<" mx:"<<mx<<endl;
		if (mx==Sum1[L]) break;
	}
	L=max(1,L);R=min(R,cnt);
	//cout<<L<<" "<<R<<endl;

	printf("%lld\n%d\n",Ans,R-L);
	return 0;
}

void Add_Edge(int u,int v,int w)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;W[edgecnt]=w;
	return;
}

int Bfs(int S)
{
	int h=1,t=0;Queue[1]=S;vis[S]=1;Dist[S]=0;Fa[S]=0;
	do
	{
		int u=Queue[++t];
		for (int i=Head[u];i!=-1;i=Next[i])
			if (vis[V[i]]==0)
				Dist[Queue[++h]=V[i]]=Dist[u]+W[i],vis[V[i]]=1,Fa[V[i]]=u;
	}
	while (t!=h);
	return t;
}
