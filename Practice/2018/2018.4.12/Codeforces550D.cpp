#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

int K;

int main()
{
	scanf("%d",&K);
	if (K%2==0)
	{
		printf("NO\n");
		return 0;
	}
	printf("YES\n");
	printf("%d %d\n",(K-1+K-1)*2+2,(K-1+(K-1)*(K-1)+(K-1)/2)*2+1);
	printf("1 2\n");
	for (int i=3;i<=K+1;i++)
	{
		printf("%d 2\n",i);
		for (int j=K+2;j<=2*K;j++) printf("%d %d\n",i,j);
	}
	for (int i=K+2;i<=2*K;i+=2) printf("%d %d\n",i,i+1);
	for (int i=2*K+1;i<=3*K-1;i++)
	{
		printf("%d 1\n",i);
		for (int j=3*K;j<=4*K-2;j++) printf("%d %d\n",i,j);
	}
	for (int i=3*K;i<=4*K-2;i+=2) printf("%d %d\n",i,i+1);
	return 0;
}
