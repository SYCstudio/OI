#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int maxN=402000;
const int maxM=201000;
const int inf=2147483647;

int n,m,K;
vector<int> E[maxN];
bool Destroy[maxN]={0};
int Destroy_Order[maxN];
int Mayuri[maxN];
int LTKnum[maxN]={0};

bool Union(int u,int v);
int Find(int x);

int main()
{
    int u,v;
    cin>>n>>m;
    for (int i=1;i<=m;i++)
    {
        cin>>u>>v;
        u++;v++;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    cin>>K;
    for (int i=1;i<=K;i++)
    {
        cin>>Destroy_Order[i];
        Destroy_Order[i]++;
        Destroy[Destroy_Order[i]]=1;
    }
    for (int i=1;i<=n;i++)
        Mayuri[i]=i;
    for (int i=1;i<=n;i++)
        if (Destroy[i]==0)
            for (int j=0;j<E[i].size();j++)
            {
                v=E[i][j];
                if (Destroy[v]==0)
                    Union(i,v);
            }
    int Ans=0;
    for (int i=1;i<=n;i++)
    {
        if ((Mayuri[i]==i)&&(Destroy[i]==0))
            Ans++;
    }
    for (int i=K;i>=1;i--)
    {
        LTKnum[i]=Ans;
        u=Destroy_Order[i];
        Destroy[u]=0;
        Ans++;
        for (int j=0;j<E[u].size();j++)
        {
            v=E[u][j];
            if (Destroy[v]==0)
            {
                if (Union(u,v))
                    Ans--;
            }
        }
    }
    LTKnum[0]=Ans;
    for (int i=0;i<=K;i++)
    {
        cout<<LTKnum[i]<<endl;
    }
    return 0;
}

bool Union(int u,int v)
{
    int fu=Find(u);
    int fv=Find(v);
    if (fu!=fv)
    {
        Mayuri[fu]=fv;
        return 1;
    }
    return 0;
}

int Find(int x)
{
    if (Mayuri[x]!=x)
        Mayuri[x]=Find(Mayuri[x]);
    return Mayuri[x];
}
