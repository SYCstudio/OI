#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define RG register

const int maxN=1000100;
const int Mod=1e9+7;
const int inf=2147483647;

int n;
char str[maxN];
int Next[maxN];
int Cnt[maxN];

int main()
{
	ios::sync_with_stdio(false);
	RG int T;cin>>T;
	while (T--)
	{
		cin>>(str+1);n=strlen(str+1);
		Cnt[1]=1;
		RG int pos=0;
		RG ll Ans=1;
		for (RG int i=2;i<=n;i++)
		{
			RG int j=Next[i-1];
			while ((j!=0)&&(str[j+1]!=str[i])) j=Next[j];
			if (str[j+1]==str[i]) Next[i]=j+1;
			else Next[i]=0;
			Cnt[i]=Cnt[Next[i]]+1;
			while ((pos!=0)&&(str[pos+1]!=str[i])) pos=Next[pos];
			if (str[pos+1]==str[i]) pos++;
			while (pos*2>i) pos=Next[pos];
			Ans=Ans*(ll)(Cnt[pos]+1)%Mod;
		}
		printf("%lld\n",Ans);
	}
	return 0;
}
