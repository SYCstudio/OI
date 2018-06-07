#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define ld double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register

const int maxN=750;
const int maxM=101000;
const ld eps=1e-4;
const int inf=2147483647;

int n,m,n1,m1;
ld Val[maxN];

int Input();

namespace Dij
{
    class Edge
    {
    public:
        int v,t,s;
    };
    
    int edgecnt=0,Head[maxN],Next[maxM],Degree[maxN],D[maxN],Q[maxN];
    Edge E[maxM];
    ld Dist[maxN];
    
    void Do();
    void Add_Edge(RG int u,RG int v,RG int t,RG int s);
    ld Calc(RG int T,RG ld k);
}

namespace MxFlow
{
    class Edge
    {
    public:
        int v;
        ld flow;
    };

    int S,T;
    int edgecnt=-1,Head[maxN],Next[maxM];
    Edge E[maxM];
    queue<int> Q;
    int Depth[maxN],cur[maxN];
    ld Ans=0;

    void Do();
    void Add_Edge(RG int u,RG int v,RG ld flow);
    bool Bfs();
    ld dfs(RG int u,RG ld flow);
}

int main()
{
	//freopen("9.in","r",stdin);
    mem(Dij::Head,-1);mem(MxFlow::Head,-1);
    n=Input();m=Input();//scanf("%d%d",&n,&m);
    for (RG int i=1;i<=m;i++)
    {
        RG int u=Input(),v=Input(),t=Input(),s=Input();//scanf("%d%d%d%d",&u,&v,&t,&s);
        Dij::Add_Edge(u,v,t,s);
    }
	m1=Input();n1=Input();
    Dij::Do();
	//return 0;
    //for (int i=1;i<=n;i++) cout<<Val[i]<<" ";cout<<endl;

    //scanf("%d%d",&m1,&n1);
    MxFlow::S=n1+1;MxFlow::T=n1+2;
    RG bool flag=1;
    for (RG int i=1;i<=m1;i++)
    {
        RG int u=Input(),v=Input();//scanf("%d%d",&u,&v);
        if ((Val[u]==inf)&&(Val[v]==inf)) flag=0;
        MxFlow::Add_Edge(u,v,inf);
    }
    if (flag==0){
        printf("-1\n");return 0;
    }
    for (RG int i=1;i<=n1;i++)
        if (i&1) MxFlow::Add_Edge(MxFlow::S,i,Val[i]);
        else MxFlow::Add_Edge(i,MxFlow::T,Val[i]);

    MxFlow::Do();

    printf("%.1lf\n",MxFlow::Ans);
    return 0;
}

int Input()
{
	char ch=getchar();
	while ((ch>'9')||(ch<'0')) ch=getchar();
	int x=0;
	while ((ch>='0')&&(ch<='9')) x=x*10+ch-48,ch=getchar();
	return x;
}

namespace Dij
{
    void Do()
    {
        RG ld L=inf,R=-inf;
        for (RG int i=1;i<=edgecnt;i++) L=min(L,(ld)1.0*E[i].t/(1.0*E[i].s)),R=max(R,(ld)1.0*E[i].t/(1.0*E[i].s));
        L-=eps;R+=eps;
        for (RG int i=1;i<=n1;i++)
        {
            RG ld l=L,r=R,Ans=inf;
            do
            {
                RG ld mid=(l+r)/2.0;
                if (Calc(i,mid)<=eps) Ans=mid,r=mid-eps;
                else l=mid+eps;
            }
            while (l+eps<=r);
            Val[i]=Ans;
        }
        Val[n]=0;
        return;
    }

    void Add_Edge(RG int u,RG int v,RG int t,RG int s)
    {
		Degree[v]++;
        edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,t,s});
        return;
    }

	ld Calc(RG int T,RG ld k)
	{
		RG int h=0,t=0;
		for (RG int i=1;i<=n;i++)
		{
			Dist[i]=inf;D[i]=Degree[i];
			if (D[i]==0) Q[++h]=i;
		}
		Dist[n]=0;
		do
		{
			RG int u=Q[++t];
			for (RG int i=Head[u];i!=-1;i=Next[i])
			{
				Dist[E[i].v]=min(Dist[E[i].v],Dist[u]+E[i].t-1.0*E[i].s*k);
				D[E[i].v]--;
				if (D[E[i].v]==0)
				{
					Q[++h]=E[i].v;
					if (E[i].v==T) return Dist[T];
				}
			}
		}
		while (t!=h);
		return Dist[T];
	}

	/*
    ld Calc(int T,ld k)
    {
        while (!H.empty()) H.pop();
        for (int i=1;i<=n;i++) Dist[i]=inf;
        Dist[n]=0;H.push((HData){n,0});
        //cout<<T<<" "<<k<<endl;
        do
        {
            int u=H.top().u;ld d=H.top().dist;H.pop();
            if (Dist[u]<d) continue;
            for (int i=Head[u];i!=-1;i=Next[i])
                if (Dist[E[i].v]>Dist[u]+E[i].t-1.0*E[i].s*k)
                {
                    Dist[E[i].v]=Dist[u]+E[i].t-1.0*E[i].s*k;
                    H.push((HData){E[i].v,Dist[E[i].v]});
                }
        }
        while (!H.empty());
        //cout<<T<<" "<<k<<" "<<Dist[T]<<endl;
        return Dist[T];
    }
	//*/
}

namespace MxFlow
{
    void Do()
    {
        while (Bfs())
        {
            for (RG int i=1;i<=T;i++) cur[i]=Head[i];
            while (ld di=dfs(S,inf)) Ans+=di;
        }
        return;
    }

    void Add_Edge(RG int u,RG int v,RG ld flow)
    {
        edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,flow});
        edgecnt++;Next[edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){u,0});
        return;
    }

    bool Bfs()
    {
        while (!Q.empty()) Q.pop();
        for (RG int i=1;i<=T;i++) Depth[i]=-1;//mem(Depth,-1);
		Depth[S]=1;
        Q.push(S);
        do
        {
            RG int u=Q.front();Q.pop();
            for (RG int i=Head[u];i!=-1;i=Next[i])
                if ((E[i].flow>eps)&&(Depth[E[i].v]==-1))
                {
                    Q.push(E[i].v);
                    Depth[E[i].v]=Depth[u]+1;
                }
        }
        while (!Q.empty());
        return Depth[T]!=-1;
    }

    ld dfs(RG int u,RG ld flow)
    {
        if (u==T) return flow;
        for (RG int &i=cur[u];i!=-1;i=Next[i])
            if ((E[i].flow>eps)&&(Depth[E[i].v]==Depth[u]+1))
            {
                RG ld di=dfs(E[i].v,min(flow,E[i].flow));
                if (di>eps)
                {
                    E[i].flow-=di;E[i^1].flow+=di;
                    return di;
                }
            }
        return 0;
    }
}
