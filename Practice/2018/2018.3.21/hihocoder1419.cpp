#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100100;
const int maxBit=18;
const int inf=2147483647;

char str[maxN];
int SA[maxN],Height[maxN],Rank[maxN];
int CntA[maxN],CntB[maxN],A[maxN],B[maxN],SSA[maxN];
int ST[maxN][maxBit];
int Log[maxN];

int Lcp(int p1,int p2);

int main()
{
	ios::sync_with_stdio(false);
	for (int i=1;i<maxN;i++) Log[i]=log2(i);
	
	cin>>(str+1);
	int L=strlen(str+1);
	
	for (int i=1;i<=L;i++) CntA[str[i]]++;
	for (int i=1;i<maxN;i++) CntA[i]+=CntA[i-1];
	for (int i=L;i>=1;i--) SA[CntA[str[i]]--]=i;
	Rank[SA[1]]=1;
	for (int i=2;i<=L;i++)
	{
		Rank[SA[i]]=Rank[SA[i-1]];
		if (str[SA[i]]!=str[SA[i-1]]) Rank[SA[i]]++;
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
	//for (int i=1;i<=L;i++) cout<<SA[i]<<" ";cout<<endl;
	for (int i=1,j=0;i<=L;i++)
	{
		if (j) j--;
		while (str[i+j]==str[SA[Rank[i]-1]+j]) j++;
		Height[Rank[i]]=j;
	}
	//for (int i=1;i<=L;i++) cout<<Height[i]<<" ";cout<<endl;
	for (int i=1;i<=L;i++) ST[i][0]=Height[i];
	for (int i=1;i<maxBit;i++)
		for (int j=1;j<=L;j++)
			if (j+(1<<i)<=L)
				ST[j][i]=min(ST[j][i-1],ST[j+(1<<i)][i-1]);
	int Ans=0;
	for (int l=1;l<=L;l++)
		for (int i=1;i+l<=L;i+=l)
		{
			int r=Lcp(i,i+l);
			Ans=max(Ans,r/l+1);
			if (i>=l-r%l) Ans=max(Ans,Lcp(i-l+r%l,i+r%l)/l+1);
		}
	cout<<Ans<<endl;
	return 0;
}

int Lcp(int p1,int p2)
{
	if (Rank[p1]>Rank[p2]) swap(p1,p2);
	p1=Rank[p1];p2=Rank[p2];
	p1++;
	int l=Log[p2-p1+1];
	return min(ST[p1][l],ST[p2-(1<<l)+1][l]);
}
