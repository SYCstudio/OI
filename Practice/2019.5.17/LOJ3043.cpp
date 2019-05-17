#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

#define Inv(x) QPow(x,Mod-2)
#define ls (x<<1)
#define rs (ls|1)
const int maxN=101000;
const int Mod=998244353;
const int inv2=499122177;

class SegmentData{
public:
    int f,g,opt,sumf;
};

int n,Q,pw[maxN],ipw[maxN];
SegmentData S[maxN<<2];

int QPow(int x,int cnt);
void Operation(int x,int k);
void PushDown(int x);
void Update(int x);
void Build(int x,int l,int r);
void Modify(int x,int l,int r,int ql,int qr);
void Outp(int x,int l,int r);
int main(){
    pw[0]=ipw[0]=1;for (int i=1;i<maxN;i++) pw[i]=2ll*pw[i-1]%Mod,ipw[i]=1ll*ipw[i-1]*inv2%Mod;
    scanf("%d%d",&n,&Q);
    Build(1,1,n);int c=0;
    while (Q--){
	int opt,l,r;scanf("%d",&opt);
	if (opt==1){
	    scanf("%d%d",&l,&r);Modify(1,1,n,l,r);++c;
	}
	else printf("%lld\n",1ll*S[1].sumf*pw[c]%Mod);

	//Outp(1,1,n);
    }
    return 0;
}
int QPow(int x,int cnt){
    int ret=1;
    while (cnt){
	if (cnt&1) ret=1ll*ret*x%Mod;x=1ll*x*x%Mod;cnt>>=1;
    }
    return ret;
}
void Operation(int x,int k){
    S[x].g=(S[x].g+pw[k]-1)%Mod;
    S[x].g=1ll*S[x].g*ipw[k]%Mod;
    S[x].opt+=k;return;
}
void PushDown(int x){
    if (S[x].opt) Operation(ls,S[x].opt),Operation(rs,S[x].opt),S[x].opt=0;
    return;
}
void Update(int x){
    S[x].sumf=S[x].f;
    if (rs<maxN*4) S[x].sumf=((S[x].sumf+S[ls].sumf)%Mod+S[rs].sumf)%Mod;
    return;
}
void Build(int x,int l,int r){
    S[x].f=0;S[x].g=0;if (l==r) return;
    int mid=(l+r)>>1;Build(ls,l,mid);Build(rs,mid+1,r);
    Update(x);return;
}
void Modify(int x,int l,int r,int ql,int qr){
    //cout<<x<<" "<<l<<" "<<r<<" "<<ql<<" "<<qr<<endl;
    if (l==ql&&r==qr){
	Operation(x,1);
	S[x].sumf=(S[x].sumf-S[x].f+Mod)%Mod;
	S[x].f=1ll*(S[x].f+1)%Mod*inv2%Mod;
	S[x].sumf=(S[x].sumf+S[x].f)%Mod;
	return;
    }
    S[x].f=1ll*S[x].f*inv2%Mod;S[x].g=1ll*S[x].g*inv2%Mod;
    int mid=(l+r)>>1;PushDown(x);
    if (qr<=mid) Modify(ls,l,mid,ql,qr),S[rs].f=1ll*(S[rs].f+S[rs].g)%Mod*inv2%Mod,Update(rs);
    else if (ql>=mid+1) Modify(rs,mid+1,r,ql,qr),S[ls].f=1ll*(S[ls].f+S[ls].g)%Mod*inv2%Mod,Update(ls);
    else Modify(ls,l,mid,ql,mid),Modify(rs,mid+1,r,mid+1,qr);
    Update(x);return;
}
void Outp(int x,int l,int r){
    cout<<x<<"["<<l<<" "<<r<<"] "<<S[x].sumf<<" "<<S[x].f<<" "<<S[x].g<<endl;
    if (l==r) return;
    int mid=(l+r)>>1;PushDown(x);
    Outp(ls,l,mid);Outp(rs,mid+1,r);
    return;
}
