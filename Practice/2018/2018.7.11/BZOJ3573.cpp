#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=501000;
const int maxM=maxN<<1;
const ld eps=1e-6;
const int inf=2147483647;

int n;
int edgecnt,Head[maxN],Next[maxM],V[maxM],D[maxN];
int Val[maxN];
ld R[maxN];

void Add_Edge(int u,int v);
void dfs(int u,int fa);

int main()
{
	mem(Head,-1);
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&Val[i]);
	for (int i=1;i<n;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);
	}
	for (int i=2;i<=n;i++) D[i]--;
	R[1]=log(1);
	dfs(1,1);

	for (int i=1;i<=n;i++) R[i]=R[i]+log(Val[i]);
	sort(&R[1],&R[n+1]);

	int mx=0,cnt=1;
	for (int i=2;i<=n;i++)
	{
		if (fabs(R[i]-R[i-1])<eps) cnt++;
		else mx=max(mx,cnt),cnt=1;
	}
	mx=max(mx,cnt);

	printf("%d\n",n-mx);
	return 0;
}

void Add_Edge(int u,int v){
	Next[++edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	Next[++edgecnt]=Head[v];Head[v]=edgecnt;V[edgecnt]=u;
	D[u]++;D[v]++;return;
}

void dfs(int u,int fa)
{
	for (int i=Head[u];i!=-1;i=Next[i])
		if (V[i]!=fa){
			R[V[i]]=R[u]+log(D[u]);
			dfs(V[i],u);
		}
	return;
}
