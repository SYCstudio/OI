#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

const int maxN=1001;
const int inf=2147483647;

class Edge
{
public:
    int v,w;
};

int n,m,X;
vector<Edge> E1[maxN];
vector<Edge> E2[maxN];
queue<int> Q;
bool inqueue[maxN];
int Dist1[maxN];
int Dist2[maxN];

int main()
{
    scanf("%d%d%d",&n,&m,&X);
    for (int i=1;i<=m;i++)
    {
        int u,v,w;
        scanf("%d%d%D",&u,&v,&w);
        E1[u].push_back((Edge){v,w});
        E2[v].push_back((Edge){u,w});
    }
    memset(Dist1,127,sizeof(Dist1));
    memset(inqueue,0,sizeof(inqueue));
    Dist1[X]=0;
    inqueue[X]=1;
    while (!Q.empty())
        Q.pop();
    Q.push(X);
    do
    {
        int u=Q.front();
        Q.pop();
        inqueue[u]=0;
        for (int i=0;i<E1[u].size();i++)
        {
            int v=E1[u][i].v;
            int w=E1[u][i].w;
            if (Dist1[v]>Dist1[u]+w)
            {
                Dist1[v]=Dist1[u]+w;
                if (inqueue[v]==0)
                {
                    Q.push(v);
                    inqueue[v]=1;
                }
            }
        }
    }
    while (!Q.empty());
    memset(Dist2,127,sizeof(Dist2));
    memset(inqueue,0,sizeof(inqueue));
    Dist2[X]=0;
    inqueue[X]=1;
    Q.push(X);
    do
    {
        int u=Q.front();
        Q.pop();
        inqueue[u]=0;
        for (int i=0;i<E2[u].size();i++)
        {
            int v=E2[u][i].v;
            int w=E2[u][i].w;
            if (Dist2[v]>Dist2[u]+w)
            {
                Dist2[v]=Dist2[u]+w;
                if (inqueue[v]==0)
                {
                    Q.push(v);
                    inqueue[v]=1;
                }
            }
        }
    }
    while (!Q.empty());
    int Ans=0;
    for (int i=1;i<=n;i++)
        Ans=max(Ans,Dist1[i]+Dist2[i]);
    cout<<Ans<<endl;
    return 0;
}
