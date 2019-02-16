#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010;
const int maxM=maxN<<1;
const int Mod=1e9+7;
const int inf=2147483647;

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],W[maxM];
int F[maxN][maxN],G[maxN],Size[maxN],Pre[maxN][maxN],Suf[maxN][maxN];
int C[maxN][maxN];

void Add_Edge(int u,int v,int w);
void dfs(int u,int fa);

int main()
{
	int TTT;scanf("%d",&TTT);

	C[0][0]=1;
	for (int i=1;i<maxN;i++)
	{
		C[i][0]=1;
		for (int j=1;j<=i;j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mod;
	}
	
	while (TTT--)
	{
		edgecnt=0;mem(Head,-1);mem(F,0);mem(Size,0);mem(G,0);mem(Pre,0);mem(Suf,0);
		scanf("%d",&n);
		for (int i=1;i<n;i++)
		{
			int u,v;char ch;scanf("%d %c %d",&u,&ch,&v);u++;v++;
			Add_Edge(u,v,ch=='>');
			Add_Edge(v,u,ch=='<');
		}
		dfs(1,0);

		printf("%d\n",Pre[1][n]);
	}

	return 0;
}

void Add_Edge(int u,int v,int w){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;W[edgecnt]=w;
	return;
}

void dfs(int u,int fa){
	Size[u]=1;F[u][1]=1;
	for (int e=Head[u];e!=-1;e=Next[e])
		if (V[e]!=fa)
		{
			dfs(V[e],u);
			for (int i=1;i<=Size[u];i++)
				for (int j=1;j<=Size[V[e]];j++)
					if (W[e]==0)
						G[i+j-1]=(G[i+j-1]+1ll*C[i+j-2][i-1]*C[Size[u]+Size[V[e]]-i-j+1][Size[u]-i]%Mod*F[u][i]%Mod*Suf[V[e]][j]%Mod)%Mod;
					else
						G[i+j]=(G[i+j]+1ll*C[i+j-1][i-1]*C[Size[u]+Size[V[e]]-i-j][Size[u]-i]%Mod*F[u][i]%Mod*Pre[V[e]][j]%Mod)%Mod;
			Size[u]+=Size[V[e]];
			for (int i=1;i<=Size[u];i++) F[u][i]=G[i],G[i]=0;
		}
	for (int i=1;i<=Size[u];i++) Pre[u][i]=(Pre[u][i-1]+F[u][i])%Mod;
	for (int i=Size[u];i>=1;i--) Suf[u][i]=(Suf[u][i+1]+F[u][i])%Mod;
	return;
}
