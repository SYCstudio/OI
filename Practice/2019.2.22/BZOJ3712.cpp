#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

typedef long long ll;
const int maxN=502000;
const int maxB=20;

int n,m,K,ncnt;
int Cnt[maxN],ufs[maxN],Fa[maxB][maxN],Dep[maxN];
pair<int,int> Rct[maxN];
vector<int> Ctr[maxN];

int find(int x);
int LCA(int u,int v);
int main()
{
	scanf("%d%d%d",&n,&m,&K);
	ncnt=n;
	for (int i=1; i<=n; i++) scanf("%d",&Cnt[i]),ufs[i]=i;
	for (int i=1; i<=m; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		u=find(u);
		v=find(v);
		++ncnt;
		Fa[0][u]=Fa[0][v]=ufs[u]=ufs[v]=ufs[ncnt]=ncnt;
	}
	for (int i=ncnt; i>=1; i--) Dep[i]=Dep[Fa[0][i]]+1;
	for (int i=1; i<maxB; i++) for (int j=1; j<=ncnt; j++) Fa[i][j]=Fa[i-1][Fa[i-1][j]];
	for (int i=1; i<=K; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		int lca=LCA(u,v);
		Rct[i]=make_pair(u,v);
		Ctr[lca].push_back(i);
	}
	ll Ans=0;
	for (int i=1; i<=ncnt; i++)
		for (int j=0,sz=Ctr[i].size(); j<sz; j++) {
			int p=Ctr[i][j],mn=min(Cnt[Rct[p].first],Cnt[Rct[p].second]);
			Ans=Ans+mn+mn;
			Cnt[Rct[p].first]-=mn;
			Cnt[Rct[p].second]-=mn;
		}
	printf("%lld\n",Ans);
	return 0;
}
int find(int x)
{
	if (ufs[x]!=x) ufs[x]=find(ufs[x]);
	return ufs[x];
}
int LCA(int u,int v)
{
	if (Dep[u]<Dep[v]) swap(u,v);
	for (int i=maxB-1; i>=0; i--) if (Fa[i][u]&&Dep[Fa[i][u]]>=Dep[v]) u=Fa[i][u];
	if (u==v) return u;
	for (int i=maxB-1; i>=0; i--) if (Fa[i][u]&&Fa[i][v]&&Fa[i][u]!=Fa[i][v]) u=Fa[i][u],v=Fa[i][v];
	return Fa[0][u];
}