#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=32;
const int maxC=maxN*maxN;
const int Mod=1000000009;
const int maxNum=100001;
const int inf=2147483647;

int n,m,c;
int Cnt[maxC];
int Fac[maxNum],Inv[maxNum];
int F[maxN][maxN][maxC];
int G[maxN][maxN][maxC];

int QPow(int x,int cnt);
int C(int n,int m);

int main(){
	freopen("out","w",stdout);
	//scanf("%d%d%d",&n,&m,&c);
	//for (int i=1;i<=c;i++) scanf("%d",&Cnt[i]);
	Fac[0]=Inv[0]=1;
	for (int i=1;i<maxNum;i++) Fac[i]=1ll*Fac[i-1]*i%Mod;
	Inv[maxNum-1]=QPow(Fac[maxNum-1],Mod-2);
	for (int i=maxNum-2;i>=1;i--) Inv[i]=1ll*Inv[i+1]*(i+1)%Mod;

	for (int i=0;i<=10;i++) cout<<Fac[i]<<" ";cout<<endl;
	for (int i=0;i<=10;i++) cout<<Inv[i]<<" ";cout<<endl;

	for (int i=1;i<=10;i++)
		for (int j=1;j<=i;j++) G[i][1][j]=C(i,j);
	for (int i=1;i<=10;i++)
		for (int j=2;j<=10;j++)
			for (int k=max(i,j);k<=i*j;k++)
				for (int p=k-1;k-p<=i;p--) G[i][j][k]+=G[i][j-1][p]*C(i,k-p);
	for (int i=1;i<=5;i++)
		for (int j=1;j<=5;j++){
			cout<<"("<<i<<" "<<j<<")"<<endl;
			for (int k=1;k<=i*j;k++)
				cout<<G[i][j][k]<<" ";
			cout<<endl;
		}
}

int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

int C(int n,int m){
	if (n<m) return 0;
	cout<<"C:"<<n<<" "<<m<<":"<<1ll*Fac[n]*Inv[n-m]%Mod*Inv[m]%Mod<<endl;
	return 1ll*Fac[n]*Inv[n-m]%Mod*Inv[m]%Mod;
}
