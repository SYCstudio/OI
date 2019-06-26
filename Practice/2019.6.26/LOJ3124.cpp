#include<bits/stdc++.h>
using namespace std;

#define Inv(x) QPow(x,Mod-2)
#define pb push_back
const int maxN=1100;
const int maxM=maxN*3;
const int Mod=998244353;

int n,Iv[maxM];
vector<int> T1[maxN],T2[maxN];
int Pa[maxN],Pb[maxN],Pc[maxN];
int F[maxN][maxM],Sz[maxN],G[maxM];

int QPow(int x,int cnt);
void dfs(int u,int fa);
int main(){
    Iv[0]=1;for (int i=1;i<maxM;i++) Iv[i]=Inv(i);
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
	int a,b,c,sum;scanf("%d%d%d",&a,&b,&c);
	sum=(a+b+c)%Mod;sum=Inv(sum);
	Pa[i]=1ll*a*sum%Mod;
	Pb[i]=1ll*b*sum%Mod;
	Pc[i]=1ll*c*sum%Mod;
    }
    for (int i=1;i<n;i++){
	int u,v;scanf("%d%d",&u,&v);
	T1[u].pb(v);T2[v].pb(u);
    }
    dfs(1,0);
    int Ans=0;//cout<<"Sz:"<<Sz[1]<<endl;
    //for (int i=1;i<=Sz[1];i++) cout<<F[1][i]<<" ";cout<<endl;
    for (int i=1;i<=Sz[1];i++) Ans=(Ans+F[1][i])%Mod;
    printf("%d\n",Ans);return 0;
}
int QPow(int x,int cnt){
    int ret=1;
    while (cnt){
	if (cnt&1) ret=1ll*ret*x%Mod;
	x=1ll*x*x%Mod;cnt>>=1;
    }
    return ret;
}
void dfs(int u,int fa){
    Sz[u]=3;
    F[u][1]=1ll*Pa[u]%Mod;
    F[u][2]=2ll*Pb[u]%Mod;
    F[u][3]=3ll*Pc[u]%Mod;
    for (int i=0;i<T1[u].size();i++){
	int v=T1[u][i];if (v==fa) continue;
	dfs(v,u);
	for (int a=0;a<=Sz[u];a++)
	    for (int b=0;b<=Sz[v];b++)
		G[a+b]=(G[a+b]+1ll*F[u][a]*F[v][b]%Mod)%Mod;
	Sz[u]+=Sz[v];
	for (int j=0;j<=Sz[u];j++) F[u][j]=G[j],G[j]=0;
    }
    for (int i=0;i<T2[u].size();i++){
	int v=T2[u][i];if (v==fa) continue;
	dfs(v,u);
	for (int a=0;a<=Sz[u];a++)
	    for (int b=0;b<=Sz[v];b++){
		G[a+b]=(G[a+b]-1ll*F[u][a]*F[v][b]%Mod+Mod)%Mod;
		G[a]=(G[a]+1ll*F[u][a]*F[v][b]%Mod)%Mod;
	    }
	Sz[u]+=Sz[v];
	for (int j=0;j<=Sz[u];j++) F[u][j]=G[j],G[j]=0;
    }
    //cout<<u<<":";
    //for (int i=1;i<=Sz[u];i++) cout<<F[u][i]<<" ";cout<<endl;
    for (int i=1;i<=Sz[u];i++) F[u][i]=1ll*F[u][i]*Iv[i]%Mod;
    return;
}
