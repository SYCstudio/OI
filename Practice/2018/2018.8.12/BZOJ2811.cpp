#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;

class Range
{
public:
	int l,r;
};

int n,m,K;
int Sum[maxN],idcnt,Il[maxN],Ir[maxN],Num[maxN];
int InputL[maxN],InputR[maxN],InputO[maxN];
Range Rg[maxN],Seq[maxN];
int F[maxN],G[maxN];

bool cmp(Range A,Range B);

int main(){
	scanf("%d%d%d",&n,&K,&m);
	for (int i=1;i<=m;i++){
		scanf("%d%d%d",&InputL[i],&InputR[i],&InputO[i]);
		if (InputO[i]==0) Sum[InputL[i]]++,Sum[InputR[i]+1]--;
	}

	for (int i=1,sum=0;i<=n;i++){
		sum+=Sum[i];
		if (sum==0) Num[Il[i]=Ir[i]=++idcnt]=i;
	}
	if (K==idcnt){
		for (int i=1;i<=idcnt;i++) printf("%d\n",Num[i]);
		return 0;
	}
	Il[n+1]=n+1;
	for (int i=1;i<=n;i++) if (Ir[i]==0) Ir[i]=Ir[i-1];
	for (int i=n;i>=1;i--) if (Il[i]==0) Il[i]=Il[i+1];

	int N=0;
	for (int i=1;i<=m;i++)
		if (InputO[i]==1){
			int l=Il[InputL[i]],r=Ir[InputR[i]];
			if (l>r) continue;
			Rg[++N]=((Range){l,r});
		}

	sort(&Rg[1],&Rg[N+1],cmp);

	int nn=0;
	for (int i=N,lastr=inf;i>=1;i--)
		if (Rg[i].r<lastr){
			Seq[++nn]=Rg[i];lastr=Rg[i].r;
		}
	N=nn;reverse(&Seq[1],&Seq[N+1]);

	for (int i=1,lastr=0;i<=N;i++)
		if (Seq[i].l>lastr) F[i]=F[i-1]+1,lastr=Seq[i].r;
		else F[i]=F[i-1];

	for (int i=N,lastl=inf;i>=1;i--)
		if (Seq[i].r<lastl) G[i]=G[i+1]+1,lastl=Seq[i].l;
		else G[i]=G[i+1];

	bool flag=0;
	for (int i=1;i<=N;i++){
		if (F[i]==F[i-1]) continue;
		if (Seq[i].l==Seq[i].r){
			printf("%d\n",Num[Seq[i].l]);flag=1;continue;
		}
		int p=Seq[i].r-1;
		int p1=0,p2=N+1;
		int L=1,R=i-1;
		while (L<=R){
			int mid=(L+R)>>1;
			if (Seq[mid].r<p) p1=mid,L=mid+1;
			else R=mid-1;
		}
		L=i+1;R=N;
		while (L<=R){
			int mid=(L+R)>>1;
			if (Seq[mid].l>p) p2=mid,R=mid-1;
			else L=mid+1;
		}
		if (F[p1]+G[p2]+1>K){
			printf("%d\n",Num[Seq[i].r]);flag=1;
		}
	}
	if (flag==0) printf("-1\n");

	return 0;
}

bool cmp(Range A,Range B){
	if (A.l!=B.l) return A.l<B.l;
	else return A.r>B.r;
}
