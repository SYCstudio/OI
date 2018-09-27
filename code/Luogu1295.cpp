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
	int mnkey,mx,lz;
	SegmentData(){
		mnkey=inf;mx=lz=0;return;
	}
};

int n,m;
int Bk[maxN],Sm[maxN];
SegmentData S[maxN<<2];

void Modify(int now,int l,int r,int pos,int key);
void Replace(int now,int l,int r,int ql,int qr,int mx);
int Query(int now,int l,int r,int ql,int qr);
void Update(int now);
void PushDown(int now);
void Delta(int now,int nmx);

int main(){
}

void Modify(int now,int l,int r,int pos,int key){
	if (l==r){
		S[now].mnkey=key;return;
	}
	PushDown(now);
	int mid=(l+r)>>1;
	if (pos<=mid) Modify(lson,l,mid,pos,key);
	else Modify(rson,mid+1,r,pos,key);
	Update(now);return;
}

void Replace(int now,int l,int r,int ql,int qr,int mx){
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

int Query(int now,int l,int r,int ql,int qr){
	if ((l==ql)&&(r==qr)) return S[now].mnkey;
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return min(Query(lson,l,mid,ql,mid),Query(rson,mid+1,r,mid+1,qr));
}

void Update(int now){
	if ((S[lson].mnkey<S[rson].mnkey)||((S[lson].mnkey==S[rson].mnkey)&&(S[lson].mx>S[rson].mx))) S[now].mnkey=S[lson].mnkey,S[now].mx=S[lson].mx;
	else S[now].mnkey=S[rson].mnkey,S[now].mx=S[rson].mx;
	return;
}

void PushDown(int now){
	if (S[now].lz){
		Delta(lson,S[now].lz);Delta(rson,S[now].lz);
		S[now].lz=0;
	}
	return;
}

void Delta(int now,int nmx){
	
}
