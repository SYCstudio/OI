#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long ll;
#define ls (x<<1)
#define rs (ls|1)
class SegmentData{
    public:
    ll mx,cnt,pls,cov,sz;
};
class SegmentTree{
    public:
    SegmentData S[maxN<<2];
    void Build(int x,int l,int r);
    void PushDown(int x);
    void Update(int x);
    int Query(int x,int l,int r,int ql,int qr,ll limit);
    void SetSame(int x,int l,int r,int ql,int qr,int key);
    void RangePlus(int x,int l,int r,int ql,int qr,int key);
};

const int maxN=101000;

int n,Input[maxN];

int main(){
    int Case;scanf("%d",&Case);
    while (Case--){
        scanf("%d",&n);for (int i=1;i<=n;i++) scanf("%d",&Input[i]);
        Build(1,1,n);
    }
}