#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=maxN*2;
const int inf=2147483647;

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int top=0,Col[maxN],Cnt[maxN];
ll Sum[maxN],Ans[maxN];
int Size[maxN],Hson[maxN];
bool vis[maxN];

void Add_Edge(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int fa,int hson);
void Update(int u,int fa,int opt);

int main()
{
	mem(Head,-1);
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&Col[i]);
	for (int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}

	dfs1(1,0);
	dfs2(1,0,1);
	for (int i=1;i<=n;i++) printf("%lld ",Ans[i]);printf("\n");
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs1(int u,int fa){
	Size[u]=1;Hson[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			dfs1(V[i],u);
			Size[u]+=Size[V[i]];
			if (Size[Hson[u]]<Size[V[i]]) Hson[u]=V[i];
		}
	return;
}

void dfs2(int u,int fa,int hson){
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(V[i]!=Hson[u]))
			dfs2(V[i],u,0);
	if (Hson[u]){
		dfs2(Hson[u],u,1);vis[Hson[u]]=1;
	}
	Update(u,fa,1);vis[Hson[u]]=0;
	Ans[u]=Sum[top];
	if (hson==0) Update(u,fa,-1);
}

void Update(int u,int fa,int opt)
{
	Sum[Cnt[Col[u]]]-=1ll*Col[u];
	Cnt[Col[u]]+=opt;
	Sum[Cnt[Col[u]]]+=1ll*Col[u];
	if (Sum[top+1]) top++;
	if (Sum[top]==0) top--;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0))
			Update(V[i],u,opt);
	return;
}
