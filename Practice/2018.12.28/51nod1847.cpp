#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<map>
#include<iostream>
using namespace std;

#define uint unsigned int

const int maxN=1010000;

int n,K,srt;
int notprime[maxN],pcnt,P[maxN];
int Phi[maxN];
uint Phisum[maxN],Pow[maxN],Powsum[maxN],Stl[60][60];
int num,Num[maxN+maxN],Id[maxN+maxN],G1[maxN+maxN],G2[maxN+maxN],G3[maxN+maxN];
map<int,uint> Mp;

void Init();
uint QPow(uint x,int cnt);
int GetId(int x);
uint KSum(int n);
uint Du(int n);

int main(){
	scanf("%d%d",&n,&K);srt=sqrt(n);Init();
	for (int i=1,j;i<=n;i=j+1){
		j=n/i;Num[++num]=j;G1[num]=KSum(j)-1;G2[num]=j-1;
		if (j<=srt) Id[j]=num;
		else Id[i+maxN]=num;
		j=n/j;
		//cout<<i<<" "<<j<<endl;
	}
	//for (int i=1;i<=num;i++) cout<<Num[i]<<" "<<G1[i]<<endl;
	for (int i=1;1ll*P[i]*P[i]<=n;i++)
		for (int j=1;(j<=num)&&(1ll*P[i]*P[i]<=Num[j]);j++){
			G3[j]=G3[j]+G1[GetId(Num[j]/P[i])]-Powsum[i-1];
			G1[j]=G1[j]-Pow[P[i]]*(G1[GetId(Num[j]/P[i])]-Powsum[i-1]);
			G2[j]=G2[j]-G2[GetId(Num[j]/P[i])]+i-1;
		}
	//for (int i=1;i<=num;i++) cout<<Num[i]<<" ";cout<<endl;
	//for (int i=1;i<=num;i++) cout<<G1[i]<<" ";cout<<endl;
	//for (int i=1;i<=num;i++) cout<<G2[i]<<" ";cout<<endl;
	for (int i=1;i<=num;i++) G3[i]=G3[i]+G2[i];
	//for (int i=1;i<=num;i++) cout<<G3[i]<<" ";cout<<endl;
	uint Ans=0;
	for (int i=1,j;i<=n;i=j+1){
		j=n/(n/i);
		//cout<<i<<" "<<j<<endl;
		Ans=Ans+(G3[GetId(j)]-G3[GetId(i-1)])*(Du(n/i)*2-1);
	}
	printf("%u\n",Ans);return 0;
}

void Init(){
	notprime[1]=1;Phi[1]=1;Pow[1]=1;
	for (int i=2;i<maxN;i++){
		if (notprime[i]==0) P[++pcnt]=i,Phi[i]=i-1,Pow[i]=QPow(i,K);
		for (int j=1;(j<=pcnt)&&(1ll*i*P[j]<maxN);j++){
			notprime[i*P[j]]=1;Pow[i*P[j]]=Pow[i]*Pow[P[j]];
			if (i%P[j]==0){
				Phi[i*P[j]]=Phi[i]*P[j];break;
			}
			Phi[i*P[j]]=Phi[i]*Phi[P[j]];
		}
	}
	for (int i=1;i<maxN;i++) Phisum[i]=Phisum[i-1]+Phi[i];
	for (int i=1;i<=pcnt;i++) Powsum[i]=Powsum[i-1]+Pow[P[i]];
	Stl[0][0]=1;
	for (int i=1;i<=K;i++) for (int j=1;j<=i;j++) Stl[i][j]=Stl[i-1][j-1]+Stl[i-1][j]*j;

	//for (int i=1;i<=20;i++) cout<<P[i]<<" ";cout<<endl;
	//for (int i=1;i<=20;i++) cout<<Powsum[i]<<" ";cout<<endl;
	return;
}

uint QPow(uint x,int cnt){
	uint ret=1;
	while (cnt){
		if (cnt&1) ret=ret*x;
		x=x*x;cnt>>=1;
	}
	return ret;
}

int GetId(int x){
	if (x<=srt) return Id[x];
	return Id[n/x+maxN];
}

uint KSum(int n){
	int ret=0;
	for (int i=1;i<=K;i++){
		uint mul=1;bool flag=0;
		for (int j=n-i+1;j<=n+1;j++)
			if ((j%(i+1)==0)&&(flag==0)) mul=j/(i+1)*mul,flag=1;
			else mul=mul*j;
		ret=ret+Stl[K][i]*mul;
	}
	return ret;
}

uint Du(int n){
	//cout<<"GetDu:"<<n<<endl;
	if (n<maxN) return Phisum[n];
	if (Mp.count(n)) return Mp[n];
	uint ret=1ll*n*(n+1)/2;
	for (int i=2,j;i<=n;i=j+1){
		j=n/(n/i);
		ret=ret-(j-i+1)*Du(n/i);
	}
	return Mp[n]=ret;
}

