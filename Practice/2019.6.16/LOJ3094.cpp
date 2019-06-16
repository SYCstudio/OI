#include<bits/stdc++.h>
using namespace std;

const int maxN=160000*3;

class SegmentData{
public:
    int mn,mncnt,lz;
};

int n,Q,Seq[maxN];
int _Cnt[maxN+maxN+maxN],*Cnt=_Cnt+maxN;
SegmentData S[maxN<<2];

void PushDown(int x);
void Update(int x);
void Build(int x,int l,int r);
void Modify(int x,int l,int r,int ql,int qr,int key);
int Query(int x,int l,int r,int ql,int qr);
int main(){
    scanf("%d%d",&n,&Q);int QL=min(-n,-Q),QR=max(n+n,n+Q);
    for (int i=1;i<=n;i++) scanf("%d",&Seq[i]),++Cnt[Seq[i]];
    Build(1,QL,QR);
    for (int i=1;i<=n;i++) if (Cnt[i]) Modify(1,QL,QR,i-Cnt[i]+1,i,1);
    int L=1,R=n,delta=0;
    for (int qi=1;qi<=Q;qi++){
	int p,x;scanf("%d%d",&p,&x);
	if (p>0){
	    x-=delta;
	    if (Seq[p]<=R) Modify(1,QL,QR,Seq[p]-Cnt[Seq[p]]+1,Seq[p]-Cnt[Seq[p]]+1,-1);
	    --Cnt[Seq[p]];
	    Seq[p]=x;
	    if (Seq[p]<=R) Modify(1,QL,QR,Seq[p]-Cnt[Seq[p]],Seq[p]-Cnt[Seq[p]],1);
	    ++Cnt[Seq[p]];
	}
	else{
	    delta+=x;
	    if (x==1){
		if (Cnt[R]) Modify(1,QL,QR,R-Cnt[R]+1,R,-1);
		--L;--R;
	    }
	    else if (x==-1){
		++L;++R;
		if (Cnt[R]) Modify(1,QL,QR,R-Cnt[R]+1,R,1);
	    }
	}
	printf("%d\n",Query(1,QL,QR,L,R));
    }
    return 0;
}
#define ls (x<<1)
#define rs (ls|1)
void PushDown(int x){
    if (S[x].lz){
	S[ls].mn+=S[x].lz;S[ls].lz+=S[x].lz;
	S[rs].mn+=S[x].lz;S[rs].lz+=S[x].lz;
	S[x].lz=0;
    }
    return;
}
void Update(int x){
    S[x].mn=min(S[ls].mn,S[rs].mn);S[x].mncnt=0;
    if (S[x].mn==S[ls].mn) S[x].mncnt+=S[ls].mncnt;
    if (S[x].mn==S[rs].mn) S[x].mncnt+=S[rs].mncnt;
    return;
}
void Build(int x,int l,int r){
    if (l==r){
	S[x].mn=0;S[x].mncnt=1;
	return;
    }
    int mid=(l+r)>>1;Build(ls,l,mid);Build(rs,mid+1,r);
    Update(x);
    return;
}
void Modify(int x,int l,int r,int ql,int qr,int key){
    if (l==ql&&r==qr){
	S[x].mn+=key;S[x].lz+=key;return;
    }
    int mid=(l+r)>>1;PushDown(x);
    if (qr<=mid) Modify(ls,l,mid,ql,qr,key);
    else if (ql>=mid+1) Modify(rs,mid+1,r,ql,qr,key);
    else Modify(ls,l,mid,ql,mid,key),Modify(rs,mid+1,r,mid+1,qr,key);
    Update(x);return;
}
int Query(int x,int l,int r,int ql,int qr){
    if (l==ql&&r==qr) return S[x].mn==0?S[x].mncnt:0;
    int mid=(l+r)>>1;PushDown(x);
    if (qr<=mid) return Query(ls,l,mid,ql,qr);
    else if (ql>=mid+1) return Query(rs,mid+1,r,ql,qr);
    else return Query(ls,l,mid,ql,mid)+Query(rs,mid+1,r,mid+1,qr);
}
