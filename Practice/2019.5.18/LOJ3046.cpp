#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define pb push_back
const int maxN=203000;
const int Bit=20;

class SegmentData
{
public:
	int ls,rs,cnt,sum,l,r;
};

int n,m,Lg[maxN];
vector<int> T[maxN];
vector<int> Del[maxN];
int dfncnt,dfn[maxN],ST[Bit][maxN],Fa[maxN],D[maxN];
int scnt=0,rt[maxN];
SegmentData S[maxN*80];
long long Ans;

void dfs1(int u);
void dfs2(int u);
int LCA(int u,int v);
bool cmp(int a,int b);
void Update(int x);
void Modify(int &x,int l,int r,int p,int key);
int Merge(int u,int v,int l,int r);
int main()
{
	for (int i=2; i<maxN; i++) Lg[i]=Lg[i>>1]+1;
	scanf("%d%d",&n,&m);
	for (int i=1; i<n; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		T[u].pb(v);
		T[v].pb(u);
	}
	dfs1(1);
	for (int i=1; i<Bit; i++) for (int j=1; j+(1<<i)-1<=dfncnt; j++) ST[i][j]=min(ST[i-1][j],ST[i-1][j+(1<<(i-1))],cmp);
	for (int i=1; i<=m; i++) {
		int x,y;
		scanf("%d%d",&x,&y);
		if (x==y) continue;
		int lca=LCA(x,y),fa=Fa[lca];
		Modify(rt[x],1,dfncnt,x,1);
		Modify(rt[x],1,dfncnt,y,1);
		Modify(rt[y],1,dfncnt,x,1);
		Modify(rt[y],1,dfncnt,y,1);
		Del[fa].pb(x);
		Del[fa].pb(y);
	}
	dfs2(1);
	printf("%lld\n",Ans/2);
	return 0;
}
void dfs1(int u)
{
	ST[0][dfn[u]=++dfncnt]=u;
	for (int i=0,sz=T[u].size(); i<sz; i++) if (T[u][i]!=Fa[u]) Fa[T[u][i]]=u,D[T[u][i]]=D[u]+1,dfs1(T[u][i]),ST[0][++dfncnt]=u;
	return;
}
void dfs2(int u)
{
	for (int i=0,sz=T[u].size(); i<sz; i++) if (T[u][i]!=Fa[u]) dfs2(T[u][i]),rt[u]=Merge(rt[u],rt[T[u][i]],1,dfncnt);
	for (int i=0,sz=Del[u].size(); i<sz; i++) Modify(rt[u],1,dfncnt,Del[u][i],-2);
	if (S[rt[u]].l&&S[rt[u]].r)
		Ans=Ans+S[rt[u]].sum-D[LCA(S[rt[u]].l,S[rt[u]].r)];
	return;
}
int LCA(int u,int v)
{
	if (!u||!v) return 0;
	if (dfn[u]>dfn[v]) swap(u,v);
	int lg=Lg[dfn[v]-dfn[u]+1];
	return min(ST[lg][dfn[u]],ST[lg][dfn[v]-(1<<lg)+1],cmp);
}
bool cmp(int a,int b)
{
	return D[a]<D[b];
}
void Update(int x)
{
	S[x].l=S[S[x].ls].l?S[S[x].ls].l:S[S[x].rs].l;
	S[x].r=S[S[x].rs].r?S[S[x].rs].r:S[S[x].ls].r;
	S[x].sum=S[S[x].ls].sum+S[S[x].rs].sum;
	if (S[S[x].ls].r&&S[S[x].rs].l) S[x].sum=S[x].sum-D[LCA(S[S[x].ls].r,S[S[x].rs].l)];
	return;
}
void Modify(int &x,int l,int r,int p,int key)
{
	S[++scnt]=S[x];
	x=scnt;
	if (l==r) {
		S[x].cnt+=key;
		if (S[x].cnt) S[x].l=S[x].r=p,S[x].sum=D[p];
		else S[x].l=S[x].r=S[x].sum=0;
		return;
	}
	int mid=(l+r)>>1;
	if (dfn[p]<=mid) Modify(S[x].ls,l,mid,p,key);
	else Modify(S[x].rs,mid+1,r,p,key);
	Update(x);
	return;
}
int Merge(int u,int v,int l,int r)
{
	if (!u||!v) return u+v;
	int id=++scnt;
	if (l==r) {
		S[id].cnt=S[u].cnt+S[v].cnt;
		if (S[id].cnt) S[id].l=S[id].r=ST[0][l],S[id].sum=D[ST[0][l]];
		else S[id].l=S[id].r=S[id].sum=0;
		return id;
	}
	int mid=(l+r)>>1;
	S[id].ls=Merge(S[u].ls,S[v].ls,l,mid);
	S[id].rs=Merge(S[u].rs,S[v].rs,mid+1,r);
	Update(id);
	return id;
}
