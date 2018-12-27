#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<map>
using namespace std;

#define uint unsigned int
#define ll long long

const int maxN=10100000;

int notprime[maxN],pcnt,P[maxN],Phi[maxN],Pow[maxN];
uint PSum[maxN],PhiSum[maxN];
uint Stl[60][60];

void Init(int K);
uint QPow(uint x,int cnt);

namespace Min25
{
	int n,srt,num,Num[maxN+maxN],Id[maxN];
	uint G[maxN+maxN];

	uint KSum(int n,int K);
	uint Calc(int nn,int K);
	int GetId(int x);
	uint S(int n,int k);
}

namespace Du
{
	map<int,uint> Mp;
	uint Calc(int n);
}

int main(){
	int n,K;scanf("%d%d",&n,&K);
	Init(K);uint Ans=0;
	for (int i=1,j;i<=n;i=j+1){
		j=n/(n/i);
		Ans=Ans+(Min25::Calc(j,K)-Min25::Calc(i-1,K))*Du::Calc(n/i);
	}
	printf("%u\n",Ans);return 0;
}

void Init(int K){
	notprime[1]=1;Phi[1]=1;
	for (int i=2;i<maxN;i++){
		if (notprime[i]==0) P[++pcnt]=i,Phi[i]=i-1,Pow[i]=QPow(i,K);
		for (int j=1;(j<=pcnt)&&(1ll*i*P[j]<maxN);j++){
			notprime[i*P[j]]=1;Pow[i*P[j]]=Pow[i]*Pow[P[j]];
			if (i%P[i]==0){
				Phi[i*P[j]]=Phi[i]*P[j];break;
			}
			Phi[i*P[j]]=Phi[i]*(P[j]-1);
		}
	}
	for (int i=1;i<=pcnt;i++) PSum[i]=PSum[i]+P[i];
	for (int i=1;i<maxN;i++) PhiSum[i]=PhiSum[i]+Phi[i];
	Stl[0][0]=1;
	for (int i=1;i<=K;i++) for (int j=1;j<=K;j++) Stl[i][j]=Stl[i-1][j-1]+Stl[i-1][j]*j;
	return;
}

uint QPow(uint x,int cnt){
	uint ret=1;
	while (cnt){
		if (cnt) ret=ret*x;
		x=x*x;cnt>>=1;
	}
	return ret;
}

namespace Min25
{
	uint KSum(int n,int K){
		uint ret=0;
		for (int i=1;i<=K;i++){
			uint mul=1;bool flag=0;
			for (int j=n-i+1;j<=n+1;j++)
				if ((j%(i+1)==0)&&(flag==0)) flag=1,mul=j/(i+1)*mul;
				else mul=mul*j;
			ret=ret+mul*Stl[K][i];
		}
		return ret;
	}
	
	uint Calc(int nn,int K){
		num=0;n=nn;srt=sqrt(nn);
		for (int i=1,j;i<=n;i=j+1){
			j=n/i;Num[++num]=j;G[num]=KSum(j,K)-1;
			if (j<=srt) Id[j]=num;
			else Id[i+maxN]=num;
		}
		for (int i=1;1ll*P[i]*P[i]<=n;i++)
			for (int j=1;1ll*P[i]*P[i]<=Num[j];j++)
				G[j]=G[j]-(G[GetId(Num[j]/P[i])]-PSum[j-1])*P[j];
		return S(n,1);
	}

	int GetId(int x){
		if (n<=srt) return Id[x];
		return Id[n/x+maxN];
	}
	
	uint S(int n,int k){
		if (n<P[k]) return 0;
		uint ans=0,sum=G[GetId(n)]-PSum[k-1];
		for (int i=k;1ll*P[i]*P[i]<=n;i++){
			int mul=P[i];
			for (int e=1;1ll*mul*P[i]<=n;e++,mul*=P[i]){
				uint R=S(n/mul,i+1);
				ans=ans+R*Pow[mul/P[i]];ans=ans+Pow[mul];
				sum=sum+Pow[mul]*R+Pow[mul*P[i]];
			}
		}
		return (k==1)?ans:sum;
	}
}

namespace Du
{
	uint Calc(int n){
		if (n<maxN) return PhiSum[n];
		if (Mp.count(n)) return Mp[n];
		uint ret=(uint)((ll)n*(n+1)/2);
		for (int i=2,j;i<=n;i=j+1){
			j=n/(n/i);
			ret=ret-(j-i+1)*Calc(n/i);
		}
		return Mp[n]=ret;
	}
}
