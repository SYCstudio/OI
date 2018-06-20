#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

class Road
{
public:
    int u,v,w;
};

bool operator < (Road a,Road b)
{
    return a.w<b.w;
}

const int maxN=2000;
const int maxM=101000;
const int inf=2147483647;

int n,m;
int Mayuri[maxN];
Road E[maxM];

int Find(int x);

int main()
{
    int Ans=0;
    int cnt=0;
    cin>>n>>m;
    for (int i=1;i<=m;i++)
    {
        cin>>E[i].u>>E[i].v>>E[i].w;
    }
    sort(&E[1],&E[m+1]);
    for (int i=1;i<=n;i++)
        Mayuri[i]=i;
    int i=0;
    do
    {
        i++;
        int fu=Find(E[i].u);
        int fy=Find(E[i].v);
        if (fu!=fy)
        {
            cnt++;
            Ans=max(E[i].w,Ans);
            Mayuri[fu]=fy;
        }
        if (cnt==n-1)
            break;
    }
    while (i<m);
    if (cnt==n-1)
        cout<<Ans<<endl;
    else
        cout<<-1<<endl;
    return 0;
}

int Find(int x)
{
    if (Mayuri[x]!=x)
        Mayuri[x]=Find(Mayuri[x]);
    return Mayuri[x];
}
