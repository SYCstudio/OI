#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr));

const int maxN=65;
const int maxM=3010;
const int Mod=1000000007;
const int maxT=1010000;
const int inf=2147483647;

int n,m,mx;
int EU[maxM],EV[maxM],EW[maxM];
int notprime[maxT],pcnt,P[maxT],Mu[maxT];
int F[maxT],D[maxT],G[maxT];
int Mt[maxN][maxN];
int UFS[maxN];

void Init(int up);
int Guess();
int QPow(int x,int cnt);
int Find(int x);

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++){
		scanf("%d%d%d",&EU[i],&EV[i],&EW[i]);mx=max(mx,EW[i]);
		for (int j=1;1ll*j*j<=EW[i];j++)
			if (EW[i]%j==0){
				++D[j];
				if (j!=EW[i]/j) ++D[EW[i]/j];
			}
	}
	Init(mx);
	for (int i=1;i<=mx;i++)
		if (D[i]>=n-1){
			mem(Mt,0);for (int j=1;j<=n;j++) UFS[j]=j;
			for (int j=1;j<=m;j++)
				if (EW[j]%i==0){
					++Mt[EU[j]][EU[j]];++Mt[EV[j]][EV[j]];
					--Mt[EU[j]][EV[j]];--Mt[EV[j]][EU[j]];
					UFS[Find(EU[j])]=Find(EV[j]);
				}
			bool flag=1;
			for (int j=2;(j<=n)&&(flag);j++) if (Find(j)!=Find(1)) flag=0;
			if (flag==0) continue;
			F[i]=Guess();
			//cout<<"Calc:"<<i<<" "<<F[i]<<endl;
		}
	//for (int i=1;i<=mx;i++) cout<<F[i]<<" ";cout<<endl;
	int Ans=0;
	for (int i=1;i<=mx;i++){
		for (int j=i;j<=mx;j=j+i)
			G[i]=(G[i]+1ll*F[j]*Mu[j/i]%Mod)%Mod;
		//cout<<G[i]<<" ";
		G[i]=(G[i]+Mod)%Mod;Ans=(Ans+1ll*G[i]*i%Mod)%Mod;
	}//cout<<endl;
	printf("%d\n",Ans);return 0;
}

void Init(int up){
	notprime[1]=1;Mu[1]=1;
	for (int i=2;i<=up;i++){
		if (notprime[i]==0) P[++pcnt]=i,Mu[i]=-1;
		for (int j=1;(j<=pcnt)&&(1ll*i*P[j]<=up);j++){
			notprime[i*P[j]]=1;
			if (i%P[j]==0) break;
			Mu[i*P[j]]=-Mu[i];
		}
	}
	//for (int i=1;i<=20;i++) cout<<P[i]<<" ";cout<<endl;
	//for (int i=1;i<=20;i++) cout<<Mu[i]<<" ";cout<<endl;
	return;
}
int Guess(){
	for (int i=1;i<=n;i++) for (int j=1;j<=n;j++) Mt[i][j]=(Mt[i][j]%Mod+Mod)%Mod;
	/*
	cout<<"Guess:"<<endl;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++)
			cout<<Mt[i][j]<<" ";
		cout<<endl;
	}
	//*/
	int ret=1;
	for (int i=1;i<n;i++){
		int now=i;
		while (Mt[now][i]==0) ++now;
		if (now!=i){
			for (int j=1;j<n;j++) swap(Mt[i][j],Mt[now][j]);
			ret=(Mod-ret);
		}
		int inv=QPow(Mt[i][i],Mod-2);
		for (int j=1;j<n;j++)
			if ((j!=i)&&(Mt[j][i])){
				int mul=1ll*inv*Mt[j][i]%Mod;
				for (int k=1;k<n;k++) Mt[j][k]=(Mt[j][k]-1ll*Mt[i][k]*mul%Mod+Mod)%Mod;
			}
		ret=1ll*ret*Mt[i][i]%Mod;
	}
	/*
	for (int i=1;i<=n;i++){
		for (int j=1;j<=n;j++)
			cout<<Mt[i][j]<<" ";
		cout<<endl;
	}
	//*/
	return (ret%Mod+Mod)%Mod;
}
int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

int Find(int x){
	if (UFS[x]!=x) UFS[x]=Find(UFS[x]);
	return UFS[x];
}
