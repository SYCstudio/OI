#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long

const ll Mod=1000000007;

ll Phi(ll x);
ll Inv(ll a,ll b);
void Exgcd(ll a,ll b,ll &x,ll &y);

int main()
{
    ll inv2=Inv(2,Mod);
    ll n;
    while (scanf("%lld",&n))
    {
		if (n==0) break;
		if (n==1) {printf("0\n");continue;}
        //printf("%lld\n",Phi(n));
		printf("%lld\n",(ll)n*(ll)(n-1ll-Phi(n))%Mod*inv2%Mod);
    }
    return 0;
}

ll Phi(ll x)
{
    if (x==1) return 1;
    ll ret=x;
    for (ll i=2;i*i<=x;i++)
		if (x%i==0)
		{
			ret=ret/i*(i-1);
			while (x%i==0) x=x/i;
		}
    if (x>1) ret=ret/x*(x-1);
    return ret;
}

ll Inv(ll a,ll b)
{
    ll x,y;
    Exgcd(a,b,x,y);
    return (x%b+b)%b;
}

void Exgcd(ll a,ll b,ll &x,ll &y)
{
    if (b==0)
    {
		x=1;y=0;
		return;
    }
    Exgcd(b,a%b,x,y);
    ll tmp=x;
    x=y;y=tmp-a/b*y;
    return;
}
