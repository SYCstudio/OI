#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define NAME "guess"

const int maxN=101000*15;
const int Mod=998244353;
const int G=3;
const int inf=2147483647;

int n;
char S[maxN],T[maxN];
int P1[maxN],P2[maxN],P3[maxN],P4[maxN],P5[maxN],P6[maxN],Rader[maxN];

int QPow(int x,int cnt);
void NTT(int *P,int N,int opt);

int main()
{
	freopen(NAME".in","r",stdin);freopen(NAME".out","w",stdout);
	scanf("%s",S);scanf("%s",T);
	int l1=strlen(S),l2=strlen(T);
	reverse(&T[0],&T[l2]);

	for (int i=0;i<l1;i++)
		if (S[i]!='?') P1[i]=S[i]-'a'+1;
		else P1[i]=0;
	for (int i=0;i<l2;i++)
		if (T[i]!='?') P2[i]=T[i]-'a'+1;
		else P2[i]=0;

	for (int i=0;i<l1;i++) P3[i]=P1[i]*P1[i],P5[i]=P1[i],P1[i]=P1[i]*P1[i]*P1[i];
	for (int i=0;i<l2;i++) P4[i]=P2[i]*P2[i],P6[i]=P2[i]*P2[i]*P2[i];

	int len=l1+l2;

	int N,L=0;
	for (N=1;N<=len;N<<=1) L++;
	for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	
	NTT(P1,N,1);NTT(P2,N,1);NTT(P3,N,1);NTT(P4,N,1);NTT(P5,N,1);NTT(P6,N,1);
	for (int i=0;i<N;i++)
	{
		P1[i]=1ll*P1[i]*P2[i]%Mod;
		P3[i]=1ll*P3[i]*P4[i]%Mod;
		P5[i]=1ll*P5[i]*P6[i]%Mod;
	}
	NTT(P1,N,-1);NTT(P3,N,-1);NTT(P5,N,-1);

	for (int i=0;i<N;i++) P1[i]=(P1[i]-2ll*P3[i]%Mod+P5[i]+Mod)%Mod;

	//for (int i=0;i<l1;i++) cout<<P1[i]<<" ";cout<<endl;
	
	int tot=0;
	for (int i=l2-1;i<l1;i++) if (P1[i]==0) tot++;
	printf("%d\n",tot);
	for (int i=l2-1;i<l1;i++) if (P1[i]==0) printf("%d\n",i-l2+1);

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
				P[j+k]=(x+y)%Mod;P[j+k+i]=(x-y+Mod)%Mod;
			}
	}
	if (opt==-1)
	{
		int inv=QPow(N,Mod-2);
		for (int i=0;i<N;i++) P[i]=1ll*P[i]*inv%Mod;
	}
	return;
}
