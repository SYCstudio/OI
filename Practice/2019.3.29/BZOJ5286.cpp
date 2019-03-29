#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

const int maxN=201000;
const int inf=2000000000;

class SegmentData{
    public:
    int mxkey,ans;
};

int n,Q,P;
int T[maxN];
SegmentData S[maxN<<2];

void Build(int x,int l,int r);
void Modify(int x,int l,int r,int p,int key);
int Query(int x,int l,int r,int limit);
int main(){
    scanf("%d%d%d",&n,&Q,&P);for (int i=1;i<=n;i++) scanf("%d",&T[i]),T[i+n]=T[i];
    for (int i=1;i<=n+n;i++) T[i]=T[i]-i;
    Build(1,1,n+n);
    int lstans;printf("%d\n",lstans=S[1].ans+n-1);
    while (Q--){
        int x,y;scanf("%d%d",&x,&y);
        if (P) x^=lstans,y^=lstans;
        T[x]=y-x;T[x+n]=y-(x+n);
        Modify(1,1,n+n,x,y-x);Modify(1,1,n+n,n+x,y-(n+x));
        printf("%d\n",lstans=S[1].ans+n-1);
    }
    return 0;
}
#define ls (x<<1)
#define rs (ls|1)
void Build(int x,int l,int r){
    if (l==r){
        S[x].mxkey=T[l];S[x].ans=T[l]+l;return;
    }
    int mid=(l+r)>>1;Build(ls,l,mid);Build(rs,mid+1,r);
    S[x].mxkey=max(S[ls].mxkey,S[rs].mxkey);
    S[x].ans=Query(ls,l,mid,S[rs].mxkey);
    return;
}
void Modify(int x,int l,int r,int p,int key){
    if (l==r){
        S[x].mxkey=key;
        S[x].ans=key+l;return;
    }
    int mid=(l+r)>>1;if (p<=mid) Modify(ls,l,mid,p,key);else Modify(rs,mid+1,r,p,key);
    S[x].mxkey=max(S[ls].mxkey,S[rs].mxkey);
    S[x].ans=Query(ls,l,mid,S[rs].mxkey);
    return;
}
int Query(int x,int l,int r,int limit){
    if (l==r) return l+max(S[x].mxkey,limit);
    int mid=(l+r)>>1;
    if (S[rs].mxkey>=limit) return min(S[x].ans,Query(rs,mid+1,r,limit));
    else return min(mid+1+limit,Query(ls,l,mid,limit));
}