#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define ld double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

ld Calc(ld x);

int main()
{
	int TTT;scanf("%d",&TTT);
	while (TTT--)
	{
		ld a,b,l,r;scanf("%lf%lf%lf%lf",&a,&b,&l,&r);
		if (l==r){
			printf("%.3lf\n",(ld)0.0);continue;
		}
		ld ans=-a*b;
		printf("%.3lf\n",ans*(Calc(acos(r/a))-Calc(acos(l/a))));
	}
	return 0;
}

ld Calc(ld x)
{
	return x-0.5*sin(2.0*x);
}
