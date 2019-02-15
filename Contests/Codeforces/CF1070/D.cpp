#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int maxN=202000;
const int inf=2147483647;

int n;ll K;
int A[maxN];

int main(){
	cin>>n>>K;
	for (int i=1;i<=n;i++) cin>>A[i];
	ll Ans=0;
	for (int i=2;i<=n;i++){
		ll cnt=(A[i-1]+K-1)/K;
		Ans+=cnt;A[i]=max(0ll,A[i]-(K*cnt-A[i-1]));
	}
	Ans=Ans+(A[n]+K-1)/K;
	cout<<Ans<<endl;
	return 0;
}
