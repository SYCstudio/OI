#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

const int maxN=1001;
const int maxM=2001;
const int inf=2147483647;

class Edge
{
public:
    int v,w;
};

int n,m;
vector<Edge> E[maxN];
int Dist[maxN];
queue<int> Q;
bool inqueue[maxN];

int main()
{
    cin>>m>>n;
    for (int i=1;i<=m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        E[u].push_back((Edge){v,w});
        E[v].push_back((Edge){u,w});
    }
    for (int i=1;i<=n;i++)
        Dist[i]=inf;
    memset(inqueue,0,sizeof(inqueue));
    Dist[n]=0;
    inqueue[n]=1;
    Q.push(n);
    do
    {
        int u=Q.front();
        Q.pop();
        inqueue[u]=0;
        for (int i=0;i<E[u].size();i++)
        {
            int v=E[u][i].v;
            int w=E[u][i].w;
            if (Dist[u]+w<Dist[v])
            {
                Dist[v]=Dist[u]+w;
                if (inqueue[v]==0)
                {
                    Q.push(v);
                    inqueue[v]=1;
                }
            }
        }
    }
    while (!Q.empty());
    cout<<Dist[1]<<endl;
    return 0;
}
