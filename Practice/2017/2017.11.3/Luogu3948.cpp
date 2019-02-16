#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int maxN=80010;
const int inf=2147483647;

int n,Mod,Min,Max;
ll F[maxN];
ll Ans[maxN];

int main()
{
	freopen("shuju.in","r",stdin);
	freopen("shuju.out","w",stdout);
	int Q;
	scanf("%d%d%d%d%d",&n,&Q,&Mod,&Min,&Max);
	while (Q--)
	{
		char opt;
		cin>>opt;
		if (opt=='A')
		{
			int l,r;
			ll w;
			scanf("%d%d%lld",&l,&r,&w);
			//cout<<l<<" "<<r<<" "<<w<<endl;
			F[l]+=w;
			F[r+1]-=w;
		}
		if (opt=='Q')
		{
			//cout<<opt<<endl;
			int l,r;
			scanf("%d%d",&l,&r);
			ll sum=0;
			int cnt=0;
			for (int i=1;i<=n;i++)
			{
				sum=sum+F[i];
				if ((i>=l)&&(i<=r))
				{
					ll k=sum*i%Mod;
					if ((k>=Min)&&(k<=Max))
						cnt++;
				}
			}
			printf("%d\n",cnt);
		}
	}
	ll sum=0;
	for (int i=1;i<=n;i++)
	{
		sum=sum+F[i];
		ll k=sum*i%Mod;
		Ans[i]=Ans[i-1];
		if ((k>=Min)&&(k<=Max))
			Ans[i]++;
	}
	scanf("%d",&Q);
	while (Q--)
	{
		int l,r;
		scanf("%d%d",&l,&r);
		printf("%lld\n",Ans[r]-Ans[l-1]);
	}
	return 0;
}
