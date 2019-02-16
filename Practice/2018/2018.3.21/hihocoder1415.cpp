#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=100010*2;
const int inf=2147483647;

char Input1[maxN],Input2[maxN];
int str[maxN];
int SA[maxN],Rank[maxN],Height[maxN];
int Cnt1[maxN],Cnt2[maxN],A[maxN],B[maxN],SSA[maxN];

int main()
{
	ios::sync_with_stdio(false);
	cin>>(Input1+1);
	cin>>(Input2+1);
	int l1=strlen(Input1+1),l2=strlen(Input2+1);
	for (int i=1;i<=l1;i++) str[i]=Input1[i]-'a'+1;
	str[l1+1]='z'+1;
	for (int i=1;i<=l2;i++) str[i+l1+1]=Input2[i]-'a'+1;
	//SA
	int L=l1+l2+1;
	//cout<<L<<endl;
	for (int i=1;i<=L;i++) Cnt1[str[i]]++;
	for (int i=1;i<maxN;i++) Cnt1[i]+=Cnt1[i-1];
	for (int i=L;i>=0;i--) SA[Cnt1[str[i]]--]=i;
	Rank[SA[1]]=1;
	for (int i=2;i<=L;i++)
	{
		Rank[SA[i]]=Rank[SA[i-1]];
		if (str[SA[i]]!=str[SA[i-1]]) Rank[SA[i]]++;
	}
	//for (int i=1;i<=L;i++) cout<<SA[i]<<" ";cout<<endl;
	//for (int i=1;i<=L;i++) cout<<Rank[i]<<" ";cout<<endl;
	for (int l=1;Rank[SA[L]]<L;l=l<<1)
	{
		mem(Cnt1,0);mem(Cnt2,0);
		for (int i=1;i<=L;i++)
		{
			Cnt1[A[i]=Rank[i]]++;
			Cnt2[B[i]=((i+l<=L)?(Rank[i+l]):(0))]++;
		}
		for (int i=1;i<maxN;i++) Cnt1[i]+=Cnt1[i-1],Cnt2[i]+=Cnt2[i-1];
		for (int i=L;i>=0;i--) SSA[Cnt2[B[i]]--]=i;
		for (int i=L;i>=0;i--) SA[Cnt1[A[SSA[i]]]--]=SSA[i];
		Rank[SA[1]]=1;
		for (int i=2;i<=L;i++)
		{
			Rank[SA[i]]=Rank[SA[i-1]];
			if ((A[SA[i]]!=A[SA[i-1]])||(B[SA[i]]!=B[SA[i-1]])) Rank[SA[i]]++;
		}
	}
	//for (int i=1;i<=L;i++)cout<<(char)(str[i]+'a'-1);cout<<endl;
	for (int i=1,j=0;i<=L;i++)
	{
		if (j) j--;
		while (str[i+j]==str[SA[Rank[i]-1]+j]) j++;
		Height[Rank[i]]=j;
	}
	//for (int i=1;i<=L;i++) cout<<SA[i]<<" ";cout<<endl;
	//for (int i=1;i<=L;i++) cout<<Height[i]<<" ";cout<<endl;
	int Ans=0;
	for (int i=2;i<=L;i++)
		if (((SA[i-1]<=l1)&&(SA[i]>=l1+1))||((SA[i-1]>=l1+1)&&(SA[i]<=l1))) Ans=max(Ans,Height[i]);
	cout<<Ans<<endl;
	return 0;
}
