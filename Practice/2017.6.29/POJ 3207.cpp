#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<stack>
using namespace std;

const int maxN=2001;
const int inf=2147483647;

int n,m;
int Readx[maxN];
int Ready[maxN];
vector<int> E[maxN];//i与i+m为对应点
//Tarjan
int cnt=0;
int dfn[maxN];
int low[maxN];
bool instack[maxN];
stack<int> S;
//LTK
int LTKcnt=0;
int LTK[maxN];

void Read_and_Init();//读入并建图
void Link(int x,int y);
void tarjan(int u);
bool check();

int main()
{
    Read_and_Init();
    memset(instack,0,sizeof(instack));
    memset(dfn,0,sizeof(dfn));
    while (!S.empty())
        S.pop();
    for (int i=1;i<=2*m;i++)
        if (dfn[i]==0)
            tarjan(i);
    if (check())
        cout<<"panda is telling the truth..."<<endl;
    else
        cout<<"the evil panda is lying again"<<endl;
}

void Read_and_Init()
{
    cin>>n>>m;
    int a,b;
    for (int i=1;i<=m;i++)
    {
        cin>>Readx[i]>>Ready[i];
        Readx[i]++;
        Ready[i]++;
        if (Readx[i]>Ready[i])
            swap(Readx[i],Ready[i]);
    }
    for (int i=1;i<=m;i++)
        for (int j=i+1;j<=m;j++)
        {
            if ( ((Readx[i]<=Readx[j])&&(Readx[j]<=Ready[i])&&(Ready[i]<=Ready[j]))
                 || ((Readx[i]>=Readx[j])&&(Readx[i]<=Ready[j])&&(Ready[j]<=Ready[i]))  )
            {
                Link(i,j+m);
                Link(j,i+m);
                Link(i+m,j);
                Link(j+m,i);
            }
        }
    return;
}

void Link(int x,int y)
{
    E[x].push_back(y);
    return;
}

void tarjan(int u)
{
    cnt++;
    dfn[u]=low[u]=cnt;
    instack[u]=1;
    S.push(u);

    for (int i=0;i<E[u].size();i++)
    {
        int v=E[u][i];
        if (dfn[v]==0)
        {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else
            if (instack[v]==1)
                low[u]=min(low[u],dfn[v]);
    }
    if (dfn[u]==low[u])
    {
        int v;
        LTKcnt++;
        do
        {
            v=S.top();
            S.pop();
            instack[v]=0;
            LTK[v]=LTKcnt;
        }
        while (u!=v);
    }
    return;
}

bool check()
{
    for (int i=1;i<=m;i++)
        if (LTK[i]==LTK[i+m])
            return 0;
    return 1;
}
