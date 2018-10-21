#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))

ll a1,b1,c1,d1,a2,b2,c2,d2,a3,b3,c3,d3;
ll k,m,x;

bool C1(ll x);
bool C2(ll x);
bool C3(ll x);
bool C4(ll x);
bool C5(ll x);
bool C6(ll x);

int main(){
	int TTT;scanf("%d",&TTT);
	scanf("%lld%lld%lld%lld%lld",&a1,&b1,&c1,&d1,&k);
	scanf("%lld%lld%lld%lld%lld",&a2,&b2,&c2,&d2,&m);
	scanf("%lld%lld%lld%lld%lld",&a3,&b3,&c3,&d3,&x);
	int Ans=0;
	while (TTT--){
		if (C1(x)||C2(x-m)||C2(x-2*m)||C3(x-2*m)||C3(x-3*m)||C3(x-4*m)||C4(x-2*m)||C5(x-3*m)||C5(x-4*m)||C6(x)) Ans++;
		k=(a1*k%d1*k%d1+b1*k%d1+c1)%d1+20;
		m=(a2*m%d2*m%d2+b2*m%d2+c2)%d2+20;
		x=(a3*x%d3*x%d3+b3*x%d3+c3)%d3+20;
	}
	printf("%d\n",Ans);return 0;
}

bool C1(ll x){
	if ((x-2*k<=2*k+3*k)&&(x-2*k!=2*k+3*k-1)) return 1;
	ll kk=k;
	while ((x-2*kk)%3) kk--;
	if (x-2*kk<=6*k) return 1;
	return 0;
}

bool C2(ll x){
	if (x<=1) return 0;
	if ((x<=2*k+3*k)&&(x!=2*k+3*k-1)) return 1;
	return 0;
}

bool C3(ll x){
	if (x<0) return 0;
	if ((x<=2*k)&&(x%2==0)) return 1;
	return 0;
}

bool C4(ll x){
	if (x<0) return 0;
	if ((x<=2*k+3*k)&&(x!=2*k+3*k-1)) return 1;
	if ((x%3==0)&&(x<=6*k)) return 1;
	return 0;
}

bool C5(ll x){
	if (x<0) return 0;
	if (x<=k) return 1;
	if ((x%2==0)&&(x<=2*k)) return 1;
	if ((x%3==0)&&(x<=3*k)) return 1;
	return 0;
}

bool C6(ll x){
	if ((x==4*m)||(x==5*m)||(x==6*m)) return 1;
	return 0;
}
