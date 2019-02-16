#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=2000000;
const int inf=2147483647;

#define ll long long

int n,m;
int Ans;
int Op[maxN];
int Ed[maxN];
int Num[maxN];
ll Sum[maxN];
int Classroom[maxN];

int read();
bool check(int end);

int main()
{
	n=read();
	m=read();
	Ans=inf;
	for (int i=1;i<=n;i++)
		Classroom[i]=read();
	for (int i=1;i<=m;i++)
	{
		Num[i]=read();
		Op[i]=read();
		Ed[i]=read();
	}
	if (check(m))
	{
		printf("0\n");
		return 0;
	}
	int l=1,r=m;
	do
	{
		int mid=(l+r)/2;
		if (check(mid))
		    l=mid+1;
		else
			r=mid;
	}
	while (l<r);
	printf("-1\n%d\n",Ans);
	return 0;
}

int read()
{
	int x=0;
	char ch=getchar();
	while ((ch>'9')||(ch<'0'))
		ch=getchar();
	while ((ch<='9')&&(ch>='0'))
	{
		x=x*10+ch-48;
		ch=getchar();
	}
	return x;
}

bool check(int end)
{
	memset(Sum,0,sizeof(Sum));
	for (int i=1;i<=end;i++)
	{
		Sum[Op[i]]+=1LL*Num[i];
		Sum[Ed[i]+1]-=1LL*Num[i];
	}
	ll now=0;
	for (int i=1;i<=n;i++)
	{
		now+=Sum[i];
		if (now>Classroom[i])
		{
			Ans=min(Ans,end);
			return 0;
		}
	}
	return 1;
}
