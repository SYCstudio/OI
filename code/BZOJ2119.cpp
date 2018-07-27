#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=50100*2;
const int maxBit=21;
const int inf=2147483647;

int n,K,S[maxN];
int Log2[maxN],Appr[maxN];

class SA
{
public:
	int Num[maxN];
	int A[maxN],B[maxN],CntA[maxN],CntB[maxN];
	int SA[maxN],SSA[maxN],Rank[maxN],Height[maxBit][maxN];

	void GetSA(){
		for (int i=1;i<=n;i++) CntA[Num[i]]++;
		for (int i=1;i<maxN;i++) CntA[i]+=CntA[i-1];
		for (int i=n;i>=1;i--) SA[CntA[Num[i]]--]=i;
		Rank[SA[1]]=1;
		for (int i=2;i<=n;i++){
			Rank[SA[i]]=Rank[SA[i-1]];
			if (Num[SA[i]]!=Num[SA[i-1]]) Rank[SA[i]]++;
		}
		for (int i=1;Rank[SA[n]]!=n;i<<=1){
			mem(CntA,0);mem(CntB,0);
			for (int j=1;j<=n;j++){
				CntA[A[j]=Rank[j]]++;
				CntB[B[j]=((i+j<=n)?(Rank[i+j]):(0))]++;
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

		for (int i=1,j=0;i<=n;i++){
			while (Num[i+j]==Num[SA[Rank[i]-1]+j]) j++;
			Height[0][Rank[i]]=j;
			if (j) j--;
		}

		for (int i=1;i<maxBit;i++)
			for (int j=1;j+(1<<(i-1))<=n;j++)
				Height[i][j]=min(Height[i-1][j],Height[i-1][j+(1<<(i-1))]);

		//for (int i=1;i<=n;i++) cout<<Num[i]<<" ";cout<<endl;
		//for (int i=1;i<=n;i++) cout<<Rank[i]<<" ";cout<<endl;
		//for (int i=1;i<=n;i++) cout<<SA[i]<<" ";cout<<endl;
		//for (int i=1;i<=n;i++) cout<<Height[0][i]<<" ";cout<<endl<<endl;
		return;
	}

	int LCP(int p1,int p2){
		if ((p1<0)||(p1>n)||(p2<0)||(p2>n)) return 0;
		//cout<<"GetLCP:"<<p1<<" "<<p2<<endl;
		p1=Rank[p1];p2=Rank[p2];
		if (p1>p2) swap(p1,p2);
		//cout<<p1<<" "<<p2<<endl;
		int lg=Log2[p2-p1];
		return min(Height[lg][p1+1],Height[lg][p2-(1<<lg)+1]);
	}
};

SA A,B;

int main()
{
	for (int i=1;i<maxN;i++) Log2[i]=log2(i);
	
	scanf("%d%d",&n,&K);
	for (int i=1;i<=n;i++) scanf("%d",&S[i]);
	for (int i=1;i<n;i++) S[i]=S[i+1]-S[i];
	n--;
	for (int i=1;i<=n;i++) Appr[i]=S[i];
	sort(&Appr[1],&Appr[n+1]);int numcnt=unique(&Appr[1],&Appr[n+1])-Appr-1;
	for (int i=1;i<=n;i++) S[i]=lower_bound(&Appr[1],&Appr[numcnt+1],S[i])-Appr;
	for (int i=1;i<=n;i++) A.Num[i]=S[i],B.Num[n-i+1]=S[i];

	A.GetSA();B.GetSA();

	ll Ans=0;
	for (int len=1;len<=n;len++)
		for (int i=len;i<=n;i+=len){
			int j=i+len+K;
			if (j>n) continue;
			int a=A.LCP(i,j),b=B.LCP(n-i+2,n-j+2);
			//cout<<len<<" ("<<i<<","<<j<<") "<<a<<" "<<b<<" - ";
			a=min(a,len);b=min(b,len-1);
			Ans=Ans+max(0,a+b-len+1);//cout<<a+b-len+1<<endl;
		}

	printf("%lld\n",Ans);
	return 0;
}

/*
12 4
1 2 3 4 8 9 1 2 3 4 8 9
//*/
