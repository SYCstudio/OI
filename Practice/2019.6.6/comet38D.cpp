#include<bits/stdc++.h>
using namespace std;

#define pw(x) (1<<(x))
const int maxB=32;
const int maxN=50500;

class Base{
public:
    int B[maxB];
    Base(){
	for (int i=maxB-1;i>=0;i--) B[i]=0;return;
    }
    void Insert(int key){
	for (int i=maxB-1;i>=0;i--)
	    if (key&pw(i)){
		if (B[i]) key^=B[i];
		else{
		    B[i]=key;return;
		}
	    }
	return;
    }
    int Query(int key){
	for (int i=maxB-1;i>=0;i--)
	    key=max(key,key^B[i]);
	return key;
    }
};
class SegmentData{
public:
    int sm;
    Base B;
    void Init(int k){
	sm=k;for (int i=maxB-1;i>=0;i--) B.B[i]=0;
	B.Insert(k);return;
    }
};

int n,m,Seq[maxN];
SegmentData S[maxN<<2];

Base Merge(Base A,Base B);
void Update(int x);
void Build(int x,int l,int r);
void Plus(int x,int l,int r,int p,int k);
int Query(int x,int l,int r,int p);
Base Query(int x,int l,int r,int ql,int qr);
int main(){
    scanf("%d%d",&n,&m);for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);
    for (int i=n;i>=1;i--) Seq[i]^=Seq[i-1];
    Build(1,1,n);
    while (m--){
	int opt,l,r,v;scanf("%d%d%d%d",&opt,&l,&r,&v);
	if (opt==1){
	    Plus(1,1,n,l,v);if (r+1<=n) Plus(1,1,n,r+1,v);
	}
	else{
	    Base Ans;if (l<r) Ans=Query(1,1,n,l+1,r);
	    Ans.Insert(Query(1,1,n,l));
	    //for (int i=maxB-1;i>=0;i--) if (Ans.B[i]) cout<<Ans.B[i]<<" ";cout<<endl;
	    printf("%d\n",Ans.Query(v));
	}
    }
    return 0;
}
Base Merge(Base A,Base B){
    for (int i=maxB-1;i>=0;i--) if (B.B[i]) A.Insert(B.B[i]);
    return A;
}
#define ls (x<<1)
#define rs (ls|1)
void Update(int x){
    S[x].B=Merge(S[ls].B,S[rs].B);
    S[x].sm=S[ls].sm^S[rs].sm;
    return;
}
void Build(int x,int l,int r){
    if (l==r){
	S[x].Init(Seq[l]);return;
    }
    int mid=(l+r)>>1;Build(ls,l,mid);Build(rs,mid+1,r);
    Update(x);return;
}
void Plus(int x,int l,int r,int p,int k){
    if (l==r){
	S[x].Init(k^S[x].sm);return;
    }
    int mid=(l+r)>>1;
    if (p<=mid) Plus(ls,l,mid,p,k);else Plus(rs,mid+1,r,p,k);
    Update(x);return;
}
int Query(int x,int l,int r,int p){
    if (l==r) return S[x].sm;
    int mid=(l+r)>>1;
    if (p<=mid) return Query(ls,l,mid,p);
    else return S[ls].sm^Query(rs,mid+1,r,p);
}
Base Query(int x,int l,int r,int ql,int qr){
    if (l==ql&&r==qr) return S[x].B;
    int mid=(l+r)>>1;
    if (qr<=mid) return Query(ls,l,mid,ql,qr);
    else if (ql>=mid+1) return Query(rs,mid+1,r,ql,qr);
    else return Merge(Query(ls,l,mid,ql,mid),Query(rs,mid+1,r,mid+1,qr));
}
#undef ls
#undef rs
