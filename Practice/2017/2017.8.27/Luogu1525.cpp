#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;

const int maxN=30000*2;
const int maxM=100101;
const int inf=2147483647;

class Edge
{
public:
    int u,v,w;
};

bool operator < (Edge A,Edge B)
{
    return A.w>B.w;
}

int n,m;
Edge E[maxM];
int Mayuri[maxN];

int Find(int x);

int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=n*2;i++)
        Mayuri[i]=i;
    for (int i=1;i<=m;i++)
        scanf("%d%d%d",&E[i].u,&E[i].v,&E[i].w);
    sort(&E[1],&E[m+1]);
    bool is_outp=0;
    for (int i=1;i<=m;i++)
    {
        int f1=Find(E[i].u);
        int f2=Find(E[i].v);
        if (f1!=f2)
        {
            Mayuri[Find(E[i].u+n)]=Find(E[i].v);
            Mayuri[Find(E[i].v+n)]=Find(E[i].u);
        }
        else
        {
            cout<<E[i].w<<endl;
            is_outp=1;
            break;
        }
    }
    if (is_outp==0)
        cout<<0<<endl;
    return 0;
}


int Find(int x)
{
    if (Mayuri[x]!=x)
        Mayuri[x]=Find(Mayuri[x]);
    return Mayuri[x];
}
