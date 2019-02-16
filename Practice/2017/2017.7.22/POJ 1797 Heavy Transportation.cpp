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

int n,m;
vector<Edge> E[maxN];
int Dist[maxN];
bool vis[maxN];

int main()
{
    int T;
    cin>>T;
    for (int ti=1;ti<=T;ti++)
    {
        scanf("%d%d",&n,&m);
        for (int i=1;i<=n;i++)
            E[i].clear();
        for (int i=1;i<=m;i++)
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);

            E[u].push_back((Edge){v,w});
            E[v].push_back((Edge){u,w});
        }
        memset(Dist,0,sizeof(Dist));
        memset(vis,0,sizeof(vis));
        Dist[1]=inf;
        for (int i=1;i<n;i++)
        {
            int id,mx=-inf;
            for (int j=1;j<=n;j++)
                if ((Dist[j]>mx)&&(vis[j]==0))
                {
                    mx=Dist[j];
                    id=j;
                }
            if (id==n)
                break;
            vis[id]=1;
            for (int j=0;j<E[id].size();j++)
            {
                int v=E[id][j].v;
                if ((vis[v]==0)&&(min(Dist[id],E[id][j].w)>Dist[v]))
                {
                    Dist[v]=min(Dist[id],E[id][j].w);
                }
            }
        }
        printf("Scenario #%d:\n%d\n\n",ti,Dist[n]);
    }
    return 0;
}
