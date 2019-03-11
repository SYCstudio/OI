#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
#define ls (x<<1)
#define rs (ls|1)
const int maxN=202000;
const ll INF=1e18;
class SegmentTree{
    public:
    ll Mn[maxN<<2],Lazy[maxN<<2];
    void Plus(int x,ll key){
        Mn[x]+=key;Lazy[x]+=key;return;
    }
    void PushDown(int x){
        if (Lazy[x]){
            Plus(ls,Lazy[x]);Plus(rs,Lazy[x]);Lazy[x]=0;
        }
        return;
    }
    void Update(int x){
        Mn[x]=min(Mn[ls],Mn[rs]);return;
    }
    void Build(int x,int l,int r){
        if (l==r){
            Mn[x]=INF;
            return;
        }
        int mid=(l+r)>>1;
        Build(ls,l,mid);Build(rs,mid+1,r);Update(x);return;
    }
    void Init(int n){
        Build(1,1,n);return;
    }
    void RangePlus(int x,int l,int r,int ql,int qr,ll key){
        if (l==ql&&r==qr){
            Plus(x,key);return;
        }
        int mid=(l+r)>>1;PushDown(x);
        if (qr<=mid) RangePlus(ls,l,mid,ql,qr,key);
        else if (ql>=mid+1) RangePlus(rs,mid+1,r,ql,qr,key);
        else RangePlus(ls,l,mid,ql,mid,key),RangePlus(rs,mid+1,r,mid+1,qr,key);
        Update(x);return;
    }
    void Cmpmin(int x,int l,int r,int p,ll key){
        if (l==r){
            Mn[x]=min(Mn[x],key);return;
        }
        int mid=(l+r)>>1;PushDown(x);
        if (p<=mid) Cmpmin(ls,l,mid,p,key);else Cmpmin(rs,mid+1,r,p,key);
        Update(x);return;
    }
    ll Query(int x,int l,int r,int ql,int qr){
        if (l==ql&&r==qr) return Mn[x];
        int mid=(l+r)>>1;PushDown(x);
        if (qr<=mid) return Query(ls,l,mid,ql,qr);
        else if (ql>=mid+1) Query(rs,mid+1,r,ql,qr);
        else return min(Query(ls,l,mid,ql,mid),Query(rs,mid+1,r,mid+1,qr));
    }
    ll Get(int x,int l,int r,int opt){
        if (l==r) return Mn[x]+l*opt;
        PushDown(x);int mid=(l+r)>>1;
        return min(Get(ls,l,mid,opt),Get(rs,mid+1,r,opt));
    }
};

int n,Q,A,B;
SegmentTree T1,T2;
int P[maxN];

int main(){
    scanf("%d%d%d%d",&n,&Q,&A,&B);
    P[0]=A;
    T1.Init(n);T1.Cmpmin(1,1,n,B,B);
    T2.Init(n);T2.Cmpmin(1,1,n,B,-B);
    for (int i=1;i<=Q;i++){
        int p;scanf("%d",&p);P[i]=p;
        ll mn=INF;
        mn=min(T1.Query(1,1,n,p,n)-p,T2.Query(1,1,n,1,p)+p);
        T1.RangePlus(1,1,n,1,n,abs(p-P[i-1]));T2.RangePlus(1,1,n,1,n,abs(p-P[i-1]));
        T1.Cmpmin(1,1,n,P[i-1],mn+P[i-1]);T2.Cmpmin(1,1,n,P[i-1],mn-P[i-1]);
    }
    ll Ans=min(T1.Get(1,1,n,-1),T2.Get(1,1,n,1));
    printf("%lld\n",Ans);return 0;
}