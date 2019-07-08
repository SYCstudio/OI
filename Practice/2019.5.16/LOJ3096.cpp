#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

typedef long long ll;
const int maxN=1000001;
const int Bit=30;

int n,m,P,Q;
ll T;
int A[maxN],B[maxN],Nxt[Bit][maxN],Mark[maxN],Sm[Bit][maxN];
int vis[maxN],Sz[maxN],Fsz[maxN];

int main()
{
	scanf("%d%d%d%d%lld",&P,&Q,&n,&m,&T);
	for (int i=1; i<=n; i++) scanf("%d",&A[i]);
	for (int i=1; i<=m; i++) {
		int b;
		scanf("%d",&b);
		Mark[b]=1;
	}
	for (int i=0; i<Q; i++) Nxt[0][i]=(i+P)%Q,Sm[0][i]=Mark[Nxt[0][i]];
	for (int i=1; i<Bit; i++)
		for (int j=0; j<Q; j++) Nxt[i][j]=Nxt[i-1][Nxt[i-1][j]],Sm[i][j]=Sm[i-1][j]+Sm[i-1][Nxt[i-1][j]];
	for (int i=0; i<Q; i++)
		if (!vis[i]) {
			int sz=1,fsz=Mark[i],now=Nxt[0][i];
			vis[i]=1;
			while (now!=i) ++sz,fsz+=Mark[now],vis[now]=1,now=Nxt[0][now];
			Sz[i]=sz;
			Fsz[i]=fsz;
			now=Nxt[0][i];
			while (now!=i) Sz[now]=sz,Fsz[now]=fsz,now=Nxt[0][now];
		}

	ll Ans=0;
	for (int i=1; i<=n; i++) {
		if (T-1-A[i]<0) continue;
		int now=A[i]%Q;
		ll c=(T-1-A[i])/P;
		Ans=Ans+Mark[now];
		Ans=Ans+1ll*Fsz[now]*(c/Sz[now]);
		c=c%Sz[now];
		for (int j=Bit-1; j>=0; j--)
			if (c&(1<<j)) {
				Ans=Ans+Sm[j][now];
				now=Nxt[j][now];
			}
	}
	printf("%lld\n",Ans);
	return 0;
}
