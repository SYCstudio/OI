#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=1010;
const int maxM=2650;
const int maxK=35;
const int Mod=998244353;

int n,C,K;
int C0,C1,D0,D1;
int Belong[maxN],Student[maxN],Hate[maxN],Cityhate[maxN],Citysum[maxN];
int F[maxM],G[maxM];
int H[maxM][maxM],f[maxM][maxM],g[maxM][maxM];

void Plus(int &x,int y);
int main()
{
	int Case;
	scanf("%d",&Case);
	while (Case--) {
		memset(Hate,-1,sizeof(Hate));
		memset(Cityhate,0,sizeof(Cityhate));
		memset(Citysum,0,sizeof(Citysum));
		scanf("%d%d",&n,&C);
		scanf("%d%d%d%d",&C0,&C1,&D0,&D1);
		int SUM=0;
		for (int i=1; i<=n; i++) scanf("%d%d",&Belong[i],&Student[i]),Citysum[Belong[i]]+=Student[i],SUM+=Student[i];
		scanf("%d",&K);
		for (int i=1; i<=K; i++) {
			int id,p;
			scanf("%d%d",&id,&p);
			Hate[id]=p;
			Cityhate[Belong[id]]=1;
		}
		if (C0+C1<SUM||D0+D1<SUM) {
			puts("0");
			continue;
		}
		memset(F,0,sizeof(F));
		memset(G,0,sizeof(G));
		memset(H,0,sizeof(H));
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		F[0]=1;
		for (int i=1; i<=C; i++) if (Cityhate[i]==0&&Citysum[i]) for (int j=C0; j>=Citysum[i]; j--) Plus(F[j],F[j-Citysum[i]]);
		G[0]=1;
		for (int i=1; i<=n; i++) if (Hate[i]==-1) for (int j=D0; j>=Student[i]; j--) Plus(G[j],G[j-Student[i]]);
		H[0][0]=1;
		int sum1=0,sum2=0;
		for (int i=1; i<=C; i++)
			if (Cityhate[i]) {
				sum1=min(sum1+Citysum[i],C0);
				for (int a=0; a<=sum1; a++) for (int b=0; b<=sum2; b++) f[a][b]=g[a][b]=H[a][b],H[a][b]=0;
				for (int j=1; j<=n; j++)
					if (Belong[j]==i&&Hate[j]!=-1) {
						sum2=min(sum2+Student[j],D0);
						int k=Student[j];
						if (Hate[j]==0)
							for (int a=0; a<=sum1; a++) for (int b=sum2; b>=k; b--) Plus(g[a][b],g[a][b-k]);
						if (Hate[j]==1) {
							for (int a=0; a<=sum1; a++) for (int b=sum2; b>=k; b--) f[a][b]=f[a][b-k];
							for (int a=0; a<=sum1; a++) for (int b=0; b<k; b++) f[a][b]=0;
							for (int a=0; a<=sum1; a++) for (int b=sum2; b>=k; b--) Plus(g[a][b],g[a][b-k]);
						}
						if (Hate[j]==2)
							for (int a=0; a<=sum1; a++) for (int b=sum2; b>=k; b--) Plus(f[a][b],f[a][b-k]);
						if (Hate[j]==3) {
							for (int a=0; a<=sum1; a++) for (int b=sum2; b>=k; b--) Plus(f[a][b],f[a][b-k]);
							for (int a=0; a<=sum1; a++) for (int b=sum2; b>=k; b--) g[a][b]=g[a][b-k];
							for (int a=0; a<=sum1; a++) for (int b=0; b<k; b++) g[a][b]=0;
						}
					}
				for (int a=sum1; a>=Citysum[i]; a--) for (int b=0; b<=sum2; b++) f[a][b]=f[a-Citysum[i]][b];
				for (int a=0; a<Citysum[i]; a++) for (int b=0; b<=sum2; b++) f[a][b]=0;
				for (int a=0; a<=sum1; a++)
					for (int b=0; b<=sum2; b++) H[a][b]=(f[a][b]+g[a][b])%Mod;
			}
		for (int i=1; i<=max(C0,D0); i++) Plus(F[i],F[i-1]),Plus(G[i],G[i-1]);
		int Ans=0;
		for (int i=0; i<=sum1; i++)
			for (int j=0; j<=sum2; j++) {
				int lf=max(0,SUM-i-C1),rf=C0-i;
				if (lf>rf) continue;
				int lg=max(0,SUM-j-D1),rg=D0-j;
				if (lg>rg) continue;
				int res=H[i][j];
				if (lf) res=1ll*res*(F[rf]-F[lf-1]+Mod)%Mod;
				else res=1ll*res*F[rf]%Mod;
				if (lg) res=1ll*res*(G[rg]-G[lg-1]+Mod)%Mod;
				else res=1ll*res*G[rg]%Mod;
				Plus(Ans,res);
			}
		printf("%d\n",Ans);
	}
	return 0;
}
void Plus(int &x,int y)
{
	x+=y;
	if (x>=Mod) x-=Mod;
	return;
}
