#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=5000;
const int maxM=maxN*2;
const ld eps=1e-8;
const int inf=2147483647;

int n,K;
int P[maxN],S[maxN];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM],Size[maxN],SS[maxN];
ld F[maxN][maxN],G[maxN];

void Add_Edge(int u,int v);
void dfs(int u);
ld Calc(int u,ld p);

int main()
{
	//freopen("3.in","r",stdin);
	mem(Head,-1);
	scanf("%d%d",&K,&n);
	ld L=inf,R=0,Ans;
	for (int i=1;i<=n;i++)
	{
		int fa;
		scanf("%d%d%d",&S[i],&P[i],&fa);
		Add_Edge(fa,i);
		L=min(L,(ld)1.0*P[i]/S[i]);R=max(R,(ld)1.0*P[i]/S[i]);
	}

	dfs(0);

	L-=eps*2.0;R+=eps*2.0;
	do
	{
		//cout<<"("<<L<<","<<R<<")"<<endl;
		ld mid=(L+R)/2.0;
		if (Calc(0,mid)>=0) Ans=mid,L=mid+eps;
		else R=mid-eps;
	}
	while (L+eps<=R);

	printf("%.3LF\n",Ans);
	return 0;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

void dfs(int u)
{
	SS[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
	{
		dfs(V[i]);
		SS[u]+=SS[V[i]];
	}
	return;
}

ld Calc(int u,ld p)
{
	//cout<<"In:"<<u<<endl;
	Size[u]=1;F[u][1]=(ld)P[u]-(ld)1.0*S[u]*p;
	for (int i=2;i<=SS[u];i++) F[u][i]=-inf;
	for (int i=Head[u];i!=-1;i=Next[i])
	{
		Calc(V[i],p);
		for (int j=1;j<=Size[u]+Size[V[i]];j++) G[j]=-inf;
		for (int j=1;j<=Size[u];j++)
			for (int k=1;(k<=Size[V[i]])&&(j+k<=K+1);k++)
				G[j+k]=max(G[j+k],F[u][j]+F[V[i]][k]);
		Size[u]+=Size[V[i]];
		for (int j=1;j<=Size[u];j++) F[u][j]=max(F[u][j],G[j]);
	}
	//cout<<u<<" "<<Size[u]<<endl;
	//for (int i=1;i<=Size[u];i++) cout<<F[u][i]<<" ";cout<<endl;
	//cout<<"Out:"<<u<<" "<<Size[u]<<endl;
	return F[u][K+1];
}

