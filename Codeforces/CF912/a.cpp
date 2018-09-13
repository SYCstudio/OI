#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long

ll A,B;
ll x,y,z;
ll yellow=0,blue=0;

int main()
{
	cin>>A>>B;
	cin>>x>>y>>z;
	yellow=x*2+y;
	blue=y+3*z;
	cout<<max(0ll,yellow-A)+max(0ll,blue-B)<<endl;
	return 0;
}
