#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
#include<queue>
using namespace std;

#define ll long long

const int maxN=3000;
const int inf=147483647;

class Edge
{
public:
    int v;
    ll w;
};

int n,m;
vector<Edge> E[maxN];
ll Dist[maxN];
int Px[maxN];
int Py[maxN];
bool inqueue[maxN];
queue<int> Q;

int main()
{
    int ti=0;
    while (cin>>n)
    {
        if (n==0)
            break;
        for (int i=1;i<=n;i++)
        {
            E[i].clear();
        }
        memset(Dist,-1,sizeof(Dist));
        for (int i=1;i<=n;i++)
            cin>>Px[i]>>Py[i];
        for (int i=1;i<=n;i++)
            for (int j=i+1;j<=n;j++)
            {
                ll dist=(Px[i]-Px[j])*(Px[i]-Px[j])+(Py[i]-Py[j])*(Py[i]-Py[j]);
                E[i].push_back((Edge){j,dist});
                E[j].push_back((Edge){i,dist});
            }
        memset(inqueue,0,sizeof(inqueue));
        while (!Q.empty())
            Q.pop();
        Dist[1]=0;
        inqueue[1]=1;
        Q.push(1);
        do
        {
            int u=Q.front();
            Q.pop();
            inqueue[u]=0;
            for (int i=0;i<E[u].size();i++)
            {
                int v=E[u][i].v;
                if ((max(Dist[u],E[u][i].w)<Dist[v])||(Dist[v]==-1))
                {
                    Dist[v]=max(Dist[u],E[u][i].w);
                    if (inqueue[v]==0)
                    {
                        Q.push(v);
                        inqueue[v]=1;
                    }
                }
            }
        }
        while (!Q.empty());
        ti++;
        printf("Scenario #%d\nFrog Distance = %.3f\n\n",ti,sqrt(Dist[2]*1.0));
        //cout<<Dist[2]<<endl;
    }
    return 0;
}
