#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define NAME "polypeptide"

const int maxN=101000*10;
const int Mod=1005060097;
const int G=5;
const int inf=2147483647;

int n,m;
int Rader[maxN];
int P1[maxN],P2[maxN],P3[maxN],I1[maxN],I2[maxN];

int QPow(int x,int cnt);
void NTT(int *P,int N,int opt);
void PolyInv(int *A,int *B,int opt);

int main()
{
	freopen(NAME".in","r",stdin);freopen(NAME".out","w",stdout);
	scanf("%d%d",&n,&m);

	for (int i=1;i<=m;i++)
	{
		int key;scanf("%d",&key);
		P1[key]++;
	}
	for (int i=0;i<=n;i++) P2[i]=(Mod-P1[i])%Mod;
	P2[0]=1;

	int N;
	for (N=1;N<=n;N<<=1);
	//cout<<"N:"<<N<<endl;

	//for (int i=0;i<N;i++) cout<<P1[i]<<" ";cout<<endl;
	//for (int i=0;i<N;i++) cout<<P2[i]<<" ";cout<<endl;

	PolyInv(P2,P3,N);

	//for (int i=0;i<N;i++) cout<<P3[i]<<" ";cout<<endl;

	NTT(P1,N<<1,1);NTT(P3,N<<1,1);
	for (int i=0;i<(N<<1);i++) P1[i]=1ll*P1[i]*P3[i]%Mod;
	NTT(P1,N<<1,-1);

	//for (int i=0;i<(N<<1);i++) cout<<P1[i]<<" ";cout<<endl;
	
	printf("%d\n",P1[n]);
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
	int L=0;
	for (int i=1;i<N;i<<=1) L++;
	for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
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
	if (opt==-1){
		int inv=QPow(N,Mod-2);
		for (int i=0;i<N;i++) P[i]=1ll*P[i]*inv%Mod;
	}
	return;
}

void PolyInv(int *A,int *B,int len)
{
	if (len==1){
		B[0]=QPow(A[0],Mod-2);return;
	}
	PolyInv(A,B,len>>1);
	for (int i=0;i<len;i++) I1[i]=A[i],I2[i]=B[i];
	//cout<<"Before:"<<endl;
	//for (int i=0;i<len;i++) cout<<I1[i]<<" ";cout<<endl;
	//for (int i=0;i<len;i++) cout<<I2[i]<<" ";cout<<endl;
	NTT(I1,len<<1,1);NTT(I2,len<<1,1);
	for (int i=0;i<(len<<1);i++) I1[i]=1ll*I1[i]*I2[i]%Mod*I2[i]%Mod;
	NTT(I1,len<<1,-1);
	//cout<<"After:"<<endl;
	//for (int i=0;i<(len<<1);i++) cout<<I1[i]<<" ";cout<<endl;
	for (int i=0;i<len;i++) B[i]=((B[i]+B[i])%Mod+Mod-I1[i])%Mod;
	for (int i=0;i<(len<<1);i++) I1[i]=I2[i]=0;
	return;
}
