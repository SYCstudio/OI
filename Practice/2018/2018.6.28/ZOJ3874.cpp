#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*4;
const int Mod=786433;
const int G=10;
const int inf=2147483647;

int Rader[maxN];
int F[maxN],Fac[maxN];
int P1[maxN],P2[maxN];
int W1[maxN],W2[maxN],Inv[maxN];

int QPow(int x,int cnt);
void Divide(int l,int r);
void NTT(int *P,int N,int opt);

int main()
{
	Fac[0]=1;for (int i=1;i<maxN;i++) Fac[i]=1ll*Fac[i-1]*(ll)i%Mod;
	F[0]=1;
	for (int i=1;i<maxN;i<<=1) W1[i]=QPow(G,(Mod-1)/i),W2[i]=QPow(W1[i],Mod-2),Inv[i]=QPow(i,Mod-2);
	Divide(1,100000);
	//for (int i=1;i<=10;i++) cout<<F[i]<<" ";cout<<endl;

	int TTT;scanf("%d",&TTT);
	while (TTT--)
	{
		int n,m;scanf("%d%d",&n,&m);
		bool flag=1;
		int Ans=1;
		for (int i=1;i<=m;i++)
		{
			int k,mn=inf,mx=0;
			scanf("%d",&k);
			for (int j=1;j<=k;j++)
			{
				int num;scanf("%d",&num);
				mn=min(mn,num);mx=max(mx,num);
			}
			if (mx-mn+1!=k) flag=0;
			Ans=1ll*Ans*F[k]%Mod;
		}
		if (flag) printf("%d\n",Ans);
		else printf("0\n");
	}
	return 0;
}

int QPow(int x,int cnt)
{
	int Ret=1;
	while (cnt){
		if (cnt&1) Ret=1ll*Ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return Ret;
}

void Divide(int l,int r)
{
	if (l==r){
		F[l]=(Fac[l]-F[l]+Mod)%Mod;return;
	}
	int mid=(l+r)>>1;
	Divide(l,mid);

	int sz=r-l+1,lsz=mid-l+1,rsz=r-(mid+1)+1;
	
	int N,L=0;
	for (N=1;N<=sz+sz;N<<=1) L++;
	for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));

	for (int i=0;i<N;i++) P1[i]=P2[i]=0;
	for (int i=l;i<=mid;i++) P1[i-l+1]=F[i];
	for (int i=1;i<sz;i++) P2[i]=Fac[i];

	NTT(P1,N,1);NTT(P2,N,1);
	for (int i=0;i<N;i++) P1[i]=1ll*P1[i]*P2[i]%Mod;
	NTT(P1,N,-1);

	for (int i=mid+1;i<=r;i++) F[i]=(F[i]+P1[i-l+1])%Mod;
	Divide(mid+1,r);
	return;
}

void NTT(int *P,int N,int opt)
{
	for (int i=0;i<N;i++) if (i<Rader[i]) swap(P[i],P[Rader[i]]);
	for (int i=1;i<N;i<<=1)
	{
		int l=i<<1;
		int dw=(opt==1)?(W1[l]):(W2[l]);
		for (int j=0;j<N;j+=l)
		{
			int w=1;
			for (int k=0;k<i;k++,w=1ll*w*dw%Mod)
			{
				int X=P[j+k],Y=1ll*P[j+k+i]*w%Mod;
				P[j+k]=(X+Y)%Mod;P[j+k+i]=(X-Y+Mod)%Mod;
			}
		}
	}
	if (opt==-1)
	{
		int inv=Inv[N];
		for (int i=0;i<N;i++) P[i]=1ll*P[i]*inv%Mod;
	}
	return;
}
