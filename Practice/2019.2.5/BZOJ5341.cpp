#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=404000*2;
const int maxM=maxN<<1;
const int maxB=20;
const int inf=1000000000;
const ll INF=1e18;

int n;
ll Ans=0;

namespace T1{
	int nn,edgecnt=-1,Head[maxN],Next[maxM],V[maxM],vis[maxN];
	int hcnt=-1,HH[maxN],NN[maxN],VV[maxN];
	ll W[maxM],F[maxN],G[maxN],Dst[maxN];
	int rte,rtsize,Sz[maxN],St[maxN];
	vector<pair<int,ll> > Sn[maxN],E[maxN];
	int btop,Bp[maxN];
	void Idd_Edge(int u,int v,ll w);
	void Add_Edge(int u,int v,ll w);
	void Do();
	void dfs_init(int u,int fa);
	void dfs_root(int u,int fa,int size);
	void Hdd_Edge(int u,int v);
	void Divide(int u,int size);
	bool cmp(int a,int b);
	void dfs_get(int u,int fa,int opt,ll dw);
	void dfs_dp(int u);
}
namespace T2{
	int edgecnt=-1,Head[maxN],Next[maxM],V[maxM],Log[maxN];
	ll W[maxM],Dst[maxN];
	int Dep[maxN],dfncnt,dfn[maxN],lst[maxN],eucnt,ST[maxB][maxN],efn[maxN],est[maxN];
	void Add_Edge(int u,int v,ll w);
	void Init();
	void dfs_init(int u,int fa);
	int LCA(int u,int v);
}

