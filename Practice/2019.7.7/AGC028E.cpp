#include<bits/stdc++.h>
using namespace std;

#define mp make_pair
#define ft first
#define sd second

const int maxN=202000;
const int inf=2000000000;

int Bodd[maxN],Beven[maxN];
int n,Seq[maxN],Mx[maxN],Sttop[maxN];
stack<pair<int*,int> > Rc;

void Modify(int *B,int p,int key);
int Query(int *B,int p);
bool check(int sum,int limit);
bool legal(int m0,int m1,int minus,int mxcnt);
int main()
{
	int mxcnt=0;
	scanf("%d",&n);
	for (int i=1; i<=n; i++) scanf("%d",&Seq[i]);
	for (int i=1,mx=0; i<=n; i++) {
		Bodd[i]=-inf;
		Beven[i]=0;
		if (Seq[i]>mx) Mx[i]=1,mx=Seq[i],++mxcnt;
	}

	for (int i=n; i>=1; i--) {
		//cerr<<i<<endl;
		int odd=-inf,even=-inf;
		Sttop[i]=Rc.size();
		if (Mx[i]) {
			odd=Query(Bodd,n-Seq[i]+1)+2;
			even=Query(Beven,n-Seq[i]+1)+2;
		} else {
			odd=Query(Beven,n-Seq[i]+1)+1;
			even=Query(Bodd,n-Seq[i]+1)+1;
		}

		if (odd>=0) Modify(Bodd,n-Seq[i]+1,odd);
		if (even>=0) Modify(Beven,n-Seq[i]+1,even);
	}

	if (!check(mxcnt,1)) {
		puts("-1");
		return 0;
	}

	int minus=0,mx0=1,mx1=1;
	for (int i=1; i<=n; i++) {
		if (Mx[i]) --mxcnt;
		while (Rc.size()>Sttop[i]) *Rc.top().ft=Rc.top().sd,Rc.pop();
		if (Seq[i]>=mx0) {
			if (legal(Seq[i],mx1,minus+1,mxcnt)) {
				printf("0");
				mx0=Seq[i];
				++minus;
			} else {
				printf("1");
				if (Seq[i]>=mx1) mx1=Seq[i],--minus;
			}
		} else {
			if (legal(mx0,mx1,minus,mxcnt)) printf("0");
			else {
				printf("1");
				if (Seq[i]>=mx1) mx1=Seq[i],--minus;
			}
		}
	}
	puts("");
	return 0;
}
void Modify(int *B,int p,int key)
{
	while (p<=n) {
		if (B[p]<key) {
			Rc.push(mp(&B[p],B[p]));
			B[p]=key;
		}
		p+=(p)&(-p);
	}
	return;
}
int Query(int *B,int p)
{
	int ret=-inf;
	while (p) {
		ret=max(ret,B[p]);
		p-=(p)&(-p);
	}
	return ret;
}
bool check(int sum,int limit)
{
	if (sum<0) return 0;
	if (sum&1) return sum<=Query(Bodd,n-limit+1);
	return sum<=Query(Beven,n-limit+1);
}
bool legal(int m0,int m1,int minus,int mxcnt)
{
	return check(mxcnt-minus,m0)||check(mxcnt+minus,m1);
}
