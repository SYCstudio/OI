#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=300;
const int inf=147483647;

class Node
{
public:
    int w,id;
};

bool operator < (Node A,Node B) {return A.w<B.w;}

int n,m;
int Map[maxN][maxN];
int Ans[maxN][maxN];
int NW[maxN];
Node N[maxN];

int main()
{
    int Q;
    scanf("%d%d%d",&n,&m,&Q);
    for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) Map[i][j]=(i==j)?(0):inf,Ans[i][j]=(i==j)?(0):inf;
    for (int i=1;i<=n;i++)
    {
		scanf("%d",&N[i].w);
		N[i].id=i;
		NW[i]=N[i].w;
    }
    for (int i=1;i<=m;i++)
    {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		Map[u][v]=Map[v][u]=min(Map[u][v],w);
    }
    sort(&N[1],&N[n+1]);
    for (int k=1;k<=n;k++)
    {
		int v=N[k].id;
		for (int i=1;i<=n;i++)
			if (i!=v)
				for (int j=1;j<=n;j++)
					if ((i!=j)&&(j!=v))
					{
						Map[i][j]=Map[j][i]=min(Map[i][j],Map[i][v]+Map[v][j]);
						Ans[i][j]=min(Ans[i][j],Map[i][j]+max(NW[v],max(NW[i],NW[j])));
					}
    }
    while (Q--)
    {
		int u,v;
		scanf("%d%d",&u,&v);
		printf("%d\n",Ans[u][v]);
    }
    return 0;
}
