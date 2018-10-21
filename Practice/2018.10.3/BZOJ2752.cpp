#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=101000;
const int inf=2147483647;

class SegmentData
{
public:
	ll lkey,rkey,sum,sz,pls,all;
	SegmentData(){
		lkey=rkey=sum=sz=pls=all=0;return;
	}
};

int n,m;
ll S1[maxN],S2[maxN];
SegmentData S[maxN<<2];

void Build(int now,int l,int r);
void Modify(int now,int l,int r,int ql,int qr,ll key);
void Plus(int now,ll key);
void PushDown(int now);
SegmentData Query(int now,int l,int r,int ql,int qr);
SegmentData operator + (SegmentData A,SegmentData B);
void Outp(int now,int l,int r);

int main(){
	S1[0]=S2[0]=0;
	for (int i=1;i<maxN;i++) S1[i]=1ll*i*(i+1)/2,S2[i]=(S2[i-1]+S1[i]);
	
	scanf("%d%d",&n,&m);n--;
	Build(1,1,n);
	while (m--){
		char c;scanf(" %c",&c);
		if (c=='C'){
			int l,r,key;scanf("%d%d%d",&l,&r,&key);r--;
			Modify(1,1,n,l,r,key);
		}
		if (c=='Q'){
			int l,r;scanf("%d%d",&l,&r);r--;
			ll sum=Query(1,1,n,l,r).sum;
			ll g=__gcd(S1[r-l+1],sum);
			printf("%lld/%lld\n",sum/g,S1[r-l+1]/g);
		}
		//Outp(1,1,n);
	}
	return 0;
}

void Build(int now,int l,int r){
	S[now].sz=(r-l+1);
	if (l==r) return;
	int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	return;
}

void Modify(int now,int l,int r,int ql,int qr,ll key){
	if ((l==ql)&&(r==qr)){
		Plus(now,key);return;
	}
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) Modify(lson,l,mid,ql,qr,key);
	else if (ql>=mid+1) Modify(rson,mid+1,r,ql,qr,key);
	else{
		Modify(lson,l,mid,ql,mid,key);
		Modify(rson,mid+1,r,mid+1,qr,key);
	}
	S[now]=S[lson]+S[rson];return;
}

void Plus(int now,ll key){
	S[now].lkey+=key*S1[S[now].sz];
	S[now].rkey+=key*S1[S[now].sz];
	S[now].sum+=key*S2[S[now].sz];
	S[now].pls+=key;S[now].all+=key*S[now].sz;
	return;
}

void PushDown(int now){
	if (S[now].pls){
		Plus(lson,S[now].pls);Plus(rson,S[now].pls);
		S[now].pls=0;
	}
	return;
}

SegmentData Query(int now,int l,int r,int ql,int qr){
	if ((l==ql)&&(r==qr)) return S[now];
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return Query(lson,l,mid,ql,mid)+Query(rson,mid+1,r,mid+1,qr);
}

SegmentData operator + (SegmentData A,SegmentData B){
	SegmentData rt;
	rt.sz=A.sz+B.sz;
	rt.lkey=A.lkey+B.lkey+B.sz*A.all;
	rt.rkey=B.rkey+A.rkey+A.sz*B.all;
	rt.sum=A.sum+B.sum+A.rkey*B.sz+B.lkey*A.sz;
	rt.all=A.all+B.all;
	return rt;
}

void Outp(int now,int l,int r){
	cout<<"["<<l<<","<<r<<"] "<<S[now].lkey<<" "<<S[now].rkey<<" "<<S[now].sum<<" "<<S[now].all<<endl;
	if (l==r) return;PushDown(now);
	int mid=(l+r)>>1;
	Outp(lson,l,mid);Outp(rson,mid+1,r);
	return;
}
