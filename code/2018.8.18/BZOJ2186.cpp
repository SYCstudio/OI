#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10000100;
const int inf=2147483647;

int R;
int pcnt,P[maxN];
bool notprime[maxN];
int S1[maxN],S2[maxN],Fc[maxN];

void Init();
int QPow(int x,int cnt);

int main(){
	int TTT;
	scanf("%d%d",&TTT,&R);
	Init();
	while (TTT--){
		int n,m;scanf("%d%d",&n,&m);
		printf("%lld\n",1ll*Fc[n]*S2[m]%R*QPow(S1[m],R-2)%R);
	}

	return 0;
}

void Init(){
	notprime[1]=1;
	for (int i=2;i<maxN;i++){
		if (notprime[i]==0) P[++pcnt]=i;
		for (int j=1;(j<=pcnt)&&(1ll*i*P[j]<maxN);j++){
			notprime[i*P[j]]=1;
			if (i%P[j]==0) break;
		}
	}

	S1[0]=S2[0]=Fc[0]=1;
	for (int i=1;i<maxN;i++){
		S1[i]=S1[i-1];S2[i]=S2[i-1];
		Fc[i]=1ll*Fc[i-1]*i%R;
		if (notprime[i]==0){
			S1[i]=1ll*S1[i]*i%R;
			S2[i]=1ll*S2[i]*(i-1)%R;
		}
	}

	return;
}

int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%R;
		x=1ll*x*x%R;cnt>>=1;
	}
	return ret;
}
