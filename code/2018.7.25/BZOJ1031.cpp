#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=101000*2;
const int inf=2147483647;

char str[maxN];
int A[maxN],B[maxN],CntA[maxN],CntB[maxN];
int SA[maxN],SSA[maxN],Rank[maxN];

int main()
{
	scanf("%s",str+1);
	int len=strlen(str+1);
	for (int i=len+1;i<=len+len;i++) str[i]=str[i-len];
	len+=len;

	for (int i=1;i<=len;i++) CntA[str[i]]++;
	for (int i=1;i<maxN;i++) CntA[i]+=CntA[i-1];
	for (int i=len;i>=1;i--) SA[CntA[str[i]]--]=i;
	Rank[SA[1]]=1;
	for (int i=2;i<=len;i++)
	{
		Rank[SA[i]]=Rank[SA[i-1]];
		if (str[SA[i]]!=str[SA[i-1]]) Rank[SA[i]]++;
	}

	//for (int i=1;i<=len;i++) cout<<SA[i]<<" ";cout<<endl;
	//for (int i=1;i<=len;i++) cout<<Rank[i]<<" ";cout<<endl;

	for (int i=1;Rank[SA[len]]!=len;i<<=1)
	{
		mem(CntA,0);mem(CntB,0);
		for (int j=1;j<=len;j++)
		{
			CntA[A[j]=Rank[j]]++;
			CntB[B[j]=((i+j<=len)?(Rank[i+j]):(0))]++;
		}

		for (int j=1;j<maxN;j++) CntA[j]+=CntA[j-1],CntB[j]+=CntB[j-1];

		for (int j=len;j>=1;j--) SSA[CntB[B[j]]--]=j;
		for (int j=len;j>=1;j--) SA[CntA[A[SSA[j]]]--]=SSA[j];

		Rank[SA[1]]=1;
		for (int j=2;j<=len;j++)
		{
			Rank[SA[j]]=Rank[SA[j-1]];
			if ((A[SA[j]]!=A[SA[j-1]])||(B[SA[j]]!=B[SA[j-1]])) Rank[SA[j]]++;
		}

		//for (int j=1;j<=len;j++) cout<<SA[j]<<" ";cout<<endl;
		//for (int j=1;j<=len;j++) cout<<Rank[j]<<" ";cout<<endl;
	}

	for (int i=1;i<=len;i++) if (SA[i]<=len/2) putchar(str[SA[i]+len/2-1]);
	putchar('\n');
	//cout<<"len:"<<len<<endl;
	//for (int i=1;i<=len;i++) cout<<SA[i]<<" ";cout<<endl;
	//for (int i=1;i<=len;i++) cout<<str[i];cout<<endl;
	//for (int i=1;i<=len;i++) if (SA[i]<=len/2) cout<<SA[i]<<" ";cout<<endl;
	return 0;
}
