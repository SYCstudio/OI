#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1;
const int inf=2147483647;

ll K,D,T;
ld v1,v2;

int main()
{
	ios::sync_with_stdio(false);
	cin>>K>>D>>T;
	v1=(ld)1/T;v2=(ld)1/T/(ld)2;
	if (D<T)
	{
		int d=D;
		while (d<T) d=d+D;
		ld finish=T*v1+(d-T)*v2;
	}
}
