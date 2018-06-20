#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxsize=100;
const int inf=2147483647;

int n;
long long Node[maxsize];
long long F[maxsize][maxsize];
int Mayuri[maxsize][maxsize];

void Outp(int l,int r);

int main()
{
    memset(F,0,sizeof(F));
    cin>>n;
    for (int i=1;i<=n;i++)
        cin>>Node[i];
    for (int i=1;i<=n;i++)
        F[i][i-1]=1;
    for (int i=1;i<=n;i++)
    {
        F[i][i]=Node[i];
        Mayuri[i][i]=i;
    }
    for (int i=n;i>=1;i--)
    {
        for (int j=i+1;j<=n;j++)
        {
            for (int k=i;k<=j;k++)
                if (F[i][k-1]*F[k+1][j]+Node[k]>F[i][j])
                {
                    F[i][j]=F[i][k-1]*F[k+1][j]+Node[k];
                    Mayuri[i][j]=k;
                    cout<<"Update : "<<i<<' '<<j<<' '<<k<<' '<<F[i][j]<<endl;
                }
        }
    }
    cout<<F[1][n]<<endl;
    Outp(1,n);
    cout<<endl;
    return 0;
}

void Outp(int l,int r)
{
    if (l>r)
        return;
    cout<<Mayuri[l][r]<<' ';
    if (l==r)
        return;
    Outp(l,Mayuri[l][r]-1);
    Outp(Mayuri[l][r]+1,r);
    return;
}
