#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010000;
const int maxM=maxN<<1;

int n;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Sz[maxN],Cnt[maxN];

void Add_Edge(int u,int v);
void dfs(int u,int fa);

int main()
{
	scanf("%d",&n);
	mem(Head,-1);
	for (int i=1; i<n; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	dfs(1,1);

	for (int i=1; i<=n; i++)
		if (n%i==0)
			for (int j=i+i; j<=n; j+=i)
				Cnt[i]+=Cnt[j];

	int Ans=0;
	for (int i=1; i<=n; i++)
		if (n%i==0&&Cnt[i]==n/i) ++Ans;
	printf("%d\n",Ans);
	return 0;
}

void Add_Edge(int u,int v)
{
	Next[++edgecnt]=Head[u];
	Head[u]=edgecnt;
	V[edgecnt]=v;
	return;
}
void dfs(int u,int fa)
{
	Sz[u]=1;
	for (int i=Head[u]; i!=-1; i=Next[i])
		if (V[i]!=fa) dfs(V[i],u),Sz[u]+=Sz[V[i]];
	++Cnt[Sz[u]];
	return;
}
/*
6
1 2
2 3
2 4
4 5
5 6
//*/
