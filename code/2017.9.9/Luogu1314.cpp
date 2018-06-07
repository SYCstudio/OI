#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long

const int maxN=300000;
const int inf=2147483647;

ll n,m,S;
ll Ans=1e13;
ll Weight[maxN];
ll Value[maxN];
ll Rangel[maxN];
ll Ranger[maxN];
ll Sum[maxN];
ll Cnt[maxN];

ll read();
bool Solve(ll nowW);

int main()
{
    n=read();
    m=read();
    S=read();
    ll l=0,r=0;
    for (int i=1;i<=n;i++)
    {
	Weight[i]=read();
	Value[i]=read();
	r=max(r,Weight[i]);
    }
    for (int i=1;i<=m;i++)
    {
	Rangel[i]=read();
	Ranger[i]=read();
    }
    r=r+100;
    while (l<=r)
    {
	//cout<<l<<" "<<r<<endl;
	ll mid=(l+r)>>1;
	if (Solve(mid))
	    l=mid+1;
	else
	    r=mid-1;
	//cout<<l<<" "<<r<<endl;
    }
    cout<<Ans<<endl;
    return 0;
}

ll read()
{
    ll x=0;
    char ch=getchar();
    while ((ch<'0')||(ch>'9'))
	ch=getchar();
    while ((ch>='0')&&(ch<='9'))
    {
	x=x*10+ch-48;
	ch=getchar();
    }
    return x;
}

bool Solve(ll nowW)
{
    Sum[0]=0;
    Cnt[0]=0;
    for (int i=1;i<=n;i++)
    {
	Sum[i]=Sum[i-1]+((Weight[i]>=nowW)?(Value[i]):0);
	Cnt[i]=Cnt[i-1]+((Weight[i]>=nowW)?1:0);
    }
    /*
      cout<<nowW<<endl;
      for (int i=1;i<=n;i++)
      cout<<Sum[i]<<" ";
      cout<<endl;
      for (int i=1;i<=n;i++)
      cout<<Cnt[i]<<" ";
      cout<<endl<<endl;
    //*/
    ll tot=0;
    for (int i=1;i<=m;i++)
	tot+=(Sum[Ranger[i]]-Sum[Rangel[i]-1])*(Cnt[Ranger[i]]-Cnt[Rangel[i]-1]);
    Ans=min(Ans,abs(tot-S));
    if (tot>=S)
	return 1;
    return 0;
}
