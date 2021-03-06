#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long//注意用长整形，因为有可能会爆int

const int Mod=1000000007;
const int inf=2147483647;

class Matrix//定义矩阵
{
public:
    ll M[2][2];
    Matrix()
    {
        memset(M,0,sizeof(M));
    }
    Matrix(int Arr[2][2])//定义两个方便的矩阵初始化
    {
        for (int i=0;i<2;i++)
            for (int j=0;j<2;j++)
                M[i][j]=Arr[i][j];
    }
};

Matrix operator * (Matrix A,Matrix B)//重载乘号操作
{
    Matrix Ans;
    for (int i=0;i<2;i++)
        for (int j=0;j<2;j++)
            for (int k=0;k<2;k++)
                Ans.M[i][j]=(Ans.M[i][j]+A.M[i][k]*B.M[k][j]%Mod)%Mod;
    return Ans;
}

ll n;

int main()
{
    cin>>n;
    if (n<=2)
    {
        cout<<1<<endl;
        return 0;
    }
    n=n-2;
    int a[2][2]={{1,1},{0,0}};//初始矩阵
    int b[2][2]={{1,1},{1,0}};//即上文的T
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