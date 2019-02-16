#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

#define ll long long

const int maxN=110;
const int maxM=1001000;
const int inf=2147483647;
const int Mod=19260817;

int n,m;
char str[maxM];
ll A[maxN];
int Ans[maxM];

bool check(int x);
ll read();

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=0;i<=n;i++)
		A[i]=read();
	int Anscnt=0;
	for (int i=1;i<=m;i++)
		if (check(i))
		{
			Anscnt++;
			Ans[Anscnt]=i;
		}
	if (Anscnt==0)
		printf("0\n");
	else
	{
		printf("%d\n",Anscnt);
		for (int i=1;i<=Anscnt;i++)
			printf("%d\n",Ans[i]);
	}
	return 0;
}

ll read()
{
	ll x=0,k=1;
	char ch=getchar();
	while (((ch<'0')||(ch>'9'))&&(ch!='-'))
		ch=getchar();
	if (ch=='-')
	{
		k=-1;
		ch=getchar();
	}
	while ((ch>='0')&&(ch<='9'))
	{
		x=(x*10+ch-48)%Mod;
		ch=getchar();
	}
	return x*k;
}

bool check(int x)
{
	ll sum=0;
	for (int i=n;i>=0;i--)
		sum=(sum*x+A[i])%Mod;
	return !sum;
}
