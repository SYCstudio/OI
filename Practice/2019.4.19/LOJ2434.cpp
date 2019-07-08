#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

typedef long long ll;
const int maxN=404000;

class SplayData
{
public:
	int ch[2],fa;
};

int n,m;
vector<int> It[maxN];
SplayData S[maxN];
ll Ans,Sum[maxN],VSum[maxN],Ras[maxN],Val[maxN];

void dfs_init(int u,int fa);
void Update(int x);
bool Isroot(int x);
void Rotate(int x);
void Splay(int x);
void Access(int x,ll key);
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1; i<=n; i++) scanf("%lld",&Val[i]);
	for (int i=1; i<n; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		It[u].push_back(v);
		It[v].push_back(u);
	}

	dfs_init(1,1);
	printf("%lld\n",Ans);
	while (m--) {
		int u,key;
		scanf("%d%d",&u,&key);
		Access(u,key);
		printf("%lld\n",Ans);
	}
	return 0;
}
void dfs_init(int u,int fa)
{
	VSum[u]=0;
	ll mx=Val[u];
	int mxid=u;
	for (int i=0,sz=It[u].size(); i<sz; i++) {
		int v=It[u][i];
		if (v==fa) continue;
		S[v].fa=u;
		dfs_init(v,u);
		VSum[u]+=Sum[v];
		if (Sum[v]>mx) mx=Sum[v],mxid=v;
	}
	Sum[u]=VSum[u]+Val[u];
	if (mx+mx>Sum[u]) {
		Ras[u]=2ll*(Sum[u]-mx);
		if (mxid!=u) VSum[u]-=mx,S[u].ch[1]=mxid;
	} else Ras[u]=Sum[u]-1;
	Ans=Ans+Ras[u];
	return;
}
void Update(int x)
{
	Sum[x]=Sum[S[x].ch[0]]+Sum[S[x].ch[1]]+VSum[x]+Val[x];
	return;
}
bool Isroot(int x)
{
	int fa=S[x].fa;
	if (S[fa].ch[0]==x||S[fa].ch[1]==x) return 0;
	return 1;
}
void Rotate(int x)
{
	int y=S[x].fa,z=S[y].fa,sx=(x==S[y].ch[1]),sy=(y==S[z].ch[1]);
	S[x].fa=z;
	if (!Isroot(y)) S[z].ch[sy]=x;
	S[y].ch[sx]=S[x].ch[sx^1];
	if (S[x].ch[sx^1]) S[S[x].ch[sx^1]].fa=y;
	S[x].ch[sx^1]=y;
	S[y].fa=x;
	Update(y);
	return;
}
void Splay(int x)
{
	while (!Isroot(x)) {
		int y=S[x].fa,z=S[y].fa;
		if (!Isroot(y)) ((x==S[y].ch[0])^(y==S[z].ch[0]))?Rotate(x):Rotate(y);
		Rotate(x);
	}
	Update(x);
	return;
}
void Access(int x,ll key)
{
	int lstx=0;
	while (x) {
		Splay(x);
		Ans=Ans-Ras[x];
		Sum[x]+=key;
		if (lstx) VSum[x]+=key;
		else Val[x]+=key;
		ll rS=Sum[x]-Sum[S[x].ch[0]];
		if (Sum[lstx]+Sum[lstx]>rS) VSum[x]-=Sum[lstx],VSum[x]+=Sum[S[x].ch[1]],S[x].ch[1]=lstx;

		if (Sum[S[x].ch[1]]+Sum[S[x].ch[1]]>rS) Ras[x]=2ll*(rS-Sum[S[x].ch[1]]);
		else {
			VSum[x]+=Sum[S[x].ch[1]];
			S[x].ch[1]=0;
			if (Val[x]+Val[x]>rS) Ras[x]=2ll*(rS-Val[x]);
			else Ras[x]=rS-1;
		}
		Ans=Ans+Ras[x];
		lstx=x;
		x=S[x].fa;
	}
	return;
}
