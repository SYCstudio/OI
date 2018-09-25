#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register
#define IL inline

const int maxN=71000;
const int maxM=maxN<<1;
const int inf=2147483647;

int n,m;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],Dg[maxN],Ans[maxN];
int Mn[maxN];
int root,nowsum=0,Mx[maxN],Size[maxN],Dis[maxN];
int mxd=0,mxd2,Sum1[maxN],Sum2[maxN];
bool vis[maxN];

IL void Add_Edge(RG int u,RG int v);
IL void dfs_dp1(RG int u,RG int fa);
IL void dfs_dp2(RG int u,RG int fa);
IL void dfs_root(RG int u,RG int fa);
IL void Solve(RG int u);
IL void dfs_inc(RG int u,RG int fa,RG int d);
IL void dfs_exc(RG int u,RG int fa);
IL void dfs_calc(RG int u,RG int fa);

int main(){
	//freopen("in.in","r",stdin);freopen("o1","w",stdout);
	//mem(Head,-1);
	scanf("%d",&n);
	for (RG int i=1;i<n;++i){
		RG int u,v;scanf("%d%d",&u,&v);++Dg[u];++Dg[v];
		Add_Edge(u,v);Add_Edge(v,u);
	}

	dfs_dp1(1,1);
	dfs_dp2(1,1);
	//for (int i=1;i<=n;i++) cout<<Mn[i]<<" ";cout<<endl;
	
	root=0;Mx[0]=inf;nowsum=n;dfs_root(1,1);
	Solve(root);

	for (RG int i=1;i<=n;++i)
		if (Dg[i]==1) printf("1\n");
		else printf("%d\n",2-Ans[i]);

	return 0;
}

IL void Add_Edge(RG int u,RG int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

IL void dfs_dp1(RG int u,RG int fa){
	Mn[u]=inf;
	if (Dg[u]==1) Mn[u]=0;
	for (RG int i=Head[u];i;i=Next[i])
		if (V[i]!=fa){
			dfs_dp1(V[i],u);Mn[u]=min(Mn[u],Mn[V[i]]+1);
		}
	return;
}

IL void dfs_dp2(RG int u,RG int fa){
	for (RG int i=Head[u];i;i=Next[i])
		if (V[i]!=fa){
			Mn[V[i]]=min(Mn[V[i]],Mn[u]+1);dfs_dp2(V[i],u);
		}
	return;
}

IL void dfs_root(RG int u,RG int fa){
	Size[u]=1;Mx[u]=0;
	for (RG int i=Head[u];i;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0)){
			dfs_root(V[i],u);
			Size[u]+=Size[V[i]];Mx[u]=max(Mx[u],Size[V[i]]);
		}
	Mx[u]=max(Mx[u],nowsum-Size[u]);
	if (Mx[u]<Mx[root]) root=u;return;
}

IL void Solve(RG int u){
	//cout<<"Solve:"<<u<<endl;
	vis[u]=1;
	mxd=0;dfs_inc(u,0,0);
	while (mxd%4) mxd++;
	for (RG int i=mxd-1;i>=1;i-=4){
		Sum1[i]+=Sum1[i+1];
		Sum1[i-1]+=Sum1[i];
		Sum1[i-2]+=Sum1[i-1];
		Sum1[i-3]+=Sum1[i-2];
	}
	//cout<<"mx:"<<mxd<<":";for (int i=1;i<=mxd;i++) cout<<Sum1[i]<<" ";cout<<endl;
	Ans[u]+=Sum1[1];
	for (RG int i=Head[u];i;i=Next[i])
		if (vis[V[i]]==0){
			mxd2=0;dfs_exc(V[i],u);
			while ((mxd2-1)%4) mxd2++;
			for (RG int j=mxd2-1;j>=1;j-=4){
				Sum2[j]+=Sum2[j+1];
				Sum2[j-1]+=Sum2[j];
				Sum2[j-2]+=Sum2[j-1];
				Sum2[j-3]+=Sum2[j-2];
			}
			dfs_calc(V[i],u);
			for (RG int j=mxd2;j>=1;j-=4){
				Sum2[j]=0;Sum2[j-1]=0;Sum2[j-2]=0;Sum2[j-3]=0;
			}
		}
	for (RG int i=mxd;i>=0;i-=4){
		Sum1[i]=0;Sum1[i-1]=0;Sum1[i-2]=0;Sum1[i-3]=0;
	}

	dfs_root(u,u);
	for (RG int i=Head[u];i;i=Next[i])
		if (vis[V[i]]==0){
			root=0;nowsum=Size[V[i]];
			dfs_root(V[i],V[i]);Solve(root);
		}
	return;
}

IL void dfs_inc(RG int u,RG int fa,RG int d){//容
	Dis[u]=d;RG int k=Mn[u]-d;
	//cout<<u<<" "<<d<<endl;
	if (k>0) mxd=max(mxd,k),Sum1[k]+=2-Dg[u];
	for (RG int i=Head[u];i;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0)) dfs_inc(V[i],u,d+1);
	return;
}

IL void dfs_exc(RG int u,RG int fa){//斥
	RG int k=Mn[u]-Dis[u];
	if (k>0) mxd2=max(mxd2,k),Sum2[k]+=2-Dg[u];
	for (RG int i=Head[u];i;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0)) dfs_exc(V[i],u);
	return;
}

IL void dfs_calc(RG int u,RG int fa){
	Ans[u]+=Sum1[Dis[u]+1]-Sum2[Dis[u]+1];
	for (RG int i=Head[u];i;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0)) dfs_calc(V[i],u);
	return;
}
