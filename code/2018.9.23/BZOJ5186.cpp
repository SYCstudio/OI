#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=71000;
const int maxM=maxN<<1;
const int inf=2147483647;

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],Dg[maxN],Ans[maxN];
int Mn[maxN];
int root,nowsum=0,Mx[maxN],Size[maxN],Dis[maxN];
int mxd=0,mxd2,Sum1[maxN],Sum2[maxN];
bool vis[maxN];

void Add_Edge(int u,int v);
void dfs_dp1(int u,int fa);
void dfs_dp2(int u,int fa);
void dfs_root(int u,int fa);
void Solve(int u);
void dfs_inc(int u,int fa,int d);
void dfs_exc(int u,int fa);
void dfs_calc(int u,int fa);

int main(){
	//freopen("in.in","r",stdin);freopen("o1","w",stdout);
	mem(Head,-1);
	scanf("%d",&n);
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);Dg[u]++;Dg[v]++;
		Add_Edge(u,v);Add_Edge(v,u);
	}

	dfs_dp1(1,1);
	dfs_dp2(1,1);
	//for (int i=1;i<=n;i++) cout<<Mn[i]<<" ";cout<<endl;
	
	root=0;Mx[0]=inf;nowsum=n;dfs_root(1,1);
	Solve(root);

	for (int i=1;i<=n;i++)
		if (Dg[i]==1) printf("1\n");
		else printf("%d\n",2-Ans[i]);

	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs_dp1(int u,int fa){
	Mn[u]=inf;
	if (Dg[u]==1) Mn[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			dfs_dp1(V[i],u);Mn[u]=min(Mn[u],Mn[V[i]]+1);
		}
	return;
}

void dfs_dp2(int u,int fa){
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			Mn[V[i]]=min(Mn[V[i]],Mn[u]+1);dfs_dp2(V[i],u);
		}
	return;
}

void dfs_root(int u,int fa){
	Size[u]=1;Mx[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0)){
			dfs_root(V[i],u);
			Size[u]+=Size[V[i]];Mx[u]=max(Mx[u],Size[V[i]]);
		}
	Mx[u]=max(Mx[u],nowsum-Size[u]);
	if (Mx[u]<Mx[root]) root=u;return;
}

void Solve(int u){
	//cout<<"Solve:"<<u<<endl;
	vis[u]=1;
	mxd=0;dfs_inc(u,0,0);
	for (int i=mxd-1;i>=1;i--) Sum1[i]+=Sum1[i+1];
	//cout<<"mx:"<<mxd<<":";for (int i=1;i<=mxd;i++) cout<<Sum1[i]<<" ";cout<<endl;
	Ans[u]+=Sum1[1];
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0){
			mxd2=0;dfs_exc(V[i],u);
			for (int j=mxd2-1;j>=1;j--) Sum2[j]+=Sum2[j+1];
			dfs_calc(V[i],u);
			for (int j=mxd2;j>=1;j--) Sum2[j]=0;
		}
	for (int i=mxd;i>=0;i--) Sum1[i]=0;

	//dfs_root(u,u);
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0){
			root=0;nowsum=Size[V[i]];
			dfs_root(V[i],V[i]);Solve(root);
		}
	return;
}

void dfs_inc(int u,int fa,int d){//容
	Dis[u]=d;int k=Mn[u]-d;
	//cout<<u<<" "<<d<<endl;
	if (k>0) mxd=max(mxd,k),Sum1[k]+=2-Dg[u];
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0)) dfs_inc(V[i],u,d+1);
	return;
}

void dfs_exc(int u,int fa){//斥
	int k=Mn[u]-Dis[u];
	if (k>0) mxd2=max(mxd2,k),Sum2[k]+=2-Dg[u];
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0)) dfs_exc(V[i],u);
	return;
}

void dfs_calc(int u,int fa){
	Ans[u]+=Sum1[Dis[u]+1]-Sum2[Dis[u]+1];
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0)) dfs_calc(V[i],u);
	return;
}
