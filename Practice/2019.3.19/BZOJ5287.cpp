#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

const int maxN=101000;
const int maxM=maxN<<1;
const int Mod=998244353;

class Data
{
public:
	int a,b;
};

int n,m;
int ecnt=-1,Hd[maxN],Nt[maxM],V[maxM];
int dfncnt,dfn[maxN],Mark[maxN];
vector<int> T[maxN];
vector<pair<int,int> > Vtr[maxN];
int decnt;
pair<int,int> E[maxN];
int F[maxN][2];
Data G[maxN][2];

void Add_Edge(int u,int v);
void dfs_init(int u,int fa);
Data operator + (Data A,Data B);
Data operator * (Data A,int x);
int dfs_predp(int u);
pair<int,int> dfs_dp(int u);
pair<int,int> dfs_brute(int u);
int main()
{
	scanf("%d%d",&n,&m);
	memset(Hd,-1,sizeof(Hd));
	for (int i=1; i<=m; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	dfs_init(1,0);
	for (int i=0; i<decnt; i++) Mark[E[i].first]=Mark[E[i].second]=1;
	dfs_predp(1);
	for (int i=0; i<decnt; i++) Mark[E[i].first]=Mark[E[i].second]=0;
	int Ans=0;
	for (int S=0,N=1<<decnt; S<N; S++) {
		int cnt=0;
		for (int j=0; j<decnt; j++) if ((S>>j)&1) Mark[E[j].first]=Mark[E[j].second]=1,++cnt;
		pair<int,int> r=dfs_dp(1);
		r.first=(r.first+r.second)%Mod;
		if (cnt&1) Ans=(Ans-r.first+Mod)%Mod;
		else Ans=(Ans+r.first)%Mod;
		for (int j=0; j<decnt; j++) if ((S>>j)&1) Mark[E[j].first]=Mark[E[j].second]=0;
	}
	printf("%d\n",Ans);
	return 0;
}
void Add_Edge(int u,int v)
{
	Nt[++ecnt]=Hd[u];
	Hd[u]=ecnt;
	V[ecnt]=v;
	return;
}
void dfs_init(int u,int fa)
{
	dfn[u]=++dfncnt;
	for (int i=Hd[u]; i!=-1; i=Nt[i])
		if (V[i]!=fa) {
			if (!dfn[V[i]]) dfs_init(V[i],u),T[u].push_back(V[i]);
			else if (dfn[V[i]]<dfn[u]) E[decnt++]=make_pair(V[i],u);
		}
	return;
}
Data operator + (Data A,Data B)
{
	return ((Data) {
		(A.a+B.a)%Mod,(A.b+B.b)%Mod
	});
}
Data operator * (Data A,int x)
{
	return ((Data) {
		1ll*A.a*x%Mod,1ll*A.b*x%Mod
	});
}
int dfs_predp(int u)
{
	F[u][0]=F[u][1]=1;
	for (int i=0,sz=T[u].size(); i<sz; i++) {
		int v=T[u][i],vv=dfs_predp(v);
		if (vv) Vtr[u].push_back(make_pair(v,vv));
		else F[u][0]=1ll*F[u][0]*(F[v][0]+F[v][1])%Mod,F[u][1]=1ll*F[u][1]*F[v][0]%Mod;
	}
	if (Vtr[u].size()>=2||u==1||Mark[u]) {
		for (int i=0,sz=Vtr[u].size(); i<sz; i++) {
			Data d=G[Vtr[u][i].first][0];
			G[Vtr[u][i].first][0]=G[Vtr[u][i].first][0]+G[Vtr[u][i].first][1];
			G[Vtr[u][i].first][1]=d;
		}
		G[u][0]=((Data) {
			1,0
		});
		G[u][1]=((Data) {
			0,1
		});
		return u;
	} else if (Vtr[u].size()==1) {
		int v=Vtr[u][0].first;
		G[u][0]=(G[v][0]+G[v][1])*F[u][0];
		G[u][1]=G[v][0]*F[u][1];
		return Vtr[u][0].second;
	} else return 0;
}
pair<int,int> dfs_dp(int u)
{
	int r0=F[u][0],r1=F[u][1];
	if (Vtr[u].size()) {
		for (int i=0,sz=Vtr[u].size(); i<sz; i++) {
			pair<int,int> p=dfs_dp(Vtr[u][i].second);
			int v=Vtr[u][i].first;
			r0=1ll*r0*(1ll*p.first*G[v][0].a%Mod+1ll*p.second*G[v][0].b%Mod)%Mod;
			r1=1ll*r1*(1ll*p.first*G[v][1].a%Mod+1ll*p.second*G[v][1].b%Mod)%Mod;
		}
	}
	if (Mark[u]) r0=0;
	return make_pair(r0,r1);
}
pair<int,int> dfs_brute(int u)
{
	int r0=1,r1=1;
	for (int i=0,sz=T[u].size(); i<sz; i++) {
		pair<int,int> p=dfs_brute(T[u][i]);
		r0=1ll*r0*(p.first+p.second)%Mod;
		r1=1ll*r1*p.first%Mod;
	}
	if (Mark[u]) r0=0;
	return make_pair(r0,r1);
}