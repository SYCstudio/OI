#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
#define pb push_back
const int maxN=303000;

int n;
int A[maxN],fr[maxN];
ll F[maxN];
vector<int> O;

void Decr(int x);
int main()
{
	scanf("%d",&n);
	for (int i=1; i<=n; i++) {
		scanf("%d",&A[i]);
		F[i]=min(F[max(i-2,0)]+A[i],F[max(i-3,0)]+max(A[i],A[i-1]));
		if (F[i]==F[max(i-3,0)]+max(A[i],A[i-1])) fr[i]=1;
	}
	ll Ans=min(F[n],F[n-1]);
	for (int i=Ans==F[n]?n:n-1; i>=1; i=i-2-fr[i]) {
		Decr(i-1);
		if (fr[i]) Decr(i-2);
		Decr(i);
	}
	printf("%d\n",(int)O.size());
	for (int i=0; i<O.size(); i++) printf("%d\n",O[i]);
	return 0;
}
void Decr(int x)
{
	if (A[x]&&A[x+1]) {
		O.pb(x);
		int mn=min(A[x],A[x+1]);
		A[x]-=mn;
		A[x+1]-=mn;
	}
	return;
}
