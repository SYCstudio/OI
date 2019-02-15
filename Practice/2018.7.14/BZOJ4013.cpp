#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=150;
const int Mod=1e9+7;
const int inf=2147483647;

int n,m;
int UFS[maxN];
int Inputu[maxN],Inputv[maxN],Inputopt[maxN],Id[maxN];
int edgecnt,Head[maxN],Next[maxN],V[maxN];
int F[maxN][maxN],G[maxN],Size[maxN];
int C[maxN][maxN];

int Find(int u);
void Add_Edge(int u,int v);
void dfs(int u);

int main()
{
	scanf("%d%d",&n,&m);

	mem(Head,-1);
	for (int i=1;i<=n;i++) UFS[i]=i;
	C[0][0]=1;
	for (int i=1;i<=n+5;i++)
	{
		C[i][0]=1;
		for (int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mod;
	}
	for (int i=1;i<=m;i++)
	{
		int u,v;char ch;scanf("%d %c %d",&u,&ch,&v);
		Inputu[i]=u;Inputv[i]=v;Inputopt[i]=(ch=='=');
		if (ch=='=') UFS[Find(u)]=Find(v);
	}
	for (int i=1;i<=n;i++) Id[i]=Find(i);

	//for (int i=1;i<=n;i++) cout<<Id[i]<<" ";cout<<endl;
	
	for (int i=1;i<=m;i++) Inputu[i]=Id[Inputu[i]],Inputv[i]=Id[Inputv[i]];
	for (int i=1;i<=n;i++) UFS[i]=i;

	for (int i=1;i<=m;i++)
		if (Inputopt[i]==0)
		{
			if (Find(Inputu[i])==Find(Inputv[i])){
				printf("0\n");return 0;
			}
			UFS[Find(Inputv[i])]=Find(Inputu[i]);
			Add_Edge(Inputu[i],Inputv[i]);
		}

	for (int i=1;i<=n;i++) if ((Id[i]==i)&&(UFS[i]==i)) Add_Edge(n+1,i);

	dfs(n+1);
	int Ans=0;
	for (int i=1;i<=Size[n+1];i++) Ans=(Ans+F[n+1][i])%Mod;
	printf("%d\n",Ans);
	return 0;
}

int Find(int u)
{
	if (UFS[u]!=u) UFS[u]=Find(UFS[u]);
	return UFS[u];
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs(int u)
{
	Size[u]=1;F[u][1]=1;
	for (int e=Head[u];e!=-1;e=Next[e])
	{
		int v=V[e];dfs(v);
		for (int i=1;i<=Size[u]+Size[v];i++)
			for (int j=1;j<=Size[u];j++)
				for (int k=1;k<=Size[v];k++)
					if ((k-(i-j))>=0) G[i]=(G[i]+1ll*F[u][j]*F[v][k]%Mod*C[i-1][j-1]%Mod*C[j-1][k-(i-j)]%Mod)%Mod;
		Size[u]+=Size[v];
		for (int i=1;i<=Size[u];i++) F[u][i]=G[i],G[i]=0;
	}
	return;
}
