#include<bits/stdc++.h>
using namespace std;

const int maxN=101000;
const int Mod=998244353;

class Data{
public:
    int l,r,id;
};

int n,Q,m,K;
vector<Data> Qk[maxN];
int E[maxN],Ans[maxN],Ful[maxN],Cnt[maxN],Dwn[maxN];
int Inv[maxN+maxN],Bl[maxN],mul=0;

bool qcmp(Data A,Data B);
void Add(int p);
void Del(int p);
int main(){
    Inv[0]=Inv[1]=1;for (int i=2;i<maxN+maxN;i++) Inv[i]=(Mod-1ll*(Mod/i)*Inv[Mod%i]%Mod+Mod)%Mod;
    scanf("%d%d%d",&n,&m,&Q);for (int i=1;i<=n;i++) scanf("%d",&E[i]),++Ful[E[i]];
    int mxk=0,Block=1010;
    for (int i=1;i<=Q;i++){
	int l,r,k;scanf("%d%d%d",&l,&r,&k);Qk[k].push_back((Data){l,r,i});mxk=max(mxk,k);
    }
    for (int i=1;i<=n;i++) Bl[i]=i/Block+1;
    int c=0;
    for (K=0;K<=mxk;K++)
	if (Qk[K].size()){
	    int l=1,r=0;
	    mul=1;Dwn[n]=1;for (int j=n-1;j>=1;j--) Dwn[j]=1ll*Dwn[j+1]*(1ll*m*K%Mod+n-j)%Mod;
	    sort(Qk[K].begin(),Qk[K].end(),qcmp);
	    int d=0;
	    for (int j=0,sz=Qk[K].size();j<sz;j++){
		int ql=Qk[K][j].l,qr=Qk[K][j].r;d+=abs(l-ql);d+=abs(r-qr);
		while (r<qr) Add(++r);
		while (l>ql) Add(--l);
		while (r>qr) Del(r--);
		while (l<ql) Del(l++);
		Ans[Qk[K][j].id]=1ll*mul*Dwn[qr-ql+1]%Mod;
	    }
	    for (int j=l;j<=r;j++) --Cnt[E[j]];
	}
    for (int i=1;i<=Q;i++) printf("%d\n",Ans[i]);return 0;
}
bool qcmp(Data A,Data B){
    if (Bl[A.l]==Bl[B.l]) return A.r<B.r;
    return A.l<B.l;
}
void Add(int p){
    mul=1ll*mul*(Ful[E[p]]+K-Cnt[E[p]])%Mod;
    ++Cnt[E[p]];
    return;
}
void Del(int p){
    --Cnt[E[p]];
    mul=1ll*mul*Inv[Ful[E[p]]+K-Cnt[E[p]]]%Mod;
    return;
}
