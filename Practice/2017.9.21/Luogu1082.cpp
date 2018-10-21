#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

int exgcd(int a,int b,int &x,int &y);

int main()
{
	int a,b;
	int x,y;
	scanf("%d%d",&a,&b);
	exgcd(a,b,x,y);
	printf("%d\n",(x+b)%b);
	return 0;
}

int exgcd(int a,int b,int &x,int &y)
{
	if (b==0)
	{
		x=1;
		y=0;
		return a;
	}
	int now=exgcd(b,a%b,x,y);
	int tmp=x;
	x=y;
	y=tmp-a/b*y;
	return now;
}
