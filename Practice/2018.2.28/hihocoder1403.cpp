#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=20010;
const int inf=2147483647;

int n,K;
int Arr[maxN];
int SA[maxN],Rank[maxN],Height[maxN];
int CntA[maxN],CntB[maxN],A[maxN],B[maxN],SAA[maxN];
int Queue[maxN];

int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>K;
	for (int i=1;i<=n;i++) cin>>Arr[i];
	//GetSA
	mem(CntA,0);
	for (int i=1;i<=n;i++) CntA[Arr[i]]++;
	for (int i=1;i<=n;i++) CntA[i]+=CntA[i-1];
	for (int i=n;i>=1;i--) SA[CntA[Arr[i]]--]=i;
	//初始化结束，构造初试Rank
	Rank[SA[1]]=1;
	for (int i=2;i<=n;i++)
	{
		Rank[SA[i]]=Rank[SA[i-1]];
		if (Arr[SA[i]]!=Arr[SA[i-1]]) Rank[SA[i]]++;
	}
	//for (int i=1;i<=n;i++) cout<<SA[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Rank[i]<<" ";cout<<endl;cout<<endl;
	for (int l=1;Rank[SA[n]]<n;l=l<<1)
	{
		for (int i=0;i<=n;i++) CntA[i]=CntB[i]=0;
		for (int i=1;i<=n;i++)
		{
			CntA[A[i]=Rank[i]]++;
			CntB[B[i]=((i+l<=n)?(Rank[i+l]):(0))]++;
		}
		//cout<<"CntA:";for (int i=1;i<=n;i++) cout<<CntA[i]<<" ";cout<<endl;
		//cout<<"CntB:";for (int i=1;i<=n;i++) cout<<CntB[i]<<" ";cout<<endl;
		for (int i=1;i<=n;i++) CntA[i]+=CntA[i-1],CntB[i]+=CntB[i-1];
		for (int i=n;i>=0;i--) SAA[CntB[B[i]]--]=i;
		for (int i=n;i>=0;i--) SA[CntA[A[SAA[i]]]--]=SAA[i];
		Rank[SA[1]]=1;
		for (int i=2;i<=n;i++)
		{
			Rank[SA[i]]=Rank[SA[i-1]];
			if ((A[SA[i]]!=A[SA[i-1]])||(B[SA[i]]!=B[SA[i-1]])) Rank[SA[i]]++;
		}
		//cout<<"SA:";for (int i=1;i<=n;i++) cout<<SA[i]<<" ";cout<<endl;
		//cout<<"Rank:";for (int i=1;i<=n;i++) cout<<Rank[i]<<" ";cout<<endl<<endl;
	}
	for (int i=1,j=0;i<=n;i++)
	{
		if (j) j--;
		while (Arr[i+j]==Arr[SA[Rank[i]-1]+j]) j++;
		Height[Rank[i]]=j;
	}
	//cout<<"Height:";for (int i=1;i<=n;i++) cout<<Height[i]<<" ";cout<<endl;
	int l=0,r=0;
	int Ans=0;
	for (int i=1;i<=n;i++)
	{
		while ((l<r)&&(Height[Queue[r]]>Height[i])) r--;
		Queue[++r]=i;
		if (i<=K-1) continue;
		while ((l<r)&&(Queue[l]+K-2<i)) l++;
		Ans=max(Ans,Height[Queue[l]]);
		//cout<<Queue[l]<<" "<<i<<" "<<Height[Queue[l]]<<endl;
	}
	printf("%d\n",Ans);
	return 0;
}
