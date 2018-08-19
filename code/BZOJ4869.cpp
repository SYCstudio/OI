#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50100;
const int maxBit=31;
const int Blocksize=100000;
const int inf=2147483647;

int n,m,P,C;
int pcnt,phi[maxN];
int A[maxBit][maxN];
int Pow1[maxBit][Blocksize],Pow2[maxBit][Blocksize];

int GetPhi(int x);
void Init();

int main(){
	scanf("%d%d%d%d",&n,&m,&P,&C);
	for (int i=1;i<=n;i++) scanf("%d",&A[0][i]);

	int nowP=P;
	while (nowP!=1) phi[++pcnt]=nowP,nowP=GetPhi(nowP);
	phi[++pcnt]=1;

	Init();
}

int GetPhi(int x){
	int ret=x;
	for (int i=2;1ll*i*i<=x;i++)
		if (x%i==0){
			ret=ret/i*(i-1);
			while (x%i==0) x/=i;
		}
	if (x!=1) ret=ret/x*(x-1);
	return ret;
}

void Init(){
	for (int i=1;i<=scnt;i++){
		Pow1[i][0]=1;
		for (int j=1;j<blocksize;j++) Pow1[i][j]=1ll*Pow1[i][j-1]*C%Phi[i];
		Pow2[i][0]=1;Pow2[i][1]=1ll*Pow1[i][blocksize-1]*C%Phi[i];
	}
}
