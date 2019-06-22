#include<bits/stdc++.h>
using namespace std;

#define Inv(x) QPow(x,Mod-2)
const int maxN=101000<<4;
const int Mod=998244353;
const int G=3;

int m,R,FR;
int Fc[maxN],Ifc[maxN];
int F[maxN],Ra[maxN],A[maxN];
int M1[maxN],M2[maxN];

void Divide(int l,int r);
void NTT(int *P,int N,int opt);
int QPow(int x,int cnt);
int main(){
    Fc[0]=Ifc[0]=1;for (int i=1;i<maxN;i++) Fc[i]=1ll*Fc[i-1]*i%Mod;
    Ifc[maxN-1]=Inv(Fc[maxN-1]);for (int i=maxN-2;i>=1;i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;

    scanf("%d%d",&m,&R);for (int i=0;i<=m;i++) scanf("%d",&A[i]);
    FR=1ll*R*Inv(1+Mod-R)%Mod;

    F[0]=Inv(1+Mod-R);
    for (int i=1;i<=m;i++){
	for (int k=0;k<i;k++) F[i]=(F[i]+1ll*F[k]*Ifc[i-k]%Mod)%Mod;
	F[i]=1ll*F[i]*FR%Mod;
    }
    for (int i=0;i<=m;i++) cout<<F[i]<<" ";cout<<endl;
    int ssm=0;
    for (int i=0;i<=m;i++) ssm=(ssm+1ll*A[i]*F[i]%Mod*Fc[i]%Mod)%Mod;
    cout<<"ssm:"<<ssm<<endl;
    memset(F,0,sizeof(F));

    F[0]=1ll*Inv(1+Mod-R)*Inv(FR)%Mod;Divide(0,m);

    for (int i=0;i<=m;i++) cout<<F[i]<<" ";cout<<endl;

    int Ans=0;
    for (int i=0;i<=m;i++) Ans=(Ans+1ll*A[i]*F[i]%Mod*Fc[i]%Mod)%Mod;
    printf("%d\n",Ans);return 0;
}
int QPow(int x,int cnt){
    int ret=1;
    while (cnt){
	if (cnt&1) ret=1ll*ret*x%Mod;
	x=1ll*x*x%Mod;cnt>>=1;
    }
    return ret;
}
void Divide(int l,int r){
    if (l==r){
	F[l]=1ll*F[l]*FR%Mod;
	return;
    }
    int mid=(l+r)>>1;Divide(l,mid);
    int N=1,lsz=mid-l+1;while (N<=(r-l+1)*2) N<<=1;
    for (int i=0;i<lsz;i++) M1[i]=F[l+i];
    for (int i=0;i<=r-l+1;i++) M2[i]=Ifc[i];
    cout<<"Divide:"<<l<<" "<<mid<<" "<<r<<endl;
    for (int i=0;i<N;i++) cout<<M1[i]<<" ";cout<<endl;
    for (int i=0;i<N;i++) cout<<M2[i]<<" ";cout<<endl;
    NTT(M1,N,1);NTT(M2,N,1);
    for (int i=0;i<N;i++) M1[i]=1ll*M1[i]*M2[i]%Mod;
    NTT(M1,N,-1);
    for (int i=0;i<N;i++) cout<<M1[i]<<" ";cout<<endl<<endl;
    for (int i=lsz;i<r-l+1;i++) F[l+i]=(F[l+i]+M1[i])%Mod;
    for (int i=0;i<N;i++) M1[i]=M2[i]=0;
    Divide(mid+1,r);return;
}
void NTT(int *P,int N,int opt){
    int _N=1,l=-1;while (_N<N) _N<<=1,++l;
    for (int i=0;i<N;i++) Ra[i]=(Ra[i>>1]>>1)|((i&1)<<l);
    for (int i=0;i<N;i++) if (i<Ra[i]) swap(P[i],P[Ra[i]]);
    for (int i=1;i<N;i<<=1){
	int dw=QPow(G,(Mod-1)/(i<<1));
	if (opt==-1) dw=Inv(dw);
	for (int j=0;j<N;j+=(1<<i))
	    for (int k=0,w=1;k<i;k++,w=1ll*w*dw%Mod){
		int X=P[j+k],Y=1ll*P[j+k+i]*w%Mod;
		P[j+k]=(X+Y)%Mod;P[j+k+i]=(X-Y+Mod)%Mod;
	    }
    }
    if (opt==-1){
	int inv=Inv(N);for (int i=0;i<N;i++) P[i]=1ll*P[i]*inv%Mod;
    }
    return;
}
