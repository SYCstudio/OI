#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<map>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=10001000;
const int Mod=1e9+7;
const int inf=2147483647;

bool notprime[maxN];
int pcnt,Prime[maxN],Mu[maxN];
map<int,int> Rc;

int QPow(int x,int cnt);
void Init();
int Calc(int n);

int main(){
	Init();

	int N,K,L,R;
	scanf("%d%d%d%d",&N,&K,&L,&R);
	L=(L-1)/K;R=R/K;

	int Ans=0,lst=0,now;
	for (int i=1,j;i<=R;i=j+1){
		j=R/(int)(R/i); if (i<=L) j=min(j,L/(int)(L/i));
		//cout<<i<<" "<<j<<endl;
		//cout<<Calc(j)<<" "<<QPow(R/i-L/i,N)<<" "<<(Calc(j)-Calc(i-1))<<endl;
		now=Calc(j);
		Ans=(Ans+1ll*(now-lst)%Mod*QPow(R/i-L/i,N)%Mod)%Mod;
		//cout<<Ans<<endl;
		lst=now;
	}
	Ans=(Ans+Mod)%Mod;

	printf("%d\n",Ans);

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
	//for (int i=1;i<=50;i++) cout<<Mu[i]<<" ";cout<<endl;
	for (int i=1;i<maxN;i++) Mu[i]=(Mu[i-1]+Mu[i])%Mod;
	return;
}

int Calc(int n){
	if (n<maxN) return Mu[n];
	if (Rc.count(n)) return Rc[n];
	int ret=1;
	for (int i=2,j;i<=n;i=j+1){
		j=n/(n/i);
		ret=(ret-1ll*(j-i+1)*Calc(n/i)%Mod)%Mod;
	}
	return Rc[n]=ret;
}
/*
1
0
-1
-1
-2
-1
-2
-2
-2
-1
-2
-2
-3
-1
-2
-3
-2
-4
-1
-1
-1
587978901
//*/
