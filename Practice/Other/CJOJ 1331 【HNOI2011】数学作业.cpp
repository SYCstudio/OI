#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long

ll n,m;

class Matrix
{
public:
	ll M[3][3];
	Matrix()
	{
		memset(M,0,sizeof(M));
	}
	Matrix(ll Arr[3][3])
	{
		for (int i=0; i<3; i++)
			for (int j=0; j<3; j++)
				M[i][j]=Arr[i][j];
	}
};

Matrix operator * (Matrix A,Matrix B)
{
	Matrix Ans;
	for (int i=0; i<3; i++)
		for (int j=0; j<3; j++)
			for (int k=0; k<3; k++)
				Ans.M[i][j]=(Ans.M[i][j]+A.M[i][k]*B.M[k][j]%m)%m;
	return Ans;
}

int main()
{
	cin>>n>>m;
	ll now;
	ll last=0;
	ll a[3][3]= {{0,1,1},{0,0,0},{0,0,0}};
	ll b[3][3]= {{0,0,0},{1,1,0},{0,1,1}};
	Matrix A(a);
	for (ll i=10; last<n; i=i*10) {
		b[0][0]=i%m;
		Matrix B(b);
		now=min(i-1,n)-last;
		//cout<<now<<' '<<last<<endl;
		//system("pause");
		while (now!=0) {
			//cout<<now<<endl;
			if (now&1)
				A=A*B;
			B=B*B;
			now=now>>1;
		}
		last=min(i-1,n);
	}
	cout<<A.M[0][0]<<endl;
	return 0;
}
