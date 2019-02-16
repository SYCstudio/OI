#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ull unsigned long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=maxN*2;
const ull base=20729;
const int inf=2147483647;

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
ull W[maxN];

void dfs(int u);

int main()
{
	mem(Head,-1);
	scanf("%d",&n);
	for (int i=1;i<n;i++)
	{
		int a,b;scanf("%d%d",&a,&b);
		edgecnt++;Next[edgecnt]=Head[a];Head[a]=edgecnt;V[edgecnt]=b;
	}
	dfs(1);
	sort(&W[1],&W[n+1]);
	//for (int i=1;i<=n;i++) cout<<W[i]<<" ";cout<<endl;
	ll Ans=0;
	W[++n]=inf;
	for (int i=1,j=0;i<=n;i++) if (W[i]!=W[j]) Ans=Ans+1ll*(ll)(i-1-j+1)*(ll)(i-1-j)/2,j=i;
	printf("%lld\n",Ans);
	return 0;
}

void dfs(int u)
{
	W[u]=1;
	for (int i=Head[u];i!=-1;i=Next[i])
	{
		dfs(V[i]);
		W[u]=W[u]+W[V[i]]*base;
	}
	return;
}
