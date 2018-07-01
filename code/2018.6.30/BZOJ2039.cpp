#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register

const int maxN=1010;
const int maxM=maxN*maxN*2;
const int inf=2147483647;
const ll INF=1e18;

class Edge
{
public:
    int v;
    ll flow;
};

int n;
int S,T;
int edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
int Depth[maxN],Q[maxN],cur[maxN];

int read();
void Add_Edge(RG int u,RG int v,RG ll flow,RG int opt);
bool Bfs();
ll dfs(RG int u,RG ll flow);

int main()
{
    mem(Head,-1);
    n=read();//scanf("%d",&n);
    S=n+1;T=n+2;
	RG int val;
    for (RG int i=1;i<=n;++i)
    {
        val=read();//scanf("%d",&val);
        Add_Edge(S,i,val,0);
    }

    RG ll Ans=0,sum=0;
    for (int i=1;i<=n;++i)
    {
		sum=0;
        for (RG int j=1;j<=n;++j)
        {
            val=read();//scanf("%d",&val);
			Ans+=(ll)val;sum+=val;
            if (i<j) Add_Edge(i,j,1ll*val*2ll,1);
        }
        Add_Edge(i,T,sum,0);
    }

    /*
    for (int i=1;i<=T;i++)
    {
        for (int j=Head[i];j!=-1;j=Next[j])
            if (E[j].flow) cout<<i<<" -> "<<E[j].v<<" "<<E[j].flow<<endl;
    }

    cout<<Ans<<endl;
    //*/

    while (Bfs())
    {
        for (RG int i=1;i<=T;++i) cur[i]=Head[i];
        while (ll di=dfs(S,INF)) Ans-=di/*,cout<<":"<<di<<endl*/;
        /*
        for (int i=1;i<=T;i++)
        {
            for (int j=Head[i];j!=-1;j=Next[j])
                if (E[j].flow) cout<<i<<" -> "<<E[j].v<<" "<<E[j].flow<<endl;
        }
        //*/
    }

    printf("%lld\n",Ans);
    return 0;
}

int read()
{
	RG char ch=getchar();RG int x=0;
	while ((ch<'0')||(ch>'9')) ch=getchar();
	while ((ch>='0')&&(ch<='9')) x=x*10+ch-'0',ch=getchar();
	return x;
}

void Add_Edge(RG int u,RG int v,RG ll flow,RG int opt)
{
    Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,flow});
    Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){u,flow*opt});
    return;
}

bool Bfs()
{
    mem(Depth,-1);Q[1]=S;Depth[S]=1;
    RG int h=1,t=0;
    do
        for (RG int u=Q[++t],i=Head[u];i!=-1;i=Next[i])
            if ((E[i].flow>0)&&(Depth[E[i].v]==-1))
                Depth[Q[++h]=E[i].v]=Depth[u]+1;
    while (t!=h);
    return Depth[T]!=-1;
}

ll dfs(RG int u,RG ll flow)
{
    if (u==T) return flow;
    for (RG int &i=cur[u];i!=-1;i=Next[i])
        if ((E[i].flow>0)&&(Depth[E[i].v]==Depth[u]+1))
            if (ll di=dfs(E[i].v,min(flow,E[i].flow))){
                E[i].flow-=di;E[i^1].flow+=di;return di;
            }
    return 0;
}
