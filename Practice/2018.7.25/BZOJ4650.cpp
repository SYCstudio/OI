#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=30100;
const int maxBit=15;
const int inf=2147483647;

int Log2[maxN];

class SA
{
public:
	int len;
	char str[maxN];
	int A[maxN],B[maxN],CntA[maxN],CntB[maxN];
	int SA[maxN],SSA[maxN],Rank[maxN],Height[maxBit][maxN];

	void Init(){
		mem(str,'\0');mem(A,0);mem(B,0);mem(CntA,0);mem(CntB,0);
		mem(SA,0);mem(SSA,0);mem(Rank,0);mem(Height,0);
		return;
	}

	void GetSA(){
		for (int i=1;i<=len;i++) CntA[str[i]-'a']++;
		for (int i=1;i<=26;i++) CntA[i]+=CntA[i-1];
		for (int i=len;i>=1;i--) SA[CntA[str[i]-'a']--]=i;
		Rank[SA[1]]=1;
		for (int i=2;i<=len;i++)
		{
			Rank[SA[i]]=Rank[SA[i-1]];
			if (str[SA[i]]!=str[SA[i-1]]) Rank[SA[i]]++;
		}

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
		}

		for (int i=1,j=0;i<=len;i++)
		{
			while (str[i+j]==str[SA[Rank[i]-1]+j]) j++;
			Height[0][Rank[i]]=j;
			if (j) j--;
		}

		for (int i=1;i<maxBit;i++)
			for (int j=1;j+(1<<(i-1))<=len;j++)
				Height[i][j]=min(Height[i-1][j],Height[i-1][j+(1<<(i-1))]);

		//for (int i=1;i<=len;i++) cout<<SA[i]<<" ";cout<<endl;

		return;
	}

	int LCP(int l,int r){
		l=Rank[l];r=Rank[r];
		if (l>r) swap(l,r);
		int lg=Log2[r-l];
		return min(Height[lg][l+1],Height[lg][r-(1<<lg)+1]);
	}
};

SA A,B;
int F[maxN],G[maxN];

int main()
{
	for (int i=1;i<maxN;i++) Log2[i]=log2(i);
	int TTT;scanf("%d",&TTT);
	while (TTT--)
	{
		A.Init();B.Init();mem(F,0);mem(G,0);
		scanf("%s",A.str+1);
		int len=strlen(A.str+1);
		A.len=B.len=len;
		for (int i=1,j=len;i<=A.len;i++,j--) B.str[j]=A.str[i];

		A.GetSA();B.GetSA();

		for (int i=1;i+i<=len;i++)
			for (int j=i+i;j<=len;j+=i)
				if (A.str[j-i]==A.str[j])
				{
					int lcp=min(A.LCP(j-i,j),i),lcs=min(B.LCP(len-(j-i)+2,len-j+2),i-1);
					int k=lcp+lcs+1-i;
					if (lcp+lcs>=i)
					{
						F[j+lcp-k]++;F[j+lcp]--;
						G[j-i-lcs]++;G[j-i-lcs+k]--;
					}
				}
		for (int i=1;i<=len;i++) F[i]+=F[i-1],G[i]+=G[i-1];

		//for (int i=1;i<=len;i++) cout<<F[i]<<" ";cout<<endl;
		//for (int i=1;i<=len;i++) cout<<G[i]<<" ";cout<<endl;

		ll Ans=0;
		for (int i=1;i<len;i++) Ans=Ans+1ll*F[i]*G[i+1];

		printf("%lld\n",Ans);
	}
	return 0;
}
