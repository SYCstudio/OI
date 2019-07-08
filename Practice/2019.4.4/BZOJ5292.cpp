#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

class Data
{
public:
	int a,b;
};

const int maxN=1600;
const int Mod=1000000007;

int n,P,m,K;
int C[maxN],Pm1[maxN],Pm2[maxN],Tr1[maxN],Tr2[maxN];
Data Dp[maxN];

int Inv(int x);
int QPow(int x,int cnt);
Data operator + (Data A,Data B);
Data operator + (Data A,int B);
Data operator - (Data A,Data B);
Data operator - (Data A,int B);
Data operator * (Data A,int B);
int main()
{
	int Case;
	scanf("%d",&Case);
	while (Case--) {
		scanf("%d%d%d%d",&n,&P,&m,&K);
		if (K==0) {
			puts("-1");
			continue;
		} else if (K==1&&m==0) {
			puts("-1");
			continue;
		} else if (m==0) {
			int c=0;
			if (P==n) P=max(0,P-K),++c;
			if (P) c+=(P-1)/(K-1)+1;
			printf("%d\n",c);
			continue;
		}
		memset(Pm1,0,sizeof(Pm1));
		memset(Pm2,0,sizeof(Pm2));
		memset(Tr1,0,sizeof(Tr1));
		memset(Tr2,0,sizeof(Tr2));
		int im=Inv(m),im1=Inv(m+1);
		C[0]=Pm1[0]=1;
		Pm2[0]=QPow(1ll*m*im1%Mod,K);
		for (int i=1; i<=n; i++) {
			C[i]=1ll*C[i-1]*(K-(i-1)+Mod)%Mod*Inv(i)%Mod;
			Pm1[i]=1ll*Pm1[i-1]*im1%Mod;
			Pm2[i]=1ll*Pm2[i-1]*(m+1)%Mod*im%Mod;
		}
		for (int i=0; i<=n; i++) {
			int tmp=1ll*C[i]*Pm1[i]%Mod*Pm2[i]%Mod;
			Tr1[i]=1ll*tmp*im1%Mod;
			Tr2[i]=1ll*tmp*im1%Mod*m%Mod;
		}

		Dp[1]=((Data) {
			1,0
		});

		for (int i=1; i<n; i++) {
			Dp[i+1]=((Data) {
				0,Mod-1
			});
			Dp[i+1]=Dp[i+1]+Dp[i]*((1-(Tr1[1]+Tr2[0])%Mod+Mod)%Mod);
			for (int j=1; j<i; j++) Dp[i+1]=Dp[i+1]-Dp[j]*((Tr1[i-j+1]+Tr2[i-j])%Mod);
			Dp[i+1]=Dp[i+1]*Inv(Tr1[0]);
		}
		Data Oa=((Data) {
			0,1
		});
		for (int i=1; i<n; i++) Oa=Oa+Dp[i]*(1ll*C[n-i]*Pm1[n-i]%Mod*Pm2[n-i]%Mod);
		Oa=Oa*Inv(1-Pm2[0]+Mod);

		int a=(Dp[n].a-Oa.a+Mod)%Mod,b=(Oa.b-Dp[n].b+Mod)%Mod;
		if (a==0) {
			puts("-1");
			continue;
		}
		int X=1ll*b*Inv(a)%Mod,Ans=(1ll*Dp[P].a*X%Mod+Dp[P].b)%Mod;
		printf("%d\n",Ans);
	}
	return 0;
}
int Inv(int x)
{
	return QPow(x,Mod-2);
}
int QPow(int x,int cnt)
{
	int ret=1;
	while (cnt) {
		if (cnt&1) ret=1ll*ret*x%Mod;
		cnt>>=1;
		x=1ll*x*x%Mod;
	}
	return ret;
}
Data operator + (Data A,Data B)
{
	A.a=(A.a+B.a)%Mod;
	A.b=(A.b+B.b)%Mod;
	return A;
}
Data operator + (Data A,int B)
{
	A.b=(A.b+B)%Mod;
	return A;
}
Data operator - (Data A,Data B)
{
	A.a=(A.a-B.a+Mod)%Mod;
	A.b=(A.b-B.b+Mod)%Mod;
	return A;
}
Data operator - (Data A,int B)
{
	A.b=(A.b-B+Mod)%Mod;
	return A;
}
Data operator * (Data A,int B)
{
	A.a=1ll*A.a*B%Mod;
	A.b=1ll*A.b*B%Mod;
	return A;
}