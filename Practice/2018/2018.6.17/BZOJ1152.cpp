#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int Mod=10000;
const int inf=2147483647;

int n,m;
int Arr[maxN],Next[maxN];
ll Pow[maxN];

int main()
{
	scanf("%d%d",&n,&m);
	Pow[0]=1;for (int i=1;i<maxN;i++) Pow[i]=Pow[i-1]*n%Mod;
	while (m--)
	{
		int len;scanf("%d",&len);
		for (int i=1;i<=len;i++) scanf("%d",&Arr[i]);
		Next[0]=Next[1]=0;
		for (int i=2,j=0;i<=len;i++)
		{
			while ((j!=0)&&(Arr[i]!=Arr[j+1])) j=Next[j];
			if (Arr[i]==Arr[j+1]) j++;
			Next[i]=j;
		}
		//for (int i=1;i<=len;i++) cout<<Next[i]<<" ";cout<<endl;
		ll Ans=0;
		for (int i=len;i!=0;i=Next[i]) Ans=(Ans+Pow[i])%Mod;
		printf("%04lld\n",Ans);
	}
	return 0;
}
