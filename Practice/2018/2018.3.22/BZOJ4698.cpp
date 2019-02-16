#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1001000;
const int dpos=1000;
const int inf=2147483647;

int n,m;
int L,Arr[maxN];
int Belong[maxN];
int SA[maxN],Rank[maxN],Height[maxN];
int CntA[maxN],CntB[maxN],A[maxN],B[maxN],SSA[maxN];
bool Appear[maxN];

bool Check(int l);

int main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<=n;i++)
	{
		int m;cin>>m;
		int a;cin>>a;//Arr[++L]=a;Belong[L]=i;
		for (int j=2;j<=m;j++)
		{
			int b;cin>>b;
			Arr[++L]=b-a+dpos;Belong[L]=i;a=b;
		}
		Arr[++L]=i+1000+dpos;
	}
	//for (int i=1;i<=L;i++) cout<<Arr[i]<<" ";cout<<endl;
	for (int i=1;i<=L;i++) CntA[Arr[i]]++;
	for (int i=1;i<maxN;i++) CntA[i]+=CntA[i-1];
	for (int i=L;i>=1;i--) SA[CntA[Arr[i]]--]=i;
	Rank[SA[1]]=1;
	for (int i=2;i<=L;i++)
	{
		Rank[SA[i]]=Rank[SA[i-1]];
		if (Arr[SA[i]]!=Arr[SA[i-1]]) Rank[SA[i]]++;
	}
	for (int l=1;Rank[SA[L]]<L;l=l<<1)
	{
		mem(CntA,0);mem(CntB,0);
		for (int i=1;i<=L;i++)
		{
			CntA[A[i]=Rank[i]]++;
			CntB[B[i]=((i+l<=L)?(Rank[i+l]):(0))]++;
		}
		for (int i=1;i<maxN;i++) CntA[i]+=CntA[i-1],CntB[i]+=CntB[i-1];
		for (int i=L;i>=1;i--) SSA[CntB[B[i]]--]=i;
		for (int i=L;i>=1;i--) SA[CntA[A[SSA[i]]]--]=SSA[i];
		Rank[SA[1]]=1;
		for (int i=2;i<=L;i++)
		{
			Rank[SA[i]]=Rank[SA[i-1]];
			if ((A[SA[i]]!=A[SA[i-1]])||(B[SA[i]]!=B[SA[i-1]])) Rank[SA[i]]++;
		}
	}
	//for (int i=1;i<=L;i++) printf("%3d",Belong[Rank[i]]);printf("\n");
	//for (int i=1;i<=L;i++) printf("%3d",SA[i]);printf("\n");//cout<<SA[i]<<" ";cout<<endl;
	//for (int i=1;i<=L;i++) printf("%3d",Rank[i]);printf("\n");//cout<<Rank[i]<<" ";cout<<endl;
	/*
	for (int i=1;i<=L;i++)
	{
		for (int j=SA[i];j<=L;j++) printf("%d ",Arr[j]);
		printf("\n");
	}
	//*/
	for (int i=1,j=0;i<=L;i++)
	{
		if (j) j--;
		while (Arr[i+j]==Arr[SA[Rank[i]-1]+j]) j++;
		Height[Rank[i]]=j;
	}
	//for (int i=1;i<=L;i++) printf("%3d",Height[i]);printf("\n");//cout<<Height[i]<<" ";cout<<endl;
	int l=0,r=L;
	int Ans=0;
	do
	{
		int mid=(l+r)>>1;
		//cout<<"Check:"<<mid<<" "<<Check(mid)<<endl;
		if (Check(mid)) Ans=mid,l=mid+1;
		else r=mid-1;
	}
	while (l<=r);
	cout<<Ans+1<<endl;
	return 0;
}

bool Check(int l)
{
	mem(Appear,0);Appear[0]=1;
	for (int i=1,cnt=0;i<=L;i++)
	{
		if (Height[i]>=l)
		{
			if (Appear[Belong[SA[i]]]==0) Appear[Belong[SA[i]]]=1,cnt++;
			if (Appear[Belong[SA[i-1]]]==0) Appear[Belong[SA[i-1]]]=1,cnt++;
			if (cnt==n) return 1;
		}
		else
		{
			if (cnt!=0) mem(Appear,0);
			cnt=0;Appear[0]=1;
		}
	}
	return 0;
}
