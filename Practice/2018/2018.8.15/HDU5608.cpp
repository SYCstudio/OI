#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1000000;
const int Mod=1e9+7;
const int inf=2147483647;

bool notprime[maxN];
int pcnt,Prime[maxN],Mu[maxN];
int inv3;
int F[maxN];
map<int,int> Rc;

int QPow(int x,int cnt);
void Init();
int Calc(int n);

int main(){
	inv3=QPow(3,Mod-2);
	Init();

	int TTT;scanf("%d",&TTT);
	while (TTT--){
		int n;scanf("%d",&n);
		printf("%d\n",Calc(n));
	}

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

void Init(){
	Mu[1]=1;notprime[1]=1;
	for (int i=2;i<maxN;i++){
		if (notprime[i]==0) Prime[++pcnt]=i,Mu[i]=-1;
		for (int j=1;(j<=pcnt)&&(1ll*i*Prime[j]<maxN);j++){
			notprime[i*Prime[j]]=1;
			if (i%Prime[j]==0){
				Mu[i*Prime[j]]=0;break;
			}
			Mu[i*Prime[j]]=-Mu[i];
		}
	}
	for (int i=1;i<maxN;i++){
		int g=((1ll*i*i%Mod-3ll*i+2)%Mod+Mod)%Mod;
		for (int j=i;j<maxN;j+=i)
			F[j]=(F[j]+1ll*g*Mu[j/i]+Mod)%Mod;
	}
	for (int i=1;i<maxN;i++) F[i]=(F[i-1]+F[i])%Mod;
	return;
}

int Calc(int n){
	if (n<maxN) return F[n];
	if (Rc.count(n)) return Rc[n];
	int ret=0;
	for (int i=2,j;i<=n;i=j+1){
		j=n/(int)(n/i);
		ret=(ret+1ll*(j-i+1)*Calc(n/i)%Mod)%Mod;
	}
	return Rc[n]=(1ll*n*(n-1)%Mod*(n-2)%Mod*inv3%Mod+Mod-ret)%Mod;
}