int main(){
	mem(T1::Head,-1);mem(T2::Head,-1);mem(T1::HH,-1);
	scanf("%d",&n);
	for (int i=1;i<n;i++){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		T1::Idd_Edge(u,v,w);
	}
	for (int i=1;i<n;i++){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		T2::Add_Edge(u,v,w);
	}
	T2::Init();
	T1::Do();
	for (int i=1;i<=n;i++) Ans=max(Ans,T1::Dst[i]-T2::Dst[i]);
	printf("%lld\n",Ans);
	return 0;
}
namespace T1{
	void Idd_Edge(int u,int v,ll w){
		E[u].push_back(make_pair(v,w));
		E[v].push_back(make_pair(u,w));
		return;
	}
	void Add_Edge(int u,int v,ll w){
		Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
		Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;W[edgecnt]=w;
		return;
	}
	void Do(){
		dfs_init(1,0);nn=n;
		for (int i=1;i<=n;i++)
			if (Sn[i].size()<=2){
				for (int j=0,sz=Sn[i].size();j<sz;j++)
					Add_Edge(i,Sn[i][j].first,Sn[i][j].second);
			}
			else{
				int ls=++n,rs=++n;Add_Edge(i,ls,0);Add_Edge(i,rs,0);
				for (int j=0,sz=Sn[i].size();j<sz;j++)
					if (j&1) Sn[rs].push_back(Sn[i][j]);
					else Sn[ls].push_back(Sn[i][j]);
			}
		/*
		cout<<"After rebuild"<<endl;
		for (int i=1;i<=n;i++) for (int j=Head[i];j!=-1;j=Next[j]) cout<<i<<" "<<V[j]<<" "<<W[j]<<endl;
		//*/
		for (int i=1;i<=n;i++) F[i]=G[i]=-INF;
		Divide(1,n);
		return;
	}
	void dfs_init(int u,int fa){
		for (int i=0,sz=E[u].size();i<sz;i++)
			if (E[u][i].first!=fa){
				Sn[u].push_back(E[u][i]);Dst[E[u][i].first]=Dst[u]+E[u][i].second;
				dfs_init(E[u][i].first,u);
			}
		return;
	}
	void dfs_root(int u,int fa,int size){
		//cout<<"dfsroot:"<<u<<" "<<fa<<" "<<size<<endl;
		Sz[u]=1;
		for (int i=Head[u];i!=-1;i=Next[i])
			if (vis[i>>1]==0&&V[i]!=fa){
				dfs_root(V[i],u,size);Sz[u]+=Sz[V[i]];
				int mxs=max(Sz[V[i]],size-Sz[V[i]]);
				if (mxs<rtsize) rtsize=mxs,rte=i;
			}
		return;
	}
	void Hdd_Edge(int u,int v){
		NN[++hcnt]=HH[u];HH[u]=hcnt;VV[hcnt]=v;
		return;
	}
	void Divide(int st,int size){
		rtsize=inf;dfs_root(st,0,size);
		if (rtsize==inf) return;
		vis[rte>>1]=1;int u=V[rte],v=V[rte^1];
		btop=0;dfs_get(u,0,0,0);dfs_get(v,0,1,0);

		if (btop==0) return;
		sort(&Bp[1],&Bp[btop+1],cmp);
		int top=0;if (Bp[1]!=1) St[++top]=1;
		hcnt=-1;
		for (int i=1;i<=btop;i++){
			int u=Bp[i],lca=T2::LCA(u,St[top]);
			while (top>=2&&T2::Dep[St[top-1]]>=T2::Dep[lca]) Hdd_Edge(St[top-1],St[top]),--top;
			if (St[top]!=lca) Hdd_Edge(lca,St[top]),St[top]=lca;
			St[++top]=u;
		}
		while (top>=2) Hdd_Edge(St[top-1],St[top]),--top;
		dfs_dp(1);
		F[1]=G[1]=-INF;HH[1]=-1;

		Divide(u,Sz[u]);Divide(v,size-Sz[u]);return;
	}
	bool cmp(int a,int b){
		return T2::dfn[a]<=T2::dfn[b];
	}
	void dfs_get(int u,int fa,int opt,ll dw){
		if (u<=nn){
			Bp[++btop]=u;
			if (opt==0) F[u]=Dst[u]+dw;else G[u]=Dst[u]+dw;
		}
		//cout<<"dfs_get:"<<u<<" "<<fa<<" "<<opt<<" "<<dw<<endl;
		for (int i=Head[u];i!=-1;i=Next[i])
			if (V[i]!=fa&&vis[i>>1]==0) dfs_get(V[i],u,opt,dw+W[i]);
		return;
	}
	void dfs_dp(int u){
		for (int i=HH[u];i!=-1;i=NN[i]){
			int v=VV[i];dfs_dp(v);
			Ans=max(Ans,(max(F[u]+G[v],G[u]+F[v])+W[rte])/2-T2::Dst[u]);
			F[u]=max(F[u],F[v]);G[u]=max(G[u],G[v]);
			F[v]=G[v]=-INF;
		}
		HH[u]=-1;return;
	}
}
namespace T2{
	void Add_Edge(int u,int v,ll w){
		Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
		Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;W[edgecnt]=w;
		return;
	}
	void Init(){
		for (int i=2;i<maxN;i++) Log[i]=Log[i>>1]+1;
		dfs_init(1,0);
		for (int i=1;i<maxB;i++)
			for (int j=1;j+(1<<i)-1<=eucnt;j++)
				if (Dep[ST[i-1][j]]<Dep[ST[i-1][j+(1<<(i-1))]]) ST[i][j]=ST[i-1][j];
				else ST[i][j]=ST[i-1][j+(1<<(i-1))];
		return;
	}
	void dfs_init(int u,int fa){
		ST[0][++eucnt]=u;dfn[u]=++dfncnt;efn[u]=eucnt;
		for (int i=Head[u];i!=-1;i=Next[i])
			if (V[i]!=fa){
				Dst[V[i]]=Dst[u]+W[i];Dep[V[i]]=Dep[u]+1;
				dfs_init(V[i],u);
				ST[0][++eucnt]=u;
			}
		lst[u]=dfncnt;est[u]=eucnt;return;
	}
	int LCA(int u,int v){
		int l=min(efn[u],efn[v]),r=max(est[u],est[v]);
		int lg=Log[r-l+1];
		if (Dep[ST[lg][l]]<=Dep[ST[lg][r-(1<<lg)+1]]) return ST[lg][l];
		else return ST[lg][r-(1<<lg)+1];
	}
}