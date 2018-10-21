#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define ll long long
ll n,m,k,x;

ll Pow(ll a,ll b);

int main()
{
	cin>>n>>m>>k>>x;
	cout<<(x+m*Pow(10,k)%n)%n<<endl;
	return 0;
}

ll Pow(ll a,ll b)
{
	ll res=1;
	while (b!=0)
	{
		if (b&1)
			res=res*a%n;
		a=a*a%n;
		b=b>>1;
	}
	return res;
}
