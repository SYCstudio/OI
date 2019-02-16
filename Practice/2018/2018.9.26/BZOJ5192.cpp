#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=maxN<<1;
const int inf=2147483647;

class Option
{
public:
	char opt;int key;
};

int n,Q;
Option O[maxN];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Fa[maxN],Top[maxN],Hs[maxN],Dpt[maxN];
int nowsize,root,Size[maxN],Mx[maxN];
vector<int> Ap[maxN];
bool vis[maxN],mark[maxN];
int A[2][maxN],F[2][maxN];

void Add_Edge(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int top);
int LCA(int u,int v);
int Dist(int u,int v);
void dfs_root(int u,int fa);
void Solve(int u);
void dfs_mark(int u,int fa);
void Update(int u);
int Query(int u);

int main(){
	//freopen("in.in","r",stdin);freopen("out.out","w",stdout);
	mem(Head,-1);
	scanf("%d",&Q);
	for (int i=1;i<=Q;i++){
		scanf(" %c%d",&O[i].opt,&O[i].key);
		if (O[i].opt=='B'){
			n++;
			if (O[i].key!=-1) Add_Edge(n,O[i].key);
		}
	}

	for (int i=1;i<=n;i++)
		if (Dpt[i]==0){
			Dpt[i]=1;dfs1(i,i);dfs2(i,i);
		}

	for (int i=1;i<=n;i++)
		if (vis[i]==0){
			nowsize=n;Mx[0]=inf;root=0;
			dfs_root(i,i);
			Solve(root);
		}

	/*
	for (int i=1;i<=n;i++){
		cout<<i<<":";for (int j=Ap[i].size()-1;j>=0;j--) cout<<Ap[i][j]<<" ";cout<<endl;
	}
	//*/

	int nn=0;
	for (int i=1;i<=Q;i++){
		if (O[i].opt=='B') Update(++nn);
		if (O[i].opt=='Q') printf("%d\n",Query(O[i].key));
		/*
		cout<<i<<":"<<endl;
		for (int j=1;j<=n;j++) cout<<A[0][j]<<" "<<F[0][j]<<" "<<A[1][j]<<" "<<F[1][j]<<endl;
		cout<<endl;
		//*/
	}
}

void Add_Edge(int u,int v){
	//cout<<"Add_Edge:"<<u<<" "<<v<<endl;
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
	return;
}

void dfs1(int u,int fa){
	Size[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			Fa[V[i]]=u;Dpt[V[i]]=Dpt[u]+1;
			dfs1(V[i],u);Size[u]+=Size[V[i]];
			if (Size[V[i]]>Size[Hs[u]]) Hs[u]=V[i];
		}
	return;
}

void dfs2(int u,int top){
	Top[u]=top;
	if (Hs[u]==0) return;
	dfs2(Hs[u],top);
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=Fa[u])&&(V[i]!=Hs[u])) dfs2(V[i],V[i]);
	return;
}

void dfs_root(int u,int fa){
	Size[u]=1;Mx[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0)){
			dfs_root(V[i],u);
			Size[u]+=Size[V[i]];Mx[u]=max(Mx[u],Size[V[i]]);
		}
	Mx[u]=max(Mx[u],nowsize-Size[u]);
	if (Mx[u]<Mx[root]) root=u;return;
}

int LCA(int u,int v){
	while (Top[u]!=Top[v]){
		if (Dpt[Top[u]]<Dpt[Top[v]]) swap(u,v);
		u=Fa[Top[u]];
	}
	if (Dpt[u]>Dpt[v]) swap(u,v);
	return u;
}

int Dist(int u,int v){
	return Dpt[u]+Dpt[v]-2*Dpt[LCA(u,v)];
}

void Solve(int u){
	vis[u]=1;
	dfs_mark(u,u);dfs_root(u,u);
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0){
			root=0;nowsize=Size[V[i]];
			dfs_root(V[i],V[i]);Solve(root);
		}
	return;
}

void dfs_mark(int u,int fa){
	Ap[u].push_back(root);
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0))
			dfs_mark(V[i],u);
	return;
}

void Update(int u){
	mark[u]=1;
	//cout<<"Update:"<<u<<endl;
	for (int i=Ap[u].size()-2;i>=0;i--){
		int anc=Ap[u][i],d=Dist(u,anc);
		//cout<<anc<<" "<<d<<endl;
		if (d>=A[0][anc]){
			if (F[0][anc]!=Ap[u][i+1]){
				F[1][anc]=F[0][anc];A[1][anc]=A[0][anc];
			}
			F[0][anc]=Ap[u][i+1];A[0][anc]=d;
		}
		else if ((d>A[1][anc])&&(F[0][anc]!=Ap[u][i+1])){
			F[1][anc]=Ap[u][i+1];A[1][anc]=d;
		}
	}
	return;
}

int Query(int u){
	int mx=A[0][u];
	for (int i=Ap[u].size()-2;i>=0;i--){
		int anc=Ap[u][i],d=Dist(u,anc);
		if (mark[anc]){
			if (F[0][anc]!=Ap[u][i+1]) mx=max(mx,d+A[0][anc]);
			else mx=max(mx,d+A[1][anc]);
		}
	}
	return mx;
}
/*
7
B -1
Q 1
B 1
B 2
Q 3
B 2
Q 2

16
B -1
Q 1
B 1
Q 2
Q 1
B 2
Q 2
Q 3
Q 1
B 3
Q 1
Q 2
Q 3
B 3
Q 3
Q 5
//*/
