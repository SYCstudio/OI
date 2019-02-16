#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=2000;
const int maxM=maxN*maxN*4;
const int inf=2147483647;

class Edge
{
public:
    int u,v,flow;
};

int n,m;
int cnt=-1;
int Head[maxN];
int Next[maxM];
Edge E[maxM];
int depth[maxN];
int cur[maxN];
int Q[maxN];

void Add_Edge(int u,int v,int flow);
bool bfs();
int dfs(int u,int flow);

int main()
{
    memset(Head,-1,sizeof(Head));
    int sum=0;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n;i++)
    {
        int num;
        scanf("%d",&num);
        sum+=num;
        Add_Edge(0,i,num);
    }
    for (int i=1;i<=m;i++)
    {
        int p;
        scanf("%d",&p);
        for (int j=1;j<=p;j++)
        {
            int u;
            scanf("%d",&u);
            Add_Edge(u,n+i,1);
        }
        Add_Edge(n+i,n+m+1,1);
    }
    int Ans=0;
    while (bfs())
    {
        for (int i=0;i<=n+m+1;i++)
            cur[i]=Head[i];
        while (int di=dfs(0,inf))
            Ans+=di;
    }
    if (Ans<sum)
    {
        cout<<"No Solution!"<<endl;
        return 0;
    }
    for (int i=1;i<=n;i++)
    {
        cout<<i<<": ";
        for (int j=Head[i];j!=-1;j=Next[j])
        {
            int v=E[j].v;
            if ((v>=n+1)&&(v<=n+m)&&(E[j].flow==0))
                cout<<v-n<<" ";
        }
        cout<<endl;
    }
    return 0;
}

void Add_Edge(int u,int v,int flow)
{
    cnt++;
    Next[cnt]=Head[u];
    Head[u]=cnt;
    E[cnt].u=u;
    E[cnt].v=v;
    E[cnt].flow=flow;

    cnt++;
    Next[cnt]=Head[v];
    Head[v]=cnt;
    E[cnt].u=v;
    E[cnt].v=u;
    E[cnt].flow=0;
}

bool bfs()
{
    memset(depth,-1,sizeof(depth));
    int h=1,t=0;
    Q[1]=0;
    depth[0]=1;
    do
    {
        t++;
        int u=Q[t];
        //cout<<u<<endl;
        for (int i=Head[u];i!=-1;i=Next[i])
        {
            int v=E[i].v;
            //cout<<v<<endl;
            if ((depth[v]==-1)&&(E[i].flow>0))
            {
                depth[v]=depth[u]+1;
                h++;
                Q[h]=v;
            }
        }
    }
    while (h!=t);
    if (depth[n+m+1]==-1)
        return 0;
    return 1;
}

int dfs(int u,int flow)
{
    if (u==n+m+1)
        return flow;
    for (int &i=cur[u];i!=-1;i=Next[i])
    {
        int v=E[i].v;
        if ((depth[v]==depth[u]+1)&&(E[i].flow>0))
        {
            int di=dfs(v,min(flow,E[i].flow));
            if (di>0)
            {
                E[i].flow-=di;
                E[i^1].flow+=di;
                return di;
            }
        }
    }
    return 0;
}
