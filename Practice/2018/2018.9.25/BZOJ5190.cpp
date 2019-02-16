#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010000;
const int Mod=1e9+7;
const int inf=2147483647;

int n,m,K;
int F[maxN],Sum[maxN];

int QPow(int x,int cnt);

int main(){
	scanf("%d%d%d",&n,&m,&K);
	F[0]=1;
	for (int i=1;i<K;i++) F[i]=1ll*F[i-1]*m%Mod,Sum[i]=(Sum[i-1]+F[i])%Mod;
	for (int i=K;i<=n;i++) F[i]=1ll*(Sum[i-1]-Sum[i-K]+Mod)%Mod*(m-1)%Mod,Sum[i]=(Sum[i-1]+F[i])%Mod;
	//for (int i=1;i<=n;i++) cout<<F[i]<<" ";cout<<endl;
	printf("%d\n",(QPow(m,n)-F[n]+Mod)%Mod);return 0;
}

int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}
