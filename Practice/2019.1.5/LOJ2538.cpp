#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=3010;
const int Mod=998244353;

int n,m,K;
int W1[maxN],W2[maxN];
int f[maxN][maxN],g[maxN][maxN],s[maxN][maxN];
int Fc[maxN],Ifc[maxN];

int QPow(int x,int cnt);
int C(int n,int m);
int F(int a,int b);
int G(int a,int b);

int main()
{
	//freopen("in","r",stdin);
	Fc[0]=Ifc[0]=1;
	for (int i=1; i<maxN; i++) Fc[i]=1ll*Fc[i-1]*i%Mod;
	Ifc[maxN-1]=QPow(Fc[maxN-1],Mod-2);
	for (int i=maxN-2; i>=1; i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;
	int Case;
	scanf("%d",&Case);
	while (Case--) {
		scanf("%d%d%d",&n,&m,&K);
		for (int i=1; i<=n; i++) scanf("%d",&W1[i]);
		for (int i=1; i<=n; i++) scanf("%d",&W2[i]);
		sort(&W1[1],&W1[n+1]);
		reverse(&W1[1],&W1[n+1]);
		sort(&W2[1],&W2[n+1]);
		reverse(&W2[1],&W2[n+1]);
		//mem(f,0);mem(g,0);mem(s,0);
		for (int i=1; i<=n; i++) {
			f[1][i]=W1[i];
			s[1][i]=(s[1][i-1]+f[1][i])%Mod;
		}
		for (int i=2; i<=n; i++)
			for (int j=1; j<=n; j++) {
				f[i][j]=1ll*s[i-1][j-1]*W1[j]%Mod;
				s[i][j]=(s[i][j-1]+f[i][j])%Mod;
			}
		//mem(s,0);
		for (int i=1; i<=n; i++) {
			g[1][i]=W2[i];
			s[1][i]=(s[1][i-1]+g[1][i])%Mod;
		}
		for (int i=2; i<=n; i++)
			for (int j=1; j<=n; j++) {
				g[i][j]=(1ll*C(j-1,i-1)*W2[j]%Mod+s[i-1][j-1])%Mod;
				s[i][j]=(s[i][j-1]+g[i][j])%Mod;
			}
		/*
		for (int i=1;i<=n;i++){
			for (int j=1;j<=n;j++)
				cout<<f[i][j]<<" ";
			cout<<endl;
		}cout<<endl;
		for (int i=1;i<=n;i++){
			for (int j=1;j<=n;j++)
				cout<<g[i][j]<<" ";
			cout<<endl;
		}
		//*/
		int Ans=0;
		for (int p=0; p<=m; p++) {
			if ((p>n)||(m-p>n)) continue;
			if (p<K) Ans=(Ans+1ll*F(p,p)*G(m-p,K-p)%Mod)%Mod;
			else Ans=(Ans+1ll*F(p,K-1)*G(m-p,1)%Mod)%Mod;
		}
		printf("%d\n",Ans);
	}
	return 0;
}

int QPow(int x,int cnt)
{
	int ret=1;
	while (cnt) {
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;
		cnt>>=1;
	}
	return ret;
}
int C(int n,int m)
{
	if ((n<0)||(m<0)||(n<m)) return 0;
	return 1ll*Fc[n]*Ifc[n-m]%Mod*Ifc[m]%Mod;
}
int F(int a,int b)
{
	if (b==0) return C(n,a);
	int ret=0;
	for (int l=1; l<=n; l++) ret=(ret+1ll*f[b][l]*C(n-l,a-b)%Mod)%Mod;
	//cout<<"F("<<a<<","<<b<<") "<<ret<<endl;
	return ret;
}
int G(int a,int b)
{
	int ret=0;
	for (int l=1; l<=n; l++) ret=(ret+1ll*g[b][l]*C(n-l,a-b)%Mod)%Mod;
	//cout<<"G("<<a<<","<<b<<") "<<ret<<endl;
	return ret;
}
