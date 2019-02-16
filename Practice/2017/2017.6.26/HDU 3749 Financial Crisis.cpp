#include<iostream>
#include<cstdio>
#include<cstdlib>
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
    int u,v;
};

const int maxN=6000;
const int maxM=10005;
const int inf=2147483647;

int n,m,Q;
//Graph
vector<int> E[maxN];
//Bcc 点双连通分量
int Bcccnt;//点双连通分量的数量
int Bccnow[maxN];//点当前所属的点双连通分量中编号最大的一个，有助于判重
vector<int> Belong[maxN];//每个点属于的点双连通分量的编号
vector<int> Bcc[maxN];//每个点双连通分量中有的点
//Tarjan
int cnt;
int dfn[maxN];
int low[maxM];
stack<EDGE> S;//用来存边的栈
//Mayuri
int Mayuri[maxN];

void init();
void tarjan(int u,int father);
int Find(int x);

int main()
{
    int T=0;
    while (1)
    {
        int u,v;
        scanf("%d%d%d",&n,&m,&Q);
        if (n+m+Q<=0)
            break;
        init();
        T++;
        printf("Case %d:\n",T);
        for (int i=1;i<=m;i++)
        {
            scanf("%d%d",&u,&v);
            u++;v++;
            E[u].push_back(v);
            E[v].push_back(u);
            u=Find(u);
            v=Find(v);
            if (u!=v)
                Mayuri[u]=v;
        }
        cnt=0;
        for (int i=1;i<=n;i++)
            if (dfn[i]==0)
                tarjan(i,i);
        /*cout<<"Tarjan Result:"<<endl;
        cout<<Bcccnt<<endl;
        for (int i=1;i<=Bcccnt;i++)
        {
            for (int j=0;j<Bcc[i].size();j++)
                cout<<Bcc[i][j]<<' ';
            cout<<endl;
        }
        cout<<"Node"<<endl;
        for (int i=1;i<=n;i++)
        {
            for (int j=0;j<Belong[i].size();j++)
                cout<<Belong[i][j]<<' ';
            cout<<endl;
        }*/
        for (int i=1;i<=Q;i++)
        {
            scanf("%d%d",&u,&v);
            u++;v++;
            if (Find(u)!=Find(v))
            {
                printf("zero\n");
                continue;
            }
            bool flag=0;
            for (int i=0;(i<Belong[u].size())&&(!flag);i++)
                for (int j=0;(j<Belong[v].size())&&(!flag);j++)
                    if (Belong[u][i]==Belong[v][j])
                    {
                        int k=Belong[u][i];
                        if (Bcc[k].size()>2)
                        {
                            printf("two or more\n");
                            flag=1;
                        }
                    }
            if (flag==0)
                printf("one\n");
        }
    }
}

void init()
{
    cnt=0;
    Bcccnt=0;
    mem(dfn,0);
    mem(Bccnow,0);
    while (!S.empty())
        S.pop();
    for (int i=1;i<=n;i++)
        Bcc[i].clear();
    for (int i=1;i<=n;i++)
        Belong[i].clear();
    for (int i=1;i<=n;i++)
        E[i].clear();
    for (int i=1;i<=n;i++)
        Mayuri[i]=i;
    return;
}

void tarjan(int u,int father)
{
    int v;
    EDGE G;
    cnt++;
    dfn[u]=low[u]=cnt;
    for (int i=0;i<E[u].size();i++)
    {
        v=E[u][i];
        if (v==father)
            continue;
        if (dfn[v]==0)
        {
            S.push((EDGE){u,v});
            tarjan(v,u);
            low[u]=min(low[u],low[v]);
            if (low[v]>=dfn[u])//说明找到了一个点双连通分量
            {
                Bcccnt++;
                Bcc[Bcccnt].clear();
                do
                {
                    G=S.top();
                    S.pop();
                    if (Bccnow[G.u]!=Bcccnt)//如果G.u还没有在Bcccnt这个分量重出现过
                    {
                        Bccnow[G.u]=Bcccnt;
                        Belong[G.u].push_back(Bcccnt);
                        Bcc[Bcccnt].push_back(G.u);
                    }
                    if (Bccnow[G.v]!=Bcccnt)//同G.u的处理
                    {
                        Bccnow[G.v]=Bcccnt;
                        Belong[G.v].push_back(Bcccnt);
                        Bcc[Bcccnt].push_back(G.v);
                    }
                }
                while ((u!=G.u)||(v!=G.v));
            }
        }
        else
        {
            if (dfn[v]<dfn[u])
            {
                S.push((EDGE){u,v});
                low[u]=min(low[u],dfn[v]);
            }
        }
    }
    return;
}

int Find(int x)
{
    if (Mayuri[x]!=x)
        Mayuri[x]=Find(Mayuri[x]);
    return Mayuri[x];
}
