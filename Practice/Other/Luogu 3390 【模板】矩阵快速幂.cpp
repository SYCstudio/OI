#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long

const int maxN=201;
const ll Mod=1000000007;
const ll inf=2147483647;

int n;

class Matrix
{
public:
	ll M[maxN][maxN];
	Matrix(int x)
	{
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				M[i][j]=x;
	}
	Matrix(ll Arr[maxN][maxN])
	{
		for (int i=0; i<n; i++)
			for (int j=0; j<n; j++)
				M[i][j]=Arr[i][j];
	}
	void print()
	{
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++)
				cout<<M[i][j]<<' ';
			cout<<endl;
		}
	}
};

Matrix operator * (Matrix A,Matrix B)
{
	Matrix Ans(0);
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			for (int k=0; k<n; k++)
				Ans.M[i][j]=(Ans.M[i][j]+A.M[i][k]*B.M[k][j]%Mod)%Mod;
	return Ans;
}

ll Arr[maxN][maxN];

ll read();
void Pow(ll Po);

int main()
{
	n=read();
	ll Po=read();
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			Arr[i][j]=read();
	Pow(Po-1);
	return 0;
}

ll read()
{
	ll x=0;
	ll k=1;
	char ch=getchar();
	while (((ch>'9')||(ch<'0'))&&(ch!='-'))
		ch=getchar();
	if (ch=='-') {
		k=-1;
		ch=getchar();
	}
	while ((ch>='0')&&(ch<='9')) {
		x=x*10+ch-48;
		ch=getchar();
	}
	return x*k;
}

void Pow(ll P)
{
	Matrix A(Arr);
	Matrix B(Arr);
	while (P!=0) {
		if (P&1)
			A=A*B;
		B=B*B;
		P=P>>1;
	}
	A.print();
	return;
}
