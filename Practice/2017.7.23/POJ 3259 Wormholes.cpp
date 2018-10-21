#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

const int maxN=600;
const int inf=2147483647;

class Edge
{
public:
    int v,w;
};

int n,m,m2;
vector<Edge> E[maxN];
bool inqueue[maxN];
queue<int> Q;
int Dist[maxN];
int Tot[maxN];

int main()
{
    int T;
    while (cin>>T)
    {
    for (int ti=1;ti<=T;ti++)
    {
        scanf("%d%d%d",&n,&m,&m2);
        for (int i=1;i<=n;i++)
        {
            Dist[i]=inf;
            E[i].clear();
        }
        for (int i=1;i<=m;i++)
        {
            int u,w,v;
            scanf("%d%d%d",&u,&v,&w);
            E[u].push_back((Edge){v,w});
            E[v].push_back((Edge){u,w});
        }
        for (int i=1;i<=m2;i++)
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            E[u].push_back((Edge){v,-w});
        }
        memset(inqueue,0,sizeof(inqueue));
        memset(Tot,0,sizeof(Tot));
        while (!Q.empty())
            Q.pop();
        Dist[1]=0;
        Q.push(1);
        inqueue[1]=1;
        bool get=0;
        do
        {
            int u=Q.front();
            Q.pop();
            inqueue[u]=0;
            Tot[u]++;
            if (Tot[u]>=n)
            {
                get=1;
                break;
            }
            for (int i=0;i<E[u].size();i++)
            {
                int v=E[u][i].v;
                int w=E[u][i].w;
                if (Dist[v]>Dist[u]+w)
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
        if (get)
            cout<<"YES"<<endl;
        else
            cout<<"NO"<<endl;
    }
    }
    return 0;
}
