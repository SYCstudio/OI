#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxN=2000;
const int inf=2147483647;

int n;
int Arr[maxN];
int F[maxN];

int main()
{
	while (cin>>n)
	{
		if (n==0)
			break;
		memset(F,0,sizeof(F));
		int Ans=0;
		for (int i=1;i<=n;i++)
		{
			scanf("%d",&Arr[i]);
			F[i]=Arr[i];
			for (int j=1;j<i;j++)
				if (Arr[j]<Arr[i])
					F[i]=max(F[i],F[j]+Arr[i]);
			Ans=max(Ans,F[i]);
		}
		printf("%d\n",Ans);
	}
	return 0;
}
