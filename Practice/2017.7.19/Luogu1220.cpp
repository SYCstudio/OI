#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=60;
const int inf=147483647;

int n,C;
int F[maxN][maxN][3];
int Sum[maxN];
int D[maxN];
int P[maxN];

int main()
{
    cin>>n>>C;
    Sum[0]=0;//注意前缀和初始化
    for (int i=0;i<=n;i++)
        for (int j=0;j<=n;j++)
            F[i][j][0]=F[i][j][1]=inf;//因为F要取最小，所以先置无穷大初值。
    for (int i=1;i<=n;i++)
    {
        cin>>D[i]>>P[i];
        Sum[i]=Sum[i-1]+P[i];//输入的同时计算前缀和
    }
    F[C][C][1]=F[C][C][0]=0;//初值
    for (int i=C;i>=1;i--)
        for (int j=i+1;j<=n;j++)//注意这里j的循环开始值，不能是C+1，因为这样会使得后面推的时候出现未计算的项
        {
            F[i][j][0]=min(F[i+1][j][0]+(D[i+1]-D[i])*(Sum[n]-Sum[j]+Sum[i]),
                           F[i+1][j][1]+(D[j]-D[i])*(Sum[n]-Sum[j]+Sum[i]));
            F[i][j][1]=min(F[i][j-1][0]+(D[j]-D[i])*(Sum[n]-Sum[j-1]+Sum[i-1]),
                           F[i][j-1][1]+(D[j]-D[j-1])*(Sum[n]-Sum[j-1]+Sum[i-1]));
            //cout<<i<<" "<<j<<" "<<F[i][j][0]<<" "<<F[i][j][1]<<endl;
        }
    cout<<min(F[1][n][0],F[1][n][1])<<endl;
    return 0;
}
