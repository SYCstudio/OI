#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
#include<iostream>
using namespace std;

#define RG register
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
class Option
{
public:
	int opt,u,v;
};
const int maxN=101000*2;
const int maxM=maxN<<1;

int n,m,Q,nodecnt=0;
Option O[maxN];
pair<int,int> Es[maxN];
map<int,int> E[maxN];
int f1[maxN],f2[maxN],Dep[maxN],Fa[maxN],Sz[maxN],Del[maxN];
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM],dfncnt,dfn[maxN],low[maxN];
int Ans[maxN];

int find(int *f,int x);
void Add_Edge(int u,int fa);
void dfs(RG int u,RG int fa);
void Add(RG int u,RG int v);
int main()
{
	mem(Head,-1);
	scanf("%d%d%d",&n,&m,&Q);
	nodecnt=n;
	for (int i=1; i<=m; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		if (u>v) swap(u,v);
		++E[u][v];
	}
	for (int i=1; i<=Q; i++) {
		char ipt;
		scanf(" %c%d%d",&ipt,&O[i].u,&O[i].v);
		if (O[i].u>O[i].v) swap(O[i].u,O[i].v);
		if (ipt=='Z') O[i].opt=1,E[O[i].u][O[i].v]--;
		else O[i].opt=2;
	}
	for (int i=1; i<=n; i++) f1[i]=f2[i]=i;
	int top=0;
	for (int i=1; i<=n; i++)
		for (map<int,int>::iterator it=E[i].begin(); it!=E[i].end(); it++)
			if ((*it).second) {
				if (find(f1,i)!=find(f1,(*it).first)) Add_Edge(i,(*it).first),f1[find(f1,i)]=find(f2,(*it).first);
				else Es[++top]=make_pair(i,(*it).first);
			}
	for (int i=1; i<=n; i++) if (Dep[i]==0) dfs(i,i);
	for (int i=1; i<=top; i++) Add(Es[i].first,Es[i].second);
	for (int i=Q; i>=1; i--)
		if (O[i].opt==1) Add(O[i].u,O[i].v);
		else Ans[i]=find(f2,O[i].u)==find(f2,O[i].v);
	for (int i=1; i<=Q; i++) if (O[i].opt==2) Ans[i]?puts("Yes"):puts("No");
	return 0;
}
int find(int *f,int x)
{
	if (f[x]!=x) f[x]=find(f,f[x]);
	return f[x];
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
void dfs(int u,int fa)
{
	if (Del[u]) return;
	f1[u]=Fa[u]=fa;
	Dep[u]=Dep[fa]+1;
	Sz[u]=1;
	for (int i=Head[u]; i!=-1; i=Next[i]) if (V[i]!=fa) dfs(V[i],u),Sz[u]+=Sz[V[i]];
	return;
}
void Add(RG int u,RG int v)
{
	//cerr<<u<<" "<<v<<endl;
	RG int fu,fv,id,scnt,i,j,k,top,lst;
	static int Seq[maxN],Bp[maxN];
	u=find(f2,u);
	v=find(f2,v);
	fu=find(f1,u);
	fv=find(f1,v);
	if (u==v) return;
	if (fu==fv) {
		id=++nodecnt;
		f2[id]=id;
		f1[id]=fu;
		scnt=0;
		while (u!=v) {
			if (Dep[u]<Dep[v]) swap(u,v);
			Seq[++scnt]=u;
			Del[u]=1;
			u=Fa[u];
		}
		Seq[++scnt]=u;
		int fa=Fa[u];
		Del[u]=1;
		for (i=1; i<=scnt; ++i) {
			f2[Seq[i]]=id;
			top=0;
			for (j=Head[Seq[i]]; ~j; j=Next[j])
				if (!Del[V[j]]) {
					for (k=Head[V[j]]; ~k; k=Next[k]) if (V[k]==Seq[i]) V[k]=id;
					Bp[++top]=j;
					if (V[j]!=fa) Fa[V[j]]=id;
				}
			for (j=1; j<=top; ++j) Next[Bp[j]]=Head[id],Head[id]=Bp[j];
			Head[Seq[i]]=-1;
		}
		Fa[id]=fa;
		Dep[id]=Dep[Fa[u]]+1;
		Sz[id]=Sz[u];
	} else {
		if (Sz[fu]<Sz[fv]) swap(fu,fv),swap(u,v);
		Sz[fu]+=Sz[fv];
		dfs(v,u);
		Add_Edge(v,u);
	}
}