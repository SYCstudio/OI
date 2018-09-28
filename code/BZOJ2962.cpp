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

const int maxN=50500;
const int Mod=19940417;
const int inf=2147483647;

class Data
{
public:
	int f[22];
};

class SegmentData
{
public:
	int ng,ad,len;
	Data D;
	SegmentData(){
		ng=ad=0;return;
	}
};

int n,Q;
int Seq[maxN],C[maxN][25];
SegmentData S[maxN<<2];

void Build(int now,int l,int r);
void Update(int now);
void PushDown(int now);
void Nega(int now);
void Plus(int now,int c);
void Modify(int now,int l,int r,int ql,int qr,int key);
void Renega(int now,int l,int r,int ql,int qr);
Data Query(int now,int l,int r,int ql,int qr);
Data operator + (Data A,Data B);
void Outp(int now,int l,int r);

int main(){
	for (int i=0;i<maxN;i++)
		for (int j=C[i][0]=1;j<=min(20,i);j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mod;
	scanf("%d%d",&n,&Q);
	for (int i=1;i<=n;i++) scanf("%d",&Seq[i]);
	Build(1,1,n);
	Outp(1,1,n);cout<<endl;

	while (Q--){
		char opt;int a,b,c;
		scanf(" %c%d%d%d",&opt,&a,&b,&c);
		if (opt=='I') Modify(1,1,n,a,b,(c%Mod+Mod)%Mod);
		if (opt=='R') Renega(1,1,n,a,b);
		if (opt=='Q') printf("%d\n",Query(1,1,n,a,b).f[c]);
		Outp(1,1,n);cout<<endl;
	}

	return 0;
}

void Build(int now,int l,int r){
	S[now].len=(r-l+1);
	if (l==r){
		S[now].D.f[1]=Seq[l];return;
	}
	int mid=(l+r)>>1;
	Build(lson,l,mid);Build(rson,mid+1,r);
	Update(now);return;
}

void Update(int now){
	S[now].D=S[lson].D+S[rson].D;
	return;
}

void PushDown(int now){
	if (S[now].ng){
		Nega(lson);Nega(rson);S[now].ng=0;
	}
	if (S[now].ad){
		Plus(lson,S[now].ad);Plus(rson,S[now].ad);S[now].ad=0;
	}
	return;
}
void Nega(int now){
	S[now].ng^=1;S[now].ad=(Mod-S[now].ad)%Mod;
	for (int i=1;i<=20;i+=2) S[now].D.f[i]=(Mod-S[now].D.f[i])%Mod;
	return;
}

void Plus(int now,int c){
	cout<<"Plus:"<<now<<" "<<c<<endl;
	c=(c%Mod+Mod)%Mod;
	S[now].ad=(S[now].ad+c)%Mod;
	int g[22]={0};S[now].D.f[0]=1;
	for (int i=1;i<=20;i++)
		for (int j=1,x=c;j<=i;j++,x=1ll*x*c%Mod)
			g[i]=(1ll*x*S[now].D.f[i-j]%Mod*C[S[now].len-(i-j)][j]%Mod+g[i])%Mod;
	for (int i=1;i<=20;i++) S[now].D.f[i]=g[i];
	return;
}

void Modify(int now,int l,int r,int ql,int qr,int key){
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
	Update(now);return;
}

void Renega(int now,int l,int r,int ql,int qr){
	if ((l==ql)&&(r==qr)){
		Nega(now);return;
	}
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) Renega(lson,l,mid,ql,qr);
	else if (ql>=mid+1) Renega(rson,mid+1,r,ql,qr);
	else{
		Renega(lson,l,mid,ql,mid);Renega(rson,mid+1,r,mid+1,qr);
	}
	Update(now);return;
}


Data Query(int now,int l,int r,int ql,int qr){
	if ((l==ql)&&(r==qr)) return S[now].D;
	PushDown(now);
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(lson,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rson,mid+1,r,ql,qr);
	else return Query(lson,l,mid,ql,mid)+Query(rson,mid+1,r,mid+1,qr);
}

Data operator + (Data A,Data B){
	Data rt;
	for (int i=1;i<=20;i++) rt.f[i]=(A.f[i]+B.f[i])%Mod;
	for (int i=1;i<=20;i++)
		for (int j=1;j<i;j++)
			rt.f[i]=(rt.f[i]+1ll*A.f[j]*B.f[i-j]%Mod)%Mod;
	return rt;
}

void Outp(int now,int l,int r){
	PushDown(now);
	cout<<now<<"["<<l<<","<<r<<"]"<<endl;
	for (int i=1;i<=20;i++) cout<<S[now].D.f[i]<<" ";cout<<endl;
	if (l==r) return;
	int mid=(l+r)>>1;
	Outp(lson,l,mid);Outp(rson,mid+1,r);
	return;
}
