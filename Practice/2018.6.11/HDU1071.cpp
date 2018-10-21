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

int main()
{
	int TTT;scanf("%d",&TTT);
	while (TTT--)
	{
		ld x1,y1,x2,y2,x3,y3;scanf("%lf%lf%lf%lf%lf%lf",&x1,&y1,&x2,&y2,&x3,&y3);
		ld a,b,c;
		a=(y2-y1)/((x2-x1)*(x2-x1));
		b=-2.0*a*x1;c=a*x1*x1+y1;
		b-=(y2-y3)/(x2-x3);c-=(y2-(y2-y3)/(x2-x3)*x2);
		printf("%.2lf\n",a*(x3*x3*x3/3.0-x2*x2*x2/3.0)+b*(x3*x3/2.0-x2*x2/2.0)+c*(x3-x2));
	}
	return 0;
}
