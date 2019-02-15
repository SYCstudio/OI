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

int n,K;
char str[maxN];
int A[maxN],B[maxN],CntA[maxN],CntB[maxN];
int SA[maxN],SSA[maxN],Rank[maxN],Height[maxN],Sum[maxN];
int Cut[maxN];

void GetSA();
bool Check(int rk);

int main()
{
	//while (scanf("%d",&K)!=EOF)
	scanf("%d",&K);
	{
		scanf("%s",str+1);
		n=strlen(str+1);

		GetSA();

		int L=1,R=Sum[n],Ans;
		do
		{
			int mid=(L+R)>>1;
			if (Check(mid)) Ans=mid,R=mid-1;
			else L=mid+1;
		}
		while (L<=R);

		//cout<<"Ans:"<<Ans<<endl;

		int pos=lower_bound(&Sum[1],&Sum[n+1],Ans)-Sum;
		int l=SA[pos],r=n-(Sum[pos]-Ans);

		for (int i=l;i<=r;i++) putchar(str[i]);putchar('\n');
	}

	return 0;
}

void GetSA()
{
	mem(CntA,0);mem(Sum,0);mem(CntB,0);mem(Rank,0);mem(Height,0);
	for (int i=1;i<=n;i++) CntA[str[i]-'a']++;
	for (int i=1;i<=26;i++) CntA[i]+=CntA[i-1];
	for (int i=n;i>=1;i--) SA[CntA[str[i]-'a']--]=i;
	Rank[SA[1]]=1;
	for (int i=2;i<=n;i++){
		Rank[SA[i]]=Rank[SA[i-1]];
		if (str[SA[i]]!=str[SA[i-1]]) Rank[SA[i]]++;
	}

	for (int i=1;Rank[SA[n]]!=n;i<<=1){
		mem(CntA,0);mem(CntB,0);
		for (int j=1;j<=n;j++){
			CntA[A[j]=Rank[j]]++;
			CntB[B[j]=(i+j<=n)?(Rank[i+j]):(0)]++;
		}
		for (int j=1;j<maxN;j++) CntA[j]+=CntA[j-1],CntB[j]+=CntB[j-1];
		for (int j=n;j>=1;j--) SSA[CntB[B[j]]--]=j;
		for (int j=n;j>=1;j--) SA[CntA[A[SSA[j]]]--]=SSA[j];
		Rank[SA[1]]=1;
		for (int j=2;j<=n;j++){
			Rank[SA[j]]=Rank[SA[j-1]];
			if ((A[SA[j]]!=A[SA[j-1]])||(B[SA[j]]!=B[SA[j-1]])) Rank[SA[j]]++;
		}
	}

	for (int i=1,j=0;i<=n;i++)
	{
		while (str[i+j]==str[SA[Rank[i]-1]+j]) j++;
		Height[Rank[i]]=j;
		if (j) j--;
	}

	mem(Sum,0);
	for (int i=1;i<=n;i++) Sum[i]=Sum[i-1]+n-SA[i]-Height[i]+1;

	//for (int i=1;i<=n;i++) cout<<SA[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Rank[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Height[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Sum[i]<<" ";cout<<endl;

	return;
}

bool Check(int rk)
{
	int pos=lower_bound(&Sum[1],&Sum[n+1],rk)-Sum;
	//cout<<"lower_bound:"<<rk<<" "<<pos<<endl;
	int l=SA[pos],r=n-(Sum[pos]-rk),len=r-l+1;
	//cout<<rk<<" "<<l<<" "<<r<<" pos:"<<pos<<endl;
	mem(Cut,-1);

	Cut[l]=len;

	for (int i=pos+1,mn=len;i<=n;i++)
	{
		mn=min(mn,Height[i]);
		if (mn==0) return 0;
		Cut[SA[i]]=mn;
	}

	//for (int i=1;i<=n;i++) cout<<Cut[i]<<" ";cout<<endl;

	int cnt=0;
	for (int i=1,right=n+1;i<=n;i++)
	{
		if (i==right){
			cnt++;right=n+1;
		}
		if (Cut[i]!=-1) right=min(right,i+Cut[i]);
		//cout<<i<<" "<<cnt<<" "<<right<<endl;
	}
	//cout<<"cnt:"<<cnt<<endl;

	return cnt<K;
}
