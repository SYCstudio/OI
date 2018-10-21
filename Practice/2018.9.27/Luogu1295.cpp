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

const int maxN=201000;
const int inf=2147483647;
const ll INF=1e17;

class SegmentData
{
public:
	ll mnkey,mn,lz;
	SegmentData(){
		mnkey=INF;mn=lz=0;return;
	}
};

int n,m;
ll Bk[maxN],Sm[maxN],Q[maxN];
SegmentData S[maxN<<2];

void Modify(int now,int l,int r,int pos,ll key);
void Replace(int now,int l,int r,int ql,int qr,ll mx);
ll Query(int now,int l,int r,int ql,int qr);
void Update(int now);
void PushDown(int now);
void Delta(int now,ll nmx);
void Outp(int now,int l,int r);

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) scanf("%lld",&Bk[i]),Sm[i]=Sm[i-1]+Bk[i];
	Modify(1,0,n,0,0);
	//Outp(1,0,n);
	int L=1,R=1;Bk[0]=INF;
	for (int i=1;i<=n;i++){
		while ((L<=R)&&(Bk[Q[R]]<=Bk[i])) R--;
		//cout<<"Q:"<<i<<" "<<Q[R]<<endl;
		Replace(1,0,n,Q[R],i-1,Bk[i]);
		Q[++R]=i;
		int p=lower_bound(&Sm[0],&Sm[n+1],Sm[i]-m)-Sm;
		while (Sm[p]<Sm[i]-m) p++;
		if (p>=i) p=i-1;
		ll f=Query(1,0,n,p,i-1);
		//cout<<i<<":"<<p<<" "<<f<<endl;
		Modify(1,0,n,i,f);
		//Outp(1,0,n);
	}
	printf("%lld\n",Query(1,0,n,n,n));return 0;
}

void Modify(int now,int l,int r,int pos,ll key){
	if (l==r){
		S[now].mnkey=S[now].mn=key;return;
	}
	PushDown(now);
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(lson,l,mid,pos,key);
	else Modify(rson,mid+1,r,pos,key);
	Update(now);return;
}

void Replace(int now,int l,int r,int ql,int qr,ll mx){
	if ((l==ql)&&(r==qr)){
		Delta(now,mx);return;
	}
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) Replace(lson,l,mid,ql,qr,mx);
	else if (ql>=mid+1) Replace(rson,mid+1,r,ql,qr,mx);
	else{
		Replace(lson,l,mid,ql,mid,mx);
		Replace(rson,mid+1,r,mid+1,qr,mx);
	}
	Update(now);return;
}

ll Query(int now,int l,int r,int ql,int qr){
	if ((l==ql)&&(r==qr)) return S[now].mnkey;
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return min(Query(lson,l,mid,ql,mid),Query(rson,mid+1,r,mid+1,qr));
}

void Update(int now){
	S[now].mn=min(S[lson].mn,S[rson].mn);
	S[now].mnkey=min(S[lson].mnkey,S[rson].mnkey);
	return;
}

void PushDown(int now){
	if (S[now].lz){
		Delta(lson,S[now].lz);Delta(rson,S[now].lz);
		S[now].lz=0;
	}
	return;
}

void Delta(int now,ll nmx){
	S[now].mnkey=S[now].mn+nmx;
	S[now].lz=nmx;return;
}

void Outp(int now,int l,int r){
	if (l==r) cout<<"["<<l<<" "<<r<<"] "<<S[now].mnkey<<" "<<S[now].mn<<endl;
	if (l==r) return;
	int mid=(l+r)>>1;PushDown(now);
	Outp(lson,l,mid);Outp(rson,mid+1,r);
	return;
}
