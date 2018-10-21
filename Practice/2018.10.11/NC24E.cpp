#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define NAME "you"

const int maxN=202000;
const int maxM=maxN<<1;
const int maxQ=505000;
const int maxK=32;
const int maxBit=20;
const int Mod=998244353;
const int inf=2147483647;

class QData
{
public:
	int u,v,id;
};

int n,K,Q;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],NW[maxN];
int root,nowsum,Size[maxN],Mx[maxN],Fa[maxBit][maxN],Dph[maxN];
bool vis[maxN];
vector<int> T[maxN];
vector<QData> QD[maxN];
int Ans[maxQ],F[maxN][maxK],G[maxN][maxK];

void Add_Edge(int u,int v);
void dfs_root(int u,int fa);
int LCA(int u,int v);
void Divide1(int u);
void Divide2(int u);
void dfsf(int u,int fa);
void dfsg(int u,int fa);

int main(){
	mem(Head,-1);
	scanf("%d%d",&n,&K);
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}
	for (int i=1;i<=n;i++) scanf("%d",&NW[i]),NW[i]%=K;

	int rt;
	Mx[root=0]=inf;nowsum=n;dfs_root(1,1);
	Dph[rt=root]=1;Divide1(root);

	for (int i=1;i<maxBit;i++)
		for (int j=1;j<=n;j++) if (Fa[i-1][j]) Fa[i][j]=Fa[i-1][Fa[i-1][j]];

	scanf("%d",&Q);
	for (int i=1;i<=Q;i++){
		int u,v;scanf("%d%d",&u,&v);
		int lca=LCA(u,v);
		QD[lca].push_back((QData){u,v,i});
	}

	mem(vis,0);
	Divide2(rt);

	for (int i=1;i<=Q;i++) printf("%d\n",Ans[i]);
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs_root(int u,int fa){
	Size[u]=1;Mx[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0)){
			dfs_root(V[i],u);Size[u]+=Size[V[i]];
			Mx[u]=max(Mx[u],Size[V[i]]);
		}
	Mx[u]=max(Mx[u],nowsum-Size[u]);
	if (Mx[u]<Mx[root]) root=u;return;
}

void Divide1(int u){
	vis[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0){
			root=0;nowsum=Size[V[i]];
			dfs_root(V[i],V[i]);
			Fa[0][root]=u;Dph[root]=Dph[u]+1;T[u].push_back(root);
			Divide1(root);
		}
	return;
}

int LCA(int u,int v){
	if (Dph[u]<Dph[v]) swap(u,v);
	for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u])&&(Dph[Fa[i][u]]>=Dph[v])) u=Fa[i][u];
	if (u==v) return u;
	for (int i=maxBit-1;i>=0;i--) if ((Fa[i][u])&&(Fa[i][v])&&(Fa[i][u]!=Fa[i][v])) u=Fa[i][u],v=Fa[i][v];
	return Fa[0][u];
}

void Divide2(int u){
	vis[u]=1;
	mem(F[u],0);mem(G[u],0);F[u][0]=1;F[u][NW[u]]++;G[u][0]=1;dfsf(u,0);
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0){
			mem(G[V[i]],0);G[V[i]][0]=1;G[V[i]][NW[V[i]]]++;
			dfsg(V[i],u);
		}
	for (int i=0,sz=QD[u].size();i<sz;i++){
		int uu=QD[u][i].u,vv=QD[u][i].v;
		int cnt=0;
		for (int j=0;j<K;j++) cnt=(cnt+1ll*F[uu][j]*G[vv][(K-j)%K]%Mod)%Mod;
		Ans[QD[u][i].id]=cnt;
	}
	for (int i=0,sz=T[u].size();i<sz;i++) Divide2(T[u][i]);
	return;
}

void dfsf(int u,int fa){
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((vis[V[i]]==0)&&(V[i]!=fa)){
			int v=V[i];mem(F[v],0);
			for (int j=0;j<K;j++) F[v][j]=(F[u][j]+F[u][(j-NW[v]+K)%K])%Mod;
			dfsf(v,u);
		}
	return;
}

void dfsg(int u,int fa){
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((vis[V[i]]==0)&&(V[i]!=fa)){
			int v=V[i];mem(G[v],0);
			for (int j=0;j<K;j++) G[v][j]=(G[u][j]+G[u][(j-NW[v]+K)%K])%Mod;
			dfsg(v,u);
		}
	return;
}
