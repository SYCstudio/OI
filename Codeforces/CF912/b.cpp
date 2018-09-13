#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long

ll k,n;

int main()
{
	cin>>n>>k;
	ll i;
	for (i=0;(((ll)(1))<<i)<=n;i++);
	if (k==1) cout<<n<<endl;
	else cout<<(((ll)(1))<<i)-1<<endl;
	return 0;
}
