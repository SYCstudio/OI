#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
#include<assert.h>
using namespace std;

const int maxN=202000;

int n,m;
vector<int> G[maxN],uG[maxN],sG[maxN],fG[maxN];
int dfncnt,dfn[maxN],idfn[maxN],Fa[maxN];
int semi[maxN],idom[maxN],ufs[maxN],mi[maxN],Ans[maxN];

void dfs_init(int u);
int find(int x);
void dfs_calc(int u);
int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1; i<=m; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
		uG[v].push_back(u);
	}
	for (int i=1; i<=n; i++) semi[i]=idom[i]=ufs[i]=mi[i]=i;

	dfs_init(1);

	for (int i=n; i>=2; i--) {
		int u=idfn[i],tmp=n;
		for (int j=0,sz=uG[u].size(); j<sz; j++) {
			int v=uG[u][j];
			if (dfn[v]<dfn[u]) tmp=min(tmp,dfn[v]);
			else find(v),tmp=min(tmp,dfn[semi[mi[v]]]);
		}
		semi[u]=idfn[tmp];
		ufs[u]=Fa[u];
		sG[semi[u]].push_back(u);

		u=idfn[i-1];
		for (int j=0,sz=sG[u].size(); j<sz; j++) {
			int v=sG[u][j];
			find(v);
			if (semi[v]==semi[mi[v]]) idom[v]=semi[v];
			else idom[v]=-mi[v];
		}
	}
	for (int i=2; i<=n; i++) {
		int u=idfn[i];
		if (idom[u]<0) idom[u]=idom[-idom[u]];
		fG[idom[u]].push_back(u);
	}
	//for (int i=1;i<=n;i++) cout<<semi[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<idom[i]<<" ";cout<<endl;

	dfs_calc(1);

	for (int i=1; i<=n; i++) printf("%d ",Ans[i]);
	return 0;
}
void dfs_init(int u)
{
	idfn[dfn[u]=++dfncnt]=u;
	for (int i=0,sz=G[u].size(); i<sz; i++) if (!dfn[G[u][i]]) dfs_init(G[u][i]),Fa[G[u][i]]=u;
}
int find(int x)
{
	if (ufs[x]==x) return x;
	int ofa=ufs[x];
	ufs[x]=find(ufs[x]);
	if (dfn[semi[mi[ofa]]]<dfn[semi[mi[x]]]) mi[x]=mi[ofa];
	return ufs[x];
}
void dfs_calc(int u)
{
	Ans[u]=1;
	for (int i=0,sz=fG[u].size(); i<sz; i++) dfs_calc(fG[u][i]),Ans[u]+=Ans[fG[u][i]];
	return;
}
