#pragma comment(linker, "/STACK:1024000000,1024000000")
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100100;
const int maxM=100100;
const int inf=2147483647;

int n,m;
int cnt;
int Map[maxN];
//Graph
int Head[maxN];
int Next[maxM];
int V[maxM];
//tarjan
int dfn[maxN];
int low[maxN];
//Bcc
int Bcccnt;
vector<int> bcc[maxN];
int bcctot[maxN];//统计连通块周围的割点数量
//GD
bool GD[maxN];
int GD_cnt=0;
//Stack
stack<int> S;

void init();
int change(int x);
void Add_Edge(int u,int v);
void tarjan(int u,int father);

int main()
{
    int T=0;
    while (cin>>m)
    {
        int a,b;
        if (m==0)
            break;
        T++;
        init();
        for (int i=1;i<=m;i++)
        {
            cin>>a>>b;
            //a=change(a);
            //b=change(b);
            Add_Edge(a,b);
            Add_Edge(b,a);
            n=max(n,max(a,b));
        }
        cnt=0;
        //cout<<"BZY"<<endl;
        for (int i=1;i<=n;i++)
        {
            if (dfn[i]==0)
                tarjan(i,-1);
        }
        /*cout<<"tarjan end:"<<endl;
        for (int i=1;i<=Bcccnt;i++)
        {
            cout<<i<<":";
            int Si=bcc[i].size();
            for (int j=0;j<Si;j++)
                cout<<bcc[i][j]<<' ';
            cout<<endl;
        }*/
        if (Bcccnt==1)
        {
            cout<<"Case "<<T<<": "<<2<<' '<<(long long)n*((long long)n-1)/2<<endl;
            continue;
        }
        //cout<<"TAR"<<endl;
        //for (int i=1;i<=n;i++)
        //    cout<<i<<'['<<Map[i]<<']'<<' ';
        //cout<<endl;
        //cout<<"The GD is:"<<endl;
        //for (int i=1;i<=n;i++)
        //    cout<<GD[i]<<' ';
        //cout<<endl;
        //cout<<"The low is:"<<endl;
        //for (int i=1;i<=n;i++)
        //    cout<<low[i]<<' ';
        //cout<<endl;

        for (int i=1;i<=Bcccnt;i++)
        {
            int Size=bcc[i].size();
            for (int j=0;j<Size;j++)
                if (GD[bcc[i][j]]==1)
                    bcctot[i]++;
        }
        long long Ans=0;
        long long Method=1;

        for (int i=1;i<=Bcccnt;i++)
            if (bcctot[i]==1)
            {
                Ans++;
                Method=Method*(bcc[i].size()-1);
            }
        //cout<<"The LTK is:"<<endl;
        //for (int i=1;i<=n;i++)
        //    cout<<LTK[i]<<' ';
        //cout<<endl;
        //cout<<endl;
        cout<<"Case "<<T<<": "<<Ans<<' '<<Method<<endl;
    }
    return 0;
}

void init()
{
    cnt=0;
    Bcccnt=0;
    n=0;
    GD_cnt=0;
    mem(bcctot,0);
    mem(dfn,0);
    mem(Head,-1);
    mem(Next,-1);
    mem(Map,-1);
    mem(GD,0);
    //mem(GD_Degree,0);
    while (!S.empty())
    {
        S.pop();
    }
    return;
}

int change(int x)
{
    if (Map[x]==-1)
    {
        n++;
        Map[x]=n;
    }
    return Map[x];
}

void Add_Edge(int u,int v)
{
    cnt++;
    V[cnt]=v;
    Next[cnt]=Head[u];
    Head[u]=cnt;
    return;
}

void tarjan(int u,int father)
{
    S.push(u);
    cnt++;
    dfn[u]=low[u]=cnt;
    int childcnt=0;
    int v;

    for (int i=Head[u];i!=-1;i=Next[i])
    {
        v=V[i];
        if (dfn[v]==0)
        {
            tarjan(v,u);
            childcnt++;
            low[u]=min(low[u],low[v]);
            if (low[v]>=dfn[u])
            {
                GD[u]=1;
                Bcccnt++;
                bcc[Bcccnt].clear();
                int vv;
                do
                {
                    vv=S.top();
                    S.pop();
                    bcc[Bcccnt].push_back(vv);
                }
                while (vv!=v);
                bcc[Bcccnt].push_back(u);
            }
        }
        else
            if (v!=father)
                low[u]=min(low[u],dfn[v]);
    }
    if ((father<0)&&(childcnt==1))
        GD[u]=0;
    if (GD[u]==1)
        GD_cnt++;
    return;
}
