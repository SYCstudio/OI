#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10100000;
const int Mod=1e9+7;
const int inf=2147483647;

int inv2,inv6;
bool notprime[maxN];
int pricnt,Prime[maxN],Phi[maxN];
map<int,int> Rc;

int QPow(int x,int cnt);
void Init();
int Calc(int n);

int main(){
	inv2=QPow(2,Mod-2);inv6=QPow(6,Mod-2);
	Init();

	int N;scanf("%d",&N);
	printf("1\n%d\n",Calc(N));

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
	Phi[1]=1;notprime[1]=1;
	for (int i=2;i<maxN;i++){
		if (notprime[i]==0) Prime[++pricnt]=i,Phi[i]=i-1;
		for (int j=1;(j<=pricnt)&&(1ll*i*Prime[j]<maxN);j++){
			notprime[i*Prime[j]]=1;
			if (i%Prime[j]==0){
				Phi[i*Prime[j]]=Phi[i]*Prime[j];break;
			}
			Phi[i*Prime[j]]=Phi[i]*Phi[Prime[j]];
		}
	}

	//for (int i=1;i<=40;i++) cout<<Phi[i*i]<<" ";cout<<endl;
	for (int i=1;i<maxN;i++) Phi[i]=1ll*Phi[i]*i%Mod;

	for (int i=1;i<maxN;i++) Phi[i]=(Phi[i]+Phi[i-1])%Mod;

	return;
}

int Calc(int n){
	if (n<maxN) return Phi[n];
	if (Rc.count(n)) return Rc[n];
	int ret=0;
	for (int i=2,j;i<=n;i=j+1){
		j=n/(int)(n/i);
		ret=(ret+1ll*(i+j)*(j-i+1)%Mod*inv2%Mod*Calc(n/i)%Mod)%Mod;
	}
	return Rc[n]=(1ll*n*(n+1)%Mod*(2*n+1)%Mod*inv6%Mod+Mod-ret)%Mod;
}
