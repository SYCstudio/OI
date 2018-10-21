#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define ld long double
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=20;
const int maxM=5010000;
const int inf=2147483647;

int n,s1,s2,K,mid;
ll Prime[maxN];
ll Seq1[maxM],Seq2[maxM];

void dfs1(int u,ll sum);
void dfs2(int u,ll sum);
ll Calc(ll limit);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld",&Prime[i]);
	sort(&Prime[1],&Prime[n+1]);

	mid=n/3;

	//Seq1[++s1]=1;
	dfs1(1,1);dfs2(mid+1,1);
	//cout<<s1<<" "<<s2<<endl;
	sort(&Seq1[1],&Seq1[s1+1]);sort(&Seq2[1],&Seq2[s2+1]);
	//for (int i=1;i<=s1;i++) cout<<Seq1[i]<<" ";cout<<endl;
	//for (int i=1;i<=s2;i++) cout<<Seq2[i]<<" ";cout<<endl;
	scanf("%d",&K);

	ll L=1,R=1e18,Ans=0;
	do{
		ll mid=(L+R)>>1;
		if (Calc(mid)>=K) Ans=mid,R=mid-1;
		else L=mid+1;
	}
	while (L<=R);
	
	printf("%lld\n",Ans);return 0;
}

void dfs1(int u,ll sum){
	if (sum!=1) Seq1[++s1]=sum;
	for (int i=u;i<=mid;i++)
		if ((ld)sum*Prime[i]<=1e18)
			dfs1(i,sum*Prime[i]);
	return;
}

void dfs2(int u,ll sum){
	if (sum!=1) Seq2[++s2]=sum;
	for (int i=u;i<=n;i++)
		if ((ld)sum*Prime[i]<=1e18)
			dfs2(i,sum*Prime[i]);
	return;
}

ll Calc(ll limit){
	ll r=s2,l=0;
	while (Seq2[r]>limit) r--;
	ll ret=r+1;
	//cout<<"calc:"<<limit<<" nowret:"<<ret<<endl;
	for (int i=1;(i<=s1)&&(Seq1[i]<=limit);i++){
		while (((ld)Seq1[i]*(ld)Seq2[r])>limit) r--;
		ret=ret+r+1;
		//if (r==0) break;
		//cout<<i<<" "<<r<<" "<<ret<<endl;
	}
	//cout<<limit<<" "<<ret<<endl;
	return ret;
}
/*
2
41 61
66

16
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53
755104793
//*/
