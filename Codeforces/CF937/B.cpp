#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1;
const int inf=2147483647;

ll p,y;

int main()
{
	ios::sync_with_stdio(false);
	cin>>p>>y;bool flag=0;
	do
	{
		int fac=-1;
		for (ll i=2;i*i<=y;i++)
			if (y%i==0){
				fac=i;break;
			}
		if ((fac==-1)||((fac>p)&&(y/fac>p))) {
			printf("%lld\n",y);flag=1;
			break;
		}
		y--;
	}
	while (y>p);
	if (flag==0) printf("-1\n");
	return 0;
}
