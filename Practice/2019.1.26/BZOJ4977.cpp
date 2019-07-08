#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

#define ll long long

const int maxN=101000;

int n,m;
int A[maxN];
pair<int,int> P[maxN];
priority_queue<int> H;

int main()
{
	//freopen("in","r",stdin);
	scanf("%d%d",&n,&m);
	for (int i=1; i<=n; i++) scanf("%d",&A[i]);
	for (int i=1; i<=m; i++) {
		int b,c;
		scanf("%d%d",&b,&c);
		P[i].first=b;
		P[i].second=c-b;
	}
	sort(&A[1],&A[n+1]);
	sort(&P[1],&P[m+1]);
	ll Ans=0;
	for (int i=1,j=1; i<=n; i++) {
		while (j<=m&&P[j].first<A[i]) H.push(P[j++].second);
		if (H.empty()||H.top()+A[i]<0) continue;
		Ans=Ans+H.top()+A[i];
		H.pop();
		H.push(-A[i]);
	}
	printf("%lld\n",Ans);
	return 0;
}
