#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*15;
const int Mod=998244353;
const int G=3;
const int inf=2147483647;

char Input[maxN];
int A[maxN],B[maxN],C[maxN],D[maxN],Rader[maxN];

int QPow(int x,int cnt);
void NTT(int *P,int N,int opt);

int main()
{
	scanf("%s",Input);
	int len=strlen(Input);
	reverse(&Input[0],&Input[len]);
	
	for (int i=0;i<len;i++) A[i]=B[i]=C[i]=D[i]=Input[i]-'0';
	A[0]+=1;B[0]+=2;C[0]+=3;D[0]+=4;
	//cout<<A[0]<<" "<<B[0]<<" "<<C[0]<<" "<<D[0]<<endl;

	int N,L=0;
	for (N=1;N<=len*2;N<<=1) L++;
	for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	
	NTT(A,N,1);NTT(B,N,1);
	for (int i=0;i<N;i++) A[i]=1ll*A[i]*B[i]%Mod;
	NTT(A,N,-1);
	for (int i=0;i<N;i++) A[i+1]+=A[i]/10,A[i]%=10;

	L=0;
	for (N=1;N<=len*3;N<<=1) L++;
	for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	NTT(A,N,1);NTT(C,N,1);
	for (int i=0;i<N;i++) A[i]=1ll*A[i]*C[i]%Mod;
	NTT(A,N,-1);
	for (int i=0;i<N;i++) A[i+1]+=A[i]/10,A[i]%=10;

	L=0;
	for (N=1;N<=len*4;N<<=1) L++;
	for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	NTT(A,N,1);NTT(D,N,1);
	for (int i=0;i<N;i++) A[i]=1ll*A[i]*D[i]%Mod;
	NTT(A,N,-1);
	
	for (int i=N;i>=1;i--) A[i-1]+=A[i]%24*10,A[i]/=24;
	A[0]/=24;
	for (int i=0;i<N;i++) A[i+1]+=A[i]/10,A[i]%=10;
	int p;
	for (p=N;p>=0;p--) if (A[p]!=0) break;
	for (;p>=0;p--) printf("%d",A[p]);
	printf("\n");
	return 0;
}

int QPow(int x,int cnt)
{
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

void NTT(int *P,int N,int opt)
{
	for (int i=0;i<N;i++) if (i<Rader[i]) swap(P[i],P[Rader[i]]);
	for (int i=1;i<N;i<<=1)
	{
		int dw=QPow(G,(Mod-1)/(i<<1));
		if (opt==-1) dw=QPow(dw,Mod-2);
		for (int j=0;j<N;j+=(i<<1))
			for (int k=0,w=1;k<i;k++,w=1ll*w*dw%Mod)
			{
				int x=P[j+k],y=1ll*P[j+k+i]*w%Mod;
				P[j+k]=(x+y)%Mod;P[j+k+i]=(x+Mod-y)%Mod;
			}
	}
	if (opt==-1)
	{
		int inv=QPow(N,Mod-2);
		for (int i=0;i<N;i++) P[i]=1ll*P[i]*inv%Mod;
	}
	return;
}
