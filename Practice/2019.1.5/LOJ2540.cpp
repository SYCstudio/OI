#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1<<20;
const int Mod=998244353;

int n,m;
int F[maxN],Mx[maxN],Nr[maxN];

int QPow(int x,int cnt);

int main()
{
	scanf("%d%d",&n,&m);
	int N=1<<n;
	for (int i=1; i<=m; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		--u;
		--v;
		Nr[u]|=(1<<v);
		Nr[v]|=(1<<u);
	}
	for (int i=0; i<n; i++) Nr[i]|=(1<<i);
	//for (int i=0;i<n;i++) cout<<Nr[i]<<" ";cout<<endl;
	F[0]=1;
	for (int S=1; S<N; S++) {
		int cnt=0;
		for (int i=0; i<n; i++)
			if (S&(1<<i)) {
				int nS=(S|Nr[i])^Nr[i];
				++cnt;
				if (Mx[nS]+1>Mx[S]) Mx[S]=Mx[nS]+1,F[S]=0;
				if (Mx[nS]+1==Mx[S]) F[S]=(F[S]+F[nS])%Mod;
			}
		//cout<<S<<" "<<F[S]<<" "<<cnt<<endl;
		F[S]=1ll*F[S]*QPow(cnt,Mod-2)%Mod;
	}
	//for (int i=0;i<N;i++) cout<<F[i]<<" ";cout<<endl;
	printf("%d\n",F[N-1]);
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
