#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<stack>
using namespace std;
 
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
 
const int maxsize=1001;
const int inf=2147483647;
 
int n,m;
int cnt;
//Graph
int First[maxsize];
int Next[maxsize];
int Last[maxsize];
int V[maxsize];
//TARJAN
int dfn[maxsize];
int low[maxsize];
//stack
stack<int> S;
bool instack[maxsize];
//Degree
int InDegree[maxsize];
int OutDegree[maxsize];
//QLTZT
int QLTZTcnt=0;
int QLTZT[maxsize];
 
void init();
void Add_Edge(int u,int v);
void tarjan(int u);
 
int main()
{
    init();
    int a,b;
    m=0;
    cin>>n;
    for (int i=1;i<=n;i++)
    {
        do
        {
            cin>>a;
            if (a==0)
                break;
            Add_Edge(i,a);
            //cout<<i<<' '<<a<<endl;
        }
        while (a!=0);
    }
    /*for (int i=1;i<=n;i++)
    {
        cout<<i<<" : ";
        for (int j=First[i];j!=-1;j=Next[j])
            cout<<V[j]<<" ";
        cout<<endl;
    }
    cout<<cnt<<endl;*/
    for (int i=1;i<=n;i++)
        if (dfn[i]==0)
            tarjan(i);
 
    for (int i=1;i<=n;i++)
        for (int j=First[i];j!=-1;j=Next[j])
        {
            int v=V[j];
            if (QLTZT[i]!=QLTZT[v])
            {
                OutDegree[QLTZT[i]]++;
                InDegree[QLTZT[v]]++;
            }
        }
    int In_0_cnt=0;
    int Out_0_cnt=0;
 
    for (int i=1;i<=QLTZTcnt;i++)
    {
        if (InDegree[i]==0)
            In_0_cnt++;
        if (OutDegree[i]==0)
            Out_0_cnt++;
    }
    cout<<In_0_cnt<<endl;
    cout<<max(In_0_cnt,Out_0_cnt)<<endl;
    return 0;
}
 
void init()
{
    cnt=0;
    mem(First,-1);
    mem(Next,-1);
    mem(instack,0);
    mem(dfn,0);
    mem(InDegree,0);
    mem(OutDegree,0);
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
            if (low[v]<low[u])
                low[u]=low[v];
        }
        else
        {
            if ((instack[v]==1)&&(dfn[v]<low[u]))
                low[u]=dfn[v];
        }
    }
    if (dfn[u]==low[u])
    {
        QLTZTcnt++;
        do
        {
            v=S.top();
            S.pop();
            QLTZT[v]=QLTZTcnt;
            instack[v]=0;
        }
        while (v!=u);
    }
    return;
}