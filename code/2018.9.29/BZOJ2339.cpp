#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010000;
const int Mod=100000007;
const int inf=2147483647;

int n,m;
ll A[maxN],F[maxN];

int QPow(int x,int cnt);

int main(){
	scanf("%d%d",&n,&m);

	F[1]=F[2]=0;int N=(QPow(2,n)-1+Mod)%Mod;
	A[0]=1;
	for (int i=1;i<=m;i++) A[i]=(1ll*A[i-1]*(N-i+1)%Mod+Mod)%Mod;
	for (int i=3;i<=m;i++) F[i]=((A[i-1]-F[i-1]-1ll*F[i-2]*(i-1)%Mod*(N-(i-2))%Mod)%Mod+Mod)%Mod;

	int x=1;
	for (int i=1;i<=m;i++) x=1ll*x*i%Mod;
	printf("%lld\n",1ll*F[m]*QPow(x,Mod-2)%Mod);
	return 0;
}

int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}
