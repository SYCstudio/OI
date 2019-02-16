#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=201;
const int maxM=maxN*maxN*2;
const int inf=2147483647;

int n,m;
int Map[maxN][maxN];
int Match[maxN];
int use[maxN];
int Readx[maxN];
int Ready[maxN];
int Mayuri[maxN];

int Find(int x);
bool Hungary(int u);

int main()
{
    int T;
    scanf("%d",&T);
    while (T--)
    {
        memset(Map,0,sizeof(Map));
        int f;
        scanf("%d%d%d",&n,&m,&f);
        for (int i=1;i<=m;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            Map[u][v]=1;
        }
        for (int i=1;i<=n;i++)
            Mayuri[i]=i;
        for (int i=1;i<=f;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            int fu=Find(u);
            int fv=Find(v);
            if (fu!=fv)
                Mayuri[fu]=fv;
        }
        for (int i=1;i<=n;i++)
            for (int j=1;j<=n;j++)
                if (Find(i)==Find(j))
                    for (int k=1;k<=n;k++)
                        if (Map[i][k]==1)
                            Map[j][k]=1;
        int Ans=0;
        while (1)
        {
            int matchcnt=0;
            memset(Match,-1,sizeof(Match));
            for (int i=1;i<=n;i++)
            {
                memset(use,0,sizeof(use));
                if (Hungary(i))
                    matchcnt++;
            }
            if (matchcnt<n)
                break;
            for (int i=1;i<=n;i++)
                Map[Match[i]][i]=0;
            Ans++;
        }
        printf("%d\n",Ans);
    }
    return 0;
}

int Find(int x)
{
    if (Mayuri[x]!=x)
        Mayuri[x]=Find(Mayuri[x]);
    return Mayuri[x];
}

bool Hungary(int u)
{
    for (int i=1;i<=n;i++)
        if ((Map[u][i]==1)&&(use[i]==0))
        {
            use[i]=1;
            if ((Match[i]==-1)||(Hungary(Match[i])))
            {
                Match[i]=u;
                return 1;
            }
        }
    return 0;
}
