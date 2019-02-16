#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=800;
const int maxM=maxN*maxN*2;
const int inf=2147483647;

class Edge
{
public:
    int u,v,cost,flow;
};

int n,m;
int nodesum=0;
int cnt=-1;
int Arr[maxN][maxN];
int Map[maxN][maxN];
int Head[maxN];
int Next[maxM];
Edge E[maxM];
int Dist[maxN];
bool inqueue[maxN];
int Path[maxN];
int Flow[maxN];
int Queue[maxM];

void Add_Edge(int u,int v,int cost,int flow);
bool spfa();

int main()
{
    scanf("%d%d",&m,&n);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m+i-1;j++)
        {
            scanf("%d",&Arr[i][j]);
            nodesum++;
            Map[i][j]=nodesum;
        }
    //Q1
    cnt=-1;
    memset(Head,-1,sizeof(Head));
    for (int i=1;i<=m;i++)
        Add_Edge(0,i,0,1);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=i+m-1;j++)
        {
            Add_Edge(Map[i][j],Map[i][j]+nodesum,Arr[i][j],1);
            if (i!=n)
            {
                Add_Edge(Map[i][j]+nodesum,Map[i+1][j],0,1);
                Add_Edge(Map[i][j]+nodesum,Map[i+1][j+1],0,1);
            }
        }
    for (int i=1;i<=m+n-1;i++)
        Add_Edge(Map[n][i]+nodesum,nodesum*2+1,0,1);
    int Ans=0;
    /*cout<<nodesum<<endl;
    for (int i=0;i<=2*nodesum+1;i++)
    {
        for (int j=Head[i];j!=-1;j=Next[j])
        {
            if (E[j].flow==0)
                continue;
            cout<<i<<" "<<E[j].v<<' '<<E[j].flow<<' '<<E[j].cost<<endl;
        }
        cout<<endl;
    }
    system("pause");*/
    while (spfa())
    {
        int now=nodesum*2+1;
        int last=Path[now];
        int nowflow=Flow[nodesum*2+1];
        while(now!=0)
        {
            E[last].flow-=nowflow;
            E[last^1].flow+=nowflow;
            now=E[last].u;
            last=Path[now];
        }
        Ans+=Flow[nodesum*2+1]*Dist[nodesum*2+1];
    }
    cout<<Ans<<endl;
    //Q2
    cnt=-1;
    memset(Head,-1,sizeof(Head));
    for (int i=1;i<=m;i++)
        Add_Edge(0,i,0,1);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m+i-1;j++)
        {
            Add_Edge(Map[i][j],Map[i][j]+nodesum,Arr[i][j],inf);
            if (i!=n)
            {
                Add_Edge(Map[i][j]+nodesum,Map[i+1][j],0,1);
                Add_Edge(Map[i][j]+nodesum,Map[i+1][j+1],0,1);
            }
        }
    for (int i=1;i<=n+m-1;i++)
        Add_Edge(Map[n][i]+nodesum,nodesum*2+1,0,inf);
    Ans=0;
    while (spfa())
    {
        int now=nodesum*2+1;
        int last=Path[now];
        int nowflow=Flow[nodesum*2+1];
        while (now!=0)
        {
            E[last].flow-=nowflow;
            E[last^1].flow+=nowflow;
            now=E[last].u;
            last=Path[now];
        }
        Ans+=nowflow*Dist[nodesum*2+1];
    }
    cout<<Ans<<endl;
    //Q3
    memset(Head,-1,sizeof(Head));
    cnt=-1;
    for (int i=1;i<=m;i++)
        Add_Edge(0,i,0,1);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m+i-1;j++)
        {
            Add_Edge(Map[i][j],Map[i][j]+nodesum,Arr[i][j],inf);
            if (i!=n)
            {
                Add_Edge(Map[i][j]+nodesum,Map[i+1][j],0,inf);
                Add_Edge(Map[i][j]+nodesum,Map[i+1][j+1],0,inf);
            }
        }
    for (int i=1;i<=n+m-1;i++)
        Add_Edge(Map[n][i]+nodesum,nodesum*2+1,0,inf);
    Ans=0;
    while (spfa())
    {
        int now=nodesum*2+1;
        int last=Path[now];
        int nowflow=Flow[nodesum*2+1];
        while (now!=0)
        {
            E[last].flow-=nowflow;
            E[last^1].flow+=nowflow;
            now=E[last].u;
            last=Path[now];
        }
        Ans+=nowflow*Dist[nodesum*2+1];
    }
    cout<<Ans<<endl;
    return 0;
}

void Add_Edge(int u,int v,int cost,int flow)
{
    cnt++;
    Next[cnt]=Head[u];
    Head[u]=cnt;
    E[cnt].u=u;
    E[cnt].v=v;
    E[cnt].cost=cost;
    E[cnt].flow=flow;

    cnt++;
    Next[cnt]=Head[v];
    Head[v]=cnt;
    E[cnt].u=v;
    E[cnt].v=u;
    E[cnt].cost=-cost;
    E[cnt].flow=0;
}

bool spfa()
{
    for (int i=0;i<=2*nodesum+1;i++)
        Dist[i]=-inf;
    memset(inqueue,0,sizeof(inqueue));
    int h=1,t=0;
    Queue[1]=0;
    inqueue[0]=1;
    Dist[0]=0;
    Flow[0]=inf;
    do
    {
        t++;
        int u=Queue[t];
        //cout<<Dist[u]<<endl;
        for (int i=Head[u];i!=-1;i=Next[i])
        {
            int v=E[i].v;
            //cout<<u<<"->"<<v<<endl;
            //cout<<Dist[u]+E[i].cost<<" "<<Dist[v]<<endl;
            //system("pause");
            if ((E[i].flow>0)&&(Dist[u]+E[i].cost>Dist[v]))
            {
                //cout<<"Modefy!"<<endl;
                Dist[v]=E[i].cost+Dist[u];
                Path[v]=i;
                Flow[v]=min(Flow[u],E[i].flow);
                if (inqueue[v]==0)
                {
                    h++;
                    Queue[h]=v;
                    inqueue[v]=1;
                }
            }
        }
        inqueue[u]=0;
    }
    while(t<h);
    if (Dist[nodesum*2+1]==-inf)
        return 0;
    return 1;
}
