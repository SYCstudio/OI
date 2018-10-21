#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=500100;
const int inf=2147483647;

ll Arr[maxN];

int main()
{
	int Q;scanf("%d",&Q);Q--;
	scanf("%lld",&Arr[1]);scanf("%lld",&Arr[1]);
	int pos=0,numcnt=1;
	ll sum=0;
	while (Q--)
	{
		int opt;scanf("%d",&opt);
		if (opt==1)
		{
			numcnt++;scanf("%lld",&Arr[numcnt]);
			while ((pos<numcnt)&&(Arr[pos+1]<=(ld)(sum+Arr[numcnt])/(ld)(pos+1))) pos++,sum=sum+Arr[pos];
		}
		if (opt==2) printf("%.8LF\n",(ld)Arr[numcnt]-(ld)((ld)sum+(ld)Arr[numcnt])/((ld)pos+(ld)1));
	}
	return 0;
}
