#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1000100;

int notprime[maxN],pcnt,P[maxN];
ll n,num,srt,Num[maxN+maxN],Id[maxN+maxN];
ll G[maxN+maxN],Sum[maxN];

void Init();
ll Calc(ll nn);
int GetId(ll x);
ll S(ll n,int k);

int main(){
	Init();
	ll L,R;scanf("%lld%lld",&L,&R);
	printf("%lld\n",Calc(R)-Calc(L-1));
	/*
	int sum=0;
	for (int i=L;i<=R;i++){
		for (int j=i-1;j>1;j--)
			if (i%j==0){
				sum+=j;break;
			}
	}
	cout<<sum<<endl;
	//*/
	
	return 0;
}

void Init(){
	notprime[1]=1;
	for (int i=2;i<maxN;i++){
		if (notprime[i]==0) P[++pcnt]=i,Sum[pcnt]=Sum[pcnt-1]+i;
		for (int j=1;(j<=pcnt)&&(1ll*i*P[j]<maxN);j++){
			notprime[i*P[j]]=1;
			if (i%P[j]==0) break;
		}
	}
	return;
}

ll Calc(ll nn){
	num=0;n=nn;mem(Id,0);srt=sqrt(n);
	for (ll i=1,j;i<=n;i=j+1){
		j=n/i;Num[++num]=j;G[num]=1ll*j*(j+1)/2-1;
		if (j<=srt) Id[j]=num;
		else Id[i+maxN]=num;
		j=n/j;
	}
	for (int i=1;(i<=pcnt)&&(1ll*P[i]*P[i]<=n);i++){
		for (int j=1;(j<=num)&&(1ll*P[i]*P[i]<=Num[j]);j++)
			G[j]=G[j]-(G[GetId(Num[j]/P[i])]-Sum[i-1])*P[i];
	}

	/*
	for (int i=1;i<=num;i++){
		int sum=0;
		for (int j=2;j<=Num[i];j++){
			sum+=j;
			for (int k=2;k<j;k++) if (j%k==0) {sum-=j;break;}
		}
		cout<<Num[i]<<" "<<G[i]<<" "<<sum<<endl;
	}
	//*/

	return S(n,1);
}

int GetId(ll x){
	if (x<=srt) return Id[x];
	else return Id[n/x+maxN];
}

ll S(ll n,int k){
	if (P[k]>n) return 0;
	ll ans=0,sum=0;sum=sum+G[GetId(n)]-Sum[k-1];
	for (int j=k;1ll*P[j]*P[j]<=n;j++){
		ll mul=P[j];
		for (int e=1;1ll*mul*P[j]<=n;e++,mul=mul*P[j]){
			ll R=S(n/mul,j+1);
			ans+=R*mul/P[j];ans+=mul;
			sum+=R*mul+mul*P[j];
		}
	}
	if (k!=1) ans=0;
	//cout<<ss<<endl;
	return (k==1)?(ans):(sum);
}
