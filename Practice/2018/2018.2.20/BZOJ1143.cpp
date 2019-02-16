#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=111;
const int maxM=1011;
const int inf=2147483647;

int n,m,dep;
int Map[maxN][maxN];
int edgecnt=0,Head[maxN*2],Next[maxN*maxN*2],V[maxN*maxN*2];
int Match[maxN*2];
int vis[maxN*2];

void Add_Edge(int u,int v);
bool Hungary(int u);

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for (int i=1;i<=m;i++){
		int u,v;cin>>u>>v;Map[u][v]=1;
	}
	for (int k=1;k<=n;k++)
		for (int i=1;i<=n;i++)
			if (Map[i][k])
				for (int j=1;j<=n;j++)
					if (Map[k][j])
						Map[i][j]|=(Map[i][k]&Map[k][j]);
	mem(Match,-1);mem(Head,-1);
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) if (Map[i][j]) Add_Edge(i,j+n);
	int cnt=0;
	for (int i=1;i<=n;i++) dep++,cnt+=Hungary(i);
	printf("%d\n",n-cnt);
	return 0;
}

void Add_Edge(int u,int v)
{
	edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
	return;
}

bool Hungary(int u)
{
	for (int i=Head[u];i!=-1;i=Next[i])
		if (vis[V[i]]!=dep)
		{
			vis[V[i]]=dep;
			if ((Match[V[i]]==-1)||(Hungary(Match[V[i]])))
			{
				Match[V[i]]=u;return 1;
			}
		}
	return 0;
}
