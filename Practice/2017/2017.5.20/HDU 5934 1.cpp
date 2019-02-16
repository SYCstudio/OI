#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<stack>
#include<cmath>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxsize=50001;
const int inf=2147483647;

int n,m;
int cnt;
//Graph
int First[maxsize];
int Last[maxsize];
int Next[maxsize];
int V[maxsize];
int Light[maxsize];
//tarjan
stack<int> S;
bool instack[maxsize];
int dfn[maxsize];
int low[maxsize];
//QLTZT
int QLTZTcnt;
int QLTZT[maxsize];
int InDegree[maxsize];
int QLTZTans[maxsize];
//xy×ø±êÏµ
long long X[maxsize];
long long Y[maxsize];
long long R[maxsize];

void init();
void Add_Edge(int u,int v);
void tarjan(int u);

int main()
{
    int T,ti;
    cin>>T;
    for (ti=1;ti<=T;ti++)
    {
        init();
        scanf("%d",&n);
        for (int i=1;i<=n;i++)
            scanf("%d%d%d%d",&X[i],&Y[i],&R[i],&Light[i]);
            //cin>>X[i]>>Y[i]>>R[i]>>Light[i];
        for (int i=1;i<n;i++)
            for (int j=i+1;j<=n;j++)
            {
                long long Dist=(X[i]-X[j])*(X[i]-X[j])+(Y[i]-Y[j])*(Y[i]-Y[j]);
                //cout<<"Node "<<i<<" And Node "<<j<<": "<<Dist<<' '<<R[i]<<' '<<R[j]<<endl;
                if (R[i]*R[i]>=Dist)
                    Add_Edge(i,j);
                if (R[j]*R[j]>=Dist)
                    Add_Edge(j,i);
            }

        //for (int i=1;i<=n;i++)
        //{
        //    cout<<i<<endl;
        //    for (int j=First[i];j!=-1;j=Next[j])
        //        cout<<V[j]<<' ';
        //    cout<<endl;
        //}

        cnt=0;
        for (int i=1;i<=n;i++)
            if (dfn[i]==0)
                tarjan(i);

        for (int i=1;i<=n;i++)
            for (int j=First[i];j!=-1;j=Next[j])
                if (QLTZT[i]!=QLTZT[V[j]])
                    InDegree[QLTZT[V[j]]]++;
        int sum=0;
        for (int i=1;i<=QLTZTcnt;i++)
            QLTZTans[i]=inf;
        for (int i=1;i<=n;i++)
            if (InDegree[QLTZT[i]]==0)
                QLTZTans[QLTZT[i]]=min(QLTZTans[QLTZT[i]],Light[i]);
        for (int i=1;i<=QLTZTcnt;i++)
            if (InDegree[i]==0)
                sum+=QLTZTans[i];
        cout<<"Case #"<<ti<<": "<<sum<<endl;
    }
}

void init()
{
    cnt=0;
    QLTZTcnt=0;
    mem(First,-1);
    mem(Next,-1);
    mem(instack,0);
    mem(dfn,0);
    mem(InDegree,0);
    while (!S.empty())
        S.pop();
    return;
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
            if (instack[v]==1)
                low[u]=min(low[u],dfn[v]);
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