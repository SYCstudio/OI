#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

ll Calc(ll mx,ll a,ll b,ll L);

int main(){
	ll a,b,c,L;scanf("%lld%lld%lld%lld",&a,&b,&c,&L);
	ll Ans=(L+3)*(L+2)*(L+1)/6;
	Ans=Ans-Calc(a,b,c,L)-Calc(b,a,c,L)-Calc(c,a,b,L);
	printf("%lld\n",Ans);return 0;
}

ll Calc(ll mx,ll a,ll b,ll L){
	ll ret=0,k;
	for (int l0=0;l0<=L;l0++)
		if (mx+l0-a-b>=0)
			k=min(mx+l0-a-b,L-l0),ret=ret+(k+2)*(k+1)/2;
			//cout<<l0<<" "<<(k+2)*(k+1)/2<<endl;
	return ret;
}
