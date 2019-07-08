#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> PLL;
#define sqr(x) ((x)*(x))
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=505000;
const int maxM=maxN<<1;
const ll INF=1e18;

PLL operator - (PLL A,PLL B)
{
	return make_pair(A.first-B.first,A.second-B.second);
}
ll Cross(PLL A,PLL B)
{
	A.second+=sqr(A.first);
	B.second+=sqr(B.first);
	return A.first*B.second-A.second*B.first;
}
class Convex
{
public:
	int sz;
	vector<PLL> C;
	Convex()
	{
		sz=-1;
		C.clear();
		return;
	}
	void clear()
	{
		sz=-1;
		C.clear();
		return;
	}
	void Insert(PLL P)
	{
		while (sz>=1&&Cross(P-C[sz-1],C[sz]-C[sz-1])>=0) --sz,C.pop_back();
		C.push_back(P);
		++sz;
		return;
	}
};
class Question
{
public:
	int id,u;
	ll x;
};

int n,m,Apr[maxN],Sorter[maxN];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],dfncnt,dfn[maxN],rht[maxN];
vector<int> Del[maxN];
PLL P[maxN];
Convex Con[maxN<<2];
ll Ans[maxN];
Question Q[maxN],Bp[maxN];

void Add_Edge(int u,int v);
void dfs_init(int u,int fa);
bool dcmp(int a,int b);
bool qcmp(Question A,Question B);
bool pcmp(int a,int b);
void Modify(int x,int l,int r,int ql,int qr,PLL P);
void Solve(int x,int l,int r,int ql,int qr);
double Slope(PLL A,PLL B);
ll Calc(ll x,PLL P);
int main()
{
	//freopen("2.in","r",stdin);freopen("out","w",stdout);
	ll C0;
	scanf("%d%d%lld",&n,&m,&C0);
	mem(Head,-1);
	for (int i=2; i<=n; i++) {
		int opt,fr,id;
		scanf("%d%d%d",&opt,&fr,&id);
		++fr;
		Add_Edge(i,fr);
		Add_Edge(fr,i);
		if (opt==0) {
			ll x,y,z,c;
			scanf("%lld%lld%lld%lld",&x,&y,&z,&c);
			P[id]=make_pair(x,c);
			Apr[id]=i;
		} else Del[id].push_back(i);
	}
	dfs_init(1,1);
	for (int i=1; i<=n; i++) Sorter[i]=i;
	sort(&Sorter[1],&Sorter[n+1],pcmp);
	for (int i=1; i<=n; i++) {
		int u=Sorter[i];
		if (Apr[u]) {
			//cout<<"("<<P[u].first<<","<<P[u].second<<") ";
			//cout<<"running at:"<<u<<endl;
			sort(Del[u].begin(),Del[u].end(),dcmp);
			int lst=dfn[Apr[u]]-1;
			for (int j=0,sz=Del[u].size(); j<sz; j++) {
				//cout<<"("<<lst<<","<<dfn[Del[u][j]]<<")"<<" "<<lst+1<<" "<<dfn[Del[u][j]]-1<<endl;
				if (lst+1<dfn[Del[u][j]]) Modify(1,1,n,lst+1,dfn[Del[u][j]]-1,P[u]);
				lst=rht[Del[u][j]];
			}
			//cout<<"("<<lst<<","<<rht[Apr[u]]<<"]"<<endl;
			if (lst!=rht[Apr[u]]) Modify(1,1,n,lst+1,rht[Apr[u]],P[u]);
		}
	}//cout<<endl;
	for (int i=1; i<=m; i++) scanf("%d%lld",&Q[i].u,&Q[i].x),++Q[i].u,Ans[i]=sqr(Q[i].x)+C0,Q[i].id=i;
	sort(&Q[1],&Q[m+1],qcmp);
	Solve(1,1,n,1,m);
	for (int i=1; i<=m; i++) printf("%lld\n",Ans[i]);
	return 0;
}
void Add_Edge(int u,int v)
{
	Next[++edgecnt]=Head[u];
	Head[u]=edgecnt;
	V[edgecnt]=v;
	return;
}
void dfs_init(int u,int fa)
{
	dfn[u]=++dfncnt;
	for (int i=Head[u]; i!=-1; i=Next[i]) if (V[i]!=fa) dfs_init(V[i],u);
	rht[u]=dfncnt;
	return;
}
bool dcmp(int a,int b)
{
	return dfn[a]<dfn[b];
}
bool qcmp(Question A,Question B)
{
	return A.x<B.x;
}
bool pcmp(int a,int b)
{
	return P[a]<P[b];
}
double Slope(PLL A,PLL B)
{
	A.second+=sqr(A.first);
	B.second+=sqr(B.first);
	return (double)(A.second-B.second)/(double)(A.first-B.first);
}
ll Calc(ll x,PLL P)
{
	return sqr(P.first-x)+P.second;
}
#define ls (x<<1)
#define rs (ls|1)
void Modify(int x,int l,int r,int ql,int qr,PLL P)
{
	if (l==ql&&r==qr) {
		Con[x].Insert(P);
		return;
	}
	int mid=(l+r)>>1;
	if (qr<=mid) Modify(ls,l,mid,ql,qr,P);
	else if (ql>=mid+1) Modify(rs,mid+1,r,ql,qr,P);
	else Modify(ls,l,mid,ql,mid,P),Modify(rs,mid+1,r,mid+1,qr,P);
	return;
}
void Solve(int x,int l,int r,int ql,int qr)
{
	if (Con[x].C.size()) {
		int sz=Con[x].C.size()-1,top=0;
		//cout<<"Solve at:"<<l<<" "<<r<<":";for (int i=0;i<=sz;i++) cout<<"("<<Con[x].C[i].first<<","<<Con[x].C[i].second<<") ";cout<<endl;
		for (int i=ql; i<=qr; i++) {
			while (top<sz&&Calc(Q[i].x,Con[x].C[top])>=Calc(Q[i].x,Con[x].C[top+1])) ++top;
			//for (top=0;top<=sz;top++)
			Ans[Q[i].id]=min(Ans[Q[i].id],Calc(Q[i].x,Con[x].C[top]));
		}
	}
	if (l==r) return;
	int pl=ql-1,pr=qr+1,mid=(l+r)>>1;
	for (int i=ql; i<=qr; i++) if (dfn[Q[i].u]<=mid) Bp[++pl]=Q[i];
		else Bp[--pr]=Q[i];
	for (int i=ql; i<=qr; i++) Q[i]=Bp[i];
	if (pl>=ql) Solve(ls,l,mid,ql,pl);
	if (pr<=qr) {
		reverse(&Q[pr],&Q[qr+1]);
		Solve(rs,mid+1,r,pr,qr);
	}
	return;
}