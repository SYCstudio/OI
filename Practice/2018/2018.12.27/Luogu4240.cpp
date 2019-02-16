#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;

#define ll long long

const int maxN=100010;
const int Mod=998244353;
const int maxB=50;

bool notprime[maxN];
int pcnt,P[maxN];
int Mu[maxN],Phi[maxN];
int F[maxN];
vector<int> G[maxN],S[maxB+5][maxB+5];

int QPow(int x,int cnt);
void Init();

int main(){
	Init();
	int Case=0;scanf("%d",&Case);
	while (Case--){
		int n,m;scanf("%d%d",&n,&m);
		if (n>m) swap(n,m);
		int up=(m+maxB)/maxB+1,Ans=0;if (up>n) up=n;
		//cout<<"up:"<<up<<endl;
		//int up=n,Ans=0;
		for (int i=1;i<=up;i++) Ans=(Ans+1ll*F[i]*G[n/i][i]%Mod*G[m/i][i]%Mod)%Mod;
		for (int i=up+1,j;i<=n;i=j+1){
			//cout<<i<<" "<<j<<" "<<n/i<<" "<<m/i<<" "<<S[n/i][m/i].size()<<endl;
			j=min(n/(n/i),m/(m/i));
			Ans=(Ans+((S[n/i][m/i][j]-S[n/i][m/i][i-1]+Mod)%Mod))%Mod;
		}
		printf("%d\n",Ans);
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
	notprime[1]=1;Mu[1]=1;Phi[1]=1;
	for (int i=2;i<maxN;i++){
		if (notprime[i]==0) notprime[i]=1,Mu[i]=Mod-1,Phi[i]=i-1,P[++pcnt]=i;
		for (int j=1;(j<=pcnt)&&(1ll*i*P[j]<maxN);j++){
			notprime[i*P[j]]=1;
			if (i%P[j]==0){
				Phi[i*P[j]]=Phi[i]*P[j];break;
			}
			Mu[i*P[j]]=Mod-Mu[i];Phi[i*P[j]]=Phi[i]*Phi[P[j]];
		}
	}
	for (int x=1;x<maxN;x++){
		int f=1ll*x*QPow(Phi[x],Mod-2)%Mod;
		for (int d=x;d<maxN;d=d+x){
			F[d]=(F[d]+1ll*f*Mu[d/x]%Mod)%Mod;
		}
	}
	for (int n=1;n<maxN;n++) G[n].resize(maxN/n+3);
	for (int d=1;d<maxN;d++) G[1][d]=Phi[d];
	for (int n=2;n<maxN;n++)
		for (int d=1;d<=maxN/n;d++)
			G[n][d]=(G[n-1][d]+Phi[n*d])%Mod;
	for (int i=1;i<=maxB;i++)
		for (int j=1;j<=maxB;j++){
			int lim=min(G[i].size(),G[j].size());
			S[i][j].resize(lim+5);
			//cout<<lim<<" "<<S[i][j].size()<<" "<<G[i].size()<<" "<<G[j].size()<<endl;
			for (int K=1;K<=lim;K++){
				//if (K>=30000) cout<<lim<<" "<<S[i][j].size()<<" "<<K<<endl;
				S[i][j][K]=(S[i][j][K-1]+1ll*F[K]*G[i][K]%Mod*G[j][K]%Mod)%Mod;
			}
			//*/
		}
	//cout<<sizeof(S)<<endl;
	return;
}
