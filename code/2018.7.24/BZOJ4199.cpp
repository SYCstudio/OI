#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=301000;
const int inf=2147483647;
const ll INF=1e18;

int n;
char str[maxN];
int Val[maxN];
int A[maxN],B[maxN],CntA[maxN],CntB[maxN];
int SA[maxN],SAA[maxN],Rank[maxN],Height[maxN];
int Q1[maxN],Q2[maxN],Q3[maxN];
int LH[maxN],RH[maxN],Lmx[maxN],Rmx[maxN],Lmn[maxN],Rmn[maxN];
ll Ans1[maxN],Ans2[maxN];
int Cnt[maxN];

int main()
{
	scanf("%d",&n);
	scanf("%s",str+1);
	for (int i=1;i<=n;i++) scanf("%d",&Val[i]);

	for (int i=1;i<=n;i++) CntA[str[i]-'a']++;
	for (int i=1;i<=26;i++) CntA[i]+=CntA[i-1];
	for (int i=n;i>=1;i--) SA[CntA[str[i]-'a']--]=i;
	Rank[SA[1]]=1;
	for (int i=2;i<=n;i++)
	{
		Rank[SA[i]]=Rank[SA[i-1]];
		if (str[SA[i]]!=str[SA[i-1]]) Rank[SA[i]]++;
	}

	//for (int i=1;i<=n;i++) cout<<Rank[i]<<" ";cout<<endl;

	for (int i=1;Rank[SA[n]]!=n;i<<=1)
	{
		mem(CntA,0);mem(CntB,0);mem(SAA,0);
		for (int j=1;j<=n;j++)
		{
			CntA[A[j]=Rank[j]]++;
			CntB[B[j]=((j+i<=n)?(Rank[j+i]):(0))]++;
		}
		for (int j=1;j<maxN;j++) CntA[j]+=CntA[j-1],CntB[j]+=CntB[j-1];
		for (int j=n;j>=1;j--) SAA[CntB[B[j]]--]=j;
		for (int j=n;j>=1;j--) SA[CntA[A[SAA[j]]]--]=SAA[j];

		Rank[SA[1]]=1;
		for (int j=2;j<=n;j++)
		{
			Rank[SA[j]]=Rank[SA[j-1]];
			if ((A[SA[j]]!=A[SA[j-1]])||(B[SA[j]]!=B[SA[j-1]])) Rank[SA[j]]++;
		}
	}

	//for (int i=1;i<=n;i++) cout<<SA[i]<<" ";cout<<endl;
	//for (int i=1;i<=n;i++) cout<<Rank[i]<<" ";cout<<endl;

	for (int i=1,j=0;i<=n;i++)
	{
		if (j) j--;
		while (str[i+j]==str[SA[Rank[i]-1]+j]) j++;
		Height[Rank[i]]=j;
	}

	//cout<<"Height:"<<endl;
	//for (int i=2;i<=n;i++) cout<<Height[i]<<" ";cout<<endl;

	Ans2[0]=-INF;
	for (int i=1;i<=n;i++) Lmn[i]=Rmn[i]=INF,Lmx[i]=Rmx[i]=Ans2[i]=-INF,LH[i]=RH[i]=i;

	int top=0;Q2[0]=Q3[0]=Val[SA[1]];
	for (int i=2;i<=n;i++)
	{
		while ((top)&&(Height[Q1[top]]>=Height[i])){
			Q2[top-1]=max(Q2[top-1],Q2[top]);Q3[top-1]=min(Q3[top-1],Q3[top]);
			top--;
		}
		Lmx[i]=Q2[top];Lmn[i]=Q3[top];LH[i]=max(1,Q1[top]);
		top++;Q1[top]=i;Q2[top]=Q3[top]=Val[SA[i]];
	}

	top=0;
	Q1[0]=n+1;Q2[0]=Q3[0]=Val[SA[n]];
	for (int i=n;i>=2;i--)
	{
		while ((top)&&(Height[Q1[top]]>Height[i])){
			Q2[top-1]=max(Q2[top-1],Q2[top]);Q3[top-1]=min(Q3[top-1],Q3[top]);
			top--;
		}
		Rmx[i]=max(Q2[top],Val[SA[i]]);Rmn[i]=min(Q3[top],Val[SA[i]]);RH[i]=Q1[top]-1;
		top++;Q1[top]=i;Q2[top]=Q3[top]=Val[SA[i-1]];
	}

	/*
	for (int i=2;i<=n;i++) cout<<LH[i]<<" ";cout<<endl;
	for (int i=2;i<=n;i++) cout<<RH[i]<<" ";cout<<endl;
	for (int i=2;i<=n;i++) cout<<Lmx[i]<<" ";cout<<endl;
	for (int i=2;i<=n;i++) cout<<Lmn[i]<<" ";cout<<endl;
	for (int i=2;i<=n;i++) cout<<Rmx[i]<<" ";cout<<endl;
	for (int i=2;i<=n;i++) cout<<Rmn[i]<<" ";cout<<endl;
	//*/

	for (int i=2;i<=n;i++){
		Ans1[Height[i]]+=1ll*(i-LH[i])*(RH[i]-i+1);
		Ans2[Height[i]]=max(Ans2[Height[i]],1ll*Lmx[i]*Rmx[i]);
		Ans2[Height[i]]=max(Ans2[Height[i]],1ll*Lmn[i]*Rmn[i]);
		Ans2[Height[i]]=max(Ans2[Height[i]],1ll*Lmx[i]*Rmn[i]);
		Ans2[Height[i]]=max(Ans2[Height[i]],1ll*Lmn[i]*Rmx[i]);
	}

	//for (int i=0;i<n;i++) cout<<Ans1[i]<<" ";cout<<endl;
	//for (int i=0;i<n;i++) cout<<Ans2[i]<<" ";cout<<endl;

	for (int i=n-1;i>=0;i--) Ans1[i]+=Ans1[i+1],Ans2[i]=max(Ans2[i],Ans2[i+1]);

	for (int i=0;i<n;i++)
		if (Ans1[i]!=0) printf("%lld %lld\n",Ans1[i],Ans2[i]);
		else printf("0 0\n");

	/*
	for (int l=1;l<=n;l++)
	{
		int mn=inf;
		for (int r=l+1;r<=n;r++)
		{
			mn=min(mn,Height[r]);
			Cnt[mn]++;
			if (mn==1) cout<<"("<<l<<","<<r<<")"<<endl;
		}
	}

	for (int i=0;i<n;i++) cout<<Cnt[i]<<" ";cout<<endl;
	//*/

	return 0;
}
