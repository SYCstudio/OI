#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

typedef long long ll;
const int maxNum=10000010;

int pcnt,P[maxNum],notp[maxNum],G[maxNum],Lw[maxNum],Lc[maxNum];
ll Sum[maxNum];

void Init();
int main()
{
	Init();
	int Case;
	scanf("%d",&Case);
	while (Case--) {
		int n,m;
		scanf("%d%d",&n,&m);
		if (n>m) swap(n,m);
		ll Ans=0;
		for (int l=1,r; l<=n; l=r+1) {
			r=min(n/(n/l),m/(m/l));
			Ans=Ans+(Sum[r]-Sum[l-1])*(n/l)*(m/l);
		}
		printf("%lld\n",Ans);
	}
	return 0;
}
void Init()
{
	G[1]=0;
	notp[1]=1;
	for (int i=2; i<maxNum; i++) {
		if (notp[i]==0) P[++pcnt]=i,Lw[i]=i,Lc[i]=1,G[i]=1;
		for (int j=1; j<=pcnt&&1ll*i*P[j]<maxNum; j++) {
			notp[i*P[j]]=1;
			if (i%P[j]==0) {
				Lw[i*P[j]]=Lw[i]*P[j];
				Lc[i*P[j]]=Lc[i]+1;
				if (Lw[i]==i) G[i*P[j]]=1;
				else if (Lc[i/Lw[i]]==Lc[i*P[j]]) G[i*P[j]]=-G[i/Lw[i]];
				break;
			}
			Lc[i*P[j]]=1;
			Lw[i*P[j]]=P[j];
			if (Lc[i]==1) G[i*P[j]]=-G[i];
		}
	}
	for (int i=1; i<maxNum; i++) Sum[i]=Sum[i-1]+G[i];
	return;
}