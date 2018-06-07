#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100010;
const int maxM=maxN*2;
const int inf=2147483647;

int n,m;
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM],W[maxM];
int Col[maxN];
bool getring;
ll edge,node;
bool vis[maxN];
ll Aper[3];

void Add_Edge(int u,int v,int w);
void dfs(int u,int col);

int main()
{
	ios::sync_with_stdio(false);mem(Head,-1);
	cin>>n>>m;
	for (int i=1;i<=m;i++){
		int u,v;cin>>u>>v;Add_Edge(u,v,1);Add_Edge(v,u,2);
	}
	mem(Col,-1);
	ll Ans=0;
	for (int i=1;i<=n;i++)
		if (Col[i]==-1)
		{
			getring=0;edge=0;node=0;Aper[0]=Aper[1]=Aper[2]=0;
			dfs(i,0);
			//cout<<getring<<" "<<edge<<" "<<node<<" "<<Aper[0]<<" "<<Aper[1]<<" "<<Aper[2]<<endl;
			if (getring) Ans+=(ll)node*node;
			else if ((Aper[0]==0)||(Aper[1]==0)||(Aper[2]==0)) Ans+=edge;
			else Ans+=(ll)Aper[0]*Aper[1]+(ll)Aper[1]*Aper[2]+(ll)Aper[2]*Aper[0];
		}
	cout<<Ans<<endl;
	return 0;
}

void Add_Edge(int u,int v,int w)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}

void dfs(int u,int col)
{
	if (Col[u]!=-1)
	{
		if (Col[u]!=col) getring=1;
		return;
	}
	
	Col[u]=col;Aper[col]++;node++;
	for (int i=Head[u];i!=-1;i=Next[i])
	{
		if (vis[i>>1]==0) vis[i>>1]=1,edge++;
		dfs(V[i],(col+W[i])%3);
	}
	return;
}
