#pragma comment(linker,"/STACK:102400000,102400000")
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int maxNum=1030;
const int maxM=maxN*2;
const int Mod=1e9+7;
const int inf=2147483647;

int n,m;
int nowsum,root;
int Size[maxN],mxSon[maxN];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Node[maxN];
bool vis[maxN];
int F[maxN][maxNum],Ans[maxNum];

void Add_Edge(int u,int v);
void GetRoot(int u,int fa);
void Solve(int u);
void GetAns(int u,int fa);

int main()
{
	ios::sync_with_stdio(false);
	int T;cin>>T;
	while (T--)
	{
		edgecnt=0;mem(Head,-1);mem(vis,0);mem(Ans,0);
		cin>>n>>m;
		for (int i=1;i<=n;i++) cin>>Node[i];
		for (int i=1;i<n;i++)
		{
			int u,v;cin>>u>>v;
			Add_Edge(u,v);Add_Edge(v,u);
		}
		root=0;mxSon[0]=inf;nowsum=n;
		GetRoot(1,0);
		Solve(root);
		for (int i=0;i<m;i++){
			printf("%d",Ans[i]);
			if (i==m-1) printf("\n");
			else printf(" ");
		}
	}
	return 0;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void GetRoot(int u,int fa)
{
	Size[u]=1;mxSon[u]=0;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((vis[V[i]]==0)&&(V[i]!=fa))
		{
			GetRoot(V[i],u);Size[u]+=Size[V[i]];
			mxSon[u]=max(mxSon[u],Size[V[i]]);
		}
	mxSon[u]=max(mxSon[u],nowsum-Size[u]);
	if (mxSon[u]<mxSon[root]) root=u;
	return;
}

void Solve(int u)
{
	for (int i=0;i<m;i++) F[u][i]=0;
	F[u][Node[u]]=1;vis[u]=1;
	GetAns(u,0);
	for (int i=0;i<m;i++) Ans[i]=(Ans[i]+F[u][i])%Mod;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]==0)
		{
			root=0;nowsum=Size[V[i]];
			GetRoot(V[i],0);
			Solve(root);
		}
	return;
}

void GetAns(int u,int fa)
{
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(vis[V[i]]==0))
		{
			for (int j=0;j<m;j++) F[V[i]][j]=0;
			for (int j=0;j<m;j++) F[V[i]][Node[V[i]]^j]=(F[V[i]][Node[V[i]]^j]+F[u][j])%Mod;
			GetAns(V[i],u);
			for (int j=0;j<m;j++) F[u][j]=(F[u][j]+F[V[i]][j])%Mod;
		}
	return;
}
