#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

const int maxN=2000;
const int inf=2147483647;

int n,m,mod;
int C[maxN+10][maxN+10];
int If[maxN+10][maxN+10];

int main()
{
	int TT;
	cin>>TT>>mod;
	memset(C,0,sizeof(C));
	for (int i=0; i<=maxN; i++) {
		C[i][0]=1;
		for (int j=1; j<=i; j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	}
	for (int i=0; i<=maxN; i++)
		for (int j=0; j<=i; j++)
			If[i][j]=(bool)(C[i][j])^1;
	/*for (int i=0;i<=10;i++)
	{
	    for (int j=0;j<=10;j++)
	        cout<<If[i][j]<<' ';
	    cout<<endl;
	}
	cout<<endl;*/
	for (int i=1; i<=maxN; i++)
		for (int j=1; j<=maxN; j++)
			If[i][j]=If[i][j]+If[i-1][j]+If[i][j-1]-If[i-1][j-1];
	/*for (int i=0;i<=10;i++)
	{
	    for (int j=0;j<=10;j++)
	        cout<<If[i][j]<<' ';
	    cout<<endl;
	}
	cout<<endl;*/
	for (int ti=1; ti<=TT; ti++) {
		cin>>n>>m;
		cout<<If[n][m]<<endl;
	}
	return 0;
}
