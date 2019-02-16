#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;

const int maxN=810;
const int maxM=600010;
const int inf=214748364;

int n,m;
int G[maxN][maxN];
int Dist[maxN][maxN];

void init();

int main()
{
    //freopen("zdlcs.in","r",stdin);
    //freopen("zdlcs.out","w",stdout);
    int a,b,c;
    int Ans=inf;
    cin>>n>>m;
    init();

    for (int i=1;i<=m;i++)
    {
        cin>>a>>b>>c;
        if (c<Dist[a][b])
            Dist[a][b]=Dist[b][a]=G[a][b]=G[b][a]=c;
    }

    for (int k=1;k<=n;k++)
    {
        for (int i=1;i<k;i++)
            for (int j=i+1;j<=n;j++)
                if ((Dist[i][j]!=inf)&&(G[i][k]!=inf)&&(G[j][k]!=inf))
                Ans=min(Ans,Dist[i][j]+G[i][k]+G[k][j]);
        for (int i=1;i<=n;i++)
            for (int j=1;j<=n;j++)
                if ((Dist[i][k]!=inf)&&(Dist[j][k]!=inf))
                Dist[i][j]=min(Dist[i][j],Dist[i][k]+Dist[k][j]);
    }
    if (Ans==inf)
        cout<<"It's impossible."<<endl;
    else
        cout<<Ans<<endl;
    fclose(stdin);
    fclose(stdout);
    return 0;
}

void init()
{
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++)
            Dist[i][j]=G[i][j]=inf;
    return;
}
