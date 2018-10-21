#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
 
#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define sqr(x) (((ll)x)*((ll)x))
 
const int maxN=50010;
const int inf=2147483647;
 
class Data
{
public:
    int l,r,id;
    ll A,B;
};
 
int n,m,size;
ll Ans=0;
int Belong[maxN],Color[maxN],Sum[maxN];
Data Q[maxN];
 
bool cmp1(Data A,Data B);
bool cmp2(Data A,Data B);
void Move(ll pos,ll opt);
ll gcd(ll a,ll b);
 
int main()
{
    scanf("%d%d",&n,&m);size=sqrt(n);
    for (int i=1;i<=n;i++) scanf("%d",&Color[i]),Belong[i]=(i-1)/size+1;
    for (int i=1;i<=m;i++) scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].id=i;
    sort(&Q[1],&Q[m+1],cmp1);
    int l=1,r=0;
    for (int i=1;i<=m;i++)
    {
        while (l<Q[i].l) Move(l,-1),l++;
        while (l>Q[i].l) Move(l-1,1),l--;
        while (r<Q[i].r) Move(r+1,1),r++;
        while (r>Q[i].r) Move(r,-1),r--;
        Q[i].A=(ll)Ans-(ll)(Q[i].r-Q[i].l+1);
        Q[i].B=(ll)(Q[i].r-Q[i].l+1)*(ll)(Q[i].r-Q[i].l);
    }
    sort(&Q[1],&Q[m+1],cmp2);
    for (int i=1;i<=m;i++)
        if (Q[i].A==0) printf("0/1\n");
        else
        {
            ll g=gcd(Q[i].A,Q[i].B);
            printf("%lld/%lld\n",Q[i].A/g,Q[i].B/g);
        }
    return 0;
}
 
bool cmp1(Data A,Data B)
{
    if (Belong[A.l]==Belong[B.l]) return A.r<B.r;
    else return A.l<B.l;
}
 
bool cmp2(Data A,Data B)
{
    return A.id<B.id;
}
 
void Move(ll pos,ll opt)
{
    Ans-=sqr(Sum[Color[pos]]);
    Sum[Color[pos]]+=opt;
    Ans+=sqr(Sum[Color[pos]]);
}
 
ll gcd(ll a,ll b)
{
    ll tmp;
    while (b) tmp=a,a=b,b=tmp%b;
    return a;
}
