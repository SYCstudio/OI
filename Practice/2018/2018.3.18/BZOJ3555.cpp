#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define ll ull
#define ull unsigned long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=30010;
const int maxL=214;
const int base1=254;
const int base2=204;
//const int Mod=1e9+7;
const int inf=2147483647;

int n,L,Alpha;
char str[maxL];
ull Hashpre[maxN][maxL];
ull Hashsuf[maxN][maxL];
ull Get[maxN];

int main()
{
	//cout<<sizeof(Val)<<endl;
	scanf("%d%d%d",&n,&L,&Alpha);
//	Base[0]=1;for (int i=1;i<maxN;i++) Base[i]=(ll)Base[i-1]*(ll)Hashbase%Mod;
	for (int i=1;i<=n;i++)
	{
		//cout<<i<<":"<<endl;
		scanf("%s",str+1);
		for (int j=1;j<=L;j++) Hashpre[i][j]=Hashpre[i][j-1]*149+str[j];
		for (int j=L;j>=1;j--) Hashsuf[i][j]=Hashsuf[i][j+1]*137+str[j];
	}
	/*
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<=L;j++) cout<<Hashpre[i][j]<<" ";cout<<endl;
		for (int j=1;j<=L;j++) cout<<Hashsuf[i][j]<<" ";cout<<endl<<endl;
	}
	//*/
	ll Ans=0;
	for (int i=1;i<=L;i++)
	{
		for (int j=1;j<=n;j++) Get[j]=Hashpre[j][i-1]*233+Hashsuf[j][i+1]*213;
		//for (int j=1;j<=n;j++) cout<<Get[j]<<" ";cout<<endl;
		sort(&Get[1],&Get[n+1]);
		ll sum=1;
		for (int j=2;j<=n;j++)
		{
			if (Get[j]==Get[j-1]){
				Ans=Ans+sum;sum++;
			}
			else sum=1;
		}
	}
	printf("%lld\n",Ans);
	return 0;
}
