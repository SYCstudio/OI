#include<bits/stdc++.h>
using namespace std;

const int maxN=110;
const int inf=2147483647;

int n,m;
int A[maxN];

int main(){
	cin>>n>>m;
	for (int i=1;i<=n;i++) cin>>A[i];
	sort(&A[1],&A[n+1]);
	int sum=0;
	int p=0;
	while (p<n){
		if (sum+A[p+1]>m) break;
		p++;sum+=A[p];
	}
	if ((p==n)&&(sum!=m)) p--;
	cout<<p<<endl;
	return 0;
}
