#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

typedef long long ll;
#define ls (x<<1)
#define rs (ls|1)
#define Dct(x) (lower_bound(&Num[1],&Num[num+1],x)-Num)
const int maxN=202000;
const ll INF=1e18;

int n,m,K;
int W[maxN],Bs[maxN];
int num,Num[maxN];
int scnt[4],Sorter[4][maxN];
int C[maxN<<2];
ll Sm[maxN<<2],Pre[3][maxN];

void Modify(int x,int l,int r,int p,int cnt);
ll Query(int x,int l,int r,int kth);
int main()
{
	scanf("%d%d%d",&n,&m,&K);
	for (int i=1; i<=n; i++) scanf("%d",&W[i]),Num[i]=W[i];
	sort(&Num[1],&Num[n+1]);
	num=unique(&Num[1],&Num[n+1])-Num-1;
	int m1,m2;
	scanf("%d",&m1);
	for (int i=1; i<=m1; i++) {
		int x;
		scanf("%d",&x);
		Bs[x]|=1;
	}
	scanf("%d",&m2);
	for (int i=1; i<=m2; i++) {
		int x;
		scanf("%d",&x);
		Bs[x]|=2;
	}
	for (int i=1; i<=n; i++) Sorter[Bs[i]][++scnt[Bs[i]]]=W[i];
	for (int i=0; i<=3; i++) sort(&Sorter[i][1],&Sorter[i][scnt[i]+1]);
	for (int i=1; i<=scnt[3]; i++) Modify(1,1,num,Dct(Sorter[3][i]),1);
	for (int i=1; i<=scnt[0]; i++) Modify(1,1,num,Dct(Sorter[0][i]),1);
	for (int i=K+1; i<=scnt[1]; i++) Modify(1,1,num,Dct(Sorter[1][i]),1);
	for (int i=K+1; i<=scnt[2]; i++) Modify(1,1,num,Dct(Sorter[2][i]),1);
	for (int i=1; i<=3; i++) for (int j=1; j<=scnt[i]; j++) Pre[i-1][j]=Pre[i-1][j-1]+Sorter[i][j];
	ll Ans=INF;
	for (int i=K; i>=0; i--) {
		if (i<=scnt[1]&&i<=scnt[2]&&K-i<=scnt[3]&&i+K<=m) {
			Ans=min(Ans,Pre[0][i]+Pre[1][i]+Pre[2][K-i]+Query(1,1,num,m-i-K));
		}
		if (i&&i<=scnt[1]) Modify(1,1,num,Dct(Sorter[1][i]),1);
		if (i&&i<=scnt[2]) Modify(1,1,num,Dct(Sorter[2][i]),1);
		if (K-i+1&&K-i+1<=scnt[3]) Modify(1,1,num,Dct(Sorter[3][K-i+1]),-1);
	}
	if (Ans==INF) puts("-1");
	else printf("%lld\n",Ans);
	return 0;
}
void Modify(int x,int l,int r,int p,int cnt)
{
	C[x]+=cnt;
	Sm[x]+=Num[p]*cnt;
	if (l==r) return;
	int mid=(l+r)>>1;
	if (p<=mid) Modify(ls,l,mid,p,cnt);
	else Modify(rs,mid+1,r,p,cnt);
	return;
}
ll Query(int x,int l,int r,int kth)
{
	if (l==r) {
		if (C[x]<kth) return -INF;
		return 1ll*Num[l]*kth;
	}
	int mid=(l+r)>>1;
	if (C[ls]>=kth) return Query(ls,l,mid,kth);
	else return Sm[ls]+Query(rs,mid+1,r,kth-C[ls]);
}