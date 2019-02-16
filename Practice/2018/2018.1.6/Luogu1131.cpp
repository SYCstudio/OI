#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=500010;
const int maxM=maxN*2;
const int inf=2147483647;

int n,S;
ll Ans=0;
int cnt=0,Head[maxN],Next[maxM],V[maxM];
ll W[maxM];
ll Time[maxN];

void Add_Edge(int u,int v,int w);
void dfs(int u,int father);

int main()
{
    mem(Head,-1);
    scanf("%d%d",&n,&S);
    for (int i=1;i<n;i++)
    {
	int u,v,w;scanf("%d%d%d",&u,&v,&w);
	Add_Edge(u,v,w);Add_Edge(v,u,w);
    }
    dfs(S,0);
    printf("%lld\n",Ans);
    return 0;
}

void Add_Edge(int u,int v,int w)
{
    cnt++;Next[cnt]=Head[u];Head[u]=cnt;V[cnt]=v;W[cnt]=w;
    return;
}

void dfs(int u,int father)
{
    Time[u]=0;
    for (int i=Head[u];i!=-1;i=Next[i])
    {
	if (V[i]==father) continue;
	dfs(V[i],u);
	Time[u]=max(Time[u],Time[V[i]]+W[i]);
    }
    for (int i=Head[u];i!=-1;i=Next[i])
    {
	if (V[i]==father) continue;
	Ans+=(ll)Time[u]-(Time[V[i]]+W[i]);
    }
    return;
}
