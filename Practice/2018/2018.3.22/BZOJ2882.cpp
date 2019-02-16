#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=300100*2;
const int inf=2147483647;

int n;
int Arr[maxN];
int SA[maxN],Rank[maxN];
int CntA[maxN],CntB[maxN],A[maxN],B[maxN],SSA[maxN];

int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++){
		cin>>Arr[i];Arr[i+n]=Arr[i];
	}
	n=n+n;
	for (int i=1;i<=n;i++) CntA[Arr[i]]++;
	for (int i=1;i<maxN;i++) CntA[i]+=CntA[i-1];
	for (int i=n;i>=1;i--) SA[CntA[Arr[i]]--]=i;
	Rank[SA[1]]=1;
	for (int i=2;i<=n;i++)
	{
		Rank[SA[i]]=Rank[SA[i-1]];
		if (Arr[SA[i]]!=Arr[SA[i-1]]) Rank[SA[i]]++;
	}
	for (int l=1;Rank[SA[n]]<n;l=l<<1)
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
	int pos;
	for (int i=1;i<=n;i++)
		if (SA[i]<=n/2){
			pos=SA[i];break;
		}
	for (int i=1;i<=n/2;i++) cout<<Arr[pos+i-1]<<" ";cout<<endl;
	return 0;
}
