#include<bits/stdc++.h>
using namespace std;

const int maxN=303000;
const int inf=2000000000;

class SegmentData{
public:
    int mx,lz;
};

int n,m,H;
int A[maxN],B[maxN];
int num,Num[maxN];
SegmentData S[maxN<<2];

void Plus(int x,int key);
void PushDown(int x);
void Modify(int x,int l,int r,int ql,int qr,int key);
int Query(int x,int l,int r,int p);

int main(){
    scanf("%d%d%d",&n,&m,&H);
    for (int i=1;i<=m;i++) scanf("%d",&B[i]);
    for (int i=1;i<=n;i++) scanf("%d",&A[i]),Num[i]=A[i];

    Num[n+1]=inf;Num[n+2]=-inf;
    sort(&Num[1],&Num[n+3]);num=unique(&Num[1],&Num[n+3])-Num-1;

    for (int i=1;i<=m;i++){
	int p=lower_bound(&Num[1],&Num[num+1],H-B[i])-Num;
	//cout<<p<<endl;
	Modify(1,1,num,p,num,-1);
    }

    //for (int i=1;i<=num;i++) cout<<Query(1,1,num,i)<<" ";cout<<endl;

    for (int i=1;i<m;i++){
	int p=lower_bound(&Num[1],&Num[num+1],A[i])-Num;
	Modify(1,1,num,p,num,1);
    }
    int Ans=0;
    for (int i=m;i<=n;i++){
	int p=lower_bound(&Num[1],&Num[num+1],A[i])-Num;
	Modify(1,1,num,p,num,1);
	if (S[1].mx<=0) ++Ans;
	p=lower_bound(&Num[1],&Num[num+1],A[i-m+1])-Num;
	Modify(1,1,num,p,num,-1);

	//for (int j=1;j<=num;j++) cout<<Query(1,1,num,j)<<" ";cout<<endl;
    }
    printf("%d\n",Ans);return 0;
}
void Plus(int x,int key){
    S[x].mx+=key;S[x].lz+=key;return;
}
#define ls (x<<1)
#define rs (ls|1)
void PushDown(int x){
    if (S[x].lz){
	Plus(ls,S[x].lz);Plus(rs,S[x].lz);
	S[x].lz=0;
    }
    return;
}
void Modify(int x,int l,int r,int ql,int qr,int key){
    if (l==ql&&r==qr){
	Plus(x,key);return;
    }
    int mid=(l+r)>>1;PushDown(x);
    if (qr<=mid) Modify(ls,l,mid,ql,qr,key);
    else if (ql>=mid+1) Modify(rs,mid+1,r,ql,qr,key);
    else Modify(ls,l,mid,ql,mid,key),Modify(rs,mid+1,r,mid+1,qr,key);
    S[x].mx=max(S[ls].mx,S[rs].mx);return;
}
int Query(int x,int l,int r,int p){
    if (l==r) return S[x].mx;
    int mid=(l+r)>>1;PushDown(x);
    if (p<=mid) return Query(ls,l,mid,p);else return Query(rs,mid+1,r,p);
}
