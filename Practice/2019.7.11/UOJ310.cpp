#include<bits/stdc++.h>
using namespace std;

#define pw(x) (1<<(x))
const int maxN=1010000;
const int maxB=20;
const int Mod=998244353;
const int inv2=Mod/2+1;

int n;
int C[pw(maxB)+10];
int Pw3[maxN];

void FWT(int *P,int N,int opt);
int main(){
	Pw3[0]=1;for (int i=1;i<maxN;i++) Pw3[i]=3ll*Pw3[i-1]%Mod;
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		int key;scanf("%d",&key);++C[key];
	}
	FWT(C,pw(maxB),1);

	for (int i=0;i<pw(maxB);i++){
		int x=1ll*(C[i]+n)*inv2%Mod,y=1ll*(n-C[i]+Mod)*inv2%Mod;
		C[i]=Pw3[x];
		if (y&1) C[i]=Mod-C[i];
	}
	FWT(C,pw(maxB),-1);
	C[0]=(C[0]-1+Mod)%Mod;
	printf("%d\n",C[0]);
	return 0;
}
void FWT(int *P,int N,int opt){
	for (int i=1;i<N;i<<=1)
		for (int j=0;j<N;j+=i+i)
			for (int k=0;k<i;k++){
				int X=P[j+k],Y=P[j+k+i];
				P[j+k]=(X+Y)%Mod;P[j+k+i]=(X-Y+Mod)%Mod;
				if (opt==-1) P[j+k]=1ll*P[j+k]*inv2%Mod,P[j+k+i]=1ll*P[j+k+i]*inv2%Mod;
			}
	return;
}
