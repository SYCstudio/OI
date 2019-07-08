#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=101000;
const int maxM=maxN<<1;
const int inf=1000000000;
int n,Ans=0;
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM];
int rt,rtsize,truert,vis[maxN],Sz[maxN],Mx[maxN],Gsz[maxN],Gmx[maxN];

void Add_Edge(int u,int v);
void dfs_size(int u,int fa,int size);
void dfs_calc(int u,int fa,int size);
void Divide(int u,int size);

int main()
{
	scanf("%d",&n);
	mem(Head,-1);
	for (int i=1; i<n; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		Add_Edge(u,v);
	}
	Divide(1,n);
	printf("%d\n",Ans);
	return 0;
}
void Add_Edge(int u,int v)
{
	Next[++edgecnt]=Head[u];
	Head[u]=edgecnt;
	V[edgecnt]=v;
	Next[++edgecnt]=Head[v];
	Head[v]=edgecnt;
	V[edgecnt]=u;
	return;
}
void dfs_size(int u,int fa,int size)
{
	Sz[u]=1;
	Mx[u]=0;
	for (int i=Head[u]; i!=-1; i=Next[i])
		if (V[i]!=fa&&vis[V[i]]==0) {
			dfs_size(V[i],u,size);
			Sz[u]+=Sz[V[i]];
			Mx[u]=max(Mx[u],Sz[V[i]]);
		}
	Mx[u]=max(Mx[u],size-Sz[u]);
	if (Mx[u]<rtsize) rtsize=Mx[u],rt=u;
	return;
}
void dfs_get(int u,int fa)
{
	Gsz[u]=1;
	for (int i=Head[u]; i!=-1; i=Next[i]) if (V[i]!=fa) dfs_get(V[i],u),Gsz[u]+=Gsz[V[i]];
	return;
}
void dfs_calc(int u,int fa,int size)
{
	Gsz[u]=1;
	Mx[u]=0;
	for (int i=Head[u]; i!=-1; i=Next[i])
		if (V[i]!=fa) {
			dfs_calc(V[i],u,size);
			Gsz[u]+=Gsz[V[i]];
			Mx[u]=max(Mx[u],Gsz[V[i]]);
		}
	Mx[u]=max(Mx[u],size-Gsz[u]);
	if (Mx[u]<rtsize) rtsize=Mx[u],rt=u;
}
void Divide(int start,int size)
{
	rtsize=inf;
	dfs_size(start,start,size);
	vis[rt]=1;
	truert=rt;
	//cerr<<"Divide:"<<rt<<" "<<size<<endl;
	int tans=inf,tu;
	for (int i=Head[truert]; i!=-1; i=Next[i]) {
		dfs_get(V[i],truert);
		rtsize=inf;
		dfs_calc(V[i],truert,Gsz[V[i]]);
		if (Mx[rt]+n-Gsz[V[i]]<tans) tans=Mx[rt]+n-Gsz[V[i]],tu=V[i];
	}
	Ans=max(Ans,tans);
	if (tans==inf||vis[tu]) return;
	int tsize=Sz[tu]>Sz[truert]?size-Sz[truert]:Sz[tu];
	Divide(tu,tsize);
	return;
}