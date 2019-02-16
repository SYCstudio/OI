#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<stack>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxn=250005;
const int maxm=1000005;
const int inf=2147483647;
const int Vec1[]={0,0,0,1,-1};
const int Vec2[]={0,1,-1,0,0};

int n,m;
int cnt;
//Graph
int First[maxn];
int Last[maxn];
int Next[maxm*2];
int V[maxm*2];
//tarjan
int dfn[maxn];
int low[maxn];
bool instack[maxn];
stack<int> S;
//QLTZT
int QLTZTcnt;
int QLTZT[maxn];
int InDegree[maxn];
int OutDegree[maxn];
//Use_for_Read
int Height[550][550];

void init();
void Add_Edge(int u,int v);
void tarjan(int u);

int main()
{
    init();
    int W,L;
    scanf("%d%d",&W,&L);//WÁÐLÐÐ
    for (int i=1;i<=L;i++)
        for (int j=1;j<=W;j++)
            scanf("%d",&Height[i][j]);
            //cin>>Height[i][j];

    for (int i=1;i<=L;i++)
        for (int j=1;j<=W;j++)
            for (int k=1;k<=4;k++)
            {
                int x=i+Vec1[k];
                int y=j+Vec2[k];
                if((x<=0)||(y<=0)||(x>L)||(y>W))
                    continue;
                //cout<<i<<'-'<<j<<" -> "<<x<<"-"<<y<<endl;
                if (Height[i][j]<=Height[x][y])
                    Add_Edge((x-1)*W+y,(i-1)*W+j);
            }
    /*for (int i=1;i<=L;i++)
        for (int j=1;j<=W;j++)
        {
            cout<<'('<<i<<','<<j<<')'<<endl;
            for (int k=First[(i-1)*W+j];k!=-1;k=Next[k])
            {
                if (V[k]%W==0)
                    cout<<'('<<V[k]/W<<','<<W<<") ";
                else
                    cout<<'('<<V[k]/W+1<<','<<V[k]%W<<") ";
            }
            cout<<endl;
        }*/
    n=W*L;cnt=0;
    for (int i=1;i<=n;i++)
        if (dfn[i]==0)
            tarjan(i);
    if (QLTZTcnt==1)
    {
        cout<<0<<endl;
        return 0;
    }
    for (int i=1;i<=n;i++)
        for (int j=First[i];j!=-1;j=Next[j])
            if (QLTZT[i]!=QLTZT[V[j]])
            {
                InDegree[QLTZT[V[j]]]++;
                OutDegree[QLTZT[i]]++;
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
    cout<<max(In_0_cnt,Out_0_cnt)<<endl;
    return 0;
}


void init()
{
    cnt=QLTZTcnt=0;
    mem(First,-1);
    mem(Next,-1);
    mem(instack,0);
    mem(InDegree,0);
    mem(OutDegree,0);
    mem(dfn,0);
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
    instack[u]=1;
    S.push(u);
    cnt++;
    dfn[u]=low[u]=cnt;

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
