#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define RG register
const int maxN=402000;
const int maxB=510;
const int inf=2000000000;

int n,m,bcnt;
int Seq[maxN],Srt[maxN],B[maxN],Bl[maxN],Br[maxN];
int Label[maxN],Val[maxN];
int Lkey[maxB][maxB],Mn[maxB][maxB],Lmn[maxN],Rmn[maxN];
int Rgmn[maxN],Sm[maxN],Lft[maxN];
pair<int,int> Pr[maxN];

int Query(int l,int r,int x);
int main()
{
	RG int i,j,l,r;
	scanf("%d%d",&n,&m);
	for (i=1; i<=n; ++i) scanf("%d",&Seq[i]),Pr[i]=make_pair(Seq[i],i);
	sort(&Pr[1],&Pr[n+1]);
	for (i=1; i<=n; ++i) Srt[i]=Pr[i].first;
	Srt[0]=-inf;

	int Block=sqrt(n);
	bcnt=(n-1)/Block+1;
	for (i=1; i<=n; ++i) {
		B[i]=(i-1)/Block+1;
		Br[B[i]]=i;
		if (!Bl[B[i]]) Bl[B[i]]=i;
	}

	for (i=1; i<=n; ++i) {
		l=max(Pr[i].second-m+1,1);
		r=Pr[i].second;
		if (B[l]==B[r]) for (j=l; j<=r; ++j) ++Val[j];
		else {
			for (j=l; j<=Br[B[l]]; ++j) ++Val[j];
			for (j=Bl[B[r]]; j<=r; ++j) ++Val[j];
			for (j=B[l]+1; j<B[r]; ++j) ++Label[j];
		}
		Lmn[i]=inf;
		for (j=Bl[B[l]]; j<=Br[B[l]]; ++j) Lmn[i]=min(Lmn[i],Val[j]);
		Rmn[i]=inf;
		for (j=Bl[B[r]]; j<=Br[B[r]]; ++j) Rmn[i]=min(Rmn[i],Val[j]);
		if (B[i]!=B[i+1]) {
			int b=B[i];
			for (j=1; j<=n; ++j) Val[j]+=Label[B[j]];
			for (j=1; j<=bcnt; ++j) Label[j]=0,Mn[b][j]=inf,Lkey[b][j]=Val[Bl[j]];
			for (j=1; j<=n; ++j) Mn[b][B[j]]=min(Mn[b][B[j]],Val[j]);
		}
	}

	int Q,lstans=0;
	scanf("%d",&Q);
	while (Q--) {
		int nx;
		scanf("%d%d%d",&l,&r,&nx);
		nx^=lstans;
		int cl=1,cr=n,p=0;
		while (cl<=cr) {
			int mid=(cl+cr)>>1;
			if (Pr[mid].first<=nx-1) p=mid,cl=mid+1;
			else cr=mid-1;
		}
		if (p==0) {
			printf("%d\n",lstans=0);
			continue;
		}
		int stb=B[p];
		for (i=1; i<=bcnt; ++i) Sm[i]=0,Lft[i]=Lkey[stb-1][i],Rgmn[i]=Mn[stb-1][i];
		for (i=Bl[stb]; i<=p; ++i) {
			int pl=max(Pr[i].second-m+1,1),pr=Pr[i].second;
			Rgmn[B[pl]]=Lmn[i];
			Rgmn[B[pr]]=Rmn[i];
			if (B[pl]<B[pr]) ++Sm[B[pl]+1],--Sm[B[pr]];
			if (pl<=Bl[B[l]]&&Bl[B[l]]<=pr) ++Lft[B[l]];
			if (pl<=Bl[B[r]]&&Bl[B[r]]<=pr&&B[l]!=B[r]) ++Lft[B[r]];
		}
		for (i=1; i<=bcnt; ++i) Sm[i]+=Sm[i-1],Rgmn[i]+=Sm[i];
		if (B[l]==B[r]) lstans=Query(l,r,nx-1);
		else {
			lstans=min(Query(l,Br[B[l]],nx-1),Query(Bl[B[r]],r,nx-1));
			for (int i=B[l]+1; i<B[r]; i++) lstans=min(lstans,Rgmn[i]);
		}
		printf("%d\n",lstans);
	}
	return 0;
}
int Query(int l,int r,int x)
{
	int val=Lft[B[l]];
	for (int i=Bl[B[l]]+1; i<=l; i++) val+=(Seq[i+m-1]<=x)-(Seq[i-1]<=x);
	int ret=val;
	for (int i=l+1; i<=r; i++) val+=(Seq[i+m-1]<=x)-(Seq[i-1]<=x),ret=min(ret,val);
	return ret;
}