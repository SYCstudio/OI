#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=202000;
const int maxM=maxN<<1;
const int inf=2000000000;

int n,Q,Val[maxN];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Sz[maxN],Hs[maxN],Top[maxN],Fa[maxN],dfncnt,dfn[maxN];
ll B1[maxN],B2[maxN];
ll Ans;

void Add_Edge(int u,int v);
void dfs1(int u,int fa);
int dfs2(int u,int top);
void Plus(int p,int k);
void Add(int l,int r,int k);
int Sum(int p);
int Query(int l,int r);

int main()
{
	scanf("%d%d",&n,&Q);
	mem(Head,-1);
	for (int i=1; i<n; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	for (int i=1; i<=n; i++) scanf("%d",&Val[i]);
	dfs1(1,1);
	dfs2(1,1);
	while (Q--) {
		int opt;
		scanf("%d",&opt);
		if (opt==1) {
			int x,y;
			scanf("%d%d",&x,&y);
			y=y-Val[x];
			Val[x]+=y;
			ll sums=0,cnt=0;
			while (x) {
				sums+=Query(dfn[Top[x]],dfn[x]);
				cnt+=dfn[x]-dfn[Top[x]]+1;
				Add(dfn[Top[x]],dfn[x],y);
				x=Fa[Top[x]];
			}
			//cout<<"s:"<<sums<<endl;
			Ans+=1ll*y*y*cnt+2ll*y*sums;
		}
		if (opt==2) {
			int x;
			scanf("%d",&x);
			ll s1=Query(1,1),sums=0,cnt=0;
			while (x) {
				cnt+=dfn[x]-dfn[Top[x]]+1;
				sums+=Query(dfn[Top[x]],dfn[x]);
				x=Fa[Top[x]];
			}
			//cout<<"s:"<<sums<<" "<<s1<<" "<<cnt<<" "<<Ans<<endl;
			printf("%lld\n",Ans+1ll*(cnt+1)*s1*s1-2ll*s1*sums);
		}

		//for (int i=1;i<=n;i++) cout<<Val[i]<<" ";cout<<endl;
		//for (int i=1;i<=n;i++) cout<<Query(dfn[i],dfn[i])<<" ";cout<<endl;
		//for (int i=1;i<=n;i++)
		//    for (int j=i;j<=n;j++)
		//	cout<<"["<<i<<","<<j<<"]"<<Query(i,j)<<endl;
	}
	return 0;
}
void Add_Edge(int u,int v)
{
	Next[++edgecnt]=Head[u];
	Head[u]=edgecnt;
	V[edgecnt]=v;
	return;
}
void dfs1(int u,int fa)
{
	Sz[u]=1;
	for (int i=Head[u]; i!=-1; i=Next[i])
		if (V[i]!=fa) {
			Fa[V[i]]=u;
			dfs1(V[i],u);
			Sz[u]+=Sz[V[i]];
			if (Sz[V[i]]>Sz[Hs[u]]) Hs[u]=V[i];
		}
	return;
}
int dfs2(int u,int top)
{
	dfn[u]=++dfncnt;
	Top[u]=top;
	int ret=Val[u];
	if (Hs[u]) ret+=dfs2(Hs[u],top);
	for (int i=Head[u]; i!=-1; i=Next[i])
		if ((V[i]!=Fa[u])&&(V[i]!=Hs[u])) ret+=dfs2(V[i],V[i]);
	Add(dfn[u],dfn[u],ret);
	Ans+=1ll*ret*ret;
	return ret;
}
void Plus(int p,int k)
{
	int x=p;
	while (x<=n) {
		B1[x]+=k;
		B2[x]+=k*p;
		x+=(x)&(-x);
	}
	return;
}
void Add(int l,int r,int k)
{
	Plus(l,k);
	Plus(r+1,-k);
	return;
}
int Sum(int p)
{
	int ret=0,x=p;
	while (x) {
		ret+=(p+1)*B1[x]-B2[x];
		x-=(x)&(-x);
	}
	return ret;
}
int Query(int l,int r)
{
	return Sum(r)-Sum(l-1);
}
