#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
#include<cstring>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

class EDGE
{
public:
    int v,h;
};

const int maxN=600;
const int maxM=600*600;
const int inf=2147483647;

int n,m;
//Graph
vector<EDGE> E[maxN];//原图
vector<int> G[maxN];//缩点后图
int Map[maxN][maxN];
//Tarjan
int cnt;
int dfn[maxN];
int low[maxN];
stack<int> S;
//QLTFL
int Qcnt;
int QLT[maxN];//每个点所在的强连通分量的编号
//Spfa
int Dist[maxN];
bool vis[maxN];

void init();
void tarjan(int u,int father);
void Spfa(int Begin);

int main()
{
    do
    {
        cin>>n>>m;
        if ((n==0)&&(m==0))
            break;
        init();
        int u,v,w;
        for (int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            E[u].push_back((EDGE){v,w});
        }
        /*cout<<"size:"<<endl;
        for (int i=1;i<=n;i++)
            cout<<E[i].size()<<' ';
        cout<<endl;*/
        mem(vis,0);
        for (int i=1;i<=n;i++)
            if (dfn[i]==0)
            {
                //mem(vis,0);
                tarjan(i,i);
            }
        /*cout<<"The Result of Tarjan:"<<endl;
        for (int i=1;i<=n;i++)
            cout<<"[ "<<dfn[i]<<' '<<low[i]<<" ] ";
        cout<<endl;
        for (int i=1;i<=n;i++)
            cout<<QLT[i]<<' ';
        cout<<endl;*/
        for (int i=1;i<=Qcnt;i++)
            for (int j=1;j<=Qcnt;j++)
                Map[i][j]=(i==j) ? 0 : inf;
        for (int i=1;i<=n;i++)
            for (int j=0;j<E[i].size();j++)
            {
                int v=E[i][j].v;
                //cout<<'['<<i<<','<<v<<']'<<endl;
                if (QLT[i]!=QLT[v])
                {
                    if (Map[QLT[i]][QLT[v]]==inf)
                        G[QLT[i]].push_back(QLT[v]);
                    Map[QLT[i]][QLT[v]]=min(Map[QLT[i]][QLT[v]],E[i][j].h);
                }
            }
        /*for (int i=1;i<=Qcnt;i++)
        {
            for (int j=1;j<=Qcnt;j++)
            {
                if (Map[i][j]==inf)
                    cout<<"inf ";
                else
                    cout<<Map[i][j]<<' ';
            }
            cout<<endl;
        }*/
        int Q;
        cin>>Q;
        for (int i=1;i<=Q;i++)
        {
            scanf("%d%d",&u,&v);
            //cout<<"A ";
            if (QLT[u]==QLT[v])
                printf("0\n");
            else
            {
                //cout<<"Case 2:"<<endl;
                Spfa(QLT[u]);
                if (Dist[QLT[v]]!=inf)
                    printf("%d\n",Dist[QLT[v]]);
                    //cout<<Dist[QLT[v]]<<endl;
                else
                    printf("Nao e possivel entregar a carta\n");
                    //cout<<"Nao e possivel entregar a carta"<<endl;
            }
        }
        printf("\n");
    }
    while (233);
    return 0;
}

void init()
{
    Qcnt=0;
    cnt=0;
    mem(dfn,0);
    while (!S.empty())
        S.pop();
    for (int i=0;i<=n;i++)
        E[i].clear();
    for (int i=0;i<=n;i++)
        G[i].clear();
    return;
}

void tarjan(int u,int father)
{
    int v;
    //cout<<"tarjan "<<u<<' '<<father<<endl;
    vis[u]=1;
    cnt++;
    dfn[u]=low[u]=cnt;
    S.push(u);
    for (int i=0;i<E[u].size();i++)
    {
            v=E[u][i].v;
            //cout<<low[u]<<endl;
            if (dfn[v]==0)
            {
                tarjan(v,u);
                low[u]=min(low[u],low[v]);
                //cout<<"TT "<<low[u]<<' '<<low[v]<<endl;
            }
            else if (vis[v]==1)
            {
                low[u]=min(low[u],dfn[v]);
            }
    }
    if (low[u]==dfn[u])
    {
        Qcnt++;
        do
        {
            v=S.top();
            S.pop();
            vis[v]=0;
            QLT[v]=Qcnt;
            //cout<<v<<' '<<endl;
        }
        while (u!=v);
        //cout<<endl;
    }
    //vis[u]=0;
    return;
}

void Spfa(int Begin)
{
    //cout<<"The Spfa begin is: "<<Begin<<endl;
    mem(vis,0);
    for (int i=1;i<=Qcnt;i++)
        Dist[i]=inf;
    queue<int> Q;
    Q.push(Begin);
    Dist[Begin]=0;
    vis[Begin]=1;
    do
    {
        int v=Q.front();
        vis[v]=0;
        Q.pop();
        for (int i=0;i<G[v].size();i++)
            if (Map[v][G[v][i]]+Dist[v]<Dist[G[v][i]])
            {
                Dist[G[v][i]]=Map[v][G[v][i]]+Dist[v];
                if (vis[G[v][i]]==0)
                {
                    Q.push(G[v][i]);
                    vis[G[v][i]]=1;
                }
            }
    }
    while(!Q.empty());
    return;
}
