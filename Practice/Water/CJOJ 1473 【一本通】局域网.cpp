#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
 
class Edge
{
public:
    int u,v,w;
};
 
const int maxM=2500;
const int maxN=101;
const int inf=2147483647;
 
int N,M;
int Esum;
int Mayuri[maxN];
Edge E[maxM];
 
bool cmp(Edge a,Edge b);
int Find(int x);
 
int main()
{
    int i,j,k;
    int cnt;
    int MST;
    int fx,fy;
    Esum=0;
 
    cin>>N>>M;
 
    for (i=1;i<=M;i++)
    {
        cin>>E[i].u>>E[i].v>>E[i].w;
        Esum+=E[i].w;
    }
 
    for (i=1;i<=N;i++)
        Mayuri[i]=i;
 
    sort(&E[1],&E[M+1],cmp);
 
    i=0;
    cnt=0;
    MST=0;
    do
    {
        i++;
        fx=Find(E[i].u);
        fy=Find(E[i].v);
        if(fx!=fy)
        {
            //cout<<E[i].u<<" "<<E[i].v<<endl;
            MST+=E[i].w;
            Mayuri[fx]=fy;
            cnt++;
        }
    }
    while ((cnt<N-1)&&(i<M));
    cout<<Esum-MST<<endl;
    return 0;
}
 
bool cmp(Edge a,Edge b)
{
    return a.w<b.w;
}
 
int Find(int x)
{
    if(Mayuri[x]==x)
        return x;
    return Mayuri[x]=Find(Mayuri[x]);
}