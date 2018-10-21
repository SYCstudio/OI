#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int maxN=202000;
const int maxM=202000;
const int inf=2147483647;

ll n,m,T;
ll P[maxN];

bool Check(ll limit);
ll Calc(ll limit);

int main(){
	int Case;cin>>Case;
	while (Case--){
		cin>>n>>m>>T;
		for (int i=1;i<=n;i++) cin>>P[i];
		ll l=1,r=T;
		do{
			ll mid=(l+r+1)>>1;
			if (Check(mid)) l=mid;
			else r=mid-1;
		}
		while (l<r);
		if ((l+1<=T)&&(Calc(l+1)>Calc(l))) l++;
		cout<<Calc(l)<<" "<<l<<endl;
	}
	return 0;
}

ll Calc(ll limit){
	ll sum=0,ret=0,tot=0,tim=0;
	for (ll i=1;i<=n;i++)
		if (P[i]<=limit){
			ret++;tot++;sum+=P[i];tim+=P[i];
			if (tim>T) return ret-1;
			if (tot==m) tim+=sum,sum=tot=0;
		}
	return ret;
}

bool Check(ll limit){
	ll sum=0,ret=0,tot=0,tim=0;
	for (ll i=1;i<=n;i++)
		if (P[i]<=limit){
			ret++;tot++;tim+=P[i];sum+=P[i];
			if (tim>T) return 0;
			if (tot==m) tim+=sum,sum=tot=0;
		}
	return 1;
}
