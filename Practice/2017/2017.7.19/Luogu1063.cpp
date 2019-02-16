#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=350;
const int inf=2147483647;

int n;
int A[maxN];
int F[maxN][maxN];

int main()
{
    cin>>n;
    for (int i=1;i<=n;i++)
        cin>>A[i];
    for (int i=1;i<=n;i++)
        A[i+n]=A[i+2*n]=A[i];
    memset(F,0,sizeof(F));
    for (int i=1;i<=n;i++)//枚举我们要计算的长度
    {
        for (int l=1;l<=2*n;l++)//枚举左端点
        {
            int r=l+i-1;//计算出右端点
            if (r>2*n)
                continue;
            for (int k=l+1;k<=r;k++)
                F[l][r]=max(F[l][r],F[l][k-1]+F[k][r]+A[l]*A[k]*A[r+1]);
            //cout<<F[l][r]<<" ";
        }
        //cout<<endl;
    }
    int Ans=0;
    for (int i=1;i<=n;i++)
        Ans=max(Ans,F[i][i+n-1]);
    cout<<Ans<<endl;
    return 0;
}
