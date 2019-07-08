#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define pw(x) (1<<(x))
typedef long long ll;
const int maxN=101000*4;
const int maxM=maxN<<1;
const int maxB=20;
const int inf=1000000000;
const ll INF=1e18;

int Log[maxN];

class Tree
{
public:
	int edgecnt,Head[maxN],Next[maxM],V[maxM];
	ll W[maxM],Dst[maxN];
	int dfncnt,dfn[maxN],eucnt,ST[maxB][maxN],Dep[maxN],el[maxN],er[maxN];
	Tree()
	{
		edgecnt=-1;
		mem(Head,-1);
		return;
	}
	void Add_Edge(int u,int v,ll w)
	{
		Next[++edgecnt]=Head[u];
		Head[u]=edgecnt;
		V[edgecnt]=v;
		W[edgecnt]=w;
		Next[++edgecnt]=Head[v];
		Head[v]=edgecnt;
		V[edgecnt]=u;
		W[edgecnt]=w;
		return;
	}
	void Input()
	{
		int u,v;
		ll w;
		scanf("%d%d%lld",&u,&v,&w);
		Add_Edge(u,v,w);
		return;
	}
	void dfs_init(int u,int fa)
	{
		dfn[u]=++dfncnt;
		ST[0][++eucnt]=u;
		el[u]=eucnt;
		for (int i=Head[u]; i!=-1; i=Next[i])
			if (V[i]!=fa) {
				Dep[V[i]]=Dep[u]+1;
				Dst[V[i]]=Dst[u]+W[i];
				dfs_init(V[i],u);
				ST[0][++eucnt]=u;
			}
		er[u]=eucnt;
		return;
	}
	void Init()
	{
		Dep[1]=1;
		dfs_init(1,1);
		for (int i=1; i<maxB; i++)
			for (int j=1; j+pw(i)-1<=eucnt; j++) {
				if (Dep[ST[i-1][j]]<=Dep[ST[i-1][j+pw(i-1)]]) ST[i][j]=ST[i-1][j];
				else ST[i][j]=ST[i-1][j+pw(i-1)];
			}
		return;
	}
	int LCA(int u,int v)
	{
		int l=min(el[u],el[v]),r=max(er[u],er[v]),lg=Log[r-l+1];
		if (Dep[ST[lg][l]]<=Dep[ST[lg][r-pw(lg)+1]]) return ST[lg][l];
		else return ST[lg][r-pw(lg)+1];
	}
	ll Dist(int u,int v)
	{
		int lca=LCA(u,v);
		return Dst[u]+Dst[v]-2ll*Dst[lca];
	}
	ll Dist(pair<int,int> A)
	{
		return Dist(A.first,A.second);
	}
};

int n,nn;
Tree T1,T2,T3;
vector<pair<int,ll> > Ti[maxN],Sn[maxN];
int vis[maxN],Sz[maxN],rte,rtsize;
ll Ans,Dc[maxN];
int btop,Bp[maxN],St[maxN];
pair<int,int> Dmt[2][maxN];
vector<int> Qt[maxN];

void dfs_init(int u,int fa);
bool cmpdfn(int a,int b);
void UpdateAns(pair<int,int> A,pair<int,int> B,int u);
pair<int,int> Merge(pair<int,int> A,pair<int,int> B);
void dfs_sz(int u,int fa,int size);
void dfs_get(int u,int fa,int opt);
void dfs_dp(int u);
void Divide(int start,int size);

int main()
{
	for (int i=2; i<maxN; i++) Log[i]=Log[i>>1]+1;
	scanf("%d",&n);
	nn=n;
	for (int i=1; i<n; i++) T1.Input();
	for (int i=1; i<n; i++) T2.Input();
	for (int i=1; i<n; i++) {
		int u,v;
		ll w;
		scanf("%d%d%lld",&u,&v,&w);
		Ti[u].push_back(make_pair(v,w));
		Ti[v].push_back(make_pair(u,w));
	}
	for (int i=1; i<=n; i++) T2.Add_Edge(i,i+n,0);
	T1.Init();
	T2.Init();
	dfs_init(1,0);
	for (int i=1,sz; i<=n; i++)
		if ((sz=Sn[i].size())<=2)
			for (int j=0; j<sz; j++) T3.Add_Edge(i,Sn[i][j].first,Sn[i][j].second);
		else {
			int ls=++n,rs=++n;
			T3.Add_Edge(i,ls,0);
			T3.Add_Edge(i,rs,0);
			for (int j=0; j<sz; j++)
				if (j&1) Sn[rs].push_back(Sn[i][j]);
				else Sn[ls].push_back(Sn[i][j]);
		}
	Divide(1,n);
	printf("%lld\n",Ans);
	return 0;
}

