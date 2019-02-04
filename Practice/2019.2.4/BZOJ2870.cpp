#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define ft first
#define sd second
#define pb push_back
#define mp make_pair

const int maxN=50500*8;
const int maxM=maxN<<1;
const int inf=1000000000;

int n,nn,NW[maxN];
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM];
vector<int> Sn[maxN];
int rte,rtsz,Sz[maxN],vis[maxN],Ans;
vector<pair<int,int> > Bp[2];

void Add_Edge(int u,int v);
void dfs(int u,int fa);
void dfs_root(int u,int fa,int size);
void dfs_calc(int u,int fa,int opt,int d,int key);
void Divide(int u,int size);

int main(){
	//freopen("3.in","r",stdin);
	scanf("%d",&n);nn=n;mem(Head,-1);
	for (int i=1;i<=n;i++) scanf("%d",&NW[i]);
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);
	}
	dfs(1,0);
	for (int i=1;i<=n;i++)
		if (Sn[i].size()<=2){
			if (i<=n) continue;
			for (int j=0,sz=Sn[i].size();j<sz;j++) Add_Edge(i,Sn[i][j]);
		}
		else{
			int ls=++n,rs=++n;NW[ls]=NW[rs]=NW[i];
			for (int j=0,sz=Sn[i].size();j<sz;j++)
				if (j&1) Sn[rs].pb(Sn[i][j]);
				else Sn[ls].pb(Sn[i][j]);
		}
	//cout<<"Init finish"<<endl;

	Divide(1,n);

	printf("%d\n",Ans);return 0;
}
void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
	return;
}
void dfs(int u,int fa){
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa) Sn[u].pb(V[i]),dfs(V[i],u);
	return;
}
void dfs_root(int u,int fa,int size){
	Sz[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa&&vis[i>>1]==0){
			dfs_root(V[i],u,size);Sz[u]+=Sz[V[i]];
			int nms=max(Sz[V[i]],size-Sz[V[i]]);
			if (nms<rtsz) rtsz=nms,rte=i;
		}
	return;
}
void dfs_calc(int u,int fa,int opt,int d,int key){
	Ans=max(Ans,d*key);
	Bp[opt].pb(mp(key,d));
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa&&vis[i>>1]==0) dfs_calc(V[i],u,opt,d+(V[i]<=nn),min(key,NW[V[i]]));
	return;
}
void Divide(int st,int size){
	//cout<<"Divide:"<<st<<" "<<size<<endl;
	rtsz=inf;
	dfs_root(st,st,size);
	if (rtsz==inf) return;
	vis[rte>>1]=1;
	int u=V[rte],v=V[rte^1];
	///cout<<u<<" "<<v<<endl;
	Bp[0].clear();Bp[1].clear();
	dfs_calc(u,0,0,u<=nn,NW[u]);
	dfs_calc(v,0,1,v<=nn,NW[v]);
	sort(Bp[0].begin(),Bp[0].end());sort(Bp[1].begin(),Bp[1].end());
	for (int i=Bp[0].size()-1,j=Bp[1].size()-1,mxl=0;i>=0;i--){
		while (j>=0&&Bp[1][j].ft>=Bp[0][i].ft) mxl=max(mxl,Bp[1][j--].sd);
		Ans=max(Ans,(Bp[0][i].sd+mxl)*Bp[0][i].ft);
	}
	for (int i=Bp[1].size()-1,j=Bp[0].size()-1,mxl=0;i>=0;i--){
		while (j>=0&&Bp[0][j].ft>=Bp[1][i].ft) mxl=max(mxl,Bp[0][j--].sd);
		Ans=max(Ans,(Bp[1][i].sd+mxl)*Bp[1][i].ft);
	}
	Divide(u,Sz[u]);Divide(v,size-Sz[u]);return;
}
