#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define ll long long

const int maxN=100010;
const int inf=2147483647;
const ll INF=1e15;

class Edge
{
public:
    ll v,w,nex;
};

int n;
ll Ans=INF;
int cnt=0,Head[maxN];
Edge E[maxN*2];
ll Size[maxN],W[maxN],NodeC[maxN];

void Add_Edge(int u,int v,int w);
void dfs1(int u,int father);
void dfs2(int u,int father,ll nowW,ll size);

int main()
{
    mem(Head,-1);
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%lld",&NodeC[i]);
    for (int i=1;i<n;i++)
    {
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		Add_Edge(u,v,w);Add_Edge(v,u,w);
    }
    dfs1(1,1);
    /*
	  for (int i=1;i<=n;i++)
	  cout<<W[i]<<" "<<Size[i]<<endl;
    //*/
    dfs2(1,1,0,0);
    printf("%lld\n",Ans);
    return 0;
}

void Add_Edge(int u,int v,int w)
{
    cnt++;E[cnt].nex=Head[u];Head[u]=cnt;
    E[cnt].v=v;E[cnt].w=w;
    return;
}

void dfs1(int u,int father)
{
    Size[u]=NodeC[u];
    for (int i=Head[u];i!=-1;i=E[i].nex)
    {
		int v=E[i].v;if (v==father) continue;
		dfs1(v,u);
		Size[u]+=Size[v];
		W[u]+=W[v]+Size[v]*E[i].w;
    }
    return;
}

void dfs2(int u,int father,ll nowW,ll size)
{
    //cout<<u<<" "<<nowW<<" "<<W[u]<<" "<<nowW+W[u]<<endl;
    Ans=min(Ans,nowW+W[u]);
    for (int i=Head[u];i!=-1;i=E[i].nex)
    {
		int v=E[i].v;if (v==father) continue;
		dfs2(v,u,nowW+W[u]-W[v]-Size[v]*E[i].w+(size+Size[u]-Size[v])*E[i].w,size+Size[u]-Size[v]);
    }
    return;
}
