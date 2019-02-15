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
const ll INF=1e18;

int n;
ll Seq[maxN],F[maxN],G[maxN];
ll L[maxN],R[maxN];

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld",&Seq[i]);
	for (int i=2;i<=n;i++) F[i]=F[i-1]+max(0ll,Seq[i-1]-Seq[i]+1);
	for (int i=n-1;i>=1;i--) G[i]=G[i+1]+max(0ll,Seq[i+1]-Seq[i]+1);
	for (int i=3,p=2;i<=n-2;i++){
		while ((p+1<i)&&(max(F[p],G[p]-G[i])>=max(F[p+1],G[p+1]-G[i]))) p++;
		L[i]=max(F[p],G[p]-G[i]);
	}
	for (int i=n-2,p=n-1;i>=3;i--){
		while ((p-1>i)&&(max(G[p],F[p]-F[i])>=max(G[p-1],F[p-1]-F[i]))) p--;
		R[i]=max(G[p],F[p]-F[i]);
	}
	ll Ans=INF;
	for (int i=3;i<=n-2;i++) Ans=min(Ans,L[i]+R[i]);
	printf("%lld\n",Ans);return 0;
}
/*
5
2 1 2 2 3
//*/
