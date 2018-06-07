#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=6000;
const int maxM=maxN*2;
const int inf=2147483647;

class Pos
{
public:
	int x,y,z;
};

int a,b,c,nodecnt,nowdepth=0;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int vis[maxN],Match[maxN];
Pos P[maxN];

void Add_Edge(int u,int v);
int dfs(int u);

int main()
{
	int T;scanf("%d",&T);
	while (T--)
	{
		nodecnt=0;
		scanf("%d%d%d",&a,&b,&c);
		for (int i=1;i<=a;i++) for (int j=1;j<=b;j++) for (int k=1;k<=c;k++)
													  {
														  int opt;scanf("%d",&opt);
														  if (opt==1) P[++nodecnt]=(Pos){i,j,k};
													  }
		if (a>b){
			swap(a,b);for (int i=1;i<=nodecnt;i++) swap(P[i].x,P[i].y);
		}
		if (a>c){
			swap(a,c);for (int i=1;i<=nodecnt;i++) swap(P[i].x,P[i].z);
		}
		if (b>c){
			swap(b,c);for (int i=1;i<=nodecnt;i++) swap(P[i].y,P[i].z);
		}
		int Ans=inf;
		for (int S=0;S<(1<<a);S++)
		{
			edgecnt=0;for (int i=1;i<=c;i++) Head[i]=Match[i]=-1;
			int ret=0;
			for (int i=1;i<=a;i++) if ((S&(1<<(i-1)))!=0) ret++;
			if (ret>=Ans) continue;
			for (int i=1;i<=nodecnt;i++) if ((S&(1<<(P[i].x-1)))==0) Add_Edge(P[i].y,P[i].z);
			for (int i=1;i<=c;i++)
			{
				nowdepth++;
				ret+=dfs(i);
				if (ret>=Ans) break;
			}
			Ans=min(Ans,ret);
		}
		printf("%d\n",Ans);
	}
	return 0;
}

int dfs(int u)
{
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]!=nowdepth)
		{
			vis[V[i]]=nowdepth;
			if ((Match[V[i]]==-1)||(dfs(Match[V[i]])))
			{
				Match[V[i]]=u;return 1;
			}
		}
	return 0;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}
