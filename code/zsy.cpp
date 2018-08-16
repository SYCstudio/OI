// luogu-judger-enable-o2
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<set>
#include<iostream>
using namespace std;
#define ll long long

int Case;
ll gi(){
    ll x=0,w=1;char ch=getchar();
    while ((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if (ch=='-') w=0,ch=getchar();
    while (ch>='0'&&ch<='9') x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
    return w?x:-x;
}
const int N = 1e5+5;
int n,cnt;
ll a[N],p[N],gain[N],atk[N];
multiset<ll>S;
ll mul(ll a,ll b,ll p){
    ll res=0;
    while (b){
        if (b&1) res=(res+a)%p;
        a=(a+a)%p;
        b>>=1;
    }
    return res;
}
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll exgcd(ll a,ll b,ll &x,ll &y){
    if (!b) {x=1;y=0;return a;}
    ll d=exgcd(b,a%b,y,x);y-=a/b*x;return d;
}
ll work(){
    n=gi();cnt=gi();S.clear();ll lim=0;
    for (int i=1;i<=n;++i) a[i]=gi();
    for (int i=1;i<=n;++i) p[i]=gi();
    for (int i=1;i<=n;++i) gain[i]=gi();
    for (int i=1;i<=cnt;++i) {
        ll ak=gi();S.insert(ak);
    }
    for (int i=1;i<=n;++i){
        if (*S.begin()>=a[i]) atk[i]=*S.begin();
        else if (S.find(a[i])!=S.end()) atk[i]=a[i];
        else{
            S.insert(a[i]);
            multiset<ll>::iterator it=S.find(a[i]);
            --it;atk[i]=*it;S.erase(S.find(a[i]));
        }
		//if (Case==0) cout<<atk[i]<<endl;
        S.erase(S.find(atk[i]));
        S.insert(gain[i]);
    }
    for (int i=1;i<=n;++i){
        lim=max(lim,(a[i]+atk[i]-1)/atk[i]);
        ll d=gcd(atk[i],p[i]);
        if (a[i]%d) return -1;
        atk[i]/=d;p[i]/=d;a[i]/=d;

        ll x,y;
        exgcd(atk[i],p[i],x,y);x=(x%p[i]+p[i])%p[i];
        a[i]=mul(x,a[i],p[i]);atk[i]=1;
        
    }

	if (Case==0) for (int i=1;i<=n;i++) cout<<a[i]<<" "<<p[i]<<endl;
	
    for (int i=2;i<=n;++i){
        ll x,y,P=p[1]/gcd(p[1],p[i])*p[i];
        ll d=exgcd(p[1],p[i],x,y),k=((a[i]-a[1])%P+P)%P;
        if (k%d) return -1;
        x=(x%p[i]+p[i])%p[i];x=mul(x,k/d,p[i]);

        a[1]+=mul(p[1],x,P);a[1]=(a[1]+P)%P;p[1]=P;

    }
    
    ll x,y;ll ans=a[1];
    if (ans<lim) ans=ans+(lim-ans+p[1]-1)/p[1];
    return ans;
}
int main(){
	freopen("dragon2.in","r",stdin);freopen("zsy.out","w",stdout);
    Case=gi();
    while (Case--) printf("%lld\n",work());
    return 0;
}
