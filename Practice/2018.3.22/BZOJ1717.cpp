#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50010;
const int maxNum=2000100;
const int inf=2147483647;

int n,K;
int Arr[maxN];
int SA[maxN],Rank[maxN],Height[maxN];
int Cnt[maxNum],CntA[maxN],CntB[maxN],A[maxN],B[maxN],SSA[maxN];
int Queue[maxN];

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>K;
	for (int i=1;i<=n;i++) cin>>Arr[i];
	for (int i=1;i<=n;i++) Cnt[Arr[i]]++;
	for (int i=1;i<maxNum;i++) Cnt[i]+=Cnt[i-1];
	for (int i=n;i>=1;i--) SA[Cnt[Arr[i]]--]=i;
	Rank[SA[1]]=1;
	for (int i=2;i<=n;i++)
	{
		Rank[SA[i]]=Rank[SA[i-1]];
		if (Arr[SA[i]]!=Arr[SA[i-1]]) Rank[SA[i]]++;
	}
	for (int l=1;Rank[SA[n]]!=n;l=l<<1)
	{
		mem(CntA,0);mem(CntB,0);
		for (int i=1;i<=n;i++)
		{
			CntA[A[i]=Rank[i]]++;
			CntB[B[i]=((i+l<=n)?(Rank[i+l]):(0))]++;
		}
		for (int i=1;i<maxN;i++) CntA[i]+=CntA[i-1],CntB[i]+=CntB[i-1];
		for (int i=n;i>=1;i--) SSA[CntB[B[i]]--]=i;
		for (int i=n;i>=1;i--) SA[CntA[A[SSA[i]]]--]=SSA[i];
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
	//for (int i=1;i<=n;i++) cout<<Height[i]<<" ";cout<<endl;
	int Ans=0,l=0,r=0;
	K--;
	for (int i=1;i<=n;i++)
	{
		while ((l<r)&&(Height[i]<Height[Queue[r]])) r--;
		Queue[++r]=i;
		if (i<K) continue;
		while ((l<r)&&(i-K+1>Queue[l])) l++;
		Ans=max(Ans,Height[Queue[l]]);
		//for (int j=l;j<=r;j++) cout<<Queue[j]<<" ";cout<<endl;
	}
	cout<<Ans<<endl;
	return 0;
}
