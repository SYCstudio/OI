#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101;
const int Mod=1e9+7;
const int inf=2147483647;

int n;
char Input[maxN];
int edgecnt,Head[maxN],Next[maxN],V[maxN],Opt[maxN];
int C[maxN][maxN];
int Size[maxN],F[maxN][maxN],G[maxN],Pre[maxN][maxN],Suf[maxN][maxN];

void Add_Edge(int u,int v,int w);
void dfs(int u);

int main()
{
	mem(Head,-1);
	scanf("%d",&n);
	scanf("%s",Input+2);
	for (int i=2;i<=n;i++)
		if (Input[i]=='<') Add_Edge(i/2,i,1);
		else Add_Edge(i/2,i,2);

	C[0][0]=1;
	for (int i=1;i<=n;i++)
	{
		C[i][0]=1;
		for (int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mod;
	}

	dfs(1);
	int Ans=0;
	for (int i=1;i<=n;i++) Ans=(Ans+F[1][i])%Mod;
	printf("%d\n",Ans);
	return 0;
}

void Add_Edge(int u,int v,int w){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;Opt[edgecnt]=w;
	return;
}

void dfs(int u)
{
	Size[u]=1;F[u][1]=1;
	for (int e=Head[u];e!=-1;e=Next[e])
	{
		dfs(V[e]);
		for (int i=1;i<=Size[u];i++)
			for (int j=1;j<=Size[V[e]];j++)
				if (Opt[e]==1)
					G[i+j-1]=(G[i+j-1]+1ll*C[i+j-2][i-1]*C[Size[u]+Size[V[e]]-(i+j-1)][Size[u]-i]%Mod*F[u][i]%Mod*Suf[V[e]][j]%Mod)%Mod;
				else
					G[i+j]=(G[i+j]+1ll*C[i+j-1][i-1]*C[Size[u]+Size[V[e]]-i-j][Size[u]-i]%Mod*F[u][i]%Mod*Pre[V[e]][j]%Mod)%Mod;
		Size[u]+=Size[V[e]];
		for (int i=1;i<=Size[u];i++) F[u][i]=G[i],G[i]=0;
	}
	for (int i=1;i<=Size[u];i++) Pre[u][i]=(Pre[u][i-1]+F[u][i])%Mod;
	for (int i=Size[u];i>=1;i--) Suf[u][i]=(Suf[u][i+1]+F[u][i])%Mod;
	//cout<<u<<" "<<Size[u]<<endl;
	//for (int i=1;i<=Size[u];i++) cout<<F[u][i]<<" ";cout<<endl;
	return;
}
