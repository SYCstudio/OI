#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;

#define ls (x<<1)
#define rs (ls|1)

const int maxN=202000;

class SegmentData
{
public:
	int ro,ad,mx,dt;
};

int n,m;
SegmentData S[maxN<<2];

void Plus(int x,int k);
void PushDown(int x);
void Update(int x);
void Build(int x,int l,int r);
void Mor(int x,int l,int r,int ql,int qr,int k);
void Mand(int x,int l,int r,int ql,int qr,int k);
int Qmx(int x,int l,int r,int ql,int qr);

int main()
{
	scanf("%d%d",&n,&m);
	Build(1,1,n);
	while (m--) {
		int opt,l,r,x;
		scanf("%d%d%d",&opt,&l,&r);
		if (opt!=3) scanf("%d",&x);
		if (opt==1) Mand(1,1,n,l,r,x);
		if (opt==2) Mor(1,1,n,l,r,x);
		if (opt==3) printf("%d\n",Qmx(1,1,n,l,r));
	}
	return 0;
}
void Plus(int x,int k)
{
	S[x].ro+=k;
	S[x].ad+=k;
	S[x].mx+=k;
	S[x].dt+=k;
	return;
}
void PushDown(int x)
{
	if (S[x].dt) {
		Plus(ls,S[x].dt);
		Plus(rs,S[x].dt);
		S[x].dt=0;
	}
	return;
}
void Update(int x)
{
	S[x].ro=S[ls].ro|S[rs].ro;
	S[x].ad=S[ls].ad&S[rs].ad;
	S[x].mx=max(S[ls].mx,S[rs].mx);
	return;
}
void Build(int x,int l,int r)
{
	if (l==r) {
		scanf("%d",&S[x].mx);
		S[x].ro=S[x].ad=S[x].mx;
		return;
	}
	int mid=(l+r)>>1;
	Build(ls,l,mid);
	Build(rs,mid+1,r);
	Update(x);
	return;
}
void Mor(int x,int l,int r,int ql,int qr,int k)
{
	if (l==ql&&r==qr)
		if ((S[x].ad|k)-S[x].ad==(S[x].ro|k)-S[x].ro) {
			Plus(x,(S[x].ad|k)-S[x].ad);
			return;
		}
	int mid=(l+r)>>1;
	PushDown(x);
	if (qr<=mid) Mor(ls,l,mid,ql,qr,k);
	else if (ql>=mid+1) Mor(rs,mid+1,r,ql,qr,k);
	else Mor(ls,l,mid,ql,mid,k),Mor(rs,mid+1,r,mid+1,qr,k);
	Update(x);
	return;
}
void Mand(int x,int l,int r,int ql,int qr,int k)
{
	if (l==ql&&r==qr)
		if ((S[x].ad&k)-S[x].ad==(S[x].ro&k)-S[x].ro) {
			Plus(x,(S[x].ad&k)-S[x].ad);
			return;
		}
	int mid=(l+r)>>1;
	PushDown(x);
	if (qr<=mid) Mand(ls,l,mid,ql,qr,k);
	else if (ql>=mid+1) Mand(rs,mid+1,r,ql,qr,k);
	else Mand(ls,l,mid,ql,mid,k),Mand(rs,mid+1,r,mid+1,qr,k);
	Update(x);
	return;
}
int Qmx(int x,int l,int r,int ql,int qr)
{
	if (l==ql&&r==qr) return S[x].mx;
	int mid=(l+r)>>1;
	PushDown(x);
	if (qr<=mid) Qmx(ls,l,mid,ql,qr);
	else if (ql>=mid+1) Qmx(rs,mid+1,r,ql,qr);
	else return max(Qmx(ls,l,mid,ql,mid),Qmx(rs,mid+1,r,mid+1,qr));
}
