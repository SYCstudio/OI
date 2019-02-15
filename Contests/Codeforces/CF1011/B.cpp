#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=110;
const int inf=2147483647;

int n,m;
int Cnt[maxN];

int main()
{
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++){
		int key;scanf("%d",&key);Cnt[key]++;
	}

	int L=1,R=100,Ans=0;
	do
	{
		int mid=(L+R)>>1;
		int tot=0;
		for (int i=1;i<=100;i++) tot+=(int)(Cnt[i]/mid);
		if (tot>=n) Ans=mid,L=mid+1;
		else R=mid-1;
	}
	while (L<=R);
	printf("%d\n",Ans);
	return 0;
}

