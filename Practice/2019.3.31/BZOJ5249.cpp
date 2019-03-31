#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

const int maxN=505000;

int n,Sz[maxN];double K;
int num,Num[maxN],Dif[maxN],Seq[maxN],Del[maxN];
int Mn[maxN<<2],Lazy[maxN<<2];

void Plus(int x,int key);
void PushDown(int x);
void Modify(int x,int l,int r,int ql,int qr,int c);
int Query(int x,int l,int r,int limit);

int main(){
    scanf("%d%lf",&n,&K);
    for (int i=1;i<=n;i++) scanf("%d",&Dif[i]),Num[i]=Dif[i];
    sort(&Num[1],&Num[n+1]);num=unique(&Num[1],&Num[n+1])-Num-1;
    for (int i=1;i<=n;i++) Modify(1,1,num,1,lower_bound(&Num[1],&Num[num+1],Dif[i])-Num,1);
    for (int i=n;i>=1;i--) ++Sz[i],Sz[(int)(i/K)]+=Sz[i];
    for (int i=1;i<=n;i++){
        int fa=i/K;
        if (fa&&!Del[fa]) Del[fa]=1,Modify(1,1,num,1,Seq[fa],Sz[fa]-1);
        printf("%d ",Num[Seq[i]=Query(1,1,num,Sz[i])]);Modify(1,1,num,1,Seq[i],-Sz[i]);
    }
    printf("\n");
    return 0;
}
#define ls (x<<1)
#define rs (ls|1)
void Plus(int x,int key){
    Mn[x]+=key;Lazy[x]+=key;return;
}
void PushDown(int x){
    if (Lazy[x]) Plus(ls,Lazy[x]),Plus(rs,Lazy[x]),Lazy[x]=0;return;
}
void Modify(int x,int l,int r,int ql,int qr,int c){
    if (l==ql&&r==qr) return Plus(x,c);
    int mid=(l+r)>>1;PushDown(x);
    if (qr<=mid) Modify(ls,l,mid,ql,qr,c);else if (ql>=mid+1) Modify(rs,mid+1,r,ql,qr,c);
    else Modify(ls,l,mid,ql,mid,c),Modify(rs,mid+1,r,mid+1,qr,c);
    Mn[x]=min(Mn[ls],Mn[rs]);return;
}
int Query(int x,int l,int r,int limit){
    if (l==r) return Mn[x]>=limit?l:l-1;
    int mid=(l+r)>>1;PushDown(x);
    if (Mn[ls]>=limit) return Query(rs,mid+1,r,limit);
    else return Query(ls,l,mid,limit);
}