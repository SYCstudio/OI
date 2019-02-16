#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1001000;
const int Mod=1e9+7;
const int inf=2147483647;

int n1,n2;
char str1[maxN],str2[maxN];
int F[maxN];
ll Cnt[maxN];

int main()
{
	ios::sync_with_stdio(false);
	int T;cin>>T;
	while (T--)
	{
		cin>>(str1+1)>>(str2+1);
		n1=strlen(str1+1);n2=strlen(str2+1);
		for (int i=1;(i<=n1)&&(i<(n1-i+1));i++) swap(str1[i],str1[n1-i+1]);
		for (int i=1;(i<=n2)&&(i<(n2-i+1));i++) swap(str2[i],str2[n2-i+1]);
		F[0]=-1;F[1]=0;
		for (int i=2;i<=n2;i++)
		{
			int j=F[i-1];
			while ((j!=0)&&(str2[j+1]!=str2[i])) j=F[j];
			if (str2[j+1]==str2[i]) F[i]=j+1;
			else F[i]=0;
		}
		mem(Cnt,0);
		for (int i=1,j=0;i<=n1;i++)
		{
			while ((j!=0)&&(str2[j+1]!=str1[i])) j=F[j];
			if (str2[j+1]==str1[i]) j++,Cnt[j]++;
		}
		for (int i=n2;i>=1;i--) Cnt[F[i]]+=Cnt[i];
		//for (int i=1;i<=n2;i++) cout<<Cnt[i]<<" ";cout<<endl;
		ll Ans=0;
		for (ll i=n2;i>=1;i--) Ans=(Ans+Cnt[i]*i%Mod)%Mod;
		printf("%lld\n",Ans);
	}
	return 0;
}
