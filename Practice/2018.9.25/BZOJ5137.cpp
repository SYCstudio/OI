#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=402000;
const int maxBit=20;
const int inf=2147483647;

int n,L=0;
char Input[maxN];
int str[maxN];
int Belong[maxN],Len[maxN],St[maxN],lst[maxN];
int CntA[maxN],CntB[maxN],A[maxN],B[maxN];
int SSA[maxN],SA[maxN],Rank[maxN],Height[maxN];
int Ans[maxN];

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		scanf("%s",Input+1);
		int len=strlen(Input+1);
		for (int j=1;j<=len;j++)
			str[++L]=Input[j]-'a'+1,Belong[L]=i,Len[L]=len-j+1;
		if (i!=n) str[++L]='z'-'a'+1+i;
	}

	for (int i=1;i<=L;i++) CntA[str[i]]++;
	for (int i=1;i<maxN;i++) CntA[i]+=CntA[i-1];
	for (int i=L;i>=1;i--) SA[CntA[str[i]]--]=i;
	Rank[SA[1]]=1;
	for (int i=2;i<=L;i++){
		Rank[SA[i]]=Rank[SA[i-1]];
		if (str[SA[i]]!=str[SA[i-1]]) Rank[SA[i]]++; 
	}
	//for (int i=1;i<=L;i++) cout<<(int)(str[i])<<" ";cout<<endl;
	//for (int i=1;i<=L;i++) cout<<Rank[i]<<" ";cout<<endl;
	for (int i=1;Rank[SA[L]]!=L;i<<=1){
		mem(CntA,0);mem(CntB,0);
		for (int j=1;j<=L;j++){
			CntA[A[j]=Rank[j]]++;
			CntB[B[j]=((j+i<=L)?(Rank[j+i]):(0))]++;
		}
		for (int j=1;j<maxN;j++) CntA[j]+=CntA[j-1],CntB[j]+=CntB[j-1];
		for (int j=L;j>=1;j--) SSA[CntB[B[j]]--]=j;
		for (int j=L;j>=1;j--) SA[CntA[A[SSA[j]]]--]=SSA[j];
		Rank[SA[1]]=1;
		for (int j=2;j<=L;j++){
			Rank[SA[j]]=Rank[SA[j-1]];
			if ((A[SA[j]]!=A[SA[j-1]])||(B[SA[j]]!=B[SA[j-1]])) Rank[SA[j]]++;
		}
		//for (int j=1;j<=L;j++) cout<<Rank[j]<<" ";cout<<endl;
		//for (int j=1;j<=L;j++) cout<<"("<<A[j]<<","<<B[j]<<") ";cout<<endl;
	}

	//for (int i=1;i<=L;i++) cout<<SA[i]<<" ";cout<<endl;
	//for (int i=1;i<=L;i++) cout<<Rank[i]<<" ";cout<<endl;

	for (int i=1,j=0;i<=L;i++){
		while (str[i+j]==str[SA[Rank[i]-1]+j]) j++;
		Height[Rank[i]]=j;
		if (j) j--;
	}
	/*
	for (int i=L;i<=L;i++){
		cout<<Height[i]<<" "<<Len[SA[i]]<<" ";
		for (int j=SA[i];j<=L;j++) cout<<(int)(str[j])<<" ";
		cout<<endl;
	}
	//*/

	//cerr<<L<<endl;
	//for (int i=1;i<=L;i++) cout<<Height[i]<<" ";cout<<endl;

	for (int i=1,mn=0;i<=L;i++){
		if (Belong[SA[i]]==0) break;
		mn=min(mn,Height[i]);
		int a=Belong[SA[i-1]],b=Belong[SA[i]];
		if (a!=b){
			Ans[a]=Ans[a]-Height[i]+mn;
			Ans[b]=Ans[b]-Height[i]+Len[SA[i]];mn=Height[i];
		}
		else Ans[b]=Ans[b]+Len[SA[i]]-Height[i];
	}

	for (int i=1;i<=n;i++) printf("%d\n",Ans[i]);return 0;
}
