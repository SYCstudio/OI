#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
 
#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
 
const int maxN=160*2;
const int maxM=maxN*maxN*10;
const int inf=2147483647;
 
int n,m,K;

namespace Flow
{
    class Edge
    {
    public:
        int u,v,flow,w;
    };
 
    int S,T;
    int edgecnt=-1,Head[maxN],Next[maxM];
    Edge E[maxM];
    int Dist[maxN],Flow[maxN],Path[maxN];
    queue<int> Queue;
    bool inqueue[maxN];
     
    void Add(int u,int v,int flow,int w)
    {
        edgecnt++;Next[edgecnt]=Head[u];Head[u]=edgecnt;
        E[edgecnt].u=u;E[edgecnt].v=v;E[edgecnt].w=w;E[edgecnt].flow=flow;
        return;
    }
     
    void Add_Edge(int u,int v,int flow,int w)
    {
        Add(u,v,flow,w);Add(v,u,0,-w);
        return;
    }
 
    bool Spfa()
    {
        mem(Dist,-1);
        Dist[S]=0;Flow[S]=inf;inqueue[S]=1;
        while (!Queue.empty()) Queue.pop();
        Queue.push(S);
        do
        {
            int u=Queue.front();Queue.pop();
            for (int i=Head[u];i!=-1;i=Next[i])
            {
                //cout<<u<<"->"<<E[i].v<<" "<<E[i].flow<<endl;
                if ((E[i].flow>0)&&((Dist[E[i].v]==-1)||(Dist[E[i].v]>Dist[u]+E[i].w)))
                {
                    //cout<<u<<"->"<<E[i].v<<endl;
                    Dist[E[i].v]=Dist[u]+E[i].w;Path[E[i].v]=i;Flow[E[i].v]=min(Flow[u],E[i].flow);
                    if (inqueue[E[i].v]==0){
                        inqueue[E[i].v]=1;Queue.push(E[i].v);
                    }
                }
            }
            inqueue[u]=0;
        }
        while (!Queue.empty());
        //for (int i=1;i<=T;i++) cout<<Dist[i]<<" ";cout<<endl;
        if (Dist[T]==-1) return 0;
        return 1;
    }
     
    int MaxFlow()
    {
        int Ret=0;
        while (Spfa())
        {
            Ret+=Flow[T]*Dist[T];
            int now=T;
            while (now!=S)
            {
                E[Path[now]].flow-=Flow[T];
                E[Path[now]^1].flow+=Flow[T];
                now=E[Path[now]].u;
            }
        }
        return Ret;
    }
}

namespace Floyed
{
    int Dist[maxN][maxN];
    void Add_Edge(int u,int v,int w)
    {
        if ((Dist[u][v]==-1)||(Dist[u][v]>w)) Dist[u][v]=Dist[v][u]=w;
        return;
    }
    void Floyed()
    {
        for (int k=1;k<=n;k++)
		{
            for (int i=1;i<=n;i++)
                if ((i!=k)&&(Dist[i][k]!=-1))
                    for (int j=1;j<=n;j++)
                        if ((i!=j)&&(k!=j)&&(Dist[k][j]!=-1))
                            if ((Dist[i][j]==-1)||(Dist[i][j]>Dist[i][k]+Dist[k][j]))
                                Dist[i][j]=Dist[j][i]=Dist[i][k]+Dist[k][j];
			for (int i=1;i<k;i++) if (Dist[i][k]!=-1) Flow::Add_Edge(i+n,k,inf,Dist[i][k]);
		}
        return;
    }
}

int main()
{
	//freopen("in.in","r",stdin);freopen("out.out","w",stdout);
    mem(Floyed::Dist,-1);mem(Flow::Head,-1);
    scanf("%d%d%d",&n,&m,&K);n++;
    for (int i=1;i<=m;i++)
    {
        int u,v,w;scanf("%d%d%d",&u,&v,&w);u++;v++;
        Floyed::Add_Edge(u,v,w);
    }
    Floyed::Floyed();
    /*
    for (int i=1;i<=n;i++)
        for (int j=i+1;j<=n;j++)
            //if (Floyed::Dist[i][j]!=-1)
                cout<<i<<"->"<<j<<" "<<Floyed::Dist[i][j]<<endl;
    //*/
    Flow::S=n*2+1;Flow::T=Flow::S+1;
	/*
    for (int i=1;i<=n;i++)
        for (int j=i+1;j<=n;j++)
            if (Floyed::Dist[i][j]!=-1)
                Flow::Add_Edge(i+n,j,inf,Floyed::Dist[i][j]);
	//*/
    for (int i=2;i<=n;i++) Flow::Add_Edge(i,Flow::T,1,0),Flow::Add_Edge(Flow::S,i+n,1,0);
    Flow::Add_Edge(Flow::S,n+1,K,0);
    printf("%d\n",Flow::MaxFlow());
    return 0;
}
