#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=200;
const int inf=2147483647;

int n;
int A[maxN];
int F1[maxN][maxN];
int F2[maxN][maxN];

int main()
{
	cin>>n;
	for (int i=1; i<=n; i++)
		cin>>A[i],A[i]=A[i-1]+A[i];
	for (int i=1; i<=n; i++)
		A[i+n]=A[i]+A[n];
	n=n*2;
	memset(F1,126,sizeof(F1));
	memset(F2,129,sizeof(F2));
	for (int i=1; i<=n; i++)
		F1[i][i]=F2[i][i]=0;
	for (int i=n; i>=1; i--)
		for (int j=i+1; j<n; j++)
			for (int k=i; k<j; k++) {
				//cout<<F[i][k]+F[k+1][j]+A[j]-A[i-1]<<' '<<F[i][j]<<endl;
				F1[i][j]=min(F1[i][j],F1[i][k]+F1[k+1][j]+A[j]-A[i-1]);
				F2[i][j]=max(F2[i][j],F2[i][k]+F2[k+1][j]+A[j]-A[i-1]);
			}
	int Ans1=inf;
	int Ans2=-inf;
	for (int i=0; i<=n/2; i++) {
		Ans1=min(Ans1,F1[i][i+n/2-1]);
		Ans2=max(Ans2,F2[i][i+n/2-1]);
	}
	cout<<Ans1<<endl<<Ans2<<endl;
	return 0;
}
