#include<bits/stdc++.h>
using namespace std;

#define Inv(x) QPow(x,Mod-2)
#define pb push_back

const int maxN=5050;
const int maxM=310;
const int Mod=998244353;

int m,n,Sz[maxN],Ts[maxN];
vector<int> T[maxN];
int dp[maxN][maxN][3],dpg[maxN][3];
int F[maxN][maxN];
int Fc[maxN],Ifc[maxN],Mic[maxN];
int Poly[maxN],iPoly[maxN],bp[maxN];

int QPow(int x,int cnt);
int C(int n,int m);
void Plus(int &x,int y);
void dfs(int u,int fa);
int main()
{
	Fc[0]=Ifc[0]=1;
	for (int i=1; i<maxN; i++) Fc[i]=1ll*Fc[i-1]*i%Mod;
	Ifc[maxN-1]=Inv(Fc[maxN-1]);
	for (int i=maxN-2; i>=1; i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;
	Mic[0]=1;
	for (int i=1; i<maxN; i++) Mic[i]=Mod-Mic[i-1];

	scanf("%d",&m);
	for (int mi=1; mi<=m; mi++) {
		scanf("%d",&Ts[mi]);
		for (int i=1; i<Ts[mi]; i++) {
			int u,v;
			scanf("%d%d",&u,&v);
			T[u].pb(v);
			T[v].pb(u);
		}
		dfs(1,0);
		for (int i=1; i<=Ts[mi]; i++) F[mi][i]=dp[1][i][2];

		/*
		cout<<mi<<":"<<endl;
		for (int i=1;i<=Ts[mi];i++){
		    for (int j=0;j<=Sz[i];j++) cout<<"("<<dp[i][j][0]<<" "<<dp[i][j][1]<<" "<<dp[i][j][2]<<") ";cout<<endl;
		}
		//*/
		//for (int i=1;i<=Ts[mi];i++) cout<<F[mi][i]<<" ";cout<<endl;

		for (int i=1; i<=Ts[mi]; i++) T[i].clear();
		for (int i=1; i<=Ts[mi]; i++) for (int j=0; j<=Sz[i]; j++) dp[i][j][0]=dp[i][j][1]=dp[i][j][2]=0;
	}

	for (int i=1; i<=Ts[1]; i++) for (int j=1; j<=i; j++) Plus(Poly[j-1],1ll*F[1][i]*Fc[i-1]%Mod*C(i-1,j-1)%Mod*Mic[i-j]%Mod);
	for (int i=1; i<=Ts[1]; i++) for (int j=2; j<=i; j++) Plus(iPoly[j-2],1ll*F[1][i]*Fc[i-1]%Mod*C(i-1,j-1)%Mod*Mic[i-j]%Mod);
	for (int i=0; i<=Ts[1]; i++) Poly[i]=(Poly[i]-iPoly[i]+Mod)%Mod,iPoly[i]=0;
	for (int i=0; i<=Ts[1]; i++) Poly[i]=1ll*Poly[i]*Ifc[i]%Mod;

	//for (int i=0;i<=Ts[1];i++) cout<<Poly[i]<<" ";cout<<endl;

	int sum=Ts[1];
	for (int mi=2; mi<=m; mi++) {
		for (int i=1; i<=Ts[mi]; i++) for (int j=1; j<=i; j++) Plus(iPoly[j],1ll*F[mi][i]*Fc[i]%Mod*C(i-1,j-1)%Mod*Mic[i-j]%Mod);
		for (int i=0; i<=Ts[mi]; i++) iPoly[i]=1ll*iPoly[i]*Ifc[i]%Mod;
		for (int a=0; a<=sum; a++) for (int b=0; b<=Ts[mi]; b++) Plus(bp[a+b],1ll*Poly[a]*iPoly[b]%Mod);
		sum+=Ts[mi];
		for (int i=0; i<=sum; i++) Poly[i]=bp[i],bp[i]=0,iPoly[i]=0;

		//for (int i=0;i<=sum;i++) cout<<Poly[i]<<" ";cout<<endl;
	}

	//for (int i=0;i<=sum;i++) cout<<Poly[i]<<" ";cout<<endl;

	int Ans=0;
	for (int i=0; i<=sum; i++) Plus(Ans,1ll*Poly[i]*Fc[i]%Mod);
	printf("%d\n",Ans);
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
	if (n<0||m<0||n<m) return 0;
	return 1ll*Fc[n]*Ifc[m]%Mod*Ifc[n-m]%Mod;
}
void Plus(int &x,int y)
{
	x+=y;
	if (x>=Mod) x-=Mod;
	return;
}
void dfs(int u,int fa)
{
	Sz[u]=1;
	dp[u][1][2]=1;
	dp[u][0][0]=1;
	dp[u][0][1]=1;
	for (int i=0; i<T[u].size(); i++) {
		int v=T[u][i];
		if (v==fa) continue;
		dfs(v,u);
		for (int a=0; a<=Sz[u]; a++)
			for (int b=0; b<=Sz[v]; b++) {
				Plus(dpg[a+b][1],1ll*dp[u][a][0]*dp[v][b][1]%Mod);
				//Plus(dpg[a+b+1][2],2ll*dp[u][a][0]%Mod*dp[v][b][1]%Mod);
				Plus(dpg[a+b][0],1ll*dp[u][a][0]*dp[v][b][2]%Mod);
				Plus(dpg[a+b+1][2],2ll*dp[u][a][1]*dp[v][b][1]%Mod);
				Plus(dpg[a+b][1],1ll*dp[u][a][1]*dp[v][b][2]%Mod);
				Plus(dpg[a+b][2],1ll*dp[u][a][2]*dp[v][b][2]%Mod);
			}
		Sz[u]+=Sz[v];
		for (int j=0; j<=Sz[u]; j++) for (int c=0; c<=2; c++) dp[u][j][c]=dpg[j][c],dpg[j][c]=0;
	}
	return;
}
