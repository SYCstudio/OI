#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int maxM=202000;
const int Mod=1e9+7;

int n,m,X,Y;
int edgecnt=0,Head[maxN],Next[maxM],V[maxM];
int Q[maxN],D[maxN],Td[maxN],F[maxN];

int QPow(int x,int cnt);

int main()
{
	scanf("%d%d%d%d",&n,&m,&X,&Y);
	mem(Head,-1);
	for (int i=1; i<=m; i++) {
		int u,v;
		scanf("%d%d",&u,&v);
		Next[++edgecnt]=Head[u];
		Head[u]=edgecnt;
		V[edgecnt]=v;
		++D[v];
		++Td[v];
	}
	if ((X==Y)||(Y==1)) {
		int Ans=1;
		for (int i=2; i<=n; i++) Ans=1ll*Ans*D[i]%Mod;
		printf("%d\n",Ans);
		return 0;
	}
	++D[Y];
	int Ans=1,ql=0,qr=0;
	for (int i=2; i<=n; i++) Ans=1ll*Ans*D[i]%Mod;
	F[Y]=Ans;
	for (int i=1; i<=n; i++) if (Td[i]==0) Q[++qr]=i;
	while (ql<=qr) {
		int u=Q[ql++];
		F[u]=1ll*F[u]*QPow(D[u],Mod-2)%Mod;
		for (int i=Head[u]; i!=-1; i=Next[i]) {
			F[V[i]]=(F[V[i]]+F[u])%Mod;
			if ((--Td[V[i]])==0) Q[++qr]=V[i];
		}
	}
	Ans=(Ans-F[X]+Mod)%Mod;
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
