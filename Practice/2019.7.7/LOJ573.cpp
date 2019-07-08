#include<bits/stdc++.h>
using namespace std;

#define Inv(x) QPow(x,Mod-2)
const int maxN=505000*2;
const int Mod=998244353;

class Data
{
public:
	int a,b,c,d;
	Data()
	{
		a=b=c=0;
		d=1;
	}
};

int n,m;
int Seq[maxN];
Data S[maxN<<2];

Data operator + (Data A,Data B);
int QPow(int x,int cnt);
void Build(int x,int l,int r);
void Extend(int x,int l,int r,int p);
Data Query(int x,int l,int r,int ql,int qr);
int main()
{
	int Type;
	scanf("%d%d%d",&n,&m,&Type);
	int RG=n+m;
	for (int i=1; i<=n; i++) scanf("%d",&Seq[i]);

	Build(1,1,RG);
	int lstans=0;
	for (int mi=1; mi<=m; mi++) {
		int opt;
		scanf("%d",&opt);
		if (opt==1) {
			int key;
			scanf("%d",&key);
			if (Type) key^=lstans;
			Seq[++n]=key;
			Extend(1,1,RG,n);
		} else {
			int l,r;
			scanf("%d%d",&l,&r);
			if (Type) l^=lstans,r^=lstans;
			if (l==r) printf("%d 1\n",Seq[l]),lstans=Seq[l]^1;
			else {
				Data d=Query(1,1,RG,l,r-1);
				lstans=1ll*(1ll*d.a*Seq[r]%Mod+d.b)%Mod;
				int fm=1ll*(1ll*d.c*Seq[r]%Mod+d.d)%Mod;
				//cerr<<lstans<<" "<<fm<<endl;
				//lstans=1ll*lstans*Inv(fm)%Mod;
				//cerr<<d.a<<" "<<d.b<<" "<<d.c<<" "<<d.d<<" "<<Seq[r]<<endl;
				//cerr<<lstans<<" "<<fm<<endl;
				printf("%d %d\n",lstans,fm);
				lstans^=fm;
			}
		}
	}
	return 0;
}
Data operator + (Data A,Data B)
{
	Data C;
	C.a=(1ll*A.a*B.a%Mod+1ll*A.b*B.c%Mod)%Mod;
	C.b=(1ll*A.a*B.b%Mod+1ll*A.b*B.d%Mod)%Mod;
	C.c=(1ll*A.c*B.a%Mod+1ll*A.d*B.c%Mod)%Mod;
	C.d=(1ll*A.c*B.b%Mod+1ll*A.d*B.d%Mod)%Mod;
	return C;
}
int QPow(int x,int cnt)
{
	int ret=1;
	while (cnt) {
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;
		cnt>>=1;
	}
	return ret;
}
#define ls (x<<1)
#define rs (ls|1)
void Build(int x,int l,int r)
{
	if (l==r) {
		S[x].a=Seq[l];
		S[x].b=S[x].c=1;
		S[x].d=0;
		return;
	}
	int mid=(l+r)>>1;
	Build(ls,l,mid);
	Build(rs,mid+1,r);
	S[x]=S[ls]+S[rs];
	return;
}
Data Query(int x,int l,int r,int ql,int qr)
{
	if (l==ql&&r==qr) return S[x];
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(ls,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rs,mid+1,r,ql,qr);
	return Query(ls,l,mid,ql,mid)+Query(rs,mid+1,r,mid+1,qr);
}
void Extend(int x,int l,int r,int p)
{
	if (l==r) {
		S[x].a=Seq[l];
		S[x].b=S[x].c=1;
		S[x].d=0;
		return;
	}
	int mid=(l+r)>>1;
	if (p<=mid) Extend(ls,l,mid,p);
	else Extend(rs,mid+1,r,p);
	S[x]=S[ls]+S[rs];
	return;
}
