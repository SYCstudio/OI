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
    void Init(int p,int n);
    void Build(int x,int l,int r,int p);
    void Plus(int x,ll key);
    void PushDown(int x);
    void Update(int x);
    void RangePlus(int x,int l,int r,int ql,int qr,ll key);
    void Cmpmin(int x,int l,int r,int p,ll key);
    int Query(int x,int l,int r,int ql,int qr);
};

int n,Q,A,B;
SegmentTree T1,T2;
int P[maxN];

int main(){
    scanf("%d%d%d%d",&n,&Q,&A,&B);
    P[0]=A;T1.opt=1;T2.opt=-1;
    T1.Init(B,n);T2.Init(B,n);
    for (int i=1;i<=Q;i++){
        int p;scanf("%d",&p);P[i]=p;
        ll mn=INF;
        mn=min(T1.Query(1,1,n,p,n)-p,T2.Query(1,1,n,1,p)+p);
        if (p!=1) T1.RangePlus(1,1,n,1,p-1,abs(p-P[i-1])),T2.RangePlus(1,1,n,1,p-1,abs(p-P[i-1]));
        if (p!=n) T1.RangePlus(1,1,n,p+1,n,abs(p-P[i-1])),T2.RangePlus(1,1,n,p+1,n,abs(p-P[i-1]));
        T1.Cmpmin(1,1,n,P[i-1],mn+P[i-1]);T2.Cmpmin(1,1,n,P[i-1],mn-P[i-1]);
    }
}