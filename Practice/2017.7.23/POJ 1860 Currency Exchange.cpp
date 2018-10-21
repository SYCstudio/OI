#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;

const int maxN=201;
const int inf=2147483647;

class Data
{
public:
    int v;
    double R,C;
};

int n,m,S;
double V;
vector<Data> E[maxN];
double Dist[maxN];
bool inqueue[maxN];
int Tot[maxN];
queue<int> Q;

int main()
{
    while(cin>>n>>m>>S>>V)
    {
        for (int i=1;i<=n;i++)
            E[i].clear();
        for (int i=1;i<=m;i++)
        {
            int u,v;
            double Ruv,Cuv,Rvu,Cvu;
            cin>>u>>v>>Ruv>>Cuv>>Rvu>>Cvu;
            E[u].push_back((Data){v,Ruv,Cuv});
            E[v].push_back((Data){u,Rvu,Cvu});
        }
        memset(Dist,0,sizeof(Dist));
        memset(inqueue,0,sizeof(inqueue));
        memset(Tot,0,sizeof(Tot));
        while (!Q.empty())
            Q.pop();
        Dist[S]=V;
        Q.push(S);
        inqueue[S]=1;
        bool get=0;
        do
        {
            int u=Q.front();
            //cout<<u<<endl;
            //cout<<Dist[u]<<endl;
            Q.pop();
            inqueue[u]=0;
            Tot[u]++;
            if (Tot[u]>=n)
            {
                get=1;
                cout<<"YES"<<endl;
                break;
            }
            for (int i=0;i<E[u].size();i++)
            {
                int v=E[u][i].v;
                double w=(Dist[u]-E[u][i].C)*E[u][i].R;
                if (w>Dist[v])
                {
                    Dist[v]=w;
                    if (inqueue[v]==0)
                    {
                        Q.push(v);
                        inqueue[v]=1;
                    }
                }
            }
        }
        while (!Q.empty());
        if (get==0)
            cout<<"NO"<<endl;
    }
    return 0;
}
