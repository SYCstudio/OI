#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100;
const ll Mod=1e9+7;
const int inv2=500000004;
const int inf=2147483647;

ll na,A[maxN],nb,B[maxN];
ll n,m;
ll F[maxN][2][2];

void Plus(ll &x,ll y);

int main(){
	ll TTT,K;scanf("%lld%lld",&TTT,&K);
	while (TTT--){
		scanf("%lld%lld",&n,&m);na=nb=0;mem(F,0);mem(A,0);mem(B,0);m=min(n,m);
		ll Ans=0;
		Ans=((n+1)%Mod)*((n+2)%Mod)%Mod*inv2%Mod;
		//cout<<"AA:"<<Ans<<endl;
		if (n>m) Ans=((Ans-((n-m)%Mod)*((n-m+1)%Mod)%Mod*inv2%Mod)%Mod+Mod)%Mod;
		//cout<<"AB:"<<Ans<<endl;
		//Ans=(Ans-m%Mod*(m-1)%Mod*inv2%Mod+Mod)%Mod;
		while (n) A[++na]=n%K,n/=K;
		while (m) B[++nb]=m%K,m/=K;
		int mxn=max(na,nb);F[0][0][0]=1;
		for (int i=0;i<mxn;i++)
			for (int a=0;a<K;a++)
				for (int b=0;b<=a;b++){
					Plus(F[i+1][a>A[i+1]][b>B[i+1]],F[i][0][0]);
					Plus(F[i+1][a>=A[i+1]][b>B[i+1]],F[i][1][0]);
					Plus(F[i+1][a>A[i+1]][b>=B[i+1]],F[i][0][1]);
					Plus(F[i+1][a>=A[i+1]][b>=B[i+1]],F[i][1][1]);
				}
		//cout<<"A:"<<Ans<<endl;
		Ans=(Ans-F[mxn][0][0]+Mod)%Mod;
		printf("%lld\n",Ans);
	}
}

void Plus(ll &x,ll y){
	y%=Mod;x=x+y;
	if (x>=Mod) x-=Mod;return;
}
