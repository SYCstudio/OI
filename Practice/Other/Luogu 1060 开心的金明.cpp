#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=30001;
const int maxM=25;

int n,m;
int W[maxM];
int V[maxM];
int F[maxN][maxM];

int main()
{
    cin>>n>>m;
    for (int i=1;i<=m;i++)
    {
        int x,y;
        cin>>x>>y;
        V[i]=x;
        W[i]=x*y;
    }
    memset(F,0,sizeof(F));
    for (int i=0;i<=n;i++)
        F[0][i]=0;
    //sort(&W[1],&W[m+1]);
    for (int i=1;i<=m;i++)
    {
        for (int j=n;j>=0;j--)
        {
            if (j>=V[i])
                F[i][j]=max(F[i-1][j],F[i-1][j-V[i]]+W[i]);
            else
                F[i][j]=max(F[i-1][j],F[i][j]);
            //cout<<F[i][j]<<' ';
        }
        //cout<<endl;
    }
    cout<<F[m][n]<<endl;
    return 0;
}
