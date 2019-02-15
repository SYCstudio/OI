#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=40;
const int inf=2147483647;

int Opt[maxN];

int main()
{
	int n,m,ans;
	scanf("%d%d",&m,&n);
	for (int i=1;i<=n;i++){
		printf("1\n");fflush(stdout);scanf("%d",&ans);
		if (ans==0) exit(0);
		if (ans==1) Opt[i]=-1;
		else Opt[i]=1;
	}


	int L=1,R=m,outp=0,cnt=0;
	do
	{
		cnt++;
		if (cnt>n) cnt=1;
		int mid=(L+R)>>1;
		printf("%d\n",mid);fflush(stdout);scanf("%d",&ans);
		if (ans==0) exit(0);
		ans*=Opt[cnt];
		if (ans==1) R=mid-1;
		else L=mid+1;
	}
	while (L<=R);
	printf("%d\n",L);fflush(stdout);scanf("%d",&ans);
	return 0;
}

