#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const int Mod=10000007;
const int maxB=55;
const int Phi=9988440;

ll n;
int Binom[maxB][maxB];

int dfs(int d,int c);
int Calc(int d,int c);
int QPow(int x,int cnt);
int main()
{
	for (int i=0; i<maxB; i++) for (int j=Binom[i][0]=1; j<=i; j++) Binom[i][j]=(Binom[i-1][j-1]+Binom[i-1][j])%Phi;
	/*
	for (int i=0;i<maxB;i++){
	for (int j=0;j<=i;j++) cout<<Binom[i][j]<<" ";cout<<endl;
	}
	//*/
	scanf("%lld",&n);
	printf("%d\n",dfs(50,0));

	/*
	int sum=1;
	for (int i=1;i<=n;i++){
	int x=i,c=0;
	while (x) c+=x&1,x>>=1;
	sum=1ll*sum*c%Mod;
	}
	cout<<sum<<endl;
	//*/

	return 0;
}
int dfs(int d,int c)
{
	if (d==-1) return c==0?1:c;
	int bw=(n>>d)&1;
	if (bw==0) return dfs(d-1,c);
	else return 1ll*Calc(d,c)*dfs(d-1,c+1)%Mod;
}
int Calc(int d,int c)
{
	//cout<<"Calc:"<<d<<" "<<c<<endl;
	if (d==-1) return c;
	int ret=1;
	for (int i=c==0?1:0; i<=d; i++) ret=1ll*ret*QPow(i+c,Binom[d][i])%Mod;
	//cout<<ret<<endl;
	return ret;
}
int QPow(int x,int cnt)
{
	int ret=1;
	while (cnt) {
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;
		cnt>>=1;
	}
	return ret;
}
