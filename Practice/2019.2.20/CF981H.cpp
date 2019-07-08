#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
const int maxN=303000;
const int maxM=maxN<<1;
const int G=3;
const int Mod=998244353;
const int maxB=18;

int n,K,Ans=0;
int Fc[maxN],Ifc[maxN],R[maxN];
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int F[maxN],Sz[maxN],Seq[maxN],Bp[maxB][maxN],St[maxN];
vector<int> Son[maxN],Poly[maxN];

int QPow(int x,int cnt);
int Inv(int x);
int C(int n,int m);
void NTT(int *P,int N,int opt);
void Add_Edge(int u,int v);
bool cmp(int a,int b);
void dfs(int u,int fa);
void Divide(int d,int l,int r);

int main()
{
	Fc[0]=Ifc[0]=1;
	for (int i=1; i<maxN; i++) Fc[i]=1ll*Fc[i-1]*i%Mod;
	Ifc[maxN-1]=Inv(Fc[maxN-1]);
	for (int i=maxN-2; i>=1; i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;

	scanf("%d%d",&n,&K);
	mem(Head,-1);
	if (K==1) {
		int Ans=(1ll*n*(n-1)/2)%Mod;
		printf("%d\n",Ans);
		return 0;
	}
	for (int i=1; i<n; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		Add_Edge(u,v);
		Add_Edge(v,u);
	}

	dfs(1,1);

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
int Inv(int x)
{
	return QPow(x,Mod-2);
}
void NTT(int *P,int N,int opt)
{
	int l=-1,_N=N;
	while (_N) ++l,_N>>=1;
	for (int i=0; i<N; i++) R[i]=(R[i>>1]>>1)|((i&1)<<(l-1));
	for (int i=0; i<N; i++) if (i<R[i]) swap(P[i],P[R[i]]);
	for (int i=1; i<N; i<<=1) {
		int dw=QPow(G,(Mod-1)/(i<<1));
		if (opt==-1) dw=Inv(dw);
		for (int j=0; j<N; j+=(i<<1))
			for (int k=0,w=1; k<i; k++,w=1ll*w*dw%Mod) {
				int X=P[j+k],Y=1ll*P[j+k+i]*w%Mod;
				P[j+k]=X+Y;
				if (P[j+k]>=Mod) P[j+k]-=Mod;
				P[j+k+i]=X-Y;
				if (P[j+k+i]<0) P[j+k+i]+=Mod;
			}
	}
	if (opt==-1) {
		int inv=Inv(N);
		for (int i=0; i<N; i++) P[i]=1ll*P[i]*inv%Mod;
	}
	return;
}
void Add_Edge(int u,int v)
{
	Next[++edgecnt]=Head[u];
	Head[u]=edgecnt;
	V[edgecnt]=v;
	return;
}
bool cmp(int a,int b)
{
	return Sz[a]<Sz[b];
}
int C(int n,int m)
{
	if (n<0||m<0||n<m) return 0;
	return 1ll*Fc[n]*Ifc[m]%Mod*Ifc[n-m]%Mod;
}
void dfs(int u,int fa)
{
	Sz[u]=1;
	for (int i=Head[u]; i!=-1; i=Next[i])
		if (V[i]!=fa) {
			dfs(V[i],u);
			Sz[u]+=Sz[V[i]];
			Son[u].push_back(V[i]);
			//cout<<"Calc at dfs1:"<<u<<" "<<F[u]<<" "<<F[V[i]]<<endl;
			Ans=(Ans+1ll*F[u]*F[V[i]]%Mod)%Mod;
			F[u]=(F[u]+F[V[i]])%Mod;
		}
	if (Sz[u]==1) {
		Poly[u].resize(1);
		Poly[u][0]=1;
	} else {
		sort(Son[u].begin(),Son[u].end(),cmp);
		int cnt=Son[u].size();
		for (int i=1; i<=cnt; i++) Seq[i]=Sz[Son[u][i-1]];
		Divide(0,1,cnt);
		Poly[u].resize(cnt+1);
		for (int i=0; i<=cnt; i++) Poly[u][i]=Bp[0][i];
		mem(Bp[0],0);

		//cout<<"running at:"<<u<<endl;
		//for (int i=0;i<=cnt;i++) cout<<Poly[u][i]<<" ";cout<<endl;

		for (int i=0,j; i<cnt; i=j+1) {
			j=i;
			while (j+1<cnt&&Sz[Son[u][j+1]]==Sz[Son[u][i]]) ++j;
			int sz=Sz[Son[u][i]],sum=0;
			St[0]=Poly[u][0];
			for (int k=1; k<=cnt; k++) St[k]=(Poly[u][k]-1ll*St[k-1]*sz%Mod+Mod)%Mod;
			for (int k=cnt; k>=1; k--) St[k]=(St[k]+1ll*St[k-1]*(n-Sz[u])%Mod)%Mod;
			//cout<<"At:"<<u<<" "<<sz<<endl;
			//for (int k=0;k<=cnt;k++) cout<<Poly[u][k]<<" ";cout<<endl;
			for (int k=0; k<=cnt&&k<=K; k++) sum=(sum+1ll*St[k]*Fc[K]%Mod*Ifc[K-k]%Mod)%Mod;
			for (int k=i; k<=j; k++) Ans=(Ans+1ll*F[Son[u][k]]*sum%Mod)%Mod;
		}
	}
	for (int i=0,sz=Poly[u].size(); i<sz&&i<=K; i++) F[u]=(F[u]+1ll*Poly[u][i]*Fc[K]%Mod*Ifc[K-i]%Mod)%Mod;
	return;
}
void Divide(int d,int l,int r)
{
	if (l==r) {
		Bp[d][0]=1;
		Bp[d][1]=Seq[l];
		return;
	}
	int sz=(r-l+1),mid=(l+r)>>1;
	Divide(d+1,l,mid);
	for (int i=0; i<=sz; i++) Bp[d][i]=Bp[d+1][i],Bp[d+1][i]=0;
	Divide(d+1,mid+1,r);
	int N=1;
	while (N<=sz) N<<=1;
	//cout<<"Divide:"<<d<<" "<<l<<" "<<r<<endl;
	//for (int i=0;i<N;i++) cout<<Bp[d][i]<<" ";cout<<endl;
	//for (int i=0;i<N;i++) cout<<Bp[d+1][i]<<" ";cout<<endl;
	NTT(Bp[d],N,1);
	NTT(Bp[d+1],N,1);
	for (int i=0; i<N; i++) Bp[d][i]=1ll*Bp[d][i]*Bp[d+1][i]%Mod;
	NTT(Bp[d],N,-1);
	//for (int i=0;i<N;i++) cout<<Bp[d][i]<<" ";cout<<endl;
	for (int i=0; i<N; i++) Bp[d+1][i]=0;
	for (int i=sz+1; i<N; i++) Bp[d][i]=0;
	return;
}