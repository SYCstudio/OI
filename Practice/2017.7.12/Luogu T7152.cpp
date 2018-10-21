#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long

ll n,X,Mod;

class Matrix//定义一个矩阵结构体
{
public:
    ll M[3][3];
    Matrix()//初始化0
    {
        for (int i=0;i<3;i++)
            for (int j=0;j<3;j++)
                M[i][j]=0;
    }
    Matrix(ll Arr[3][3])//用数组来初始化
    {
        for (int i=0;i<3;i++)
            for (int j=0;j<3;j++)
                M[i][j]=Arr[i][j];
    }
};

Matrix operator * (Matrix A,Matrix B)//重载乘法运算符
{
    Matrix Ans;
    for (int i=0;i<3;i++)
        for (int j=0;j<3;j++)
            for (int k=0;k<3;k++)
                Ans.M[i][j]=(Ans.M[i][j]+A.M[i][k]*B.M[k][j]%Mod)%Mod;
    return Ans;
}

const int inf=2147483647;

ll Pow();

int main()//无比简单的主函数
{
    cin>>n>>X>>Mod;
    cout<<Pow()<<endl;
    return 0;
}

ll Pow()//矩阵快速幂
{
    ll a[3][3]={{0,1,1},{0,0,0},{0,0,0}};//初始状态
    ll b[3][3]={{X,0,0},{1,1,0},{0,1,1}};//用来使状态发生转移的矩阵，即文中提到的T
    Matrix A(a);
    Matrix B(b);
    while (n!=0)
    {
        if (n&1)
        {
            A=A*B;//注意这里的乘法顺序，矩阵乘法不满足交换律
        }
        B=B*B;
        n=n>>1;
    }
    return A.M[0][0];//根据我们的定义，最后的值就在A.M[0][0]
}