#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=200100;
const int inf=2147483647;

class Heap
{
public:
	ll key,lazy;
	int ls,rs,dis;
};

int n;
ll L;
Heap H[maxN];
int edgecnt,Head[maxN],Next[maxN],V[maxN];
int Size[maxN],Id[maxN];
ll W[maxN];

void dfs(int u);
void Mark(int u,ll plus);
int Merge(int r1,int r2);
void PushDown(int u);

int main()
{
	mem(Head,-1);
	scanf("%d%lld",&n,&L);
	for (int i=2;i<=n;i++)
	{
		int fa;ll len;scanf("%d%lld",&fa,&len);
		edgecnt++;Next[edgecnt]=Head[fa];Head[fa]=edgecnt;V[edgecnt]=i;W[edgecnt]=len;
	}
	dfs(1);
	for (int i=1;i<=n;i++) printf("%d\n",Size[i]);
	return 0;
}

void dfs(int u)
{
	Size[u]=1;Id[u]=u;
	for (int i=Head[u];i!=-1;i=Next[i])
	{
		dfs(V[i]);
		Mark(Id[V[i]],W[i]);Id[u]=Merge(Id[u],Id[V[i]]);
		Size[u]+=Size[V[i]];
	}
	while (H[Id[u]].key>L) Id[u]=Merge(H[Id[u]].ls,H[Id[u]].rs),Size[u]--;
	return;
}

void Mark(int u,ll plus)
{
	H[u].key+=plus;H[u].lazy+=plus;
	return;
}

int Merge(int r1,int r2)
{
	if (r1==0) return r2;
	if (r2==0) return r1;
	PushDown(r1);PushDown(r2);
	if (H[r1].key<H[r2].key) swap(r1,r2);
	H[r1].rs=Merge(H[r1].rs,r2);
	if (H[H[r1].ls].dis<H[H[r1].rs].dis) swap(H[r1].ls,H[r1].rs);
	if (H[r1].rs) H[r1].dis=H[H[r1].rs].dis+1;
	else H[r1].dis=0;
	return r1;
}

void PushDown(int u)
{
	if (H[u].ls) Mark(H[u].ls,H[u].lazy);
	if (H[u].rs) Mark(H[u].rs,H[u].lazy);
	H[u].lazy=0;return;
}
