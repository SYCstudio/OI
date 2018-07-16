#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=505000;
const int maxM=1010000*3;
const int Mod=998244353;
const int inf=2147483647;

int n,m;
int edgecnt=-1,Head[maxN],Next[maxM],V[maxM];
int dfncnt,dfn[maxN],low[maxN],top,St[maxM],NodeW[maxN];
bool ink[maxN],vis[maxN],Fob[maxM];
int F[maxN],G[maxN];

void Add_Edge(int u,int v);
void dfs_check(int u,int fa);
void tarjan(int u,int fa);
void dfs_dp(int u,int fa);

int main()
{
	int TTT;scanf("%d",&TTT);
	G[0]=G[1]=1;for (int i=2;i<maxN;i++) G[i]=(G[i-1]+1ll*G[i-2]*(i-1)%Mod)%Mod;
	
	while (TTT--)
	{
		edgecnt=-1;
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++) NodeW[i]=0,ink[i]=vis[i]=0,Head[i]=-1;
		for (int i=1;i<=m;i++)
		{
			int u,v;scanf("%d%d",&u,&v);
			Add_Edge(u,v);
		}

		dfs_check(1,1);
		//cout<<"check finish"<<endl;

		bool flag=1;
		for (int i=1;i<=n;i++)
			if (NodeW[i]>=2){
				flag=0;break;
			}
		if (flag==0){
			printf("0\n");continue;
		}

		dfncnt=0;top=0;for (int i=1;i<=n;i++) ink[i]=dfn[i]=0;
		tarjan(1,0);
		//cout<<"tarjan fihish"<<endl;

		for (int i=1;i<=n;i++) vis[i]=0;
		int Ans=1;
		for (int i=1;i<=n;i++)
			if (vis[i]==0){
				dfs_dp(i,i);
				Ans=1ll*Ans*F[i]%Mod;
			}
		printf("%d\n",Ans);
	}
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;Fob[edgecnt]=0;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;Fob[edgecnt]=0;
	return;
}

void dfs_check(int u,int fa){
	vis[u]=ink[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			if (vis[V[i]]==0){
				dfs_check(V[i],u);NodeW[u]+=NodeW[V[i]];
			}
			else if (ink[V[i]]) NodeW[u]++,NodeW[V[i]]--;
		}
	ink[u]=0;return;
}

void tarjan(int u,int fa)
{
	//cout<<"tarjan:"<<u<<endl;
	dfn[u]=low[u]=++dfncnt;ink[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa)
		{
			int v=V[i];
			if (dfn[v]==0){
				St[++top]=i;
				tarjan(v,u);
				low[u]=min(low[u],low[v]);
				if (low[v]==dfn[u])
				{
					int w;
					do
					{
						w=St[top--];
						Fob[w]=Fob[w^1]=1;
					}
					while (w!=i);
				}
			}
			else if (ink[V[i]]) low[u]=min(low[u],dfn[V[i]]),St[++top]=i;
		}
	ink[u]=0;
	if ((low[u]==dfn[u])&&(top)) top--;
	//cout<<"t "<<u<<endl;
	return;
}

void dfs_dp(int u,int fa)
{
	F[u]=1;int son=0;vis[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
		if ((V[i]!=fa)&&(Fob[i]==0))
		{
			dfs_dp(V[i],u);son++;
			F[u]=1ll*F[u]*F[V[i]]%Mod;
		}
	if (u!=fa) F[u]=1ll*F[u]*G[son+1]%Mod;
	else F[u]=1ll*F[u]*G[son]%Mod;
}

