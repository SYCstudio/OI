#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long

const int inf=2147483647;

ll n,Mod,p,q,A1,A2;

class Matrix//定义矩阵结构体
{
public:
    ll M[2][2];
    Matrix()
    {
        memset(M,0,sizeof(M));
    }
    Matrix(ll Arr[2][2])
    {
        for (int i=0;i<2;i++)
            for (int j=0;j<2;j++)
                M[i][j]=Arr[i][j];
    }
};

Matrix operator * (Matrix A,Matrix B)//重载乘法操作
{
    Matrix Ans;
    for (int i=0;i<2;i++)
        for (int j=0;j<2;j++)
            for (int k=0;k<2;k++)
                Ans.M[i][j]=(Ans.M[i][j]+A.M[i][k]*B.M[k][j]%Mod)%Mod;
    return Ans;
}

int main()
{
    cin>>p>>q>>A1>>A2>>n>>Mod;
    if (n==1)//1和2的情况特殊处理（虽然我也不知道是否有特殊点）
    {
        cout<<A1<<endl;
        return 0;
    }
    if (n==2)
    {
        cout<<A2<<endl;
        return 0;
    }
    n=n-2;
    ll a[2][2]={{A2,A1},{0,0}};//初始矩阵
    ll b[2][2]={{p,1},{q,0}};
    Matrix A(a);
    Matrix B(b);
    while (n!=0)//快速幂
    {
        if (n&1)
            A=A*B;
        B=B*B;
        n=n>>1;
    }
    cout<<A.M[0][0]<<endl;
    return 0;
}