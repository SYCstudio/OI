#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

ll Calc(ll a,ll b,ll c,ll L);

int main(){
	ll a,b,c,L;
	scanf("%lld%lld%lld%lld",&a,&b,&c,&L);
	printf("%lld\n",Calc(a,b,c,L)+Calc(b,a,c,L)+Calc(c,a,b,L));
	return 0;
}

ll Calc(ll a,ll b,ll c,ll L){
	if (b>a) L-=(b-a),a=b;
	if (c>a) L-=(c-a),a=c;
	if (L<0) return 0;
	ll ret=0;
	for (int l0=0;l0<=L;l0++){
		ll k=min(L-l0,a+l0-b-c);
		ret=ret+(L-l0+2)*(L-l0+1)/2;
		if (k<0) continue;
		ret=ret-(k+2)*(k+1)/2;
	}
	cout<<a<<" "<<b<<" "<<c<<" "<<L<<":"<<ret<<endl;
	return ret;
}
