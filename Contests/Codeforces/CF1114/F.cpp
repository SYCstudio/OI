#include<bits/stdc++.h>
using namespace std;

#define ls (x<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
typedef long long ll;
const int maxN=404000;
const int Mod=1e9+7;
const int maxNum=302;

int notprime[maxN],pcnt,P[maxN];
int n,Q;
int S[maxN<<2],Mul[maxN<<2],Sz[maxN<<2];
ll Bs[maxN<<2],Or[maxN<<2];
int Inv[maxN];

void Init();
int QPow(int x,int cnt);
void Build(int x,int l,int r);
void Update(int x);
void PushDown(int x);
void RMul(int x,int key);
void ROr(int x,ll s);
void Modify(int x,int l,int r,int ql,int qr,int key,ll ns);
int Query(int x,int l,int r,int ql,int qr);
ll GetOr(int x,int l,int r,int ql,int qr);

int main(){
    Init();
    scanf("%d%d",&n,&Q);
    Build(1,1,n);
    while (Q--){
        char ipt[20];int l,r,x;scanf(" %s %d%d",ipt,&l,&r);
        if (ipt[0]=='M'){
            scanf("%d",&x);
            ll ns=0;for (int i=0;i<=pcnt;i++) if (x%P[i]==0) ns|=(1ll<<i);
            //cout<<x<<" "<<ns<<endl;
            Modify(1,1,n,l,r,x,ns);
        }
        else{
            int Ans=Query(1,1,n,l,r);ll s=GetOr(1,1,n,l,r);
            //cout<<"Ans:"<<Ans<<" "<<s<<endl;
            for (int i=0;i<=pcnt;i++) if (s&(1ll<<i)) Ans=1ll*Ans*Inv[i]%Mod;
            printf("%d\n",Ans);
        }
    }
    return 0;
}
void Init(){
    notprime[1]=1;
    for (int i=2;i<maxNum;i++){
        if (notprime[i]==0) P[++pcnt]=i;
        for (int j=1;j<=pcnt&&1ll*i*P[j]<maxNum;j++){
            notprime[i*P[j]]=1;
            if (i%P[j]==0) break;
        }
    }
    for (int i=0;i<pcnt;i++) P[i]=P[i+1];--pcnt;
    for (int i=0;i<=pcnt;i++) Inv[i]=1ll*(P[i]-1)*QPow(P[i],Mod-2)%Mod;
    //for (int i=0;i<=pcnt;i++) cout<<P[i]<<" ";cout<<endl;
    //cout<<pcnt<<endl;
    //for (int i=1;i<=pcnt;i++) cout<<P[i]<<" ";cout<<endl;
}
int QPow(int x,int cnt){
    int ret=1;
    while (cnt){
        if (cnt&1) ret=1ll*ret*x%Mod;
        x=1ll*x*x%Mod;cnt>>=1;
    }
    return ret;
}
void Build(int x,int l,int r){
    Or[x]=0;Mul[x]=1;Sz[x]=r-l+1;
    if (l==r){
        scanf("%d",&S[x]);
        for (int i=0;i<=pcnt;i++) if (S[x]%P[i]==0) Bs[x]|=1ll<<i;
        //cout<<"Build:"<<S[x]<<" "<<Bs[x]<<endl;
        return;
    }
    Build(ls,l,mid);Build(rs,mid+1,r);
    Update(x);return;
}
void Update(int x){
    S[x]=1ll*S[ls]*S[rs]%Mod;
    Bs[x]=Bs[ls]|Bs[rs];return;
}
void PushDown(int x){
    if (Mul[x]!=1){
        RMul(ls,Mul[x]);RMul(rs,Mul[x]);
        Mul[x]=1;
    }
    if (Or[x]){
        ROr(ls,Or[x]);ROr(rs,Or[x]);
        Or[x]=0;
    }
    return;
}
void RMul(int x,int key){
    S[x]=1ll*S[x]*QPow(key,Sz[x])%Mod;Mul[x]=1ll*Mul[x]*key%Mod;
    return;
}
void ROr(int x,ll s){
    Bs[x]|=s;Or[x]|=s;return;
}
void Modify(int x,int l,int r,int ql,int qr,int key,ll ns){
    if (l==ql&&r==qr){
        RMul(x,key);ROr(x,ns);return;
    }
    PushDown(x);
    if (qr<=mid) Modify(ls,l,mid,ql,qr,key,ns);
    else if (ql>=mid+1) Modify(rs,mid+1,r,ql,qr,key,ns);
    else Modify(ls,l,mid,ql,mid,key,ns),Modify(rs,mid+1,r,mid+1,qr,key,ns);
    Update(x);return;
}
int Query(int x,int l,int r,int ql,int qr){
    if (l==ql&&r==qr) return S[x];
    PushDown(x);
    if (qr<=mid) return Query(ls,l,mid,ql,qr);
    else if (ql>=mid+1) return Query(rs,mid+1,r,ql,qr);
    else return 1ll*Query(ls,l,mid,ql,mid)*Query(rs,mid+1,r,mid+1,qr)%Mod;
}
ll GetOr(int x,int l,int r,int ql,int qr){
    if (l==ql&&r==qr) return Bs[x];
    PushDown(x);
    if (qr<=mid) return GetOr(ls,l,mid,ql,qr);
    else if (ql>=mid+1) return GetOr(rs,mid+1,r,ql,qr);
    else return GetOr(ls,l,mid,ql,mid)|GetOr(rs,mid+1,r,mid+1,qr);
}