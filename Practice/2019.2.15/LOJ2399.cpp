#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<map>
using namespace std;

typedef long long ll;
#define ls (x<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
const int maxN=50500;
class SegmentTree{
    public:
    int Mx[maxN<<2],Key[maxN];
    private:
    int QueryL(int x,int l,int r,int ql,int qr,int limit){
        if (Mx[x]<=limit) return 0;
        if (l==r) return l;
        if (l==ql&&r==qr){
            if (Mx[ls]>limit) return QueryL(ls,l,mid,ql,mid,limit);
            return QueryL(rs,mid+1,r,mid+1,qr,limit);
        }
        if (qr<=mid) return QueryL(ls,l,mid,ql,qr,limit);
        else if (ql>=mid+1) return QueryL(rs,mid+1,r,ql,qr,limit);
        else{
            int ret=QueryL(ls,l,mid,ql,mid,limit);
            return ret?ret:QueryL(rs,mid+1,r,mid+1,qr,limit);
        }
    }
    int QueryR(int x,int l,int r,int ql,int qr,int limit){
        if (Mx[x]<=limit) return 0;
        if (l==r) return l;
        if (l==ql&&r==qr){
            if (Mx[rs]>limit) return QueryR(rs,mid+1,r,mid+1,qr,limit);
            return QueryR(ls,l,mid,ql,mid,limit);
        }
        if (qr<=mid) return QueryR(ls,l,mid,ql,qr,limit);
        else if (ql>=mid+1) return QueryR(rs,mid+1,r,ql,qr,limit);
        else{
            int ret=QueryR(rs,mid+1,r,mid+1,qr,limit);
            return ret?ret:QueryR(ls,l,mid,ql,mid,limit);
        }
    }
    public:
    void Build(int x,int l,int r){
        if (l==r) return Mx[x]=Key[l],(void(0));
        Build(ls,l,mid);Build(rs,mid+1,r);
        Mx[x]=max(Mx[ls],Mx[rs]);return;
    }
    int QueryL(int pos,int limit,int n){
        if (pos==1) return 0;
        return QueryR(1,1,n,1,pos-1,limit);
    }
    int QueryR(int pos,int limit,int n){
        if (pos==n) return 0;
        return QueryL(1,1,n,pos+1,n,limit);
    }
};
int H,W,Q;
int A[maxN],B[maxN];
SegmentTree T1,T2;
map<int,ll> Rc[2][maxN];

ll Solve(int x,int y,int opt);

int main(){
    scanf("%d%d%d",&H,&W,&Q);
    for (int i=1;i<=H;i++) scanf("%d",&A[i]),T1.Key[i]=A[i];
    for (int i=1;i<=W;i++) scanf("%d",&B[i]),T2.Key[i]=B[i];
    T1.Build(1,1,H);T2.Build(1,1,W);
    while (Q--){
        int x,y;scanf("%d%d",&x,&y);
        printf("%lld\n",max(Solve(x,y,0),Solve(x,y,1)));
    }
    return 0;
}
ll Solve(int x,int y,int opt){
    if (Rc[opt][x].count(y)) return Rc[opt][x][y];
    //cout<<"running on :"<<x<<" "<<y<<" "<<opt<<endl;
    ll Ans=0;
    if (opt==0){
        int ly=T2.QueryL(y,A[x],W),ry=T2.QueryR(y,A[x],W);
        //cout<<ly<<" "<<ry<<endl;
        if (ly) Ans=max(Ans,Solve(x,ly,opt^1)+y-ly);
        else Ans=max(Ans,(ll)y-1);
        if (ry) Ans=max(Ans,Solve(x,ry,opt^1)+ry-y);
        else Ans=max(Ans,(ll)W-y);
    }
    else{
        int lx=T1.QueryL(x,B[y],H),rx=T1.QueryR(x,B[y],H);
        //cout<<lx<<" "<<rx<<endl;
        if (lx) Ans=max(Ans,Solve(lx,y,opt^1)+x-lx);
        else Ans=max(Ans,(ll)x-1);
        if (rx) Ans=max(Ans,Solve(rx,y,opt^1)+rx-x);
        else Ans=max(Ans,(ll)H-x);
    }
    return Rc[opt][x][y]=Ans;
}