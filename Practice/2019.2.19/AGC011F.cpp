#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;

typedef long long ll;
#define Dct(x) (lower_bound(&Num[1],&Num[num+1],x)-Num)
#define ls (x<<1)
#define rs (ls|1)
const int maxN=101000*5;

int n,K;
ll Sm[maxN],num,Num[maxN],F[maxN],Lft[maxN],Rht[maxN];
int C[maxN<<2];

void Cover(int x,int c);
void PushDown(int x);
void Modify(int x,int l,int r,int ql,int qr,int c);
int Query(int x,int l,int r,int p);
ll Calc(ll pos);
int main()
{
	//freopen("in","r",stdin);
	ll sum=0;
	scanf("%d%d",&n,&K);
	for (int i=1; i<=n; i++) {
		int key,opt;
		scanf("%d%d",&key,&opt);
		if (opt==1&&key*2>K) {
			printf("-1\n");
			exit(0);
		}
		Sm[i]=(Sm[i-1]+key)%K;
		sum+=key;
		if (opt==2) Lft[i]=0,Rht[i]=K-1;
		else Lft[i]=(K-Sm[i-1]*2%K)%K,Rht[i]=(K-Sm[i]*2%K)%K;
		Num[++num]=Lft[i];
		Num[++num]=Rht[i];
	}
	Num[++num]=0;
	Num[++num]=K-1;
	sort(&Num[1],&Num[num+1]);
	num=unique(&Num[1],&Num[num+1])-Num-1;
	//for (int i=1;i<=num;i++) cout<<Num[i]<<" ";cout<<endl;
	for (int i=n; i>=1; i--) {
		int l=Dct(Lft[i]),r=Dct(Rht[i]);
		F[i]=Calc(Lft[i]);
		//cout<<"("<<l<<" "<<r<<")"<<endl;
		if (l<=r) {
			if (l>1) Modify(1,1,num,1,l-1,i);
			if (r<num) Modify(1,1,num,r+1,num,i);
		} else if (r+1<=l-1) Modify(1,1,num,r+1,l-1,i);
		//cout<<F[i]<<" "<<Lft[i]<<endl;for (int j=1;j<=num;j++) cout<<Query(1,1,num,j)<<" ";cout<<endl;
	}
	ll Ans=F[1];
	for (int i=1; i<=num; i++) Ans=min(Ans,Calc(Num[i]));
	printf("%lld\n",Ans+sum*2);
	return 0;
}
void PushDown(int x)
{
	if (C[x]) {
		C[ls]=C[x];
		C[rs]=C[x];
		C[x]=0;
	}
	return;
}
void Modify(int x,int l,int r,int ql,int qr,int c)
{
	if (l==ql&&r==qr) {
		C[x]=c;
		return;
	}
	int mid=(l+r)>>1;
	PushDown(x);
	if (qr<=mid) Modify(ls,l,mid,ql,qr,c);
	else if (ql>=mid+1) Modify(rs,mid+1,r,ql,qr,c);
	else Modify(ls,l,mid,ql,mid,c),Modify(rs,mid+1,r,mid+1,qr,c);
	return;
}
int Query(int x,int l,int r,int p)
{
	if (l==r) return C[x];
	int mid=(l+r)>>1;
	PushDown(x);
	if (p<=mid) return Query(ls,l,mid,p);
	else return Query(rs,mid+1,r,p);
}
ll Calc(ll pos)
{
	int p=Dct(pos),id=Query(1,1,num,p);
	if (id==0) return 0;
	return F[id]+(Lft[id]-pos+K)%K;
}