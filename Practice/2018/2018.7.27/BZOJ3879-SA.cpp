#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=505000;
const int maxBit=20;
const ll Mod=23333333333333333;
const int inf=2147483647;

int n,m;
char str[maxN];
int A[maxN],B[maxN],CntA[maxN],CntB[maxN];
int SA[maxN],SSA[maxN],Rank[maxN],Height[maxBit][maxN];
int Seq[maxN],Log2[maxN],Ht[maxN],L[maxN],R[maxN],Q[maxN];

int LCP(int p1,int p2);

int main()
{
	for (int i=1;i<maxN;i++) Log2[i]=log2(i);
	scanf("%d%d",&n,&m);
	scanf("%s",str+1);
	
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
	for (int i=1,j=0;i<=n;i++){
		while (str[i+j]==str[SA[Rank[i]-1]+j]) j++;
		Height[0][Rank[i]]=j;
		if (j) j--;
	}

	//for (int i=1;i<=n;i++) cout<<Rank[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<SA[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Height[0][i]<<" ";cout<<endl;

	for (int i=1;i<maxBit;i++)
		for (int j=1;j+(1<<(i-1))<=n;j++)
			Height[i][j]=min(Height[i-1][j],Height[i-1][j+(1<<(i-1))]);

	while (m--){
		int cnt;scanf("%d",&cnt);
		for (int i=1;i<=cnt;i++){
			int p;scanf("%d",&p);Seq[i]=Rank[p];
		}
		sort(&Seq[1],&Seq[cnt+1]);cnt=unique(&Seq[1],&Seq[cnt+1])-Seq-1;
		for (int i=1;i<cnt;i++) Ht[i]=LCP(Seq[i],Seq[i+1]);

		//for (int i=1;i<=cnt;i++) cout<<Seq[i]<<" ";cout<<endl;
		//for (int i=1;i<cnt;i++) cout<<Ht[i]<<" ";cout<<endl;
		
		int top=0;Q[0]=0;
		for (int i=1;i<cnt;i++){
			while ((top)&&(Ht[Q[top]]>=Ht[i])) top--;
			L[i]=Q[top]+1;Q[++top]=i;
		}
		top=0;Q[0]=cnt;
		for (int i=cnt-1;i>=1;i--){
			while ((top)&&(Ht[Q[top]]>Ht[i])) top--;
			R[i]=Q[top];Q[++top]=i;
		}

		//for (int i=1;i<cnt;i++) cout<<L[i]<<" ";cout<<endl;
		//for (int i=1;i<cnt;i++) cout<<R[i]<<" ";cout<<endl;

		ll Ans=0;
		for (int i=1;i<cnt;i++) Ans=(Ans+1ll*Ht[i]*(i-L[i]+1)%Mod*(R[i]-i)%Mod)%Mod;

		printf("%lld\n",Ans);
	}
	return 0;
}

int LCP(int p1,int p2){
	if (p1>p2) swap(p1,p2);
	int len=p2-p1;
	int lg=Log2[len];
	return min(Height[lg][p1+1],Height[lg][p2-(1<<lg)+1]);
}
/*
7 3
popoqqq
1 4
2 3 5
4 1 2 5 6

9 5
aabbabaaa
4 1 4 5 7
3 7 8 9
3 3 4 6
3 2 5 7
9 1 2 3 4 5 6 7 8 9
//*/
