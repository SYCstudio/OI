#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;

#define ll long long
#define mem(Arr,x) memset(Arr,x,sizeof(Arr))
#define lson (now<<1)
#define rson (lson|1)

const int maxN=70000;
const int Mod=998244353;
const int G=3;
const int inf=2147483647;

int n,m;
int X[maxN],Rader[maxN*5],Ans[maxN];
vector<int> Input,I[maxN*4],I1,I2,M1;

int QPow(int x,int cnt);
void NTT(vector<int> &P,int N,int opt);
void Mul(vector<int> &A,vector<int> B);
void PolyInv(vector<int> A,vector<int> &B,int len);
void PolyMod(vector<int> A,vector<int> B,vector<int> &R);
void GetMul(int now,int l,int r);
void Divide(int now,int l,int r,vector<int> F);

int main(){
	//freopen("in","r",stdin);freopen("out","w",stdout);
	scanf("%d%d",&n,&m);Input.resize(n+1);
	for (int i=0;i<=n;i++) scanf("%d",&Input[i]);
	for (int i=1;i<=m;i++) scanf("%d",&X[i]);

	GetMul(1,1,m);
	//for (int i=0;i<I[1].size();i++) cout<<I[1][i]<<" ";cout<<endl;
	Divide(1,1,m,Input);

	for (int i=1;i<=m;i++) printf("%d\n",Ans[i]);
	return 0;
}

int QPow(int x,int cnt){
	int ret=1;
	while (cnt){
		if (cnt&1) ret=1ll*ret*x%Mod;
		x=1ll*x*x%Mod;cnt>>=1;
	}
	return ret;
}

void NTT(vector<int> &P,int N,int opt){
	int L=log2(N);
	for (int i=0;i<N;i++) Rader[i]=(Rader[i>>1]>>1)|((i&1)<<(L-1));
	for (int i=0;i<N;i++) if (i<Rader[i]) swap(P[i],P[Rader[i]]);
	for (int i=1;i<N;i<<=1){
		int dw=QPow(G,(Mod-1)/(i<<1));if (opt==-1) dw=QPow(dw,Mod-2);
		for (int j=0;j<N;j+=(i<<1))
			for (int k=0,w=1;k<i;k++,w=1ll*w*dw%Mod){
				int X=P[j+k],Y=1ll*P[j+k+i]*w%Mod;
				P[j+k]=(X+Y)%Mod;P[j+k+i]=(X-Y+Mod)%Mod;
			}
	}
	if (opt==-1){
		int inv=QPow(N,Mod-2);
		for (int i=0;i<N;i++) P[i]=1ll*P[i]*inv%Mod;
	}
	return;
}

void Mul(vector<int> &A,vector<int> B){
	/*
	cout<<"Mul:"<<endl;
	for (int i=0;i<A.size();i++) cout<<A[i]<<" ";cout<<endl;
	for (int i=0;i<B.size();i++) cout<<B[i]<<" ";cout<<endl;
	//*/
	int l1=A.size()-1,l2=B.size()-1;
	int N=1;while (N<=l1+l2) N<<=1;
	A.resize(N);B.resize(N);
	NTT(A,N,1);NTT(B,N,1);
	for (int i=0;i<N;i++) A[i]=1ll*A[i]*B[i]%Mod;
	NTT(A,N,-1);
	A.resize(l1+l2+1);
	return;
}

void PolyInv(vector<int> A,vector<int> &B,int len){
	A.resize(len);
	if (len==1){
		B[0]=QPow(A[0],Mod-2);return;
	}
	PolyInv(A,B,len>>1);
	I1.resize(len<<1);I2.resize(len<<1);
	for (int i=0;i<len;i++) I1[i]=A[i],I2[i]=B[i];
	NTT(I1,len<<1,1);NTT(I2,len<<1,1);
	for (int i=0;i<len<<1;i++) I1[i]=1ll*I1[i]*I2[i]%Mod*I2[i]%Mod;
	NTT(I1,len<<1,-1);
	for (int i=0;i<len;i++) B[i]=(2ll*B[i]-I1[i]+Mod)%Mod;
	I1.resize(0);I2.resize(0);
	//cout<<"PolyInv:"<<len<<endl;
	//for (int i=0;i<len;i++) cout<<B[i]<<" ";cout<<endl;
	return;
}

void PolyMod(vector<int> A,vector<int> B,vector<int> &R){
	//cout<<"PolyMode:"<<endl;
	//cout<<"A:";for (int i=0;i<A.size();i++) cout<<A[i]<<" ";cout<<endl;
	//cout<<"B:";for (int i=0;i<B.size();i++) cout<<B[i]<<" ";cout<<endl;
	int n=A.size()-1,m=B.size()-1,p=n-m;
	for (int i=0;i<n-i;i++) swap(A[i],A[n-i]);
	for (int i=0;i<m-i;i++) swap(B[i],B[m-i]);
	
	int N=1;while (N<=m) N<<=1;
	B.resize(N);M1.resize(N);
	PolyInv(B,M1,N);B.resize(m+1);M1.resize(p+1);

	//cout<<"B:";for (int i=0;i<B.size();i++) cout<<B[i]<<" ";cout<<endl;
	//cout<<"Inv:";for (int i=0;i<M1.size();i++) cout<<M1[i]<<" ";cout<<endl;
	
	Mul(M1,A);//cout<<"A "<<p<<" "<<M1.size()<<endl;M1.resize(p+1);cout<<"A"<<endl;
	for (int i=0;i<p-i;i++) swap(M1[i],M1[p-i]);
	for (int i=0;i<n-i;i++) swap(A[i],A[n-i]);
	for (int i=0;i<m-i;i++) swap(B[i],B[m-i]);

	M1.resize(p+1);
	//cout<<"P:";for (int i=0;i<M1.size();i++) cout<<M1[i]<<" ";cout<<endl;
	Mul(M1,B);

	R.resize(m);
	for (int i=0;i<m;i++) R[i]=(A[i]-M1[i]+Mod)%Mod;
	//cout<<"R:";for (int i=0;i<R.size();i++) cout<<R[i]<<" ";cout<<endl;
	M1.resize(0);
	return;
}

void GetMul(int now,int l,int r){
	//cout<<"GetMul:"<<now<<" "<<l<<" "<<r<<endl;
	if (l==r){
		I[now].resize(2);I[now][0]=(Mod-X[l])%Mod;I[now][1]=1;
		return;
	}
	int mid=(l+r)>>1;
	GetMul(lson,l,mid);GetMul(rson,mid+1,r);
	I[now]=I[lson];Mul(I[now],I[rson]);
	return;
}

void Divide(int now,int l,int r,vector<int> F){
	//cout<<"Divide:"<<now<<" "<<l<<" "<<r<<endl;
	int sz=(r-l+1);
	//for (int i=0;i<F.size();i++) cout<<F[i]<<" ";cout<<endl;
	//for (int i=0;i<I[now].size();i++) cout<<I[now][i]<<" ";cout<<endl;
	if (F.size()-1>=sz) PolyMod(F,I[now],F);
	F.resize(sz+1);
	//for (int i=0;i<F.size();i++) cout<<F[i]<<" ";cout<<endl;
	if (l==r){
		Ans[l]=F[0];return;
	}
	int mid=(l+r)>>1;
	Divide(lson,l,mid,F);Divide(rson,mid+1,r,F);
	return;
}
