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
const int maxK=5010;
const int inf=2147483647;

int N,M,K;
int G[maxK];
bool notprime[maxN];
int pcnt,Prime[maxN],Mu[maxN],SMu[maxN];
map< pair<int,int>,int> Rc;

int gcd(int a,int b);
void Init();
int CalcF(int n,int k);
int CalcG(int n);

int main(){
	scanf("%d%d%d",&N,&M,&K);
	Init();

	ll Ans=0,lst=0,now;
	for (int i=1,j;i<=min(N,M);i=j+1){
		j=min(N/(N/i),M/(M/i));
		//cout<<i<<" "<<j<<endl;
		now=CalcF(j,K);
		Ans=Ans+1ll*(ll)(N/i)*(now-lst)*CalcG(M/i);
		lst=now;
	}

	printf("%lld\n",Ans);
	return 0;
}

int gcd(int a,int b){
	int t;
	while (a) t=a,a=b%a,b=t;
	return b;
}

void Init(){
	for (int i=1;i<=K;i++) G[i]=(gcd(i,K)==1);
	for (int i=1;i<=K;i++) G[i]=G[i-1]+G[i];
	//for (int i=1;i<=100;i++) cout<<G[i]<<" ";cout<<endl;
	notprime[1]=1;Mu[1]=1;
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
	//for (int i=1;i<=100;i++) cout<<Mu[i]<<" ";cout<<endl;
	for (int i=1;i<maxN;i++) SMu[i]=SMu[i-1]+Mu[i];
	return;
}

int CalcF(int n,int k){
	if (n==0) return 0;
	if ((k==1)&&(n<maxN)) return SMu[n];
	if (Rc.count(make_pair(n,k))) return Rc[make_pair(n,k)];
	int ret=0;
	if (k==1){
		ret=1;
		for (int i=2,j;i<=n;i=j+1){
			j=n/(n/i);
			ret=ret-(j-i+1)*CalcF(n/i,k);
		}
	}
	else{
		for (int i=1;i*i<=k;i++)
			if (k%i==0){
				if (Mu[i]!=0) ret=ret+CalcF(n/i,i);
				if ((i*i!=k)&&(Mu[k/i]!=0)) ret=ret+CalcF(n/(k/i),k/i);
			}
	}
	return Rc[make_pair(n,k)]=ret;
}

int CalcG(int n){
	return (n/K)*G[K]+G[n%K];
}