void dfs_init(int u,int fa)
{
	for (int i=0,sz=Ti[u].size(); i<sz; i++)
		if (Ti[u][i].first!=fa) Sn[u].push_back(Ti[u][i]),dfs_init(Ti[u][i].first,u);
	return;
}
bool cmpdfn(int a,int b)
{
	return T1.dfn[a]<=T1.dfn[b];
}
void UpdateAns(pair<int,int> A,pair<int,int> B,int u)
{
	ll mxd=-INF;
	if (A.first&&B.first) mxd=max(mxd,T2.Dist(A.first,B.first));
	if (A.first&&B.second) mxd=max(mxd,T2.Dist(A.first,B.second));
	if (A.second&&B.first) mxd=max(mxd,T2.Dist(A.second,B.first));
	if (A.second&&B.second) mxd=max(mxd,T2.Dist(A.second,B.second));
	Ans=max(Ans,mxd-T1.Dst[u]*2+T3.W[rte]);
	return;
}
pair<int,int> Merge(pair<int,int> A,pair<int,int> B)
{
	//cout<<"Merge:"<<A.first<<" "<<A.second<<" "<<B.first<<" "<<B.second<<endl;
	if ((!A.first)+(!A.second)==2) return B;
	if ((!B.first)+(!B.second)==2) return A;
	int cnt=(!A.first)+(!A.second)+(!B.first)+(!B.second);
	if (cnt==4) return A;
	if (cnt==3) return (A.first||A.second)?(A):(B);
	if (cnt==2) return make_pair(A.first,B.first);
	if (!A.second) swap(A,B);
	pair<int,int> Rt=A;
	ll rd=T2.Dist(Rt.first,Rt.second);
	if (B.first&&B.second&&T2.Dist(B)>rd) Rt=B,rd=T2.Dist(B);
	if (A.first&&B.first&&T2.Dist(A.first,B.first)>rd) Rt=make_pair(A.first,B.first),rd=T2.Dist(Rt);
	if (A.first&&B.second&&T2.Dist(A.first,B.second)>rd) Rt=make_pair(A.first,B.second),rd=T2.Dist(Rt);
	if (A.second&&B.first&&T2.Dist(A.second,B.first)>rd) Rt=make_pair(A.second,B.first),rd=T2.Dist(Rt);
	if (A.second&&B.second&&T2.Dist(A.second,B.second)>rd) Rt=make_pair(A.second,B.second),rd=T2.Dist(Rt);
	return Rt;
}
void dfs_sz(int u,int fa,int size)
{
	Sz[u]=1;
	for (int i=T3.Head[u]; i!=-1; i=T3.Next[i])
		if (vis[i>>1]==0&&T3.V[i]!=fa) {
			dfs_sz(T3.V[i],u,size);
			Sz[u]+=Sz[T3.V[i]];
			int mxs=max(Sz[T3.V[i]],size-Sz[T3.V[i]]);
			if (mxs<rtsize) rtsize=mxs,rte=i;
		}
	return;
}
void dfs_get(int u,int fa,int opt)
{
	if (u<=nn) {
		Bp[++btop]=u;
		Dmt[opt][u]=make_pair(u+nn,0);
		T2.Dst[u+nn]=T2.Dst[u]+T1.Dst[u]+Dc[u];
	}
	for (int i=T3.Head[u]; i!=-1; i=T3.Next[i])
		if (vis[i>>1]==0&&T3.V[i]!=fa) {
			Dc[T3.V[i]]=Dc[u]+T3.W[i];
			dfs_get(T3.V[i],u,opt);
		}
	return;
}
void dfs_dp(int u)
{
	for (int i=0,sz=Qt[u].size(); i<sz; i++) {
		int v=Qt[u][i];
		dfs_dp(v);
		UpdateAns(Dmt[0][u],Dmt[1][v],u);
		UpdateAns(Dmt[1][u],Dmt[0][v],u);
		Dmt[0][u]=Merge(Dmt[0][u],Dmt[0][v]);
		Dmt[1][u]=Merge(Dmt[1][u],Dmt[1][v]);
		Dmt[0][v]=Dmt[1][v]=make_pair(0,0);
		//cout<<"After:"<<u<<"->"<<v<<endl;
		//cout<<"("<<Dmt[0][u].first<<","<<Dmt[0][u].second<<") ("<<Dmt[1][u].first<<","<<Dmt[1][u].second<<")"<<endl;
	}
	//cout<<"dfsdp:"<<u<<endl;
	//cout<<"("<<Dmt[0][u].first<<","<<Dmt[0][u].second<<") ("<<Dmt[1][u].first<<","<<Dmt[1][u].second<<")"<<endl;
	//cout<<"Ans:"<<Ans<<endl;
	Qt[u].clear();
	return;
}
void Divide(int start,int size)
{
	rtsize=inf;
	dfs_sz(start,0,size);
	if (rtsize==inf) return;
	vis[rte>>1]=1;
	int u=T3.V[rte],v=T3.V[rte^1];
	//cout<<"Divide:"<<u<<" "<<v<<endl;

	Dc[u]=Dc[v]=0;
	btop=0;
	dfs_get(u,0,0);
	dfs_get(v,0,1);
	sort(&Bp[1],&Bp[btop+1],cmpdfn);

	//for (int i=1;i<=btop;i++) cout<<Bp[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Dc[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<T2.Dst[i+nn]<<" ";cout<<endl;

	int top=1;
	St[1]=1;
	for (int i=((Bp[1]==1)?(2):(1)); i<=btop; i++) {
		int lca=T1.LCA(St[top],Bp[i]);
		while (top>=2&&T1.Dep[St[top-1]]>=T1.Dep[lca]) Qt[St[top-1]].push_back(St[top]),--top;
		if (St[top]!=lca) Qt[lca].push_back(St[top]),St[top]=lca;
		St[++top]=Bp[i];
	}
	//for (int i=1;i<=top;i++) cout<<St[i]<<" ";cout<<endl;
	while (top>=2) Qt[St[top-1]].push_back(St[top]),--top;

	//for (int i=1;i<=n;i++) for (int j=0,sz=Qt[i].size();j<sz;j++) cout<<i<<" -> "<<Qt[i][j]<<endl;

	dfs_dp(1);
	Dmt[0][1]=Dmt[1][1]=make_pair(0,0);
	//cout<<size<<" "<<Sz[u]<<" "<<size-Sz[u]<<endl;
	Divide(u,Sz[u]);
	Divide(v,size-Sz[u]);
	return;
}