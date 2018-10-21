#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000;
const int inf=2147483647;

int n;
int Arr[maxN];
int CntA[maxN+20],CntB[maxN+20],SAA[maxN];
int SA[maxN],Rank[maxN],Height[maxN];
int A[maxN],B[maxN];

bool Check(int mid);

int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++) cin>>Arr[i];
	for (int i=1;i<=n;i++) CntA[Arr[i]]++;
	for (int i=1;i<=maxN;i++) CntA[i]+=CntA[i-1];
	for (int i=n;i>=1;i--) SA[CntA[Arr[i]]--]=i;
	Rank[SA[1]]=1;
	for (int i=2;i<=n;i++)
	{
		Rank[SA[i]]=Rank[SA[i-1]];
		if (Arr[SA[i]]!=Arr[SA[i-1]]) Rank[SA[i]]++;
	}
	for (int l=1;Rank[SA[n]]<n;l=l<<1)
	{
		for (int i=0;i<=maxN;i++) CntA[i]=CntB[i]=0;
		for (int i=1;i<=n;i++)
		{
			CntA[A[i]=Rank[i]]++;
			CntB[B[i]=((i+l<=n)?(Rank[i+l]):(0))]++;
		}
		for (int i=1;i<=maxN;i++) CntA[i]+=CntA[i-1],CntB[i]+=CntB[i-1];
		for (int i=n;i>=0;i--) SAA[CntB[B[i]]--]=i;
		for (int i=n;i>=0;i--) SA[CntA[A[SAA[i]]]--]=SAA[i];
		Rank[SA[1]]=1;
		for (int i=2;i<=n;i++)
		{
			Rank[SA[i]]=Rank[SA[i-1]];
			if ((A[SA[i]]!=A[SA[i-1]])||(B[SA[i]]!=B[SA[i-1]])) Rank[SA[i]]++;
		}
	}
	for (int i=1,j=0;i<=n;i++)
	{
		if (j) j--;
		while (Arr[i+j]==Arr[SA[Rank[i]-1]+j]) j++;
		Height[Rank[i]]=j;
	}
	int l=0,r=n;
	int Ans=0;
	do
	{
		int mid=(l+r)>>1;
		if (Check(mid)) Ans=mid,l=mid+1;
		else r=mid-1;
	}
	while (l<=r);
	printf("%d\n",Ans);
	return 0;
}

bool Check(int mid)
{
	int mnsa=maxN,mxsa=0;
	for (int i=1;i<=n;i++)
		if (Height[i]>=mid)
		{
			mnsa=min(mnsa,SA[i]);
			mxsa=max(mxsa,SA[i]);
			if (mxsa-mnsa>=mid) return 1;
		}
		else mnsa=mxsa=SA[i];
	return 0;
}
