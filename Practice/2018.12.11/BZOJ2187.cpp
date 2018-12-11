#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

const int inf=2147483647;

void Calc(ll a,ll b,ll c,ll d,ll &p,ll &q);

int main(){
	ll a,b,c,d,p,q;
	while (scanf("%lld%lld%lld%lld",&a,&b,&c,&d)!=EOF){
		Calc(a,b,c,d,p,q);
		printf("%lld/%lld\n",p,q);
	}
	return 0;
}

void Calc(ll a,ll b,ll c,ll d,ll &p,ll &q){
	//cout<<a<<" "<<b<<" "<<c<<" "<<d<<endl;
	if ((ll)(a/b)+1<=((ll)(c+d-1)/d)-1) p=(ll)(a/b)+1,q=1;
	else if (a==0) p=1,q=d/c+1;
	else if ((a<=b)&&(c<=d)) Calc(d,c,b,a,q,p);
	else Calc(a%b,b,c-(ll)(a/b)*d,d,p,q),p+=(ll)(a/b)*q;
}
/*
1 3 1 2
2 1 3 1
2 1 4 1
1000 1001 1001 1002
//*/
