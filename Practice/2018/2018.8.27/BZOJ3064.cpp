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

const int maxN=301000;
const int inf=2147483647;
const ll INF=1e17;

class Data
{
public:
	ll a,b;
	ll calc(ll x){
		return max(x+a,b);
	}
};

class SegmentData
{
public:
	ll mx,hmx;
	Data d,hd;
};

int n,m;
int Seq[maxN];
SegmentData S[maxN<<2];

Data max(Data A,Data B);
Data operator + (Data A,Data B);
void Build(int now,int l,int r);
void PushDown(int now);
void Update(int now);
void Cover(int now,Data A,Data B);
void Modify(int now,int l,int r,int ql,int qr,Data d);
ll Query(int now,int l,int r,int ql,int qr,int opt);

int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);
	Build(1,1,n);
	scanf("%d",&m);
	while (m--){
		char opt;int l,r;scanf(" %c %d%d",&opt,&l,&r);
		if (opt=='Q') printf("%lld\n",Query(1,1,n,l,r,1));
		if (opt=='A') printf("%lld\n",Query(1,1,n,l,r,2));
		if (opt=='P'){
			int x;scanf("%d",&x);
			Modify(1,1,n,l,r,((Data){x,-INF}));
		}
		if (opt=='C'){
			int x;scanf("%d",&x);
			Modify(1,1,n,l,r,((Data){-INF,x}));
		}
	}

	return 0;
}

Data max(Data A,Data B){
	return ((Data){max(A.a,B.a),max(A.b,B.b)});
}

Data operator + (Data A,Data B){
	return ((Data){max(-INF,A.a+B.a),max(A.b+B.a,B.b)});
}

void Build(int now,int l,int r){
	S[now].d=S[now].hd=((Data){0,-INF});
	if (l==r){
		S[now].mx=S[now].hmx=Seq[l];
		return;
	}
	int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	Update(now);return;
}

void Update(int now){
	S[now].mx=max(S[lson].mx,S[rson].mx);
	S[now].hmx=max(S[now].hmx,max(S[lson].mx,S[rson].mx));
	return;
}

void PushDown(int now){
	Cover(lson,S[now].d,S[now].hd);
	Cover(rson,S[now].d,S[now].hd);
	S[now].d=S[now].hd=((Data){0,-INF});
	return;
}

void Cover(int now,Data A,Data B){
	S[now].hd=max(S[now].hd,S[now].d+B);
	S[now].d=S[now].d+A;
	S[now].hmx=max(S[now].hmx,B.calc(S[now].mx));
	S[now].mx=A.calc(S[now].mx);
	return;
}

void Modify(int now,int l,int r,int ql,int qr,Data d){
	if ((l==ql)&&(r==qr)){
		Cover(now,d,d);return;
	}
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) Modify(lson,l,mid,ql,qr,d);
	else if (ql>=mid+1) Modify(rson,mid+1,r,ql,qr,d);
	else{
		Modify(lson,l,mid,ql,mid,d);Modify(rson,mid+1,r,mid+1,qr,d);
	}
	Update(now);return;
}

ll Query(int now,int l,int r,int ql,int qr,int opt){
	if ((l==ql)&&(r==qr)){
		if (opt==1) return S[now].mx;
		else return S[now].hmx;
	}
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr,opt);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr,opt);
	else return max(Query(lson,l,mid,ql,mid,opt),Query(rson,mid+1,r,mid+1,qr,opt));
}

