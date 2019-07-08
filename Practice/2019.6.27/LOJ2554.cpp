#include<bits/stdc++.h>
using namespace std;

#define Inv(x) QPow(x,Mod-2)
const int maxN=50500*4;
const int Mod=998244353;

int n;
int Fc[maxN],Ifc[maxN],Ra[maxN];
int F[maxN],A[maxN],B[maxN];
int L[maxN];
int St[maxN],top=0;

int QPow(int x,int cnt);
void NTT(int *P,int N,int opt);
void Divide(int l,int r);
int main()
{
	F[0]=1;
	F[1]=2;
	Divide(2,50000);
	int Case;
	scanf("%d%d",&Case,&n);
	while (Case--) {
		for (int i=1; i<=n; i++) scanf("%d",&L[i]),L[i]=i-L[i]+1;
		if (L[n]!=1) {
			puts("0");
			continue;
		}
		top=0;
		int Ans=1;
		bool flag=1;
		for (int i=1; i<=n; i++) {
			int son=0;
			while (top) {
				if (L[i]<=St[top]&&L[i]>L[St[top]]) {
					puts("0");
					flag=0;
					break;
				}
				if (L[St[top]]>=L[i]) ++son,--top;
				else break;
			}
			if (flag==0) break;
			Ans=1ll*Ans*F[son]%Mod;
			St[++top]=i;
		}
		if (flag) printf("%d\n",Ans);
	}
	return 0;
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
int sumlen=0;
void NTT(int *P,int N,int opt)
{
	sumlen+=N;
	int _N=1,l=-1;
	while (_N<N) _N<<=1,++l;
	for (int i=0; i<N; i++) Ra[i]=(Ra[i>>1]>>1)|((i&1)<<l);
	for (int i=0; i<N; i++) if (i<Ra[i]) swap(P[i],P[Ra[i]]);
	for (int i=1; i<N; i<<=1) {
		int dw=QPow(3,(Mod-1)/(i<<1));
		if (opt==-1) dw=Inv(dw);
		for (int j=0; j<N; j+=(i<<1))
			for (int k=0,w=1; k<i; k++,w=1ll*w*dw%Mod) {
				int X=P[j+k],Y=1ll*P[j+k+i]*w%Mod;
				P[j+k]=(X+Y)%Mod;
				P[j+k+i]=(X-Y+Mod)%Mod;
			}
	}
	if (opt==-1) {
		int inv=Inv(N);
		for (int i=0; i<N; i++) P[i]=1ll*P[i]*inv%Mod;
	}
	return;
}
void Divide(int l,int r)
{
	//cout<<"D:"<<l<<" "<<r<<endl;
	if (l==r) {
		if (l==0) F[0]=1;
		else if (l==1) F[1]=2;
		else F[l]=(F[l]+1ll*F[l-1]*(l-1)%Mod)%Mod;
		return;
	}
	int mid=(l+r)>>1;
	Divide(l,mid);
	int N=1;
	while (N<=r-l+1) N<<=1;
	N<<=1;

	for (int i=l; i<=mid; i++) A[i-l]=1ll*F[i]*(i-1)%Mod,B[i-l]=F[i];

	//for (int i=0;i<N;i++) cout<<A[i]<<" ";cout<<endl;
	//for (int i=0;i<N;i++) cout<<B[i]<<" ";cout<<endl;

	NTT(A,N,1);
	NTT(B,N,1);
	for (int i=0; i<N; i++) A[i]=1ll*A[i]*B[i]%Mod;
	NTT(A,N,-1);

	//for (int i=0;i<N;i++) cout<<A[i]<<" ";cout<<endl;

	for (int i=max(l+l,mid+1); i<=r; i++) F[i]=(F[i]+A[i-l-l])%Mod;

	for (int i=0; i<N; i++) A[i]=B[i]=0;

	if (l>2) {
		int up=min(l-1,r-l);
		N=1;
		while (N<=up-1+mid-l+1) N<<=1;
		for (int i=2; i<=up; i++) A[i-2]=F[i];
		for (int i=l; i<=mid; i++) B[i-l]=F[i];
		NTT(A,N,1);
		NTT(B,N,1);
		for (int i=0; i<N; i++) A[i]=1ll*A[i]*B[i]%Mod;
		NTT(A,N,-1);
		for (int i=max(l+2,mid+1); i<=r; i++) F[i]=(F[i]+1ll*A[i-l-2]*(i-2)%Mod)%Mod;
		for (int i=0; i<N; i++) A[i]=B[i]=0;
	}
	Divide(mid+1,r);
	return;
}
