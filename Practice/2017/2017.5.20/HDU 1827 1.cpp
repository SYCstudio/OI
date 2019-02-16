#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<stack>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxsize=5000;
const int inf=2147483647;

int n,m;
int cnt;
//Graph
int First[maxsize];
int Last[maxsize];
int Next[maxsize];
int V[maxsize];
//Node W
int W[maxsize];//注意：这里不是边权，而是点权
//tarjan
int dfn[maxsize];
int low[maxsize];
stack<int> S;
bool instack[maxsize];
//QLTZT
int QLTZTcnt;
int QLTZT[maxsize];
int InCnt[maxsize];
int QLTZTans[maxsize];

void init();
void Add_Edge(int u,int v);
void tarjan(int u);

int main()
{
    while (cin>>n>>m)
    {
        int a,b;
        int sum;
        init();
        for (int i=1;i<=n;i++)
            cin>>W[i];
        for (int i=1;i<=m;i++)
        {
            cin>>a>>b;
            Add_Edge(a,b);
        }

        cnt=0;
        for (int i=1;i<=n;i++)
            if (dfn[i]==0)
                tarjan(i);

        //for (int i=1;i<=n;i++)
        //    cout<<QLTZT[i]<<" ";
        //cout<<endl;

        for (int i=1;i<=n;i++)
            for (int j=First[i];j!=-1;j=Next[j])
                if (QLTZT[i]!=QLTZT[V[j]])
                {
                    //cout<<i<<"-"<<V[j]<<endl;
                    //cout<<QLTZT[i]<<"-"<<QLTZT[V[j]]<<endl<<endl;
                    InCnt[QLTZT[V[j]]]++;
                }
                    //InCnt[QLTZT[V[j]]]++;

        //for (int i=1;i<=QLTZTcnt;i++)
        //    cout<<InCnt[i]<<" ";
        //cout<<endl;

        cnt=0;
        for (int i=1;i<=QLTZTcnt;i++)
            if (InCnt[i]==0)
                cnt++;

        for (int i=1;i<=QLTZTcnt;i++)
            QLTZTans[i]=inf;

        for (int i=1;i<=n;i++)
        {
            if (InCnt[QLTZT[i]]==0)
            {
                QLTZTans[QLTZT[i]]=min(QLTZTans[QLTZT[i]],W[i]);
            }
        }

        sum=0;
        for (int i=1;i<=QLTZTcnt;i++)
            if (InCnt[i]==0)
                sum+=QLTZTans[i];
        cout<<cnt<<" "<<sum<<endl;
    }
}

void init()
{
    cnt=0;
    QLTZTcnt=0;
    mem(First,-1);
    mem(Last,-1);
    mem(Next,-1);
    mem(instack,0);
    mem(InCnt,0);
    mem(dfn,0);
    while (!S.empty())
        S.pop();
}

void Add_Edge(int u,int v)
{
    cnt++;
    V[cnt]=v;
    if (First[u]==-1)
    {
        First[u]=cnt;
        Last[u]=cnt;
    }
    else
    {
        Next[Last[u]]=cnt;
        Last[u]=cnt;
    }
    return;
}

void tarjan(int u)
{
    int v;
    cnt++;
    dfn[u]=low[u]=cnt;
    instack[u]=1;
    S.push(u);

    for (int i=First[u];i!=-1;i=Next[i])
    {
        v=V[i];
        if (dfn[v]==0)
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else
        {
            if (instack[v]==1)
                low[u]=min(low[u],dfn[v]);
        }
    }

    if (low[u]==dfn[u])
    {
        QLTZTcnt++;
        do
        {
            v=S.top();
            S.pop();
            instack[v]=0;
            QLTZT[v]=QLTZTcnt;
        }
        while (u!=v);
    }

    return;
}