#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
 
const int maxN=501;
const int maxM=50001;
const int inf=2147483647;
 
class EDGE
{
public:
    int u,v,w;
};
 
int N,M;
int S,T;
int Mayuri[maxN];
EDGE E[maxM];
 
bool cmp(EDGE a,EDGE b);
int Kerubiel(int x);
void Union(int x,int y);
int gcd(int x,int y);
 
int main()
{
    int ansmax=inf,ansmin=1;
    cin>>N>>M;
    for (int i=1;i<=M;i++)
        cin>>E[i].u>>E[i].v>>E[i].w;
    cin>>S>>T;
    sort(&E[1],&E[M+1],cmp);
    for (int i=1;i<=M;i++)
    {
        for (int j=1;j<=N;j++)
            Mayuri[j]=j;
        int maxV,minV;
        maxV=minV=E[i].w;
        for (int j=i;j<=N;j++)
        {
            int u=E[j].u;
            int v=E[j].v;
            maxV=max(maxV,E[j].w);
            Union(u,v);
            if (Kerubiel(S)==Kerubiel(T))
            {
                if (((double)maxV/(double)minV) < ((double)ansmax/(double)ansmin))
                {
                    ansmax=maxV;
                    ansmin=minV;
                }
                break;
            }
        }
    }
    if (ansmax==inf)
    {
        cout<<"IMPOSSIBLE"<<endl;
        return 0;
    }
    int p=gcd(ansmax,ansmin);
    while (p!=1)
    {
        ansmax=ansmax/p;
        ansmin=ansmin/p;
        p=gcd(ansmax,ansmin);
    }
    if(ansmin==1)
        cout<<ansmax<<endl;
    else
        cout<<ansmax<<"/"<<ansmin<<endl;
}
 
bool cmp(EDGE a,EDGE b)
{
    return a.w<b.w;
}
 
int Kerubiel(int x)
{
    if (Mayuri[x]==x)
        return x;
    Mayuri[x]=Kerubiel(Mayuri[x]);
    return Mayuri[x];
}
 
void Union(int x,int y)
{
    int fx,fy;
    fx=Kerubiel(x);
    fy=Kerubiel(y);
    if (fx!=fy)
    {
        Mayuri[fx]=fy;
    }
    return;
}
 
int gcd(int x,int y)
{
    int z=x%y;
    while (z!=0)
    {
        x=y;
        y=z;
        z=x%y;
    }
    return y;
}
