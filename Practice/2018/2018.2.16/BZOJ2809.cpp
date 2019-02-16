#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100100;
const int inf=2147483647;

class Heap
{
public:
	ll key;
	int ch[2],dis;
};

int n,M,root;
int Id[maxN];
ll Ans,Sum[maxN],Mast[maxN],Size[maxN];
Heap H[maxN];
int edgecnt=-1,Head[maxN],Next[maxN*2],V[maxN*2];

void dfs(int u);
int Merge(int r1,int r2);

int main()
{
	mem(Head,-1);
	scanf("%d%d",&n,&M);
	for (int i=1;i<=n;i++)
	{
		Id[i]=i;
		int fa;scanf("%d%lld%lld",&fa,&H[i].key,&Mast[i]);
		if (fa==0){
			root=i;continue;
		}
		edgecnt++;Next[edgecnt]=Head[fa];Head[fa]=edgecnt;V[edgecnt]=i;
	}
	dfs(root);
	printf("%lld\n",Ans);
	return 0;
}

void dfs(int u)
{
	Sum[u]=H[u].key;Size[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
	{
		dfs(V[i]);
		Sum[u]+=Sum[V[i]];Size[u]+=Size[V[i]];
	}
	for (int i=Head[u];i!=-1;i=Next[i])
		Id[u]=Merge(Id[u],Id[V[i]]);
	while (Sum[u]>M)
	{
		Sum[u]-=H[Id[u]].key;Size[u]--;
		Id[u]=Merge(H[Id[u]].ch[0],H[Id[u]].ch[1]);
	}
	Ans=max(Ans,Size[u]*Mast[u]);
	return;
}

int Merge(int r1,int r2)
{
	if (r2==0) return r1;
	if (r1==0) return r2;
	if (H[r1].key<H[r2].key) swap(r1,r2);
	H[r1].ch[1]=Merge(H[r1].ch[1],r2);
	if (H[H[r1].ch[0]].dis<H[H[r1].ch[1]].ch[1]) swap(H[r1].ch[0],H[r1].ch[1]);
	if (H[r1].ch[1]) H[r1].dis=H[H[r1].ch[1]].dis+1;
	else H[r1].dis=0;
	return r1;
}
