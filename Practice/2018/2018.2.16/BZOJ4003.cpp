#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=300100;
const int inf=2147483647;

class Heap
{
public:
	ll key,plus,mul;
	int ch[2],dis;
	Heap()
		{
			plus=0;mul=1;
			return;
		}
};

int n,m;
int edgecnt=-1,Head[maxN],Next[maxN*2],V[maxN*2];
int Id[maxN];
ll Def[maxN],Opt[maxN],Val[maxN],Depth[maxN];
int St[maxN],Ed[maxN],Fail[maxN];
Heap H[maxN];

int Merge(int r1,int r2);
void PushDown(int rt);
void Mark(int rt,ll plus,ll mul);
void dfs(int u);

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%lld",&Def[i]);
	for (int i=2;i<=n;i++)
	{
		int fa;scanf("%d%lld%lld",&fa,&Opt[i],&Val[i]);
		edgecnt++;Next[edgecnt]=Head[fa];Head[fa]=edgecnt;V[edgecnt]=i;
	}
	for (int i=1;i<=m;i++)
	{
		scanf("%lld%d",&H[i].key,&St[i]);
		if (Id[St[i]]==0) Id[St[i]]=i;
		else Id[St[i]]=Merge(Id[St[i]],i);
	}
	Depth[1]=1;dfs(1);
	for (int i=1;i<=n;i++) printf("%d\n",Fail[i]);
	for (int i=1;i<=m;i++) printf("%lld\n",Depth[St[i]]-Depth[Ed[i]]);
	return 0;
}

int Merge(int r1,int r2)
{
	if (r1==0) return r2;
	if (r2==0) return r1;
	PushDown(r1);PushDown(r2);
	if (H[r1].key>H[r2].key) swap(r1,r2);
	H[r1].ch[1]=Merge(H[r1].ch[1],r2);
	if (H[H[r1].ch[0]].dis<H[H[r1].ch[1]].dis) swap(H[r1].ch[0],H[r1].ch[1]);
	if (H[r1].ch[1]) H[r1].dis=H[H[r1].ch[1]].dis+1;
	else H[r1].dis=0;
	return r1;
}

void PushDown(int rt)
{
	if (H[rt].ch[0]) Mark(H[rt].ch[0],H[rt].plus,H[rt].mul);
	if (H[rt].ch[1]) Mark(H[rt].ch[1],H[rt].plus,H[rt].mul);
	H[rt].mul=1;H[rt].plus=0;return;
}

void Mark(int rt,ll plus,ll mul)
{
	H[rt].key=H[rt].key*mul+plus;
	H[rt].plus=H[rt].plus*mul+plus;
	H[rt].mul=H[rt].mul*mul;
	return;
}

void dfs(int u)
{
	for (int i=Head[u];i!=-1;i=Next[i])
		Depth[V[i]]=Depth[u]+1,dfs(V[i]);
	for (int i=Head[u];i!=-1;i=Next[i])
	{
		if (Id[V[i]]==0) continue;
		if (Id[u]==0) Id[u]=Id[V[i]];
		else Id[u]=Merge(Id[u],Id[V[i]]);
	}
	while ((Id[u])&&(H[Id[u]].key<Def[u]))
	{
		Fail[u]++;Ed[Id[u]]=u;
		PushDown(Id[u]);Id[u]=Merge(H[Id[u]].ch[0],H[Id[u]].ch[1]);
	}
	if (Id[u])
	{
		if (Opt[u]==0) Mark(Id[u],Val[u],1);
		if (Opt[u]==1) Mark(Id[u],0,Val[u]);
	}
	return;
}
