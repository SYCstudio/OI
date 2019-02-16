#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=1010000;
const int Mod=19930726;
const int inf=2147483647;

int len;
ll K;
char str[maxN];
int P[maxN];
ll Num[maxN];

ll Calc(int limit);
ll QPow(ll x,ll cnt);

int main()
{
	scanf("%d%lld",&len,&K);
	scanf("%s",str+1);

	//for (int i=len;i>=1;i--) str[2*i]=str[i],str[2*i-1]='#';
	//str[0]='@';str[1]='#';str[2*len+1]='#';
	str[0]='@';

	int mx=0,pos=0;
	for (int i=1;i<=len;i++)
	{
		if (i<mx) P[i]=min(P[pos*2-i],mx-i);
		else P[i]=1;
		while (str[i+P[i]]==str[i-P[i]]) P[i]++;
		if (i+P[i]>mx){
			mx=i+P[i];pos=i;
		}
	}

	//for (int i=1;i<=len;i++) cout<<str[i]<<" ";cout<<endl;
	//for (int i=1;i<=len;i++) cout<<P[i]<<" ";cout<<endl;

	for (int i=1;i<=len;i++) P[i]=P[i]*2-1;

	int L=0,R=0;
	for (int i=1;i<=len;i++) R=max(R,P[i]);

	int tot=-1;
	do
	{
		int mid=(L+R)>>1;
		if (Calc(mid)>=K) L=mid+1,tot=mid;
		else R=mid-1;
	}
	while (L<=R);

	if (tot==-1) printf("%d\n",tot);
	else 
	{
		ll Ans=1,cnt=0;
		Num[tot+2]=tot+2;
		for (int i=tot+4;i<maxN;i+=2)
			Num[i]=1ll*Num[i-2]*i%Mod;
		for (int i=1;i<=len;i++)
			if (P[i]>=tot+2){
				Ans=1ll*Num[P[i]]*Ans%Mod;
				cnt=cnt+1ll*(P[i]-(tot+2))/2+1;
			}
		Ans=1ll*Ans*QPow(tot,K-cnt)%Mod;
		printf("%lld\n",Ans);
	}
	return 0;
}

ll Calc(int limit)
{
	if ((limit&1)==0) limit++;
	ll ret=0;
	for (int i=1;i<=len;i++)
		if (P[i]>=limit) ret+=1ll*(P[i]-limit)/2+1;
	return ret;
}

ll QPow(ll x,ll cnt){
	ll ret=1;
	while (cnt){
		if (cnt&1) ret=ret*x%Mod;
		x=x*x%Mod;cnt>>=1;
	}
	return ret;
}
