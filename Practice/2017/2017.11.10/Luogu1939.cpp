#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int Mod=1e9+7;

class Matrix
{
public:
    ll M[3][3];
    Matrix()
		{
			mem(M,0);
		}
    Matrix(int Arr[3][3])
		{
			for (int i=0;i<3;i++)
				for (int j=0;j<3;j++)
					M[i][j]=Arr[i][j];
		}
};

Matrix operator * (Matrix A,Matrix B)
{
    Matrix Ans;
    for (int i=0;i<3;i++)
		for (int j=0;j<3;j++)
			for (int k=0;k<3;k++)
				Ans.M[i][j]=(Ans.M[i][j]+A.M[i][k]*B.M[k][j]%Mod)%Mod;
    return Ans;
}

int Solve(int n);

int main()
{
    int T;
    scanf("%d",&T);
    while (T--)
    {
		int n;
		scanf("%d",&n);
		printf("%d\n",Solve(n));
    }
    return 0;
}

int Solve(int n)
{
    if (n<=3) return 1;
    n=n-3;
    int Arr[3][3]={{1,1,1},
				   {0,0,0},
				   {0,0,0}};
    int Brr[3][3]={{1,1,0},
				   {0,0,1},
				   {1,0,0}};
    Matrix A(Arr);
    Matrix B(Brr);
    while (n)
    {
		if (n&1) A=A*B;
		B=B*B;
		n=n>>1;
    }
    return A.M[0][0];
}
