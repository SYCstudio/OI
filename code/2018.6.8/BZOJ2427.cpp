#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101;
const int maxM=510;
const int inf=2147483647;

int n,m;
int W[maxN],V[maxN];
int Cnt[maxN];

namespace G1
{
    int edgecnt=0,Head[maxN],Next[maxM],V[maxM],Fa[maxN];
    int dfncnt=0,dfn[maxN],low[maxN],idcnt,Id[maxN];
    int top,S[maxN];
    bool ink[maxN];

    void Add_Edge(int u,int v);
    void tarjan(int u);
}

namespace G2
{
    int edgecnt=0,Head[maxN],Next[maxM],V[maxM],Fa[maxN];
    int Sz[maxN],Val[maxN],D[maxN];
    int F[maxN][maxM],G[maxM];
	bool vis[maxN];

    void Add_Edge(int u,int v);
    void Do();
    void dfs(int u);
}

int main()
{
	//freopen("1.in","r",stdin);freopen("out","w",stdout);
    mem(G1::Head,-1);mem(G2::Head,-1);
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++) scanf("%d",&W[i]);
    for (int i=1;i<=n;i++) scanf("%d",&V[i]);
    for (int i=1;i<=n;i++)
    {
        int fa;scanf("%d",&fa);
        if (fa!=0) G1::Add_Edge(fa,i);
		G1::Fa[i]=fa;Cnt[i]++;
    }

	//for (int i=1;i<=n;i++) cout<<Cnt[i]<<" ";cout<<endl;

    for (int i=1;i<=n;i++)
        if (G1::dfn[i]==0) G1::tarjan(i);

	//cout<<G1::idcnt<<endl;

	for (int i=1;i<=n;i++)
		if (G1::Id[G1::Fa[i]]!=G1::Id[i]) G2::Fa[G1::Id[i]]=G1::Id[G1::Fa[i]];
	for (int i=1;i<=G1::idcnt;i++) G2::Add_Edge(G2::Fa[i],i);

    for (int i=1;i<=n;i++) G2::Sz[G1::Id[i]]+=W[i],G2::Val[G1::Id[i]]+=V[i];

    for (int i=1;i<=G1::idcnt;i++) if (G2::D[i]==0) G2::Add_Edge(0,i);

    G2::Do();

    int Ans=0;
    for (int i=1;i<=m;i++) Ans=max(Ans,G2::F[0][i]);
    printf("%d\n",Ans);

    return 0;
}

namespace G1
{
    void Add_Edge(int u,int v)
    {
        edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
        return;
    }

    void tarjan(int u)
    {
        dfn[u]=low[u]=++dfncnt;
        S[++top]=u;ink[u]=1;
        for (int i=Head[u];i!=-1;i=Next[i])
            //if (V[i]!=fa)
            {
                if (dfn[V[i]]==0){
                    tarjan(V[i]);low[u]=min(low[u],low[V[i]]);
                }
                else if (ink[V[i]]) low[u]=min(low[u],dfn[V[i]]);
            }
        if (dfn[u]==low[u])
        {
            idcnt++;int v;
            do v=S[top--],Id[v]=idcnt,ink[v]=0;
            while (v!=u);
        }
        return;
    }
}

namespace G2
{
    void Add_Edge(int u,int v)
    {
        D[v]++;
        edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;V[edgecnt]=v;
        return;
    }

    void Do()
    {
		/*
		int cnt=0;
		for (int i=0;i<=G1::idcnt;i++)
			for (int j=Head[i];j!=-1;j=Next[j])
				cout<<V[j]<<" ",cnt++;
		cout<<endl;
		cout<<"cnt:"<<cnt<<endl;
		//*/
		
        dfs(0);

		/*
		for (int i=1;i<=G1::idcnt;i++) cout<<Sz[i]<<" ";cout<<endl;
		for (int i=1;i<=G1::idcnt;i++) cout<<Val[i]<<" ";cout<<endl;
		for (int i=0;i<=G1::idcnt;i++)
		{
			cout<<i<<":"<<endl;
			for (int j=1;j<=m;j++)
				cout<<"["<<j<<"]"<<F[i][j]<<" ";
			cout<<endl<<endl;
		}
		//*/
        return;
    }

    void dfs(int u)
    {
		vis[u]=1;
		//cout<<"dfs:"<<u<<endl;
		if (Sz[u]>m) return;
        //if (Sz[u]<=m) F[u][Sz[u]]=Val[u];
        for (int e=Head[u];e!=-1;e=Next[e])
        {
			if (vis[V[e]]) continue;
            dfs(V[e]);
			for (int i=1;i<=m;i++) G[i]=F[u][i];
            for (int i=m;i>=1;i--)
                for (int j=0;j<=i;j++)
                    G[i]=max(G[i],F[u][i-j]+F[V[e]][j]);
			for (int i=1;i<=m;i++) F[u][i]=G[i];
        }
		for (int i=m-Sz[u];i>=0;i--) F[u][i+Sz[u]]=F[u][i]+Val[u];
		for (int i=Sz[u]-1;i>=0;i--) F[u][i]=0;
        return;
    }
}
