#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define NAME "marshland"

const int maxMap=71;
const int maxN=maxMap*maxMap;
const int maxM=maxN*30;
const int inf=2147483647;

class Edge
{
public:
    int v,flow,w;
};

int n,m,K;
int Val[maxN][maxN];
int Id[maxN][maxN];
int S,T,edgecnt=-1,Head[maxN],Next[maxM];
Edge E[maxM];
bool fob[maxN][maxN];
int Dist[maxN],Flow[maxN],Path[maxN];
queue<int> Q;
bool inq[maxN];

void Add_Edge(int u,int v,int flow,int w);
bool spfa();

int main()
{
    //freopen(NAME".in","r",stdin);freopen(NAME".out","w",stdout);
    mem(Head,-1);
    scanf("%d%d%d",&n,&m,&K);
    int sum=0;
    for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) scanf("%d",&Val[i][j]),sum+=Val[i][j];
    for (int i=1;i<=K;i++)
    {
        int u,v;scanf("%d%d",&u,&v);
        fob[u][v]=1;
    }
    int idcnt=0;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++){
            Id[i][j]=++idcnt;
            if ((i+j)%2==1) idcnt++;
        }
    S=++idcnt;T=++idcnt;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            if (fob[i][j]) continue;
            else if ((i%2==1)&&(j%2==1))
            {
                Add_Edge(S,Id[i][j],1,0);
                if (i!=1) Add_Edge(Id[i][j],Id[i-1][j],1,0);
                if (i!=n) Add_Edge(Id[i][j],Id[i+1][j],1,0);
                if (j!=1) Add_Edge(Id[i][j],Id[i][j-1],1,0);
                if (j!=n) Add_Edge(Id[i][j],Id[i][j+1],1,0);
            }
            else if ((i+j)%2==1)
                Add_Edge(Id[i][j],Id[i][j]+1,1,Val[i][j]);
            else
            {
                Add_Edge(Id[i][j],T,1,0);
                if (i!=1) Add_Edge(Id[i-1][j]+1,Id[i][j],1,0);
                if (i!=n) Add_Edge(Id[i+1][j]+1,Id[i][j],1,0);
                if (j!=1) Add_Edge(Id[i][j-1]+1,Id[i][j],1,0);
                if (j!=n) Add_Edge(Id[i][j+1]+1,Id[i][j],1,0);
            }
    int mxflow=0,ans=0;
    while (spfa())
    {
        if (Dist[T]<0) break;
        mxflow+=Flow[T];ans+=Dist[T]*Flow[T];
        if (mxflow>=m) break;
        int now=T;
        while (now!=S){
            E[Path[now]].flow-=Flow[T];E[Path[now]^1].flow+=Flow[T];now=E[Path[now]^1].v;
        }
    }

    printf("%d\n",sum-ans);
    return 0;
}

void Add_Edge(int u,int v,int flow,int w)
{
    Next[++edgecnt]=Head[u];Head[u]=edgecnt;E[edgecnt]=((Edge){v,flow,w});
    Next[++edgecnt]=Head[v];Head[v]=edgecnt;E[edgecnt]=((Edge){u,0,-w});
    return;
}

bool spfa()
{
    while (!Q.empty()) Q.pop();mem(inq,0);
    for (int i=1;i<=T;i++) Dist[i]=-inf;Dist[S]=0;Flow[S]=inf;inq[S]=1;Q.push(S);
    do
    {
        int u=Q.front();Q.pop();
        for (int i=Head[u];i!=-1;i=Next[i])
            if ((E[i].flow>0)&&(Dist[E[i].v]<Dist[u]+E[i].w))
            {
                Dist[E[i].v]=Dist[u]+E[i].w;Flow[E[i].v]=min(Flow[u],E[i].flow);Path[E[i].v]=i;
                if (inq[E[i].v]==0){
                    inq[E[i].v]=1;Q.push(E[i].v);
                }
            }
        inq[u]=0;
    }
    while (!Q.empty());
    return Dist[T]!=-inf;
}

