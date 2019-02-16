#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=21;
const ld eps=1e-10;
const int inf=2147483647;

int n,K;
int Cnt[1<<maxN];
ld P[1<<maxN];
ld F[1<<maxN];
ld Ans[maxN];

int main(){
	scanf("%d%d",&n,&K);int cnt=n,N=1<<n;
	for (int i=0;i<n;i++){
		scanf("%LF",&P[1<<i]);
		if (P[1<<i]<eps) --cnt;
	}
	K=min(K,cnt);
	for (int i=0;i<N;i++){
		Cnt[i]=Cnt[i>>1]+(i&1);
		P[i]=P[i&(-i)]+P[i-((i)&(-i))];
	}
	F[0]=1;
	for (int i=0;i<N;i++){
		for (int j=0;j<n;j++) if (((i>>j)&1)&&(fabs(1-P[i^(1<<j)])>eps)) F[i]=F[i]+F[i^(1<<j)]*P[1<<j]/(1-P[i^(1<<j)]);
		if (Cnt[i]==K) for (int j=0;j<n;j++) if ((i>>j)&1) Ans[j]+=F[i];
	}
	for (int i=0;i<n;i++) printf("%.15LF ",Ans[i]);return 0;
}
