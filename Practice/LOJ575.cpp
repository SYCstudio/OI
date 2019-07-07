#include<bits/stdc++.h>
using namespace std;

#define Inv(x) QPow(x,Mod-2)
const int maxN=101000*4;
const int Mod=998244353;

int Fc[maxN],Ifc[maxN];
char In[maxN];
int F[maxN],C[maxN],Ra[maxN],A[maxN],B[maxN];

int QPow(int x,int cnt);
void NTT(int *P,int N,int opt);
void Divide(int l,int r);
int main(){
    Fc[0]=Ifc[0]=1;for (int i=1;i<maxN;i++) Fc[i]=1ll*Fc[i-1]*i%Mod;
    Ifc[maxN-1]=Inv(Fc[maxN-1]);for (int i=maxN-2;i>=1;i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;

    scanf("%s",In+1);F[0]=1;int n=strlen(In+1);
    for (int i=1;i<=n;i++) C[i]=C[i-1]+(In[i]=='>');

    F[0]=1;
    for (int i=1;i<=n;i++)
	for (int j=0;j<i;j++)
	    if (In[j]!='>'){
		if ((C[i-1]-C[j])&1) F[i]=(F[i]-1ll*F[j]*Ifc[i-j]%Mod+Mod)%Mod;
		else F[i]=(F[i]+1ll*F[j]*Ifc[i-j]%Mod)%Mod;
	    }

    for (int i=0;i<=n;i++) cout<<F[i]<<" ";cout<<endl;

    cout<<1ll*F[n]*Fc[n]%Mod<<endl;

    memset(F,0,sizeof(F));F[0]=1;

    Divide(0,n);

    for (int i=0;i<=n;i++) cout<<F[i]<<" ";cout<<endl;

    printf("%d\n",(int)(1ll*F[n]*Fc[n]%Mod));return 0;
}
int QPow(int x,int cnt){
    int ret=1;
    while (cnt){
	if (cnt&1) ret=1ll*ret*x%Mod;
	x=1ll*x*x%Mod;cnt>>=1;
    }
    return ret;
}
void NTT(int *P,int N,int opt){
    int _N=1,l=-1;while (_N<N) _N<<=1,++l;
    for (int i=0;i<N;i++) Ra[i]=(Ra[i>>1]>>1)|((i&1)<<l);
    for (int i=0;i<N;i++) if (i<Ra[i]) swap(P[i],P[Ra[i]]);
    for (int i=1;i<N;i<<=1){
	int dw=QPow(3,(Mod-1)/(i<<1));
	if (opt==-1) dw=Inv(dw);
	for (int j=0;j<N;j+=i<<1)
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
void Divide(int l,int r){
    if (l==r) return;
    int mid=(l+r)>>1;Divide(l,mid);
    
    for (int i=l;i<=mid;i++){
	A[i-l]=F[i];if (C[i]&1) A[i]=(Mod-A[i])%Mod;
    }
    for (int i=0;i<=r-l+1;i++) B[i]=Ifc[i];
    int sz=mid-l+1+r-l+1,len=1;
    while (len<=sz) len<<=1;
    
    NTT(A,len,1);NTT(B,len,1);
    for (int i=0;i<len;i++) A[i]=1ll*A[i]*B[i]%Mod;
    NTT(A,len,-1);

    for (int i=mid+1;i<=r;i++){
	if (C[i-1]&1) F[i]=(F[i]-A[i-l]+Mod)%Mod;
	else F[i]=(F[i]+A[i-l])%Mod;
    }
    for (int i=0;i<len;i++) A[i]=B[i]=0;

    Divide(mid+1,r);return;
}
