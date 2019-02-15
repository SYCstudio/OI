#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*2;
const int maxM=maxN<<1;
const int inf=2147483647;

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Depth[maxN],MxD[maxN],Hson[maxN],Fa[maxN],Top[maxN];
int fcnt=0,gcnt=0,fdfn[maxN],gdfn[maxN];
ll Ans=0,F[maxN],G[maxN];

void Add_Edge(int u,int v);
void dfs1(int u,int fa);
void dfs2(int u,int top);
void dp(int u);

int main(){
	mem(Head,-1);
	scanf("%d",&n);
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}
	Depth[1]=1;dfs1(1,1);dfs2(1,1);

	/*
	for (int i=1;i<=n;i++) cout<<Depth[i]<<" ";cout<<endl;
	for (int i=1;i<=n;i++) cout<<Top[i]<<" ";cout<<endl;
	for (int i=1;i<=n;i++) cout<<fdfn[i]<<" ";cout<<endl;
	for (int i=1;i<=n;i++) cout<<gdfn[i]<<" ";cout<<endl;
	//*/
	
	dp(1);

	printf("%lld\n",Ans);

	/*
	cout<<"F:"<<endl;
	for (int i=1;i<=n;i++){
		int len=MxD[i]-Depth[i];
		for (int j=0;j<=len;j++) cout<<F[fdfn[i]+j]<<" ";cout<<endl;

	}
	cout<<"G:"<<endl;
	for (int i=1;i<=n;i++){
		int len=MxD[i]-Depth[i];
		for (int j=0;j<=len;j++) cout<<G[gdfn[i]+j]<<" ";cout<<endl;
	}
	//*/

	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs1(int u,int fa){
	MxD[u]=Depth[u];
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			Fa[V[i]]=u;Depth[V[i]]=Depth[u]+1;dfs1(V[i],u);
			if (MxD[V[i]]>MxD[u]) Hson[u]=V[i],MxD[u]=MxD[V[i]];
		}
	return;
}

void dfs2(int u,int top){
	Top[u]=top;fdfn[u]=++fcnt;
	if (u!=top) gdfn[u]=gdfn[Fa[u]]-1;
	else{
		int len=MxD[u]-Depth[u]+1;
		gcnt+=len;gdfn[u]=gcnt;gcnt+=len-1;
	}
	if (Hson[u]==0) return;
	dfs2(Hson[u],top);
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=Fa[u])&&(V[i]!=Hson[u]))
			dfs2(V[i],V[i]);
	return;
}			

void dp(int u){
	F[fdfn[u]]=1;
	if (Hson[u]==0) return;
	dp(Hson[u]);
	int fu=fdfn[u],gu=gdfn[u];
	Ans+=G[gu];
	//cout<<"now:"<<u<<endl;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=Fa[u])&&(V[i]!=Hson[u])){
			int v=V[i],len=MxD[v]-Depth[v];dp(v);
			int fv=fdfn[v],gv=gdfn[v];
			for (int j=0;j<=len;j++){
				if (j>=1){
					Ans+=1ll*F[fu+j-1]*G[gv+j];
					//cout<<"Ans1: ["<<u<<" "<<v<<"] "<<F[fu+j-1]<<" "<<G[gv+j]<<endl;
				}
				Ans+=1ll*G[gu+j+1]*F[fv+j];
				//cout<<"Ans2: ["<<u<<" "<<v<<"] "<<G[gu+j+1]<<" "<<F[fv+j]<<endl;
				if (j>=1) G[gu+j-1]+=G[gv+j];
				G[gu+j+1]+=F[fu+j+1]*F[fv+j];
			}
			for (int j=0;j<=len;j++) F[fu+j+1]+=F[fv+j];
			//cout<<u<<"->"<<v<<" "<<len<<endl;
			//cout<<"F:";for (int j=0;j<=MxD[u]-Depth[u];j++) cout<<F[fu+j]<<" ";cout<<endl;
			//cout<<"G:";for (int j=0;j<=MxD[u]-Depth[u];j++) cout<<G[gu+j]<<" ";cout<<endl;
		}
	return;
}
