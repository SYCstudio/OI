#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1001000;
const int inf=2147483647;

int n;
char str[maxN];
int F[maxN];

int main()
{
	int cas=0;
	ios::sync_with_stdio(false);
	while (cin>>n)
	{
		if (n==0) break;
		cin>>(str+1);
		F[1]=0;F[0]=-1;
		for (int i=2;i<=n;i++)
		{
			int j=F[i-1];
			while ((j!=0)&&(str[j+1]!=str[i])) j=F[j];
			if (str[j+1]==str[i]) F[i]=j+1;
			else F[i]=0;
		}
		printf("Test case #%d\n",++cas);
		for (int i=2;i<=n;i++)
			if ((F[i]!=0)&&(i%(i-F[i])==0)) printf("%d %d\n",i,i/(i-F[i]));
		printf("\n");
	}
	return 0;
}
