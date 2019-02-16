#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1011;
const int inf=2147483647;

int n,m,e;
int cnt=0,Head[maxN],Next[maxN*maxN],V[maxN*maxN];
int Match[maxN];
bool vis[maxN];

bool Hungary(int u);

int main()
{
    mem(Match,-1);mem(Head,-1);
    scanf("%d%d%d",&n,&m,&e);
    for (int i=1;i<=e;i++)
    {
	int u,v;
	scanf("%d%d",&u,&v);
	if ((u>n)||(v>m)) continue;
	cnt++;Next[cnt]=Head[u];Head[u]=cnt;V[cnt]=v;
    }
    int Ans=0;
    for (int i=1;i<=n;i++)
    {
	mem(vis,0);
	if (Hungary(i))
	    Ans++;
    }
    printf("%d\n",Ans);
    return 0;
}

bool Hungary(int u)
{
    for (int i=Head[u];i!=-1;i=Next[i])
    {
	int v=V[i];
	if (vis[v]) continue;
	vis[v]=1;
	if ((Match[v]==-1)||(Hungary(Match[v])))
	{
	    Match[v]=u;
	    return 1;
	}
    }
    return 0;
}
