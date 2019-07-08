#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

const int maxN=201000;
const int maxM=maxN<<1;
const int Mod=1e9+7;

int n,Case;
int Fc[maxN],Ifc[maxN],St[maxN],Fa[maxN];
pair<int,int> Edge[maxN];
int Sz[maxN][2],Son[maxN][2];

int Inv(int x);
int QPow(int x,int cnt);
int C(int n,int m);
int Calc(int lsz,int rsz);
void Outp(int A,int B);
int main()
{
	Fc[0]=Ifc[0]=1;
	for (int i=1; i<maxN; i++) Fc[i]=1ll*Fc[i-1]*i%Mod;
	Ifc[maxN-1]=QPow(Fc[maxN-1],Mod-2);
	for (int i=maxN-2; i>=1; i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;

	scanf("%d",&Case);
	scanf("%d",&n);
	int ecnt=n-3;
	for (int i=1; i<=ecnt; i++) {
		scanf("%d%d",&Edge[i].first,&Edge[i].second);
		if (Edge[i].first>Edge[i].second) swap(Edge[i].first,Edge[i].second);
		if (Edge[i].second==n) {
			--ecnt;
			--i;
			continue;
		}
		Edge[i].second=-Edge[i].second;
	}
	sort(&Edge[1],&Edge[ecnt+1]);//for (int i=1;i<=ecnt;i++) Edge[i].second=-Edge[i].second;
	//for (int i=1;i<=ecnt;i++) cout<<Edge[i].first<<" "<<Edge[i].second<<"|";cout<<endl;
	int top=0;
	for (int i=1; i<=ecnt; i++) {
		while (top&&-Edge[St[top]].second<=Edge[i].first) --top;
		Fa[i]=St[top];
		St[++top]=i;
	}
	//for (int i=1;i<=ecnt;i++) cout<<Fa[i]<<" ";cout<<endl;
	int Ans1=0,Ans2=1,sum=0;
	for (int i=ecnt; i>=1; i--) {
		Ans2=1ll*Ans2*Calc(Sz[i][0],Sz[i][1])%Mod;
		++Ans1;
		if (Fa[i]) {
			if (Edge[i].first==Edge[Fa[i]].first) Son[Fa[i]][0]=i,Sz[Fa[i]][0]=Sz[i][0]+Sz[i][1]+1;
			else Son[Fa[i]][1]=i,Sz[Fa[i]][1]=Sz[i][0]+Sz[i][1]+1;
		} else Ans2=1ll*Ans2*Calc(Sz[i][0]+Sz[i][1]+1,sum)%Mod,sum+=Sz[i][0]+Sz[i][1]+1;
	}
	//for (int i=1;i<=ecnt;i++) cout<<Son[i][0]<<" "<<Son[i][1]<<endl;
	Outp(Ans1,Ans2);
	int Q;
	scanf("%d",&Q);
	while (Q--) {
		int u,v;
		scanf("%d%d",&u,&v);
		if (u>v) swap(u,v);
		int A1=Ans1,A2=Ans2,x=lower_bound(&Edge[1],&Edge[ecnt+1],make_pair(u,-v))-Edge,fa=Fa[x];
		if (fa) {
			//printf("%d %d (%d %d)?",x,fa,u,v);
			int sx=(x==Son[fa][1]);
			A2=1ll*A2*Inv(Calc(Sz[x][0],Sz[x][1]))%Mod;
			A2=1ll*A2*Inv(Calc(Sz[fa][0],Sz[fa][1]))%Mod;
			A2=1ll*A2*Calc(Sz[x][sx^1],Sz[fa][sx^1])%Mod;
			A2=1ll*A2*Calc(Sz[x][sx],Sz[x][sx^1]+Sz[fa][sx^1]+1)%Mod;
		} else {
			A1--;
			A2=1ll*A2*Inv(Calc(Sz[x][0],Sz[x][1]))%Mod;
			A2=1ll*A2*Inv(Calc(Sz[x][0]+Sz[x][1]+1,sum-Sz[x][0]-Sz[x][1]-1))%Mod;
			A2=1ll*A2*Calc(Sz[x][0],sum-Sz[x][0]-Sz[x][1]-1)%Mod;
			A2=1ll*A2*Calc(Sz[x][1],sum-Sz[x][1]-1)%Mod;
		}
		Outp(A1,A2);
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
		x=1ll*x*x%Mod;
		cnt>>=1;
	}
	return ret;
}
int C(int n,int m)
{
	if (n<m) return 0;
	return 1ll*Fc[n]*Ifc[m]%Mod*Ifc[n-m]%Mod;
}
int Calc(int n,int m)
{
	return C(n+m,m);
}
void Outp(int A,int B)
{
	if (Case) printf("%d %d\n",A,B);
	else printf("%d\n",A);
}
