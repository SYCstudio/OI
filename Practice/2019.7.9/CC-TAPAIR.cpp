#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
#define pb push_back
const int maxN=101000;
const int maxM=303000;

int n,m;
vector<int> T[maxN];
int dfncnt,dfn[maxN];
ull NW[maxN],Sm[maxM];
int smcnt;

ull make(ull l,ull r);
ull rp(){return (1ll*rand())^(1ll*rand())<<15^(1ll*rand())<<30^(1ll*rand())<<45^(1ll*rand())<<60;}
void dfs(int u,int fa);
int main(){
	//freopen("in","r",stdin);freopen("out","w",stdout);
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++){
		int u,v;scanf("%d%d",&u,&v);T[u].pb(v);T[v].pb(u);
	}
	dfs(1,0);
	ll Ans=0;
	sort(&Sm[1],&Sm[smcnt+1]);
	//for (int i=1;i<=smcnt;i++) cout<<Sm[i]<<" ";cout<<endl;
	int p=0;while (p+1<=smcnt&&Sm[p+1]==0) ++p;
	Ans=1ll*p*(p-1)/2+p*(smcnt-p);
	for (int l=p+1,r;l<=smcnt;l=r+1){
		r=l;while (r+1<=smcnt&&Sm[r]==Sm[r+1]) ++r;
		int sz=r-l+1;
		Ans=Ans+1ll*sz*(sz-1)/2;
	}
	printf("%lld\n",Ans);
	return 0;
}
ull make(ull l,ull r){
	double dou=1.0*rand()/RAND_MAX;
	return min(r,(ull)(dou*(r-l+1)+l));
}
void dfs(int u,int fa){
	dfn[u]=++dfncnt;
	for (int i=0;i<T[u].size();i++){
		int v=T[u][i];if (v==fa) continue;
		if (!dfn[v]) dfs(v,u),NW[u]^=NW[v],Sm[++smcnt]=NW[v];
		else if (dfn[v]<dfn[u]) {
			ull key=rp();
			NW[u]^=key;NW[v]^=key;Sm[++smcnt]=key;
		}
	}
	return;
}
