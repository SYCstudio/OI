#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long

ll n,m;

class Matrix//定义矩阵
{
public:
    ll M[3][3];
    Matrix()
    {
        memset(M,0,sizeof(M));
    }
    Matrix(ll Arr[3][3])
    {
        for (int i=0;i<3;i++)
            for (int j=0;j<3;j++)
                M[i][j]=Arr[i][j];
    }
};

Matrix operator * (Matrix A,Matrix B)//重载乘法操作
{
    Matrix Ans;
    for (int i=0;i<3;i++)
        for (int j=0;j<3;j++)
            for (int k=0;k<3;k++)
                Ans.M[i][j]=(Ans.M[i][j]+A.M[i][k]*B.M[k][j]%m)%m;
    return Ans;
}

int main()
{
    cin>>n>>m;
    ll now;
    ll last=0;
    ll a[3][3]={{0,1,1},{0,0,0},{0,0,0}};
    ll b[3][3]={{0,0,0},{1,1,0},{0,1,1}};
    Matrix A(a);
    for (ll i=10;last<n;i=i*10)//分情况进行矩阵快速幂
    {
        b[0][0]=i%m;
        Matrix B(b);
        now=min(i-1,n)-last;//now是当前这么多位能到的最大数，如两位时是99-9=9,三位时是999-99=900,注意要与n取一次最小
        //cout<<now<<' '<<last<<endl;
        //system("pause");
        while (now!=0)//矩阵快速幂
        {
            //cout<<now<<endl;
            if (now&1)
                A=A*B;
            B=B*B;
            now=now>>1;
        }
        last=min(i-1,n);//Last记录上次能到的最大数
    }
    cout<<A.M[0][0]<<endl;
    return 0;
}