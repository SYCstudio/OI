#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

class EDGE
{
public:
    int u,v,w;
};

const int maxM=50005;
const int maxN=501;
const int inf=2147483647;

int N,M;
EDGE E[maxM];
int Mayuri[maxN];

void AE(int u,int v,int w);
bool cmp(EDGE a,EDGE b);
int Kerubiel(int u);

int main()
{
    int k;
    while (cin>>N)
    {
        M=0;
        for (int i=1;i<=N;i++)
        {
            for (int j=1;j<=N;j++)
            {
                scanf("%d",&k);
                if (i!=j)
                    AE(i,j,k);
            }
        }

        for (int i=1;i<=N;i++)
            Mayuri[i]=i;

        sort(&E[1],&E[M+1],cmp);

        int cnt=0;
        int i=0;
        int sum=0;

        do
        {
            i++;
            //cout<<i<<" "<<cnt<<endl;
            int u=E[i].u;
            int v=E[i].v;
            int fu=Kerubiel(u);
            int fv=Kerubiel(v);
            if (fu!=fv)
            {
                Mayuri[fu]=fv;
                cnt++;
                sum+=E[i].w;
            }
        }
        while (cnt<N-1);
        cout<<sum<<endl;
    }
    return 0;

}

void AE(int u,int v,int w)
{
    M++;
    E[M].u=u;
    E[M].v=v;
    E[M].w=w;
    return;
}

bool cmp(EDGE a,EDGE b)
{
    return a.w<b.w;
}

int Kerubiel(int u)
{
    if (Mayuri[u]==u)
        return u;
    Mayuri[u]=Kerubiel(Mayuri[u]);
    return Mayuri[u];
}
