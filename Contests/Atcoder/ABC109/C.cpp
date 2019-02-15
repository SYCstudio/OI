#include<bits/stdc++.h>
using namespace std;

const int maxN=101000;

int n,X;
int P[maxN];

int main(){
	cin>>n>>X;
	for (int i=1;i<=n;i++) cin>>P[i];
	int g=abs(X-P[1]);
	for (int i=2;i<=n;i++) g=__gcd(g,abs(X-P[i]));
	cout<<g<<endl;return 0;
}
