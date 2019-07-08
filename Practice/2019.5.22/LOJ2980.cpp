#include<bits/stdc++.h>
using namespace std;

class Mat
{
public:
	int M[4][4];
	Mat()
	{
		memset(M,0,sizeof(M));
		return;
	}
	Mat(int opt)
	{
		memset(M,0,sizeof(M));
		M[0][0]=M[1][1]=M[2][2]=M[3][3]=1;
		if (opt==0) M[1][0]=1;
		if (opt==1) M[2][1]=1;
		if (opt==2) M[0][2]=1;
		return;
	}
	Mat(int opt,int v)
	{
		memset(M,0,sizeof(M));
		M[0][0]=M[1][1]=M[2][2]=M[3][3]=1;
		if (opt==0) M[3][0]=v;
		if (opt==1) M[1][1]=v;
		if (opt==2) M[2][2]=0,M[3][2]=v;
		return;
	}
};

#define ls (x<<1)
#define rs (ls|1)
const int maxN=300000;
const int Mod=998244353;

int n,Q;
Mat S[maxN<<2],T[maxN<<2];

Mat operator + (Mat A,Mat B);
Mat operator * (Mat A,Mat B);
void Build(int x,int l,int r);
void PushDown(int x);
void Modify(int x,int l,int r,int ql,int qr,Mat M);
Mat Query(int x,int l,int r,int ql,int qr);
int main()
{
	scanf("%d",&n);
	Build(1,1,n);
	scanf("%d",&Q);
	while (Q--) {
		int opt,l,r,v;
		scanf("%d%d%d",&opt,&l,&r);
		if (opt<=3) Modify(1,1,n,l,r,Mat(opt-1));
		else if (opt<=6) {
			scanf("%d",&v);
			Modify(1,1,n,l,r,Mat(opt-4,v));
		} else {
			Mat R=Query(1,1,n,l,r);
			printf("%d %d %d\n",R.M[0][0],R.M[0][1],R.M[0][2]);
		}
	}
	return 0;
}
Mat operator + (Mat A,Mat B)
{
	for (int i=0; i<4; i++)
		for (int j=0; j<4; j++) {
			A.M[i][j]+=B.M[i][j];
			if (A.M[i][j]>=Mod) A.M[i][j]-=Mod;
		}
	return A;
}
Mat operator * (Mat A,Mat B)
{
	Mat C;
	for (int i=0; i<4; i++)
		for (int j=0; j<4; j++) {
			unsigned long long res=0;
			for (int k=0; k<4; k++) res+=1ull*A.M[i][k]*B.M[k][j];
			C.M[i][j]=res%Mod;
		}
	return C;
}
void Build(int x,int l,int r)
{
	T[x]=Mat(5);
	if (l==r) {
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		S[x].M[0][0]=a;
		S[x].M[0][1]=b;
		S[x].M[0][2]=c;
		S[x].M[0][3]=1;
		return;
	}
	int mid=(l+r)>>1;
	Build(ls,l,mid);
	Build(rs,mid+1,r);
	S[x]=S[ls]+S[rs];
	return;
}
void Modify(int x,int l,int r,int ql,int qr,Mat M)
{
	if (l==ql&&r==qr) {
		S[x]=S[x]*M;
		T[x]=T[x]*M;
		return;
	}
	S[ls]=S[ls]*T[x];
	T[ls]=T[ls]*T[x];
	S[rs]=S[rs]*T[x];
	T[rs]=T[rs]*T[x];
	T[x]=Mat(5);
	int mid=(l+r)>>1;
	if (qr<=mid) Modify(ls,l,mid,ql,qr,M);
	else if (ql>=mid+1) Modify(rs,mid+1,r,ql,qr,M);
	else Modify(ls,l,mid,ql,mid,M),Modify(rs,mid+1,r,mid+1,qr,M);
	S[x]=S[ls]+S[rs];
	return;
}
Mat Query(int x,int l,int r,int ql,int qr)
{
	if (l==ql&&r==qr) return S[x];
	S[ls]=S[ls]*T[x];
	T[ls]=T[ls]*T[x];
	S[rs]=S[rs]*T[x];
	T[rs]=T[rs]*T[x];
	T[x]=Mat(5);
	int mid=(l+r)>>1;
	if (qr<=mid) return Query(ls,l,mid,ql,qr);
	else if (ql>=mid+1) return Query(rs,mid+1,r,ql,qr);
	else return Query(ls,l,mid,ql,mid)+Query(rs,mid+1,r,mid+1,qr);
}
