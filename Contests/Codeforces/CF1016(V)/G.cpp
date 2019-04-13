#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
#define pw(x) (1<<(x))

const int maxN=202000;
const int maxP=15;

ll X,Y,A[maxN];int n,Cnt[pw(maxP)+10];
vector<ll> Fcy,Pfy;
vector<pair<int,int> > Pfxy;

ll Mul(ll A,ll B,ll Mod);
ll QPow(ll A,ll cnt,ll Mod);
void Fc(ll X,vector<ll> & V);
ll random(ll l,ll r);
bool MillerRabin(ll X);
ll PollardRho(ll X);
int main(){
    srand(20150622);scanf("%d%lld%lld",&n,&X,&Y);
    if (Y%X) return puts("0"),0;
    Fc(Y,Fcy);sort(Fcy.begin(),Fcy.end());
    for (int i=0,sz=Fcy.size();i<sz;i++)
	if (Pfy.empty()||Fcy[i]!=Pfy.back()) Pfy.push_back(Fcy[i]),Pfxy.push_back(make_pair(0,1));
	else ++Pfxy.back().second;
    ll H=X;int psz=Pfy.size(),N=pw(psz);
    for (int i=0;i<psz;i++) while (H%Pfy[i]==0) ++Pfxy[i].first,H/=Pfy[i];
    //for (int i=0;i<psz;i++) cout<<Pfy[i]<<" ";cout<<endl;
    //for (int i=0;i<psz;i++) cout<<"("<<Pfxy[i].first<<" "<<Pfxy[i].second<<") ";cout<<endl;
    for (int i=1;i<=n;i++) scanf("%lld",&A[i]);
    for (int i=1;i<=n;i++){
	if (Y%A[i]) continue;
	int S=0;ll H=A[i];
	for (int j=0;j<psz;j++){
	    int c=0;while (H%Pfy[j]==0) ++c,H/=Pfy[j];
	    if (c==Pfxy[j].second) S|=pw(j);
	}
	++Cnt[S];
    }
    for (int i=0;i<psz;i++) for (int S=0;S<N;S++) if (!(S&pw(i))) Cnt[S]+=Cnt[S^pw(i)];
    ll Ans=0;
    for (int i=1;i<=n;i++){
	if (A[i]%X) continue;
	int S=N-1;ll H=A[i];
	for (int j=0;j<psz;j++){
	    int c=0;while (H%Pfy[j]==0) ++c,H/=Pfy[j];
	    if (c==Pfxy[j].first||Pfxy[j].first==Pfxy[j].second) S^=pw(j);
	}
	Ans=Ans+Cnt[S];
    }
    printf("%lld\n",Ans);return 0;
}
ll Mul(ll A,ll B,ll Mod){
    return (A*B-(ll)((ld)A/Mod*(ld)B+0.5)*Mod+Mod)%Mod;
}
ll QPow(ll A,ll cnt,ll Mod){
    ll ret=1;
    while (cnt){
	if (cnt&1) ret=Mul(ret,A,Mod);
	cnt>>=1;A=Mul(A,A,Mod);
    }
    return ret;
}
ll random(ll l,ll r){
    ld dou=1.0*rand()/RAND_MAX;
    return min(r,(ll)(dou*(r-l+1)+l));
}
bool MillerRabin(ll X){
    static int pcnt=10,P[]={2,3,5,7,11,13,17,19,23,29};
    for (int i=0;i<pcnt;i++){
	if (X<=P[i]) continue;
	if (QPow(P[i],X-1,X)!=1) return 0;
	ll dx=X-1;
	while (~dx&1){
	    dx>>=1;ll dt=QPow(P[i],dx,X);
	    if (Mul(dt,dt,X)==1&&dt!=1&&dt!=X-1) return 0;
	}
    }
    return 1;
}
ll PollardRho(ll X){
    ll x=0,y=0,a=random(1,X-1),b=2,g=1;
    while (1){
	ll mul=1;y=x;
	for (int i=1;i<b;i++){
	    y=(Mul(y,y,X)+a)%X;
	    mul=Mul(mul,abs(y-x),X);
	    if (!(i&127)){
		g=__gcd(mul,X);
		if (g>1) return g;
	    }
	}
	b<<=1;x=y;
	if (g>1||(g=__gcd(mul,X))>1) break;
    }
    if (g==X) g=1;return g;
}
void Fc(ll X,vector<ll> &V){
    if (MillerRabin(X)) V.push_back(X);
    else{
	ll g=1;
	while (g==1||g==X) g=PollardRho(X);
	Fc(g,V);Fc(X/g,V);
    }
    return;
}
