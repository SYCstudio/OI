#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

const int maxsize=1001;
const int inf=2147483647;
const long long P=10007;

long long A,B,K,N,M;
long long Tri[maxsize][maxsize]= {0};

int main()
{
	cin>>A>>B>>K>>N>>M;
	Tri[0][1]=1;
	for (int i=1; i<=K; i++) {
		Tri[i][1]=1;
		for (int j=2; j<=i; j++)
			Tri[i][j]=(Tri[i-1][j-1]+Tri[i-1][j])%P;
		Tri[i][i+1]=1;
	}

	/*for (int i=1;i<=K;i++)
	{
	    for (int j=1;j<=i+1;j++)
	        cout<<Tri[i][j]<<" ";
	    cout<<endl;
	}*/

	long long S1=1,S2=1;
	for (int i=1; i<=N; i++)
		S1=S1*A%P;
	for (int i=1; i<=M; i++)
		S2=S2*B%P;
	cout<<S1*S2%P*Tri[K][N+1]%P<<endl;
	return 0;
}
