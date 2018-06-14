#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

int main()
{
	int n,p,q;
	while (scanf("%d%d%d",&n,&p,&q)!=EOF)
	{
		int k=n%(p+q);
		if ((k==0)||(k>p)) printf("WIN\n");
		else printf("LOST\n");
	}
	return 0;
}
