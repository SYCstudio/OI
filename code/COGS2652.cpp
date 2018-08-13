#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define NAME "cdcq_b"

const int maxN=201000;
const int maxM=maxN<<1;
const ld eps=1e-8;
const int inf=2147483647;

int n,m;
int A[maxN],B[maxN];
ld Val[maxN];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int MxD[maxN],Fa[maxN],dfncnt,dfn[maxN],Hson[maxN];
ld F[maxN],Mx,Sum[maxN];

void Add_Edge(int u,int v);
void dfs1(int u);
void dfs2(int u);
void dp(int u);

int main(){
	freopen(NAME".in","r",stdin);freopen(NAME".out","w",stdout);
	mem(Head,-1);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%d",&A[i]);
	for (int i=1;i<=n;i++) scanf("%d",&B[i]);
	for (int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
	}

	if (m<=1){
		ld Ans=inf;
		for (int i=1;i<=n;i++) Ans=min(Ans,(ld)A[i]/(ld)B[i]);
		printf("%.2LF\n",Ans);return 0;
	}

	dfs1(1);dfs2(1);

	//for (int i=1;i<=n;i++) cout<<MxD[i]<<" ";cout<<endl;

	ld L=0,R=4010000000,Ans=-1;
	do{
		ld mid=(L+R)/2.0;
		for (int i=1;i<=n;i++) Val[i]=mid*(ld)B[i]-(ld)A[i],F[i]=-inf,Sum[i]=0;
		Mx=-inf;
		dp(1);
		if (Mx==-inf){
			printf("-1\n");return 0;
		}
		//cout<<mid<<" "<<Mx<<endl;
		if (Mx>=0) Ans=mid,R=mid-eps;
		else L=mid+eps;
	}
	while (L+eps<=R);

	printf("%.2LF\n",Ans);

	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs1(int u){
	MxD[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=Fa[u]){
			Fa[V[i]]=u;dfs1(V[i]);
			if (MxD[V[i]]+1>MxD[u]) MxD[u]=MxD[V[i]]+1,Hson[u]=V[i];
		}
	return;
}

void dfs2(int u){
	dfn[u]=++dfncnt;
	if (Hson[u]==0) return;
	dfs2(Hson[u]);
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=Fa[u])&&(V[i]!=Hson[u]))
			dfs2(V[i]);
	return;
}

void dp(int u){
	int fu=dfn[u];F[fu]=Val[u];
	if (Hson[u]==0) return;
	dp(Hson[u]);
	F[fu]=-Sum[Hson[u]];Sum[u]=Sum[Hson[u]]+Val[u];
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=Fa[u])&&(V[i]!=Hson[u])){
			int v=V[i],fv=dfn[v],len=MxD[v];
			dp(v);
			for (int j=1;j<=len;j++)
				if ((m-j>=1)&&(m-j<=MxD[u]))
					Mx=max(Mx,F[fv+j-1]+F[fu+(m-j)-1]+Sum[u]+Sum[v]);
			for (int j=1;j<=len;j++)
				F[fu+j]=max(F[fu+j],F[fv+j-1]+Sum[v]-Sum[u]+Val[u]);
		}
	if (MxD[u]>=m) Mx=max(Mx,F[fu+m-1]+Sum[u]);
	return;
}
/*
3 2
2 3 3
6 6 6
1 2
2 3

9 3
9 4 4 1 6 5 1 9 5
8 3 3 1 5 4 1 8 4
1 2
2 3
3 4
3 5
1 6
6 7
7 8
6 9 
//*/
