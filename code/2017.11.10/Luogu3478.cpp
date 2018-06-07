#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register
#define IL inline

const int maxN=1000100;
const int inf=2147483647;

int n;
ll cnt=0,Head[maxN],Next[maxN*2],V[maxN*2];
ll F[maxN],Depth[maxN],Size[maxN];
ll Ans=0,id;

void Add_Edge(int u,int v);
void dfs1(int u,int father,ll depth);
void dfs2(int u,int father,ll sum,ll sz);

int main()
{
    mem(Head,-1);
    scanf("%d",&n);
    for (int i=1;i<n;i++)
    {
		int u,v;scanf("%d%d",&u,&v);
		Add_Edge(u,v);Add_Edge(v,u);
    }
    dfs1(1,1,0);
    //for (int i=1;i<=n;i++) cout<<F[i]<<" ";
    //cout<<endl;
    dfs2(1,1,0,0);
    printf("%lld\n",id);
    return 0;
}

void Add_Edge(int u,int v)
{
    cnt++;Next[cnt]=Head[u];Head[u]=cnt;V[cnt]=v;
    return;
}

void dfs1(int u,int father,ll depth)
{
    Depth[u]=depth;
    F[u]=depth;
    Size[u]=1;
    for (RG int i=Head[u];i!=-1;i=Next[i])
    {
		RG int v=V[i];if (v==father) continue;
		dfs1(v,u,depth+1);
		F[u]+=F[v];
		Size[u]+=Size[v];
    }
    return;
}

void dfs2(int u,int father,ll sum,ll sz)
{
    //cout<<u<<" "<<sum+F[u]-Size[u]*Depth[u]<<endl;
    if ((Ans<sum+(ll)F[u]-(ll)Size[u]*Depth[u])||((Ans==sum+(ll)F[u]-(ll)Size[u]*Depth[u])&&(id>u)))
    {
		Ans=sum+F[u]-Size[u]*Depth[u];id=u;
    }
    for (int i=Head[u];i!=-1;i=Next[i])
    {
		int v=V[i];if (v==father)continue;
		dfs2(v,u,(ll)sum+(ll)(F[u]-F[v])-(ll)Depth[u]*((ll)Size[u]-Size[v])+sz+Size[u]-Size[v],sz+Size[u]-Size[v]);
    }
    return;
}
